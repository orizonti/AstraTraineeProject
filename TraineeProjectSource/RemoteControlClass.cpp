#include "stdafx.h"
#include "RemoteControlClass.h"
#include <qdebug.h>
#include "RemoteAimingWindowControl.h"

RemoteAimingClass::RemoteAimingClass()
{

    RemoteToBaseTransform.LoadRotationFromFile("/home/broms/TrainerData/RotateMatrixOutput1.txt");
    RemoteToBaseTransform.Inverse();

    //TCPServer.SetPort(2323);
    //TCPServer.StartLocalServer();
    ErrorPortWindowControl = new RemoteAimingWindowControl;
    ErrorPortWindowControl->SetHandleControl(this);
}

RemoteAimingClass::~RemoteAimingClass()
{
    ErrorPortWindowControl->close();
    delete ErrorPortWindowControl;
}


QPair<double, double> RemoteAimingClass::GetCoord()
{
    return RemoteAimingCoord;
}

void RemoteAimingClass::SetCoord(QPair<double, double> Coord)
{
    //QPair<double, double> Error;
    //Error.first = TCPServer.DataValues[0];
    //Error.second = TCPServer.DataValues[1];
    RemoteAimingCoord = Coord;
    if(work_mode == aiming_mode)
    RemoteAimingCoord >> RemoteToBaseTransform >> RemoteAimingCoord;
}

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

    qDebug() << "Start local server at port - " << Port;
      if (!Server->listen(QHostAddress::Any,Port))
      {
          qDebug() << "Unable to start server";
          Server->close();
          return;
      }
      qDebug() << "is Server listen - "  << Server->isListening();

     //Server->waitForNewConnection(30000);

}
void TCPServerEngine::sendToClient(QTcpSocket* Socket, const QString &str)
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
        qDebug() << "Error port connected from - " << SocketToClient->peerAddress().toString();
}

void TCPServerEngine::SlotReadData()
{
        Data.append(SocketToClient->readAll());
        emit DataReceived();

}

void operator>>(QDataStream& in_stream, Header_Data& Data)
{
    in_stream >> Data.HEADER1;
    in_stream >> Data.HEADER2;
}


bool RemoteAimingClass::isValid()
{
    return RemoteToBaseTransform.isValid();
}

void RemoteAimingClass::SlotResetRotationBlocks()
{
   RemoteToBaseTransform.Reset();
}
void RemoteAimingClass::SlotSetActiveChannel(int Channel)
{
    error_direction = (error_port_direction)Channel;
}

void RemoteAimingClass::SlotLoadDataFromFile(QString FileName)
{
}

void RemoteAimingClass::SlotSetMode(int Mode)
{
    work_mode = (error_port_work_modes)Mode;
}


void RemoteControlClass::PerformRemoteCommand()
{

    Header_Data header;
    QDataStream in_stream(TCPServer.Data);
    in_stream >> header;

    //QPair<double,double> Coord;
    
    //if (header.isValid())
    //{
    //    in_stream >> Coord.first >> Coord.second; 
    //}
}

void RemoteControlClass::SendStateToRemote()
{

}