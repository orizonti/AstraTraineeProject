#pragma once

#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include <tuple>

#include "LaserCommonInterface.h"
#include "LaserPowerCommands.h"
#include <QTimer>


class LaserPowerInterface : public LaserCommonInterface
{
	Q_OBJECT
public:
	LaserPowerInterface(QString Address, quint16 Port);
	~LaserPowerInterface();

	void ConnectToLaser(QString Address, quint16 Port);
	DataLaserStruct GetState();

    QTcpSocket *socketLaser = 0;
	QString    IPLaser;
    QTimer     timerGetLaserState;
    QByteArray inputBuffer;

    LASER_MESSAGE LASER_CURRENT_PARAM;
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
	signals:
	void SignalLaserMessage(LASER_MESSAGE);

};



