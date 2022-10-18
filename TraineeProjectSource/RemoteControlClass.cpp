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
qDebug() << "      DELETE ERROR RECIEVER CLASS";
}

void RemoteAimingClass::SlotRecieveNewSTNData()
{
	// TODO: Implement Method
	throw "Not Implemented Exception: void RemoteAimingClass::SlotRecieveNewSTNData()";
}

void RemoteAimingClass::SignalNewErrorAvaible(QPair<double, double> ErrorCoords)
{
	// TODO: Implement Method
	throw "Not Implemented Exception: void RemoteAimingClass::SignalNewErrorAvaible(QPair<double, double> ErrorCoords)";
}

QPair<double, double> RemoteAimingClass::GetCoord()
{
    QPair<double, double> Error;
    Error.first = TCPServer.DataValues[0];
    Error.second = TCPServer.DataValues[1];

    if(work_mode == aiming_mode)
    Error >> RemoteToBaseTransform >> Error;

    return Error;
}

void RemoteAimingClass::SetCoord(QPair<double, double> Coord)
{
	qDebug() << "			ERROR RECIEVER SETCOORD MUST BE IMPLEMENTED";
}

void TCPServerEngine::SetPort(int port)
{
   Port = port;
}

TCPServerEngine::TCPServerEngine(QObject *parent) : QObject(parent)
{
    DataValues = {0,0,0,0,0,0};
}

TCPServerEngine::TCPServerEngine(TCPServerEngine& server)
{

    Port = server.Port;
    Server = server.Server;
    SocketToClient = server.SocketToClient;
    DataValues = {0,0,0,0,0,0};
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
		Header_Data header;
        QByteArray Data = SocketToClient->readAll();
        QDataStream in_stream(Data);
        in_stream >> header;
        

        if (header.isValid())
        {
        for(float& Value: DataValues){in_stream >> Value;}
        emit DataReceived();
        }

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
    qDebug() << "Current direction - " << error_direction;
}

void RemoteAimingClass::SlotLoadDataFromFile(QString FileName)
{
}

void RemoteAimingClass::SlotSetMode(int Mode)
{
    work_mode = (error_port_work_modes)Mode;
    qDebug() << "Work mode - " << work_mode;
}

