#ifndef TCPCONNECTIONCLASS_H
#define TCPCONNECTIONCLASS_H

#include <QObject>

#include <QFile>
#include <QSocketNotifier>
#include <qsocketnotifier.h>
#include "RemoteControlProtocol.h"
#include <QTcpSocket>
#include <QTcpServer>

class TCPServerEngine : public QObject
{
    Q_OBJECT
public:
    explicit TCPServerEngine(QObject *parent = nullptr);
	TCPServerEngine(TCPServerEngine& server);
    void SendToClient(QTcpSocket* Socket, const QString& str);
    void SetPort(int port);
	

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



#endif // TCPCONNECTIONCLASS_H
