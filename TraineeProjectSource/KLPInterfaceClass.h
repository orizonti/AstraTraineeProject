/* Класс главного окна программы
 */

#ifndef MAINDLG_H
#define MAINDLG_H





#include <mppd_wrap.h>
#include <mppd_cmd_definitions.h>
#include <mppd_definitions.h>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <queue>


#include "EngineInterfaceClass.h"
#include "CameraInterfaceClass.h"
#include "DebugStream.h"
#include <memory>

class ResetCommandCommutator
{
public:

    ResetCommandCommutator()
    {
              FC_HEADER.DeviceID =  0x78;
              FC_HEADER.MessageId = 0x01;
              FC_HEADER.Length = 8 + 1;
    }
    AsmHeader FC_HEADER;
    quint8 ResetRegim = 0;

friend void operator<<(QDataStream& out, ResetCommandCommutator& SendPocket);
};

class StatusRequestCommutator
{
public:

    StatusRequestCommutator()
    {
              FC_HEADER.DeviceID =  0x78;
              FC_HEADER.MessageId = 0x04;
              FC_HEADER.Length = 8 + 5;
    }
    AsmHeader FC_HEADER;
    quint32 ReqFrequency = 1000;
    quint8 Param = 0;

friend void operator<<(QDataStream& out, StatusRequestCommutator& SendPocket);
};


class Regim_CommutatorCommand
{
public:

	Regim_CommutatorCommand()
	{

		FC_HEADER.DeviceID = 0x78;
		FC_HEADER.MessageId = 0x06;
		FC_HEADER.Length = 8 + 8;
	}

	AsmHeader FC_HEADER;
	quint8 Regim = 0;
	quint8 TTLSignal = 0;

	quint16 ChannelsSupply = 0xFFFF;
	quint32 Reserv = 0;


	void TurnOnOffSupply(bool OnOff)
	{
		if (OnOff)
		ChannelsSupply = 0xFFFF;

		if (!OnOff)
			ChannelsSupply = 0x00;

	}




	friend void operator<<(QDataStream& out, Regim_CommutatorCommand& SendPocket);
};

class StatusCommutatorStruct
{
public:

	StatusCommutatorStruct()
	{
		FC_HEADER.DeviceID = 0x78;
		FC_HEADER.MessageId = 0x05;
	}

   AsmHeader FC_HEADER;
    quint8 StateController;
    quint8 TempSensorState;
    qint8 Temeperature1;
    qint8 Temeperature2;
    qint8 Temeperature3;
    qint8 Temeperature4;
    qint8 Temeperature5;
    qint8 Temeperature7;
    qint8 Temeperature8;
    qint8 Temeperature9;

    quint8 SignalTTLIn;
    quint8 SignalTTLOut;

    quint16 PowerSupplyChannels;
    quint16 Reserv;

    quint8  WeTemp1;
    quint16 WePresure1;
    quint8  WeHumidity1;

    quint8  WeTemp2;
    quint16 WePresure2;
    quint8  WeHumidity2;

    quint32 FC1Params;
    quint32 FC2Params;

    quint32 ABCDVersion;	
	friend void operator>>(QDataStream& in, StatusCommutatorStruct& RecievePocket);


}; 



class KLPInterfaceClass
{

public:
KLPInterfaceClass();
~KLPInterfaceClass();

	typeblocksenum TypeBlock = typeblocksenum::KLPInterfaeBlock;
uint8_t WriteCommandData(QByteArray CommandData,OutFcChannelFlags FCChannel);
uint8_t WriteCommandDataEx(QByteArray CommandData,OutFcChannelFlags FCChannel);


void SetSateCommutator(Regim_CommutatorCommand State);
void ResetCommutator();
void StatusRequest();

StatusCommutatorStruct StateCommutator;

void InitialaizeInterface();

// TO DELETE
void DeinitializeInterface();
void CardSoftReset();
//======================

void CreateVirtualChannel();
static InterruptData LastInterrupt;
int current_write_buffer = 0;
static void PerformInterruptionFunction();
static void RecieveInterruptionFunction(mppd_wrap* KLPCardHandler);

static std::mutex interruptions_lock;
static std::queue<InterruptData> available_interruptions;
static void append_new_interruption(InterruptData interrupt);
static InterruptData get_new_interruption();

static mppd_wrap* CardModule;

static stateblocksenum StateBlock;
static	std::shared_ptr<CameraInterfaceClass> CameraInterface;
static	std::shared_ptr<EngineInterfaceClass> EngineInterface1;
static	std::shared_ptr<EngineInterfaceClass> EngineInterface2;
static	std::shared_ptr<EngineInterfaceClass> EngineInterface3;
static  KLPInterfaceClass* KLPInterface;

static	void *ReadDataBuffer1;
static	void *ReadDataBuffer2;
static	void *WriteDataBuffer1;
static	void *WriteDataBuffer2;


};


#endif // MAINDLG_H
