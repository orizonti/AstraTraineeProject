#include "stdafx.h"
#include "ErrorRecieverClass.h"
#include <qdebug.h>
#include "ErrorPortControl.h"

ErrorRecieverClass::ErrorRecieverClass()
{

    RemoteToBaseTransform.LoadRotationFromFile("E:/TrainerData/RotateMatrixOutput1.txt");
    RemoteToBaseTransform.Inverse();

    TCPServer.StartLocalServer();
    ErrorPortWindowControl = new ErrorPortControl;
    ErrorPortWindowControl->SetHandleControl(this);
}

ErrorRecieverClass::~ErrorRecieverClass()
{
    ErrorPortWindowControl->close();
    delete ErrorPortWindowControl;
qDebug() << "      DELETE ERROR RECIEVER CLASS";
}

void ErrorRecieverClass::SlotRecieveNewSTNData()
{
	// TODO: Implement Method
	throw "Not Implemented Exception: void ErrorRecieverClass::SlotRecieveNewSTNData()";
}

void ErrorRecieverClass::SignalNewErrorAvaible(QPair<double, double> ErrorCoords)
{
	// TODO: Implement Method
	throw "Not Implemented Exception: void ErrorRecieverClass::SignalNewErrorAvaible(QPair<double, double> ErrorCoords)";
}

QPair<double, double> ErrorRecieverClass::GetCoord()
{
    QPair<double, double> Error;
    Error.first = TCPServer.DataValues[0];
    Error.second = TCPServer.DataValues[1];

    if(work_mode == aiming_mode)
    Error >> RemoteToBaseTransform >> Error;

    return Error;
}

void ErrorRecieverClass::SetCoord(QPair<double, double> Coord)
{
	qDebug() << "			ERROR RECIEVER SETCOORD MUST BE IMPLEMENTED";
}

TCPServerEngine::TCPServerEngine(int LocalPort ,QObject *parent) : QObject(parent)
{
    Port = LocalPort;
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

      qDebug() << "Start local server at port - " << Port;
      if (!Server->listen(QHostAddress::Any,Port))
      {
          qDebug() << "Unable to start server";
          Server->close();
          return;
      }
      qDebug() << "Server connect to " << Server->serverAddress().toString();
      connect(Server, &QTcpServer::newConnection,
              this,   &TCPServerEngine::SlotNewConnection
             );

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


bool ErrorRecieverClass::isValid()
{
    return RemoteToBaseTransform.isValid();
}

void ErrorRecieverClass::SlotResetRotationBlocks()
{
   RemoteToBaseTransform.Reset();
}
void ErrorRecieverClass::SlotSetActiveChannel(int Channel)
{
    error_direction = (error_port_direction)Channel;
    qDebug() << "Current direction - " << error_direction;
}

void ErrorRecieverClass::SlotLoadDataFromFile(QString FileName)
{
}

void ErrorRecieverClass::SlotSetMode(int Mode)
{
    work_mode = (error_port_work_modes)Mode;
    qDebug() << "Work mode - " << work_mode;
}

