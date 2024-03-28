#ifndef UDPCONNECTIONCLASS_H
#define UDPCONNECTIONCLASS_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QFile>
#include <QSocketNotifier>
#include <qsocketnotifier.h>
#include "RemoteControlProtocol.h"


class UDPEngineInterface : public QObject
{
    Q_OBJECT
public:
    UDPEngineInterface(QString Address, QString Remote, int REMOTE_PORT, int LOCAL_PORT);
    void initSocket(QString Address);
    void SendCommand(const QByteArray& Command);
	QString PrintCommand(KLP_CMD_TYPES CMD_TYPE);

    template<typename T> void SendConfirmation(MessageStruct<T> Message);
    template<typename T> int ProcessMessage(MessageStruct<T> Message);

    QUdpSocket* CommandSocket;
    QUdpSocket* AimingSocket;
    QSocketNotifier* m_notifier;
    QString RemoteAddress = "172.28.255.56";
    int REM_PORT = 7575;
    int LOC_PORT = 7575;
    
MessageStruct<COMMAND_GUID_LASER>     LaserGuidCmd;    //THREE RED LASERS AT POWER LASERS
MessageStruct<COMMAND_POWER_LASER>    LaserPowerCmd;
MessageStruct<COMMAND_POINT_LASER>    LaserPointerCmd; //UMI, ONE SEPARATE LASER MODULE with 600, 900, 1000 nm CHANNELS

MessageStruct<COMMAND_ENGINE_CONTROL> EngineControl;
MessageStruct<COMMAND_CAMERA_CONTROL> CameraControl;
MessageStruct<STATE_STRUCT>           StateMessage;
MessageStruct<COMMAND_AIMING_COORD>   AimingControl;

    QByteArray InputBuffer;
    int MinDataSize = sizeof(MessageStruct<COMMAND_ENGINE_CONTROL>);
public slots:
  void readUDP();
signals:
void SignalNewMessage(KLP_CMD_TYPES); 

};


#endif // UDPCONNECTIONCLASS_H
