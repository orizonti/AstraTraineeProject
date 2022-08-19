#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "CommonLaserInterfaceClass.h"
#include "PilotLaserWindow.h"
#include <QAbstractSocket>

class HEADER_LASER_CONTROL
{
public:
    quint16 COMMAND = 0;
     qint16 EXECUTION_CODE = 0;
    quint32 DATA_SIZE = -1;

};

class GUID_COMMAND_STRUCT
{
public:
    GUID_COMMAND_STRUCT()
    {
        this->HEADER.COMMAND = 2504; // 0x9C 0x80
        this->HEADER.DATA_SIZE = 4;
    }

    HEADER_LASER_CONTROL HEADER;
    quint16 NUMBER_CHANNEL;
    quint16 ON_OFF; //0 - off 1 - on
    quint16 CRC;
};

struct ACCESS_LEVEL_COMMAND
{
    ACCESS_LEVEL_COMMAND()
    {
        HEADER.COMMAND = 2080;
        HEADER.DATA_SIZE = 14;
    }

    HEADER_LASER_CONTROL HEADER;
    quint16 Version = 1;
    quint16 AccessLevel = 1; //Operator 1 //Enginer 2 //Supervisor 100
    quint8  Passwd[10] = {0};
    quint16 CRC;
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

    quint16 GetCRC(unsigned char * data, int dataSize);
    HEADER_LASER_CONTROL HEADER_DATA;

	public slots:
	    void TurnLaserBeamOnOff(bool OnOff);
		void slotReadyRead   (                            );
		void slotError       (QAbstractSocket::SocketError);
		void slotConnected   (        );

};



