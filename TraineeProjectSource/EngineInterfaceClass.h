#pragma once
#include "DataEngineStructure.h"
#include "PassTwoCoordClass.h"
#include "FC_STRUCTS.h"
#include <mppd_wrap.h>
#include <mppd_cmd_definitions.h>
#include <mppd_definitions.h>

class KLPInterfaceClass;

struct EngineHeader
{
    quint8 MessageID;
    quint8 DeviceID;
    quint8 LenghtData;
    quint8 Reserv = 0;
};

class ResetCommandEngine
{
public:

    ResetCommandEngine()
    {

        HEADER.DeviceID = 0x0A;
        HEADER.MessageID = 0x01;
        HEADER.LenghtData = 1+1;

              FC_HEADER.DeviceID =  0x0A;
              FC_HEADER.MessageId = 0x01;
              FC_HEADER.Length = 8 + 4 + 1 + 1;
    }
    AsmHeader FC_HEADER;
    EngineHeader HEADER;
    quint8 ResetRegim;

friend void operator<<(QDataStream& out, ResetCommandEngine& SendPocket);
};

class Status_EngineStruct
{
public:

	AsmHeader FC_HEADER;

	quint8 RegimFlags = 0;
	quint8 StateFlags = 0;

	quint8 TempSensor1 = 0;
	quint8 TempSensor2 = 0;

	float PosAngleX = 0;
	float PosAngleY = 0;

	qint16 PosADC_X = 0;
	qint16 PosADC_Y = 0;

	qint16 ValueToDAC_X = 0;
	qint16 ValueToDAC_Y = 0;

	qint16 EdgeMinX = 0;
	qint16 EdgeMaxX = 0;

	qint16 EdgeMinY = 0;
	qint16 EdgeMaxY = 0;

	qint32 ABCDVersion;
	friend void operator>>(QDataStream& in, Status_EngineStruct& SendPocket);
	Status_EngineStruct()
	{

		FC_HEADER.DeviceID = 0x0A;
		FC_HEADER.MessageId = 0x05;
	};
};
class ControlEngineCommand
{
public:

	ControlEngineCommand()
	{

		FC_HEADER.DeviceID = 0x0A;
		FC_HEADER.MessageId = 0xB0;
		FC_HEADER.Length = 24;
	}

	AsmHeader FC_HEADER;

	quint16 Pos_X_DAC = 0;
	quint16 Pos_Y_DAC = 0;

	float Pos_X_Angle = 0;
	float Pos_Y_Angle = 0;

	quint8 ControlRegim = 0;

	void SetPosAngle(float X_Rad, float Y_Rad);
	friend void operator<<(QDataStream& out, ControlEngineCommand& SendCommand);
};



class EngineInterfaceClass : public PassTwoCoordClass
{
public:
	EngineInterfaceClass(KLPInterfaceClass* KLP, quint32 MessageID, quint32 DeviceID);
	~EngineInterfaceClass();


	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	int count = 0;
	bool VerticalAxisOn = true;
	bool HorizontalAxisOn = true;
	bool FlagChunkCommandSend = false;

	void SetCoord(QPair<double, double> Coord);
	void SetCoordAbs(QPair<double,double> CoordAbs);
	void SetToNull();
	void ResetEngine();
	QPair<double,double> GetCoord();


	int CommandDelayMks = 0;
	QPair<double, double> ControlCoord;
private:
	static KLPInterfaceClass* KLPInterface;
public:
	void RecieveEngineStatus(QDataStream& DataEngine);

	ControlEngineCommand EngineState;
	Status_EngineStruct  Status_Engine;
	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);

	static QByteArray CommonBuffer;
	static void PushCommandToChunk(QByteArray Command);
    static OutFcChannelFlags EngineChannelNumber;

};
