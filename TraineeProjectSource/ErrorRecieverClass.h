#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"
#include "RotateOperationContainer.h"
#include <QTcpSocket>
#include <QSerialPort>
#include <QTcpServer>

enum error_port_work_modes {aiming_mode = 1, registration_mode = 2};
enum error_port_direction {direct_to_all = 0, direct_to_channel1 = 1, direct_to_channel2 = 2, direct_to_channel3 = 3};

class ErrorPortControl;

class Header_Data
{
public:
	uchar HEADER1;
	uchar HEADER2;
	bool isValid() {return (HEADER1 == 0xC1 && HEADER2 == 0xC2); };

	friend void operator>>(QDataStream& in_stream, Header_Data& Data);

};


class TCPServerEngine : public QObject
{
    Q_OBJECT
public:
    explicit TCPServerEngine(int Port,QObject *parent = nullptr);
	TCPServerEngine(TCPServerEngine& server);
    void sendToClient(QTcpSocket* Socket, const QString& str);
	

    int Port;
    QTcpServer* Server = 0;
    QTcpSocket* SocketToClient = 0;
    QVector<float> DataValues;
signals:
	void DataReceived();

public slots:
    void SlotNewConnection();
    void SlotReadData();
    void StartLocalServer();


};

class ErrorRecieverHandleInterface
{
public:
virtual	void SlotResetRotationBlocks() = 0;
virtual	void SlotSetActiveChannel(int Channel) = 0;
virtual	void SlotLoadDataFromFile(QString FileName) = 0;
virtual	void SlotSetMode(int Mode) = 0;
};


class ErrorRecieverClass
	: public PassTwoCoordClass, public ErrorRecieverHandleInterface
{
private:
	void SlotRecieveNewSTNData();
public:
	typeblocksenum TypeBlock = typeblocksenum::RecieveErrorBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
    error_port_work_modes work_mode = aiming_mode;
	error_port_direction error_direction = direct_to_channel1;

	ErrorPortControl* ErrorPortWindowControl = 0;

	void SignalNewErrorAvaible(QPair<double, double> ErrorCoords);
	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> Coord);
	bool isValid();

	QPair<double, double> Error;

	ErrorRecieverClass();
	~ErrorRecieverClass();

public:
	void SlotResetRotationBlocks();
	void SlotSetActiveChannel(int Channel);
	void SlotLoadDataFromFile(QString FileName);
	void SlotSetMode(int Mode);

public:	
	RotateOperationContainer RemoteToBaseTransform;

	QSerialPort PortToSTN;
	TCPServerEngine&& TCPServer = TCPServerEngine(2323);

};