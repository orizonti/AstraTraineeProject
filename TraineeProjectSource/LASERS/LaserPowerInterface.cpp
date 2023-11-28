#include "CommonHeaders.h"
#include "LaserPowerInterface.h"

int COMMAND_REQUEST::LaserMessageCount = 0;


#define TAG "[ LASER POWER ]" 
LaserPowerInterface::LaserPowerInterface(QString Address, quint16 Port)
{
	qRegisterMetaType<LASER_MESSAGE>("LASER_MESSAGE");

	socketLaser = new QTcpSocket;
	ConnectToLaser(Address, Port);
	IPLaser = Address;
    QObject::connect(&timerGetLaserState,&QTimer::timeout,this,&LaserPowerInterface::slotSendStateRequest);
}

LaserPowerInterface::~LaserPowerInterface()
{
	 socketLaser->disconnectFromHost();

   // SocketGuidLaser->abort();
   //       if(SocketGuidLaser->waitForDisconnected(4000))
            //qDebug() << TAG << "SOCKET CONNECTED - " << Address << Port;

         delete socketLaser;
}

void LaserPowerInterface::ConnectToLaser(QString Address, quint16 Port)
{

	socketLaser->abort();

	connect(socketLaser, SIGNAL(connected()),this, SLOT(slotConnected()));
	connect(socketLaser, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slotError(QAbstractSocket::SocketError)));
	connect(socketLaser, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));

      socketLaser->connectToHost(Address,Port);

}

void LaserPowerInterface::TurnLaserBeamOnOff(bool OnOff)
{
    if(this->OnOff != OnOff) this->OnOff = OnOff; else return;

    //GUID_COMMAND_STRUCT Command; Command.NUMBER_CHANNEL = 0;

    //if( OnOff) Command.ON_OFF = 1;
    //if(!OnOff) Command.ON_OFF = 0;

    //Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
    //QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);

    //if (socketLaser->state() == 3) { socketLaser->write(ArrayCommand); }

    if( OnOff) this->LaserState = stateblocksenum::BlockAtWork;
    if(!OnOff) this->LaserState = stateblocksenum::BlockDisable;

    LaserCommonInterface::TurnLaserBeamOnOff(OnOff);
}

DataLaserStruct LaserPowerInterface::GetState()
{
	return	LaserCommonInterface::GetState();
}

void LaserPowerInterface::SendRequestToUpControlStatus()
{
	     ACCESS_LEVEL_COMMAND Command;
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);

     socketLaser->write(ArrayCommand);
}

void LaserPowerInterface::SendRequestGetLaserParam()
{
	 auto Command = GET_PARAM_COMMAND(CODE_LASER_DATA);
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     //qDebug() << TAG << "GET LASER PARAM : " << ArrayCommand.toHex();
     socketLaser->write(ArrayCommand);
}
void LaserPowerInterface::SendRequestGetChillerParam()
{
	 auto Command = GET_PARAM_COMMAND(CODE_CHILLER_DATA);
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     //qDebug() << TAG << "GET CHILLER PARAM: " << ArrayCommand.toHex();
     socketLaser->write(ArrayCommand);
}
void LaserPowerInterface::SendRequestReset()
{
     qDebug() << TAG << "SEND RESET TO LASER";
	 auto Command = RESET_COMMAND();
     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);
     socketLaser->write(ArrayCommand);
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


