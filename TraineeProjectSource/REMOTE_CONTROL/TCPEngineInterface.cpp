#include "TCPEngineInterface.h"
#include <algorithm>
#include <qhostaddress.h>
#include <typeinfo>

void TCPServerEngine::SetPort(int port)
{
   Port = port;
}

TCPServerEngine::TCPServerEngine(QObject *parent) : QObject(parent)
{
}

TCPServerEngine::TCPServerEngine(TCPServerEngine& server)
{

    Port = server.Port;
    Server = server.Server;
    SocketToClient = server.SocketToClient;
}

void TCPServerEngine::StartLocalServer()
{
       Server = new QTcpServer(this);
       connect(Server, &QTcpServer::newConnection,
               this,   &TCPServerEngine::SlotNewConnection
       );

    qDebug() << TAG << "START LOCAL SERVER AT PORT - " << Port;
      if (!Server->listen(QHostAddress::Any,Port))
      {
          qDebug() << TAG << "UNABLE TO START SERVER";
          Server->close();
          return;
      }

     //Server->waitForNewConnection(30000);

}
void TCPServerEngine::SendToClient(QTcpSocket* Socket, const QString &str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    Socket->write(arrBlock);
}

void TCPServerEngine::SlotNewConnection()
{
        SocketToClient = Server->nextPendingConnection();

        connect(SocketToClient, SIGNAL(disconnected()),
                SocketToClient, SLOT(deleteLater())
               );
        connect(SocketToClient, SIGNAL(readyRead()),
                this,          SLOT(SlotReadData())
               );

        //sendToClient(SocketToClient, QString(" connected ").toUtf8());
        qDebug() << TAG << "Error port connected from - " << SocketToClient->peerAddress().toString();
}

void TCPServerEngine::SlotReadData()
{
        Data.append(SocketToClient->readAll());
        emit DataReceived();

}



bool RemoteAimingInterface::isValid()
{
    return RemoteToBaseTransform.isValid();
}