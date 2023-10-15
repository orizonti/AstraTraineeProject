#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "CommonLaserInterfaceClass.h"
#include "PilotLaserWindow.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include <tuple>

//status1
#define LASER_EMISSION_SLOW_ON     0x00000001
#define LASER_GUID_ON              0x00000004
#define LASER_LASER_READY_ON       0x00000008
#define LASER_ANALOG_ON            0x00000040
#define LASER_EMISSION_ENABLED_ON  0x00000080
#define LASER_CHILLER_READY_ON     0x00000400
#define LASER_MAIN_POWER_ON        0x00001000
#define LASER_HAS_ERROR_ON         0x00002000
#define LASER_ROBOT_SWITCH_ON      0x00200000
#define LASER_EMISSION_SIGNAL      0x00800000
#define LASER_SHUTDOWN_STATE       0x10000000
#define LASER_STANDBY_STATE        0x40000000

//enum LASER_FLAGS
//{
//FLAG_EMISSION_SLOW_ON = LASER_EMISSION_SLOW_ON,    
//FLAG_GUID_ON = LASER_GUID_ON,
//FLAG_LASER_READY_ON = LASER_LASER_READY_ON,
//FLAG_ANALOG_ON = LASER_ANALOG_ON,
//FLAG_EMISSION_ENABLED_ON = LASER_EMISSION_ENABLED_ON,
//FLAG_CHILLER_READY_ON = LASER_CHILLER_READY_ON,
//FLAG_MAIN_POWER_ON = LASER_MAIN_POWER_ON,
//FLAG_HAS_ERROR_ON = LASER_HAS_ERROR_ON,
//FLAG_ROBOT_SWITCH_ON = LASER_ROBOT_SWITCH_ON,
//FLAG_EMISSION_SIGNAL = LASER_EMISSION_SIGNAL,
//FLAG_SHUTDOWN_STATE = LASER_SHUTDOWN_STATE,
//FLAG_STANDBY_STATE = LASER_STANDBY_STATE
//};
quint16 GetCRC(unsigned char * data, int dataSize);

class COMMAND_REQUEST
{
public:
    quint16 COMMAND_CODE = 0;
     qint16 EXECUTION_CODE = 0;
    quint32 DATA_SIZE = -1;

void LoadData(QByteArray& Array);
static std::tuple<quint16,quint16> GetHeader(QByteArray array);
static int LaserMessageCount;

friend void operator>>(QDataStream& in_stream, COMMAND_REQUEST& Head) {in_stream >> Head.COMMAND_CODE; 
                                                                       in_stream >> Head.EXECUTION_CODE;
                                                                       in_stream >> Head.DATA_SIZE;
                                                                     };
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

class GET_PARAM_COMMAND : public COMMAND_REQUEST
{
public:
    GET_PARAM_COMMAND(quint16 PARAM_CODE) { COMMAND_CODE = PARAM_CODE; DATA_SIZE = 0;};
    quint16 CRC;
};
class RESET_COMMAND : public COMMAND_REQUEST
{
public:
    RESET_COMMAND() { COMMAND_CODE = CODE_RESET; DATA_SIZE = 0; }
    quint16 CRC;
};
class ANALOG_CTRL_COMMAND : public COMMAND_REQUEST
{
public:
    ANALOG_CTRL_COMMAND() { COMMAND_CODE = CODE_ANALOG_CTRL; DATA_SIZE = 2; }
    quint16 OnOff;
    quint16 CRC;
};
class EMISSION_TURN_COMMAND : public COMMAND_REQUEST
{
public:
    EMISSION_TURN_COMMAND() { COMMAND_CODE = CODE_EMISSION; DATA_SIZE = 2; }
    quint16 OnOff;
    quint16 CRC;
};



struct ACCESS_LEVEL_COMMAND : public COMMAND_REQUEST
{
    ACCESS_LEVEL_COMMAND()
    {
        COMMAND_CODE = 2080;
        DATA_SIZE = 14;
    }
    quint16 Version = 1;
    quint16 AccessLevel = 1; //Operator 1 //Enginer 2 //Supervisor 100
    quint8  Passwd[10] = {0};
    quint16 CRC;
};

class GUID_COMMAND_STRUCT : public COMMAND_REQUEST
{
public:
    GUID_COMMAND_STRUCT()
    {
        COMMAND_CODE = 2504; // 0x9C 0x80
        DATA_SIZE = 4;
    }
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

class LASER_PARAM_STRUCT
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
	quint32  Alarms2;
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
	void PrintStruct();
	friend void operator>>(QDataStream& in_stream, LASER_PARAM_STRUCT& Param);
};
class LASER_MESSAGE : public COMMAND_REQUEST
{
public:
    LASER_PARAM_STRUCT DATA;
    bool isValid() {return COMMAND_CODE == CODE_LASER_DATA;};
    quint16 CRC;
    void LoadData(QByteArray& Array);
	bool isLaserHasError();
	bool isLaserGuidOn();
	bool isLaserPowerOn();
	bool isLaserReady();
	bool isPowerOn(); 
	bool isChillerWork();
	bool isAnalogControlOn();
	bool isLaserStandby();
	bool isLaserShutDown();
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
    QTimer timerGetLaserState;
    QByteArray InputBuffer;

    LASER_MESSAGE LaserDynamicParam;
private:
	void SendRequestToUpControlStatus();
	void SendRequestGetLaserParam();
	void SendRequestGetChillerParam();
	void SendRequestReset();

    COMMAND_REQUEST HEADER_DATA;

	public slots:
	    void TurnLaserBeamOnOff(bool OnOff);
		void slotReadyRead   (                            );
		void slotError       (QAbstractSocket::SocketError);
		void slotConnected   (        );
        void slotSendStateRequest();

};



