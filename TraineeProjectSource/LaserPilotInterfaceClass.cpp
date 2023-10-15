#include "stdafx.h"
#include "LaserPilotInterfaceClass.h"

int COMMAND_REQUEST::LaserMessageCount = 0;


LaserPilotInterfaceClass::LaserPilotInterfaceClass(QString Address, quint16 Port)
{
	SocketGuidLaser = new QTcpSocket;
	ConnectToLaserTCP(Address, Port);
	IPLaser = Address;
    QObject::connect(&timerGetLaserState,&QTimer::timeout,this,&LaserPilotInterfaceClass::slotSendStateRequest);
}

LaserPilotInterfaceClass::~LaserPilotInterfaceClass()
{
	 SocketGuidLaser->disconnectFromHost();

   // SocketGuidLaser->abort();
   //       if(SocketGuidLaser->waitForDisconnected(4000))
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
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
	 //convert to QByteArray to can display massive
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);

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
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);

     SocketGuidLaser->write(ArrayCommand);
}

void LaserPilotInterfaceClass::SendRequestGetLaserParam()
{
	 auto Command = GET_PARAM_COMMAND(CODE_LASER_DATA);
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     //qDebug() << "GET LASER PARAM : " << ArrayCommand.toHex();
     SocketGuidLaser->write(ArrayCommand);
}
void LaserPilotInterfaceClass::SendRequestGetChillerParam()
{
	 auto Command = GET_PARAM_COMMAND(CODE_CHILLER_DATA);
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     //qDebug() << "GET CHILLER PARAM: " << ArrayCommand.toHex();
     SocketGuidLaser->write(ArrayCommand);
}
void LaserPilotInterfaceClass::SendRequestReset()
{
     qDebug() << "SEND RESET TO LASER";
	 auto Command = RESET_COMMAND();
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     SocketGuidLaser->write(ArrayCommand);
}

quint16 GetCRC(unsigned char *data, int dataSize)
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
        InputBuffer.append(SocketGuidLaser->readAll());
        COMMAND_REQUEST Request;
        LASER_MESSAGE LaserStruct;
        int WaitDataSize = sizeof(COMMAND_REQUEST)+2;

        while (InputBuffer.size() >= WaitDataSize)
        {
            auto [COMMAND_CODE,DATA_SIZE] = COMMAND_REQUEST::GetHeader(InputBuffer);
            WaitDataSize = DATA_SIZE + sizeof(COMMAND_REQUEST) + 2;
            //qDebug() << " [" << InputBuffer.toHex() << " ]";
            //qDebug() << "INPUT BUFFER SIZE: " << InputBuffer.size() << " WAIT: " << WaitDataSize;

            if(DATA_SIZE == 0) Request.LoadData(InputBuffer);
            if(COMMAND_CODE == CODE_LASER_DATA)   LaserStruct.LoadData(InputBuffer);

            if((COMMAND_CODE - 2000) <= 0)InputBuffer.clear(); break;
            if((COMMAND_CODE - 2000) >= 600)InputBuffer.clear(); break;

        }
        //if(LaserStruct.isLaserHasError()) SendRequestReset();
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
    this->SendRequestReset();
    timerGetLaserState.start(5000);
}



void LaserPilotInterfaceClass::slotSendStateRequest()
{
    this->SendRequestGetLaserParam();
    //this->SendRequestGetChillerParam();
}

std::tuple<quint16,quint16> COMMAND_REQUEST::GetHeader(QByteArray array)
{
    QDataStream in(&array,QIODevice::ReadOnly);
                in.setByteOrder(QDataStream::LittleEndian);
    quint16 HeaderCode;
    quint16 ExecutionCode;
    quint16 DataSize;
    in >> HeaderCode >> ExecutionCode >> DataSize;
    //qDebug() << "LASER: MESSAGE: " << HeaderCode << "SIZE :" << DataSize;
    return {HeaderCode,DataSize};
}

void COMMAND_REQUEST::LoadData(QByteArray& Array)
{
    QDataStream in(&Array,QIODevice::ReadOnly);
                in.setByteOrder(QDataStream::LittleEndian);
                in >> *this;
    Array.remove(0,sizeof(COMMAND_REQUEST) + 2); //additional 2 bytes CRC at END
    qDebug() << "COMMAND REQUEST:"<< COMMAND_CODE << " RESULT: " <<Qt::hex << EXECUTION_CODE;
    //qDebug() << "LOAD DATA TO : " << typeid(this).name() << " REMOVE: " << sizeof(COMMAND_REQUEST) + 2;
    LaserMessageCount++;
}
void LASER_MESSAGE::LoadData(QByteArray& Array)
{
    auto [Code,DataSize] = GetHeader(Array); if(CODE_LASER_DATA != Code) return;

    QDataStream in(&Array,QIODevice::ReadOnly);
                in.setByteOrder(QDataStream::LittleEndian);
                in >> *(COMMAND_REQUEST*)this;
                //in.readRawData((char*)(&DATA),DataSize);
                in >> DATA;
                in >> CRC;

                auto ControlCRC = GetCRC((unsigned char*)Array.data(),DataSize+8);
                qDebug() << "CRC : "<< CRC << " CONTROL: " << ControlCRC;
    Array.remove(0,sizeof(LASER_MESSAGE)); //additional 2 bytes CRC at END

    //qDebug() << "LOAD DATA TO : " << typeid(this).name() << " REMOVE: " << sizeof(LASER_MESSAGE);
    this->DATA.PrintStruct();
    LaserMessageCount++;
}

