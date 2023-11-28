#include "CommonHeaders.h"
#include "LaserPilotInterface.h"

#define TAG "[ LASER PILOT ]" 

LaserPilotInterface::LaserPilotInterface(LaserPowerInterface* PowerLaser)
{
    //qDebug() << TAG << "QT MESSAGE WARN: " << QT_NO_WARNING_OUTPUT;
    socketLaser = PowerLaser->socketLaser;
    this->NumberLaser = PowerLaser->NumberLaser + 10;
}

LaserPilotInterface::~LaserPilotInterface()
{
}


void LaserPilotInterface::TurnLaserBeamOnOff(bool OnOff)
{
	 if(this->OnOff != OnOff) this->OnOff = OnOff; else return;

     GUID_COMMAND_STRUCT Command; Command.NUMBER_CHANNEL = 0;

     if(OnOff)  Command.ON_OFF = 1;
     if(!OnOff) Command.ON_OFF = 0;

     Command.CRC = GetCRC((unsigned char*)&Command,Command.DATA_SIZE +8);
     QByteArray ArrayCommand((const char*)&Command,Command.DATA_SIZE + 10);

     if (socketLaser->state() == 3) { socketLaser->write(ArrayCommand); }

	 if(OnOff)   this->LaserState = stateblocksenum::BlockAtWork;
	 if(!OnOff)  this->LaserState = stateblocksenum::BlockDisable;

     LaserCommonInterface::TurnLaserBeamOnOff(OnOff);
}

DataLaserStruct LaserPilotInterface::GetState()
{
	return	LaserCommonInterface::GetState();
}


void LaserPilotInterface::SlotSetLaserMessage(LASER_MESSAGE LASER_PARAM)
{
    if(!LASER_PARAM.isLaserGuidOn() && LaserState == BlockAtWork) this->LaserState = BlockFault;
}





