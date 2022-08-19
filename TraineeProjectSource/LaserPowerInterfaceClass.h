#pragma once
#include "typeblocksenum.h"
#include "LaserPilotInterfaceClass.h"
#include "stateblocksenum.h"
#include "CommonLaserInterfaceClass.h"
#include <memory> 

class LaserPowerInterfaceClass : public CommonLaserInterfaceClass
{
public:
	LaserPowerInterfaceClass();
	void SetFrequency (int Frequency);
	void TurnLaserBeamOnOff(bool OnOff);
	DataLaserStruct GetState();

private:
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	unsigned long LaserHandle;
	void TurnPowerLaserBeamOff();
	void TurnPowerLaserBeamOn();
};