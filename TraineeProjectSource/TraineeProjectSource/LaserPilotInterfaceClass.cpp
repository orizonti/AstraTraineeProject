#include "CommonHeaders.h"
#include "LaserPilotInterfaceClass.h"

LaserPilotInterfaceClass::LaserPilotInterfaceClass(QString Address, quint16 Port)
{
	SocketGuidLaser = new QTcpSocket;
	ConnectToLaserTCP(Address, Port);
	IPLaser = Address;
}

LaserPilotInterfaceClass::~LaserPilotInterfaceClass()
{
	 SocketGuidLaser->disconnectFromHost();

   // SocketGuidLaser->abort();
//         if(SocketGuidLaser->waitForDisconnected(4000))
            //qDebug() << "SOCKET CONNECTED - " << Address << Port;

         delete SocketGuidLaser;
}

void LaserPilotInterfaceClass::ConnectToLaserTCP(QString Address, quint16 Port)
{

	SocketGuidLaser->abort();

	connect(SocketGuidLaser, SIGNAL(connected()),this, SLOT(slotConnected()));
	connect(SocketGuidLaser, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slotError(QAbstractSocket::SocketError)));
	connect(SocketGuidLaser, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));

      SocketGuidLaser->connectToHost(Address,Port);

}

void LaserPilotInterfaceClass::TurnLaserBeamOnOff(bool OnOff)
{
	if (this->OnOff != OnOff)
		this->OnOff = OnOff;
	else
		return;


     GUID_COMMAND_STRUCT Command;
     Command.NUMBER_CHANNEL = 0;
     if(OnOff)
     Command.ON_OFF = 1;

     if(!OnOff)
     Command.ON_OFF = 0;
     Command.CRC = this->GetCRC((unsigned char*)&Command,Command.HEADER.DATA_SIZE +8);
	 //convert to QByteArray to can display massive
     QByteArray ArrayCommand((const char*)&Command,Command.HEADER.DATA_SIZE + 10);

     if (SocketGuidLaser->state() == 3)
     {
     SocketGuidLaser->write(ArrayCommand);
     }


	 if(OnOff)
	 this->LaserState = stateblocksenum::BlockAtWork;
	 
	 if (!OnOff)
	 this->LaserState = stateblocksenum::BlockDisable;

}

DataLaserStruct LaserPilotInterfaceClass::GetState()
{
	return	CommonLaserInterfaceClass::GetState();
}

void LaserPilotInterfaceClass::SendRequestToUpControlStatus()
{
	     ACCESS_LEVEL_COMMAND Command;
     Command.CRC = this->GetCRC((unsigned char*)&Command,Command.HEADER.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.HEADER.DATA_SIZE + 10);

     SocketGuidLaser->write(ArrayCommand);
}

quint16 LaserPilotInterfaceClass::GetCRC(unsigned char *data, int dataSize)
{

    unsigned short crc16 = 0;

    for(int n = 0; n < dataSize; n++)
    {
        unsigned short ch = (unsigned short)data[n];

         for(int i =0; i < 8; i++)
         {
             unsigned short b = (crc16 ^ ch) & 1;
             crc16 >>= 1;
             ch >>= 1;
             if(b)crc16^=0xA001;
         }
    }
    return crc16;
}


void LaserPilotInterfaceClass::slotReadyRead()
{
    QDataStream in(SocketGuidLaser);
                in.setByteOrder(QDataStream::LittleEndian);
        if (SocketGuidLaser->bytesAvailable() >= 10)
        {
            quint16 CRC = 0;
            in >> HEADER_DATA.COMMAND >> HEADER_DATA.EXECUTION_CODE >> HEADER_DATA.DATA_SIZE >> CRC;
            SocketGuidLaser->flush();

        }
}
void LaserPilotInterfaceClass::slotError(QAbstractSocket::SocketError err)
{
	QString strError =
		"Error: " + (err == QAbstractSocket::HostNotFoundError ?
			"The host was not found." :
			err == QAbstractSocket::RemoteHostClosedError ?
			"The remote host is closed." :
			err == QAbstractSocket::ConnectionRefusedError ?
			"The connection was refused." :
			QString(SocketGuidLaser->errorString())
			);
}

void LaserPilotInterfaceClass::slotConnected()
{

	qDebug() << QString("CONNECTED TO HOST - %1").arg(SocketGuidLaser->peerName());
	this->SendRequestToUpControlStatus();
}


