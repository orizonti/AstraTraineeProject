#include "stdafx.h"
#include "LaserControlClass.h"

LaserControlClass::LaserControlClass()
{
    	
	LPower = new LaserPowerInterfaceClass;
	LPilot1 = new LaserPilotInterfaceClass("192.168.101.1", 5100);
	LPilot2 = new LaserPilotInterfaceClass("192.168.102.1", 5100);
	LPilot3 = new LaserPilotInterfaceClass("192.168.103.1", 5100);

	LPilot1->NumberLaser = 1;
	LPilot2->NumberLaser = 2;
	LPilot3->NumberLaser = 3;
	 LaserPointer = new LaserPointerInterfaceClass;
	 LaserPointer->NumberLaser = 4;

	 Lasers.append(LPilot2);
	 Lasers.append(LPilot1);
	 Lasers.append(LPilot3);
	 Lasers.append(LaserPointer);

	 TimerToIterateLasers.setInterval(12000);
	 QObject::connect(&TimerToIterateLasers, SIGNAL(timeout()), this, SLOT(IterateWorkingLaser()));
	 QObject::connect(this, SIGNAL(SignalTurnLaser1(bool)), LPilot1, SLOT(TurnLaserBeamOnOff(bool)));
	 QObject::connect(this, SIGNAL(SignalTurnLaser2(bool)), LPilot2, SLOT(TurnLaserBeamOnOff(bool)));
	 QObject::connect(this, SIGNAL(SignalTurnLaser3(bool)), LPilot3, SLOT(TurnLaserBeamOnOff(bool)));
}

void LaserControlClass::SlotSwitchFireBeam(bool OnOff)
{
		LPower->TurnLaserBeamOnOff(OnOff);
}

void LaserControlClass::SlotSwitchPointerBeam(bool OnOff)
{
    LaserPointer->TurnLaserBeamOnOff(OnOff);
}

void LaserControlClass::SlotSwitchPilotBeam(int Channel, bool OnOff)
{
		switch (Channel) 
		{
		case 1:
				//LPilot1->TurnLaserBeamOnOff(OnOff);
			emit SignalTurnLaser1(OnOff);
			break;
		case 2:
				//LPilot2->TurnLaserBeamOnOff(OnOff);
			emit SignalTurnLaser2(OnOff);
			break;
		case 3:
				//LPilot3->TurnLaserBeamOnOff(OnOff);
			emit SignalTurnLaser3(OnOff);
			break;
		}
}


QVector<DataLaserStruct> LaserControlClass::GetLasersState()
{
	QVector<DataLaserStruct> laserDataVector;
	laserDataVector.push_back(this->LaserPointer->GetState());
	return laserDataVector;	
}



void LaserControlClass::IterateWorkingLaser()
{
	this->SlotSwitchAllLasers(false);
	Lasers[LaserIterateCounter]->TurnLaserBeamOnOff(true);
	qDebug() << "ITERATE LASERS NUMBER - " << LaserIterateCounter;

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
	this->LPower->TurnLaserBeamOnOff(OnOff);
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