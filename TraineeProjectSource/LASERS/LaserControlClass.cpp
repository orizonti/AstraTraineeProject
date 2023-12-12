#include "CommonHeaders.h"
#include "LaserControlClass.h"

#include "LaserPilotInterface.h"
#include "LaserPowerInterface.h"
#include "LaserPointerInterface.h"
    

#define TAG "[ LASER CTRL  ]" 

LaserControlClass::LaserControlClass()
{
	qDebug() << TAG << "====================================";
    qDebug() << TAG << "                       LASERS CREATE";	
	LPower1 = new LaserPowerInterface("192.168.101.1", 5100);
	LPower2 = new LaserPowerInterface("192.168.102.1", 5100);
	LPower3 = new LaserPowerInterface("192.168.103.1", 5100);
	LPilot1 = new LaserPilotInterface(dynamic_cast<LaserPowerInterface*>(LPower1));
	LPilot2 = new LaserPilotInterface(dynamic_cast<LaserPowerInterface*>(LPower2));
	LPilot3 = new LaserPilotInterface(dynamic_cast<LaserPowerInterface*>(LPower3));
	qDebug() << TAG << "====================================";

    //LPilot1 = new LaserPointerInterface("ttyUSB0");
    //LPilot2 = new LaserPointerInterface(*dynamic_cast<LaserPointerInterface*>(LPilot1));
    //LPilot3 = new LaserPointerInterface(*dynamic_cast<LaserPointerInterface*>(LPilot1));

    LaserPointer = new LaserPointerInterface("ttyXRUSB0");

	LPower1->NumberLaser = 1;
	LPower2->NumberLaser = 2;
	LPower3->NumberLaser = 3;

	LPilot1->NumberLaser = 11;
	LPilot2->NumberLaser = 12;
	LPilot3->NumberLaser = 13;
	LaserPointer->NumberLaser = 4;

     Lasers.append(LaserPointer);
	 Lasers.append(LPilot2);
	 Lasers.append(LPilot1);
	 Lasers.append(LPilot3);

	 TimerToIterateLasers.setInterval(12000);
	 QObject::connect(&TimerToIterateLasers, SIGNAL(timeout()), this, SLOT(IterateWorkingLaser()));
	 QObject::connect(this, SIGNAL(SignalTurnLaser1(bool)), LPilot1, SLOT(TurnLaserBeamOnOff(bool)));
	 QObject::connect(this, SIGNAL(SignalTurnLaser2(bool)), LPilot2, SLOT(TurnLaserBeamOnOff(bool)));
	 QObject::connect(this, SIGNAL(SignalTurnLaser3(bool)), LPilot3, SLOT(TurnLaserBeamOnOff(bool)));
}


LaserControlClass::~LaserControlClass()
{
}

void LaserControlClass::SlotSwitchPointerBeam(bool OnOff)
{
    LaserPointer->TurnLaserBeamOnOff(OnOff);
}

void LaserControlClass::SlotSwitchPowerBeam(int Channel, bool OnOff)
{
	switch (Channel) 
	{
	case POWER_LASER1: LPower1->TurnLaserBeamOnOff(OnOff); break;
	case POWER_LASER2: LPower2->TurnLaserBeamOnOff(OnOff); break;
	case POWER_LASER3: LPower3->TurnLaserBeamOnOff(OnOff); break;
	}
}

void LaserControlClass::SlotSwitchPilotBeam(int Channel, bool OnOff)
{
	switch (Channel) 
	{
	case GUID_LASER1: emit SignalTurnLaser1(OnOff); break;
	case GUID_LASER2: emit SignalTurnLaser2(OnOff); break;
	case GUID_LASER3: emit SignalTurnLaser3(OnOff); break;
	}
}


DataLaserStruct LaserControlClass::GetLasersState()
{
	return LasersState;	
}



void LaserControlClass::IterateWorkingLaser()
{
	this->SlotSwitchAllLasers(false);
	Lasers[LaserIterateCounter]->TurnLaserBeamOnOff(true);
	qDebug() << TAG << "ITERATE LASERS NUMBER - " << LaserIterateCounter;

	LaserIterateCounter++;
	if (LaserIterateCounter >= 4)
		LaserIterateCounter = 0;
}
void LaserControlClass::SlotSwitchAllLasers(bool OnOff)
{
	this->thread()->msleep(50);
	this->LaserPointer->TurnLaserBeamOnOff(OnOff);
	this->thread()->msleep(50);

	this->LPilot1->TurnLaserBeamOnOff(OnOff);
	this->thread()->msleep(50);
	this->LPilot2->TurnLaserBeamOnOff(OnOff);
	this->thread()->msleep(50);
	this->LPilot3->TurnLaserBeamOnOff(OnOff);

	this->thread()->msleep(50);
}

void LaserControlClass::SlotStartIterateLasers(bool OnOff)
{
	if (OnOff)
		this->TimerToIterateLasers.start();
	else
	{
		this->TimerToIterateLasers.stop();
		this->SlotSwitchAllLasers(true);
	}
}
