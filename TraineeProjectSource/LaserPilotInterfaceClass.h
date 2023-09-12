#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "CommonLaserInterfaceClass.h"
#include "PilotLaserWindow.h"
#include <QAbstractSocket>
#include <QTcpSocket>
class COMMAND_HEADER
{
public:
    quint16 COMMAND_CODE = 0;
     qint16 EXECUTION_CODE = 0;
    quint32 DATA_SIZE = -1;

friend void operator>>(QDataStream& in_stream, COMMAND_HEADER& Head) {in_stream >> Head.COMMAND_CODE; 
                                                                      in_stream >> Head.EXECUTION_CODE;
                                                                      in_stream >> Head.DATA_SIZE;};
};
#define CODE_ACCESS_LEVEL 2080

#define CODE_LASER_DATA 2001
#define CODE_CHILLER_DATA 2031

#define CODE_POWERSUPPLY 2500 //quint16
#define CODE_SET_CURRENT 2501 //quint16
#define CODE_SET_POWER 2502 //quint32
#define CODE_EMISSION 2503 //quint16
#define CODE_GUIDE_LASER 2504 //StructureA
#define CODE_RESET 2506 //None
#define CODE_RESET_CRITICAL_ERROR 2507 //String
#define CODE_ANALOG_CTRL 2508 //quint16
#define CODE_MODULATION_CTRL 2509 //quint16
#define CODE_SET_RISETIME 2510 //quint16
#define CODE_SET_FALLTIME 2511 //quint16

class GET_PARAM_COMMAND
{
public:
    GET_PARAM_COMMAND(quint16 PARAM_CODE) { HEADER.COMMAND_CODE = PARAM_CODE; HEADER.DATA_SIZE = 0;};

    COMMAND_HEADER HEADER;
    quint16 CRC;
};
class RESET_COMMAND
{
public:
    RESET_COMMAND() { this->HEADER.COMMAND_CODE = CODE_RESET; this->HEADER.DATA_SIZE = 0; }
    COMMAND_HEADER HEADER;
    quint16 CRC;
};
class ANALOG_CTRL_COMMAND
{
public:
    ANALOG_CTRL_COMMAND() { this->HEADER.COMMAND_CODE = CODE_ANALOG_CTRL; this->HEADER.DATA_SIZE = 2; }
    COMMAND_HEADER HEADER;
    quint16 OnOff;
    quint16 CRC;
};
class EMISSION_TURN_COMMAND
{
public:
    EMISSION_TURN_COMMAND() { this->HEADER.COMMAND_CODE = CODE_EMISSION; this->HEADER.DATA_SIZE = 2; }
    COMMAND_HEADER HEADER;
    quint16 OnOff;
    quint16 CRC;
};



struct ACCESS_LEVEL_COMMAND
{
    ACCESS_LEVEL_COMMAND()
    {
        HEADER.COMMAND_CODE = 2080;
        HEADER.DATA_SIZE = 14;
    }

    COMMAND_HEADER HEADER;
    quint16 Version = 1;
    quint16 AccessLevel = 1; //Operator 1 //Enginer 2 //Supervisor 100
    quint8  Passwd[10] = {0};
    quint16 CRC;
};

class GUID_COMMAND_STRUCT
{
public:
    GUID_COMMAND_STRUCT()
    {
        this->HEADER.COMMAND_CODE = 2504; // 0x9C 0x80
        this->HEADER.DATA_SIZE = 4;
    }

    COMMAND_HEADER HEADER;
    quint16 NUMBER_CHANNEL;
    quint16 ON_OFF; //0 - off 1 - on
    quint16 CRC;
};


struct quint128
{
  quint64 FirstBytes;
  quint64 SecondBytes;
  friend void operator>>(QDataStream& Stream, quint128& Value) { Stream >> Value.FirstBytes; Stream >> Value.SecondBytes;};
  friend void operator<<(QDataStream& Stream, quint128& Value) { Stream << Value.FirstBytes; Stream << Value.SecondBytes;};
};
struct LASER_PARAM_STRUCT
{
    public:
    quint16  Version;
	quint16  SetCurrent;
	quint32  SetPower;
	quint32  OutputPower;
	quint16  TempMean;
	quint16  TempMin;
	quint16  TempMax;
	quint8   ModuleMinTemp;
	quint8   ModuleMaxTemp;
	quint16  WaterFloat;
	quint32  Status1;
	quint32  Status2;
	quint32  Alarms1;
	quint32  Alarams2;
	quint32  Warnings1;
	quint32  Warnings2;
	quint128 ModulesUnconnected;
	quint128 ModulesDisabled;
	quint128 ModulesReserved;
	quint128 ModulesFatalDisabled;
	quint128 ModulesError;
	quint128 ModulesInterlock;
	quint32  HardwiringInputs;
	quint32  HardwiringOutput;
	quint16  RiseTime;
	quint16  Fall_Time;
	quint16  ProgramNumber;
	quint16  ProgramEndCode;
	quint16  ProgramErrorLine;
	quint16  VoltControlValue;
	quint32  ePC_Status;
};

struct ChillerData 
{
	quint16 Version;
	quint32 Warnings;
	quint32 Alarms;
	quint32 Alarms2;
	quint16 LaserWaterTemp;
	quint16 DIWaterTemp;
	quint16 DIWaterPres;
	quint16 DIWaterCond;
	quint16 LaserWaterPres;
	quint16 ScannerWaterPres;
	quint16 ScannerWaterTemp;
	quint16 HouseInletWaterTemp;
	quint16 HouseInletWaterPres;
	quint16 HouseOutletWaterTemp;
	quint16 HouseOutletWaterPres;
};

class LaserPilotInterfaceClass : public CommonLaserInterfaceClass
{
	Q_OBJECT
public:
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;

	LaserPilotInterfaceClass(QString Address, quint16 Port);
	~LaserPilotInterfaceClass();

	PilotLaserWindow* Window;
	void ConnectToLaserTCP(QString Address, quint16 Port);
	DataLaserStruct GetState();

    QTcpSocket *SocketGuidLaser = 0;
	QString IPLaser;
private:
	void SendRequestToUpControlStatus();
	void SendRequestGetLaserParam();
	void SendRequestGetChillerParam();

    quint16 GetCRC(unsigned char * data, int dataSize);
    COMMAND_HEADER HEADER_DATA;

	public slots:
	    void TurnLaserBeamOnOff(bool OnOff);
		void slotReadyRead   (                            );
		void slotError       (QAbstractSocket::SocketError);
		void slotConnected   (        );

};



