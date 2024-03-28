#include "chillerinterface.h"
#include "stateblocksenum.h"
#include "typeblocksenum.h"

ChillerInterface::~ChillerInterface()
{
}

void ChillerInterface::ResetComPort(QString PortName)
{
 if(Port->isOpen() && Port->portName() == PortName ) return;
 if(Port->isOpen()) Port->close();
 
 this->Port->setPortName(PortName); this->Port->open(QSerialPort::ReadWrite);
 if(this->Port->isOpen()) ChillerState.PUT_MESSAGE(PortName + QString(" - OPENED"));
}

ChillerInterface::ChillerInterface()
{

 this->Port = new QSerialPort;

 Port->setBaudRate(115200); Port->setDataBits(QSerialPort::Data8);
 Port->setParity(QSerialPort::NoParity); Port->setStopBits(QSerialPort::OneStop);
 Port->setFlowControl(QSerialPort::NoFlowControl);

 QObject::connect(Port,SIGNAL(readyRead()),this,SLOT(SlotReadData()));
 QObject::connect(&TimerResetController,SIGNAL( timeout()) ,this, SLOT(SlotResetController() ));
 QObject::connect(&TimerDataRec,SIGNAL(timeout()),this,SLOT(SlotControllerDataRequest()));

 TimerResetController.start(1000*60*10);

 FRAME_NUMBER = 15; SCAN_NUMBER = 1; TemperatureLevel = 20;
 //DataFromChiller.clear(); DataFromChiller << 22 <<2 << 19 <<2 << 144;
 ChillerState.TypeBlock = typeblocksenum::ChillControlBlock;
}


void ChillerInterface::SlotReadData()
{
InputDataBuffer.append(Port->readAll());

if(InputDataBuffer.size() >= 6)
{
  HEADER_STRUCT *HEADER = (HEADER_STRUCT*)InputDataBuffer.data();

 if(InputDataBuffer.size() >= HEADER->DATA_SIZE + 6)
 {
    DataToProcess = InputDataBuffer.mid(6,HEADER->DATA_SIZE);

    if(HEADER->MESSAGE_TYPE == MESSAGE) ChillerState.PUT_MESSAGE(QString(DataToProcess));

    if(HEADER->MESSAGE_TYPE == MESSAGE)
    {
      ChillerState.SET_STATE(stateblocksenum::BlockReadyToWork);
      if(QString(DataToProcess).contains(QString("RESET"))) { QThread::sleep(2); this->SlotStartChilling(); }
    }

    if(HEADER->MESSAGE_TYPE == GET_ALL_PACKET)
    {
      //IF NO ERROR AT CHILLER WORK DATA REQUEST CurrentRecord MUST BE NULL
      ChillerState.SET_STATE(stateblocksenum::BlockAtWork);
      if(this->DataRequestCurrentRecord > 0) DataRequestCurrentRecord--;
    }

    InputDataBuffer.remove(0,HEADER->DATA_SIZE +6);
 }
}
}

void ChillerInterface::SlotResetController()
{
    UART_PACKET_COMMAND Command;
                        Command.HEADER.IDENT = PC_HEADER_IDENT;
                        Command.HEADER.MESSAGE_TYPE = RESET_MC;
                        Command.HEADER.DATA_SIZE = 8;
    ChillerState.PUT_MESSAGE(QString("TO CHILLER: RESET"));
    this->Port->write((const char*)&Command,16);
    TimerDataRec.stop();
    ChillerState.SET_STATE(stateblocksenum::BlockFault);
}

void ChillerInterface::SlotStartChilling()
{
    UART_PACKET_COMMAND Command;
                        Command.HEADER.IDENT = PC_HEADER_IDENT;
                        Command.HEADER.MESSAGE_TYPE = SET_COMMAND;
                        Command.HEADER.DATA_SIZE = 8;

    ChillerState.PUT_MESSAGE(QString("TO CHILLER: TEMP - %1 MODE - %2").arg(TemperatureLevel).arg(this->MODE));
    ChillerState.SET_STATE(stateblocksenum::BlockAtInitializaiton);
    Command.Data[0] = 1 ;
    Command.Data[1] = this->MODE;
    Command.Data[2] = TemperatureLevel;
    Command.Data[3] = TemperatureLevel/256;
    Command.Data[4] = SCAN_NUMBER;//SCAN_NUMBER;//60
    Command.Data[5] = FLAG_CHILLER_WORK;
    Command.Data[6] = FRAME_NUMBER ;
    Command.Data[7] = FRAME_NUMBER/256 ;

    if(this->Port->isOpen())
    {
        ChillerState.PUT_MESSAGE(QString("TO CHILLER: TEMP - %1 MODE - %2").arg(TemperatureLevel).arg(this->MODE));
    this->Port->write((const char*)&Command,16);
    }
    else
    emit ChillerState.PUT_MESSAGE("LOCAL: PORT IS NOT OPEN");

TimerDataRec.start(3000);
}

void ChillerInterface::SlotControllerDataRequest()
{
    UART_PACKET_COMMAND Command;
                        Command.HEADER.IDENT = PC_HEADER_IDENT;
                        Command.HEADER.MESSAGE_TYPE = GET_ALL_PACKET;
                        Command.HEADER.DATA_SIZE = 0;

    std::fill(Command.Data,Command.Data+8,0);

    this->DataRequestCurrentRecord++;
    if(this->DataRequestCurrentRecord >= 15) //IF NO ERROR AT CHILLER WORK DATA REQUEST CurrentRecord MUST BE NULL
    {
        this->DataRequestCurrentRecord = 0;
        this->SlotResetController();
    }

    if(this->Port->isOpen()) this->Port->write((const char*)&Command,16);
}


void ChillerInterface::DataToStore()
{
QDataStream in(DataToProcess);
in.setByteOrder(QDataStream::LittleEndian);

double ChillerTemperature = 0; double ObjectTemperature = 0;

qint16 Temperature1 = 0; qint16 Temperature2 = 0; qint16 iexpense = 0; qint16 Flow = 0;
int iTemperature,iPrec, iCelsius, iPrec2;

iPrec = 0; iCelsius = 0; iPrec2 = 0;

if(MODE == 15) { in >> Temperature1; in >> iexpense; in >> Temperature2; in >> Flow; }

    if(MODE == 13)
    {
    in >> Flow; in >> Temperature1; in >> Temperature2; in >> iexpense;
    iTemperature =Temperature1;
    iPrec = Temperature1 & 15;
    iPrec = (iPrec<<1) + (iPrec<<3);//*10
    iPrec = iPrec>>4;// /16

    iTemperature = iTemperature/16;

    iCelsius = Temperature2;
    iPrec2 = Temperature2 & 15;
    iPrec2 = iCelsius & 15;
    iPrec2 = (iPrec2<<1) + (iPrec2<<3);//*10
    iPrec2 = iPrec2>>4;// /16
    iCelsius =  iCelsius/16;

    }
//==============================================
ChillerTemperature = iTemperature + (double)iPrec/10.0;
ObjectTemperature = iCelsius + (double)iPrec2/10.0;

ChillerState.PUT_WATER_PARAM(iTemperature,iPrec, iCelsius,iPrec2,iexpense);
}

void ChillerInterface::SlotTurnOnOff(bool OnOff)
{
    if(OnOff)
    SlotStartChilling();
    else
    SlotResetController();
}

void ChillerInterface::SlotSetWorkTemperature(int Temperature)
{
 this->TemperatureLevel = Temperature;
 ChillerState.PUT_MESSAGE(QString("SET WORK TEMP: %1").arg(Temperature));
}