void LaserPowerInterface::slotReadyRead()
{
  inputBuffer.append(socketLaser->readAll());
  COMMAND_REQUEST Request;
  int WaitDataSize = sizeof(COMMAND_REQUEST)+2;
  
  while (inputBuffer.size() >= WaitDataSize)
  {
  auto [COMMAND_CODE,DATA_SIZE] = COMMAND_REQUEST::GetHeader(inputBuffer);
  WaitDataSize = DATA_SIZE + sizeof(COMMAND_REQUEST) + 2;
  //qDebug() << TAG << " [" << InputBuffer.toHex() << " ]";
  //qDebug() << TAG << "INPUT BUFFER SIZE: " << InputBuffer.size() << " WAIT: " << WaitDataSize;
  
  if(DATA_SIZE == 0) Request.LoadData(inputBuffer);
  if(COMMAND_CODE == CODE_LASER_DATA) { LASER_CURRENT_PARAM.LoadData(inputBuffer); 
                                        emit SignalLaserMessage(LASER_CURRENT_PARAM); };
  
  if(COMMAND_CODE<= 2000)inputBuffer.clear(); break;
  if(COMMAND_CODE>= 2600)inputBuffer.clear(); break;
  }

  if(!LASER_CURRENT_PARAM.isLaserHasError()) this->LaserState = BlockFault;;
  if(!LASER_CURRENT_PARAM.isLaserPowerOn() && LaserState == BlockAtWork) this->LaserState = BlockAtWork;
  if(LASER_CURRENT_PARAM.isLaserPowerOn() ) this->LaserState = BlockAtWork;;
  if(LASER_CURRENT_PARAM.isLaserReady() )   this->LaserState = BlockReadyToWork;

  //if(LaserStruct.isLaserHasError()) SendRequestReset();
}
void LaserPowerInterface::slotError(QAbstractSocket::SocketError err)
{
	QString strError =
		"Error: " + (err == QAbstractSocket::HostNotFoundError ?
			"The host was not found." :
			err == QAbstractSocket::RemoteHostClosedError ?
			"The remote host is closed." :
			err == QAbstractSocket::ConnectionRefusedError ?
			"The connection was refused." :
			QString(socketLaser->errorString())
			);
}

void LaserPowerInterface::slotConnected()
{

	qDebug() << TAG << QString("CONNECTED TO HOST - %1").arg(socketLaser->peerName());
	this->SendRequestToUpControlStatus();
    this->SendRequestReset();
    timerGetLaserState.start(5000);
}



void LaserPowerInterface::slotSendStateRequest()
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
    //qDebug() << TAG << "LASER: MESSAGE: " << HeaderCode << "SIZE :" << DataSize;
    return {HeaderCode,DataSize};
}

void COMMAND_REQUEST::LoadData(QByteArray& Array)
{
    QDataStream in(&Array,QIODevice::ReadOnly);
                in.setByteOrder(QDataStream::LittleEndian);
                in >> *this;
    Array.remove(0,sizeof(COMMAND_REQUEST) + 2); //additional 2 bytes CRC at END
    qDebug() << TAG << "COMMAND REQUEST:"<< COMMAND_CODE << " RESULT: " <<Qt::hex << EXECUTION_CODE;
    //qDebug() << TAG << "LOAD DATA TO : " << typeid(this).name() << " REMOVE: " << sizeof(COMMAND_REQUEST) + 2;
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
                qDebug() << TAG << "CRC : "<< CRC << " CONTROL: " << ControlCRC;
    Array.remove(0,sizeof(LASER_MESSAGE)); //additional 2 bytes CRC at END

    //qDebug() << TAG << "LOAD DATA TO : " << typeid(this).name() << " REMOVE: " << sizeof(LASER_MESSAGE);
    this->DATA.PrintStruct();
    LaserMessageCount++;
}

void LASER_PARAM_STRUCT::PrintStruct()
{
qDebug() << TAG << "======================";
qDebug() << TAG << "LASER STATE:";
//qDebug() << TAG << "TempMax   " << this->TempMax;
//qDebug() << TAG << "TempMean  " << this->TempMean;
//qDebug() << TAG << "TempMin   " << this->TempMin;
//qDebug() << TAG << "Alarms1   "<<Qt::bin << this->Alarms1;
//qDebug() << TAG << "Alarms2   "<<Qt::bin << this->Alarms2;
//qDebug() << TAG << "Status2   "<<Qt::bin << this->Status2;
//qDebug() << TAG << "Mod min temp " << this->ModuleMinTemp;
//qDebug() << TAG << "Mod max temp " << this->ModuleMaxTemp;
qDebug() << TAG << "STATUS1:   "<< Qt::bin << this->Status1;


QString Status = "[ ";
if(Status1&LASER_EMISSION_SLOW_ON) qDebug() << TAG << " EMISSION SLOW ON";
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
qDebug() << TAG << Status << " ]";
qDebug() << TAG << "======================";
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