#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"
#include "RotateOperationContainer.h"
#include <QTcpSocket>
#include <QSerialPort>
#include <QTcpServer>
#include <QTimer>
#include "HandleControlInterface.h"

enum error_port_work_modes {aiming_mode = 1, registration_mode = 2};
enum error_port_direction {direct_to_all = 0, direct_to_channel1 = 1, direct_to_channel2 = 2, direct_to_channel3 = 3};

class RemoteAimingWindowControl;

class Header_Data
{
public:
	uchar HEADER1;
	uchar HEADER2;
	bool isValid() {return (HEADER1 == 0xC1 && HEADER2 == 0xC2); };

	friend void operator>>(QDataStream& in_stream, Header_Data& Data);

};
struct COMMAND_CAMERA_CONTROL
{
  uint8_t OnOff;
};
struct COMMAND_ENGINE_CONTROL
{
  uint8_t OnOff;
};
struct COMMAND_UMI_CONTROL
{
  uint8_t OnOff;
  uint8_t Mode;

  struct DIOD_CONTROL
  {
  	uint8_t DIOD1 :1;
  	uint8_t DIOD2 :1;
  	uint8_t DIOD3 :1;
  } DiodOnOff;
};
struct COMMAND_LASER_CONTROL
{
  uint8_t OnOff;
  uint8_t PowerOnOff;
  uint8_t PilotOnOff;
};

template< typename T>
class MessageStruct
{
	public:
    uint16_t HEADER; 
    uint32_t ID_TASK; 
    uint8_t  TYPE_MESSAGE; 
    uint8_t  COMMAND_ID; 
    uint32_t DATA_SIZE; 
    T DATA; 
    uint8_t ERROR_ID; 
};



class TCPServerEngine : public QObject
{
    Q_OBJECT
public:
    explicit TCPServerEngine(QObject *parent = nullptr);
	TCPServerEngine(TCPServerEngine& server);
    void sendToClient(QTcpSocket* Socket, const QString& str);
    void SetPort(int port);
	MessageStruct<COMMAND_LASER_CONTROL> LASER_COMMAND;
	

    int Port;
    QTcpServer* Server = 0;
    QTcpSocket* SocketToClient = 0;
	QByteArray Data;
signals:
	void DataReceived();

public slots:
    void SlotNewConnection();
    void SlotReadData();
    void StartLocalServer();


};

class RemoteAimingHandleInterface
{
public:
virtual	void SlotResetRotationBlocks() = 0;
virtual	void SlotSetActiveChannel(int Channel) = 0;
virtual	void SlotLoadDataFromFile(QString FileName) = 0;
virtual	void SlotSetMode(int Mode) = 0;
};


class RemoteAimingClass
	: public PassTwoCoordClass, public RemoteAimingHandleInterface
{
private:
public:
	typeblocksenum TypeBlock = typeblocksenum::RecieveErrorBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
    error_port_work_modes work_mode = aiming_mode;
	error_port_direction error_direction = direct_to_channel1;

	RemoteAimingWindowControl* ErrorPortWindowControl = 0;

	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> Coord);
	bool isValid();

	QPair<double, double> RemoteAimingCoord;

	RemoteAimingClass();
	~RemoteAimingClass();

public:
	void SlotResetRotationBlocks();
	void SlotSetActiveChannel(int Channel);
	void SlotLoadDataFromFile(QString FileName);
	void SlotSetMode(int Mode);

public:	
	RotateOperationContainer RemoteToBaseTransform;
	QSerialPort PortToSTN;

};


class RemoteControlClass
{
	public: 
	RemoteControlClass(HandleControlInterface* Interface) { DeviceControl = Interface;};
	RemoteAimingClass AimingPort;
	TCPServerEngine TCPServer;

	private:
	QTimer timerSendState; 

	void PerformRemoteCommand();
	void SendStateToRemote();

	HandleControlInterface* DeviceControl;

};