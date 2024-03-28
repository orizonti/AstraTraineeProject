#include "CommonHeaders.h"
#include "RemoteControlInterface.h"
#include <qdebug.h>
#include "LaserCommonInterface.h"
#include "RemoteControlProtocol.h"
#include "UDPEngineInterface.h"
#define TAG "[ REMOTE CTRL]" 

#include "RemoteAimingWindowControl.h"
#include "RemoteWindowControl.h"

RemoteAimingInterface::RemoteAimingInterface()
{

    RemoteToBaseTransform.LoadRotationFromFile("/home/broms/DEVELOPMENT/DATA/TrainerData/RotateMatrixOutput1.txt");
    RemoteToBaseTransform.Inverse();

    ErrorPortWindowControl = new RemoteAimingWindowControl;
    ErrorPortWindowControl->SetHandleControl(this);
}

RemoteAimingInterface::~RemoteAimingInterface()
{
    ErrorPortWindowControl->close();
    delete ErrorPortWindowControl;
}


QPair<double, double> RemoteAimingInterface::GetCoord() { return RemoteAimingCoord; }

void RemoteAimingInterface::SetCoord(QPair<double, double> Coord)
{
    RemoteAimingCoord = Coord;
    if(work_mode == aiming_mode)
    RemoteAimingCoord >> RemoteToBaseTransform >> RemoteAimingCoord;
}

bool RemoteAimingInterface::isValid() { return RemoteToBaseTransform.isValid(); }
void RemoteAimingInterface::SlotResetRotationBlocks() { RemoteToBaseTransform.Reset(); }
void RemoteAimingInterface::SlotSetActiveChannel(int Channel) { error_direction = (error_port_direction)Channel; }
void RemoteAimingInterface::SlotLoadDataFromFile(QString FileName) { }
void RemoteAimingInterface::SlotSetMode(int Mode) { work_mode = (error_port_work_modes)Mode; }

RemoteControlInterface::RemoteControlInterface(HandleControlInterface* Interface, QObject* parent) : QObject(parent)
{
DeviceControl = Interface;
UDPInterface = new UDPEngineInterface("192.168.1.104","172.27.76.53",7575,7575);
DisplayRemoteCommand = new RemoteWindowControl;

QObject::connect(&timerSendState,SIGNAL(timeout()),this,SLOT(SlotSendStateToRemote()));
QObject::connect(this,SIGNAL(SignalNewRemoteCommand(QString)),DisplayRemoteCommand,SLOT(SlotPrintRemoteCommand(QString)));
QObject::connect(UDPInterface,SIGNAL(SignalNewMessage(KLP_CMD_TYPES)),this,SLOT(SlotPerformRemoteCommand(KLP_CMD_TYPES)));

//timerSendState.start(2000);

}

RemoteControlInterface::~RemoteControlInterface()
{
qDebug() << "DELETE REMOTE INTERFACE";
delete UDPInterface;
DisplayRemoteCommand->close();
delete DisplayRemoteCommand;
}

void RemoteControlInterface::SendExecutionReply(int Result)
{
    MessageStructEmpty Message;
                       Message.ERROR_ID = Result;
                       UDPInterface->SendCommand(Message.toByteArray());
}


