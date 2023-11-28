#include "CommonHeaders.h"
#include "RemoteControlClass.h"
#include <qdebug.h>
#include "RemoteAimingWindowControl.h"
#include "LaserCommonInterface.h"
#define TAG "[ REMOTE CTRL]" 

RemoteAimingClass::RemoteAimingClass()
{

    RemoteToBaseTransform.LoadRotationFromFile("/home/broms/DEVELOPMENT/DATA/TrainerData/RotateMatrixOutput1.txt");
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

QDataStream in_stream(TCPServer.Data);
uint16_t HEADER; in_stream >> HEADER;
uint32_t ID_TASK; in_stream >> ID_TASK;

if(HEADER == 0xC1C2)  //AIMING DATA 
{
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_AIMING_COORD>*>(TCPServer.Data.data()); 
    QPair<double,double>(Message->DATA.X, Message->DATA.Y) >> AimingPort;
}


if(HEADER == 0x8220) //COMMAND DATA
{
uint16_t DataReceived = 0;
switch(ID_TASK)
{
    case camera_control_message:
    {
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_ON_OFF>*>(TCPServer.Data.data()); DataReceived = sizeof(Message);
    qDebug() << TAG << "REMOTE CAMERA CONTROL DONT WORK";
    }
    break;
    case engine_control_message:
    {
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_ON_OFF>*>(TCPServer.Data.data()); DataReceived = sizeof(Message);
    qDebug() << TAG << "REMOTE ENGINE CONTROL DONT WORK";
    }
    break;
    case marker_laser_message:
    {
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_UMI_CONTROL>*>(TCPServer.Data.data()); DataReceived = sizeof(Message);
         DeviceControl->TurnOnOffLaser(POINTER_LASER,Message->DATA.OnOff);
    }
    break;
    case laser_system_message:
    {
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_LASER_CONTROL>*>(TCPServer.Data.data()); DataReceived = sizeof(Message);
         DeviceControl->TurnOnOffLaser(GUID_LASER1, Message->DATA.OnOff);
         DeviceControl->TurnOnOffLaser(GUID_LASER2, Message->DATA.OnOff);
         DeviceControl->TurnOnOffLaser(GUID_LASER3, Message->DATA.OnOff);
    }
    break;
    case calibration_message:
    {
    auto Message =  reinterpret_cast< MessageStruct<COMMAND_ON_OFF>*>(TCPServer.Data.data()); DataReceived = sizeof(Message);
    qDebug() << TAG << "CALIBRATION DONT WORK";
    }
    break;
}
    TCPServer.Data.remove(0,DataReceived);
}

}

void RemoteControlClass::SendStateToRemote()
{
    MessageStruct<DEVICE_STATE> StateMessage;

}

void operator>>(DataDeviceStructure& DeviceData, RemoteControlClass& RemoteControl)
{

	switch (DeviceData.TypeBlock)
    {
	case EngineControlBlock:   static_cast<DataEngineStructure&>(DeviceData)  >> RemoteControl;  break;
	case ChillControlBlock:    static_cast<DataChillerStructure&>(DeviceData) >> RemoteControl;  break;
	case WeatherControlBlock:  static_cast<DataWeatherStructure&>(DeviceData) >> RemoteControl;  break;
	case CamerasControlBlock:  static_cast<DataCamerasStructure&>(DeviceData) >> RemoteControl;  break;
	case LasersBlock:          static_cast<DataLaserStruct&>(DeviceData)      >> RemoteControl;  break;
	default: break;
	}
}

void operator>>(DataLaserStruct& LaserData, RemoteControlClass& RemoteControl)
{
   //RemoteControl.DevicesStateVector.PowerLaserState = LaserData. 
}
void operator>>(DataEngineStructure& EngineData, RemoteControlClass& RemoteControl)
{
}
void operator>>(DataCamerasStructure& CamerasData, RemoteControlClass& RemoteControl)
{

}
void operator>>(DataWeatherStructure& WeatherData, RemoteControlClass& RemoteControl)
{

}
void operator>>(DataChillerStructure& ChillerData, RemoteControlClass& RemoteControl)
{

}