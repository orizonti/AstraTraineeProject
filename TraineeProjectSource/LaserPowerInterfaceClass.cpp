
#include "stdafx.h"
#include "LaserPowerInterfaceClass.h"

LaserPowerInterfaceClass::LaserPowerInterfaceClass()
{
}





DataLaserStruct GetState()
{
	DataLaserStruct laserData;
	laserData.State = BlockReadyToWork;
	laserData.CurrentFrequency = 100;
	laserData.CurrentPower = 500;
	laserData.CurrentTemperature = 20;
	return laserData;
}

void LaserPowerInterfaceClass::TurnLaserBeamOnOff(bool OnOff)
{

}

DataLaserStruct LaserPowerInterfaceClass::GetState()
{
	return CommonLaserInterfaceClass::GetState();
}

void LaserPowerInterfaceClass::TurnPowerLaserBeamOff()
{
}

void LaserPowerInterfaceClass::TurnPowerLaserBeamOn()
{
}

