#include "UDPEngineInterface.h"
#include <algorithm>
#include <qhostaddress.h>
#include <typeinfo>

UDPEngineInterface::UDPEngineInterface(QString Address, QString Remote, int REMOTE_PORT, int LOCAL_PORT)
{
   this->RemoteAddress = Remote;
   this->LOC_PORT = LOCAL_PORT;
   this->REM_PORT = REMOTE_PORT;

   //initSocket(Address);
   initSocket("Any");
}

void UDPEngineInterface::initSocket(QString Address)
{
     CommandSocket = new QUdpSocket;

     if(Address == "Any")
     CommandSocket->bind(QHostAddress::Any,7575);
     else 
     CommandSocket->bind(QHostAddress(Address),7575);


     qDebug() << "UDP BIND: " << Address << "PORT : " << 7575 << " REMOTE: " << RemoteAddress;
     connect(CommandSocket, &QUdpSocket::readyRead, this, &UDPEngineInterface::readUDP);
}


void UDPEngineInterface::SendCommand(const QByteArray& Command)
{
  CommandSocket->writeDatagram(Command,QHostAddress(RemoteAddress),7575);
  qDebug() << "SEND: " <<  Command.toHex();
  qDebug() << "SIZE: " << Command.size();
}


template<typename T> 
void UDPEngineInterface::SendConfirmation(MessageStruct<T> Message)
{
   Message.HEADER.MESSAGE_TYPE = PACK_ACK; SendCommand(Message.toByteArray());
}

template<typename T> 
int UDPEngineInterface::ProcessMessage(MessageStruct<T> Message)
{
   SendConfirmation(Message);
   if(KLP_CMD_GROUP_LIST::isValid(Message.HEADER.CMD_TYPE)) emit SignalNewMessage(static_cast<KLP_CMD_TYPES>(Message.HEADER.CMD_TYPE));
   if(KLP_CMD_GROUP_LIST::isValid(Message.HEADER.CMD_TYPE)) qDebug() << "PROCESS VALID CMD: " << KLP_CMD_GROUP(Message.HEADER.CMD_TYPE);
   return Message.GetSize();
}

void UDPEngineInterface::readUDP()
{

//while (CommandSocket->hasPendingDatagrams())
//{
//   QNetworkDatagram datagram = CommandSocket->receiveDatagram();
//   InputBuffer.append(datagram.data());
//}

   QNetworkDatagram datagram = CommandSocket->receiveDatagram();
   InputBuffer.append(datagram.data());
   qDebug() << "MESSAGE REC: " << InputBuffer.toHex();

QDataStream in_stream_header(&InputBuffer, QIODevice::ReadWrite); in_stream_header.setByteOrder((QDataStream::LittleEndian));
QDataStream in_stream(&InputBuffer, QIODevice::ReadWrite); in_stream.setByteOrder(QDataStream::LittleEndian);
MESSAGE_HEADER HEADER;


  int BytesAvailable = InputBuffer.size();

  while(BytesAvailable >= 14)
  {
    in_stream_header >> HEADER; if(!HEADER.isValid()) {return;};
    
    int BytesProc = 0; 
    qDebug() << "MESSAGE TYPE: " <<HEADER.CMD_TYPE << KLP_CMD_GROUP(HEADER.CMD_TYPE)  << "ID: " << HEADER.MESSAGE_ID;
    
    if (HEADER.CMD_TYPE == CMD_CAMERA)    {in_stream >> CameraControl;     BytesProc = ProcessMessage(CameraControl);  }; 
    if (HEADER.CMD_TYPE == CMD_ENGINES)   {in_stream >> EngineControl;     BytesProc = ProcessMessage(EngineControl);  }; 
    if (HEADER.CMD_TYPE == CMD_POINTLASER){in_stream >> LaserPointerCmd;   BytesProc = ProcessMessage(LaserPointerCmd);}; 
    if (HEADER.CMD_TYPE == CMD_PILOTLASER){in_stream >> LaserGuidCmd   ;   BytesProc = ProcessMessage(LaserGuidCmd);   }; 
    if (HEADER.CMD_TYPE == CMD_POWERLASER){in_stream >> LaserPowerCmd;     BytesProc = ProcessMessage(LaserPowerCmd);  }; 
    if (HEADER.CMD_TYPE == CMD_AIMING)    {in_stream >> AimingControl;     BytesProc = ProcessMessage(AimingControl);  }; 
    
    BytesAvailable -= BytesProc; qDebug() << "BYTES PROCESED: " << BytesProc;
    qDebug() << "===============================================";
  }
     
  InputBuffer.remove(0,InputBuffer.size() - BytesAvailable);
}

QString UDPEngineInterface::PrintCommand(KLP_CMD_TYPES CMD_TYPE)
{
    if (CMD_TYPE == CMD_CAMERA)    return CommandToString(CameraControl.DATA);
    if (CMD_TYPE == CMD_ENGINES)   return CommandToString(EngineControl.DATA);
    if (CMD_TYPE == CMD_POINTLASER)return CommandToString(LaserPointerCmd.DATA);
    if (CMD_TYPE == CMD_PILOTLASER)return CommandToString(LaserGuidCmd.DATA);
    if (CMD_TYPE == CMD_POWERLASER)return CommandToString(LaserPowerCmd.DATA);
    if (CMD_TYPE == CMD_AIMING)    return CommandToString(AimingControl.DATA);
}