void LASER_PARAM_STRUCT::PrintStruct()
{
qDebug() << "======================";
qDebug() << "LASER STATE:";
//qDebug() << "TempMax   " << this->TempMax;
//qDebug() << "TempMean  " << this->TempMean;
//qDebug() << "TempMin   " << this->TempMin;
//qDebug() << "Alarms1   "<<Qt::bin << this->Alarms1;
//qDebug() << "Alarms2   "<<Qt::bin << this->Alarms2;
//qDebug() << "Status2   "<<Qt::bin << this->Status2;
//qDebug() << "Mod min temp " << this->ModuleMinTemp;
//qDebug() << "Mod max temp " << this->ModuleMaxTemp;
qDebug() << "STATUS1:   "<< Qt::bin << this->Status1;


QString Status = "[ ";
if(Status1&LASER_EMISSION_SLOW_ON) qDebug() << " EMISSION SLOW ON";
if(Status1&LASER_GUID_ON) Status = Status + " GUID ON |";
if(Status1&LASER_LASER_READY_ON) Status = Status + " LASER READY |";
if(Status1&LASER_ANALOG_ON) Status = Status + " ANALOG ON |";
if(Status1&LASER_EMISSION_ENABLED_ON) Status = Status + " EMISSION ENABLED ON |";
if(Status1&LASER_CHILLER_READY_ON) Status = Status + " CHILLER READY |";
if(Status1&LASER_MAIN_POWER_ON) Status = Status + " MAIN POWER ON |";
if(Status1&LASER_HAS_ERROR_ON) Status = Status + " LASER HAS ERROR |";
if(Status1&LASER_ROBOT_SWITCH_ON) Status = Status + " ROBOT SWITCH ON |";
if(Status1&LASER_EMISSION_SIGNAL) Status = Status + " EMISSION SIGNAL ON |";
if(Status1&LASER_SHUTDOWN_STATE) Status = Status + " SHUTDOWN STATE |";
if(Status1&LASER_STANDBY_STATE) Status = Status + " STANDBYSTATE";
qDebug() << Status << " ]";
qDebug() << "======================";
}

//#define LASER_EMISSION_SLOW_ON     0x00000001
//#define LASER_GUID_ON              0x00000002
//#define LASER_LASER_READY_ON       0x00000008
//#define LASER_ANALOG_ON            0x00000040
//#define LASER_EMISSION_ENABLED_ON  0x00000080
//#define LASER_CHILLER_READY_ON     0x00000400
//#define LASER_MAIN_POWER_ON        0x00001000
//#define LASER_HAS_ERROR_ON         0x00002000
//#define LASER_ROBOT_SWITCH_ON      0x00200000
//#define LASER_EMISSION_SIGNAL      0x00800000
//#define LASER_SHUTDOWN_STATE       0x10000000
//#define LASER_STANDBY_STATE        0x40000000
void operator>>(QDataStream& in_stream, LASER_PARAM_STRUCT& Param)
{
in_stream >>Param.Version;
in_stream >>Param.SetCurrent;
in_stream >>Param.SetPower;
in_stream >>Param.OutputPower;
in_stream >>Param.TempMean;
in_stream >>Param.TempMin;
in_stream >>Param.TempMax;
in_stream >>Param.ModuleMinTemp;
in_stream >>Param.ModuleMaxTemp;
in_stream >>Param.WaterFloat;
in_stream >>Param.Status1;
in_stream >>Param.Status2;
in_stream >>Param.Alarms1;
in_stream >>Param.Alarms2;
in_stream >>Param.Warnings1;
in_stream >>Param.Warnings2;
in_stream >>Param.ModulesUnconnected;
in_stream >>Param.ModulesDisabled;
in_stream >>Param.ModulesReserved;
in_stream >>Param.ModulesFatalDisabled;
in_stream >>Param.ModulesError;
in_stream >>Param.ModulesInterlock;
in_stream >>Param.HardwiringInputs;
in_stream >>Param.HardwiringOutput;
in_stream >>Param.RiseTime;
in_stream >>Param.Fall_Time;
in_stream >>Param.ProgramNumber;
in_stream >>Param.ProgramEndCode;
in_stream >>Param.ProgramErrorLine;
in_stream >>Param.VoltControlValue;
in_stream >>Param.ePC_Status;
}

bool LASER_MESSAGE::isLaserHasError()   { return DATA.Status1&LASER_HAS_ERROR_ON; }
bool LASER_MESSAGE::isLaserGuidOn()     { return DATA.Status1&LASER_GUID_ON; }
bool LASER_MESSAGE::isLaserPowerOn()    { return DATA.Status1&LASER_EMISSION_ENABLED_ON + 
                                                 DATA.Status1&LASER_EMISSION_SLOW_ON + 
                                                 DATA.Status1&LASER_EMISSION_SIGNAL; }
bool LASER_MESSAGE::isLaserReady()      { return DATA.Status1&LASER_LASER_READY_ON; }
bool LASER_MESSAGE::isPowerOn()         { return DATA.Status1&LASER_MAIN_POWER_ON; }
bool LASER_MESSAGE::isChillerWork()     { return 0; }
bool LASER_MESSAGE::isAnalogControlOn() { return DATA.Status1&LASER_ANALOG_ON; }
bool LASER_MESSAGE::isLaserStandby()    { return DATA.Status1&LASER_STANDBY_STATE; }
bool LASER_MESSAGE::isLaserShutDown()   { return DATA.Status1&LASER_SHUTDOWN_STATE;}