void RemoteControlInterface::SlotPerformRemoteCommand(KLP_CMD_TYPES CMD_TYPE)
{
   emit SignalNewRemoteCommand(QString("GET: ") + KLP_CMD_GROUP(CMD_TYPE) + " " + UDPInterface->PrintCommand(CMD_TYPE));
   switch(CMD_TYPE)
   {
       case CMD_CAMERA:
       {
          DeviceControl->TurnOnOffCamera(UDPInterface->CameraControl.DATA.OnOff);
          SendExecutionReply((int)ERROR_NO_ERRORS);
       }
       break;
       case CMD_POINTLASER:
       {
          DeviceControl->TurnOnOffLaser(POINTER_LASER,UDPInterface->LaserPointerCmd.DATA.OnOff);
          SendExecutionReply((int)ERROR_NO_ERRORS);
       }
       break;
       case CMD_PILOTLASER:
       {
          DeviceControl->TurnOnOffLaser(GUID_LASER1,UDPInterface->LaserGuidCmd.DATA.OnOff);
          DeviceControl->TurnOnOffLaser(GUID_LASER2,UDPInterface->LaserGuidCmd.DATA.OnOff);
          DeviceControl->TurnOnOffLaser(GUID_LASER3,UDPInterface->LaserGuidCmd.DATA.OnOff);
          SendExecutionReply((int)ERROR_NO_ERRORS);
       }
       case CMD_POWERLASER:
       {
          auto COMMAND = UDPInterface->LaserPowerCmd.DATA;
          if(COMMAND.Channel == 1)DeviceControl->TurnOnOffLaser(POWER_LASER1,COMMAND.OnOff);
          if(COMMAND.Channel == 2)DeviceControl->TurnOnOffLaser(POWER_LASER2,COMMAND.OnOff);
          if(COMMAND.Channel == 3)DeviceControl->TurnOnOffLaser(POWER_LASER3,COMMAND.OnOff);
          if(COMMAND.Channel == 0)
          {
             DeviceControl->TurnOnOffLaser(POWER_LASER1,COMMAND.OnOff);
             DeviceControl->TurnOnOffLaser(POWER_LASER2,COMMAND.OnOff);
             DeviceControl->TurnOnOffLaser(POWER_LASER3,COMMAND.OnOff);
          }
          SendExecutionReply((int)ERROR_NO_ERRORS);
       }
       case CMD_AIMING:
       {
            auto COMMAND = UDPInterface->AimingControl.DATA;
            QPair<double,double>(COMMAND.X, COMMAND.Y) >> AimingPort;
       }
       break;
   }
}

void RemoteControlInterface::SlotSendStateToRemote()
{
    qDebug() << "[REMOTE ] SEND STATE TO REMOTE"; 
    UDPInterface->SendCommand(this->DEVICE_STATE.toByteArray());
}

void operator>>(DataDeviceStructure& DeviceData, RemoteControlInterface& RemoteControl)
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

void operator>>(const DataLaserStruct& LaserData, RemoteControlInterface& RemoteControl)
{
   RemoteControl.DEVICE_STATE.DATA.GuidLaserState.Channel1 = LaserData.LaserGuid1;
   RemoteControl.DEVICE_STATE.DATA.GuidLaserState.Channel2 = LaserData.LaserGuid2;
   RemoteControl.DEVICE_STATE.DATA.GuidLaserState.Channel3 = LaserData.LaserGuid3;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserState.Channel1 = LaserData.LaserPower1;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserState.Channel2 = LaserData.LaserPower2;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserState.Channel3 = LaserData.LaserPower3;
   RemoteControl.DEVICE_STATE.DATA.PointerLaserState = LaserData.LaserPointer;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserTemp1 = LaserData.LaserPowerTemp1;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserTemp2 = LaserData.LaserPowerTemp2;
   RemoteControl.DEVICE_STATE.DATA.PowerLaserTemp3 = LaserData.LaserPowerTemp3;
}
void operator>>(const DataEngineStructure& EngineData, RemoteControlInterface& RemoteControl)
{
   RemoteControl.DEVICE_STATE.DATA.EnginesState.Channel1 = 1;
   RemoteControl.DEVICE_STATE.DATA.EnginesState.Channel2 = 1;
   RemoteControl.DEVICE_STATE.DATA.EnginesState.Channel3 = 1;
}
void operator>>(const DataCamerasStructure& CamerasData, RemoteControlInterface& RemoteControl)
{
   RemoteControl.DEVICE_STATE.DATA.CameraState = 1;
}
void operator>>(const DataWeatherStructure& WeatherData, RemoteControlInterface& RemoteControl)
{
   RemoteControl.DEVICE_STATE.DATA.Moisture =    WeatherData.Humidity1;
   RemoteControl.DEVICE_STATE.DATA.Temperature = WeatherData.Temp1;
   RemoteControl.DEVICE_STATE.DATA.Pressure =    WeatherData.Presure1;

}
void operator>>(const DataChillerStructure& ChillerData, RemoteControlInterface& RemoteControl)
{
   RemoteControl.DEVICE_STATE.DATA.Chiller = 1; 
   RemoteControl.DEVICE_STATE.DATA.ChillerTemp1 = ChillerData.TEMP_CHILL1; 
   RemoteControl.DEVICE_STATE.DATA.ChillerTemp2 = ChillerData.TEMP_CHILL2; 
}