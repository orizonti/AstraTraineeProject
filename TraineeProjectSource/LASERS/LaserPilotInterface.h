#pragma once
#include "typeblocksenum.h"
#include "LaserPowerInterface.h"
#include "stateblocksenum.h"
#include "LaserCommonInterface.h"
#include <memory> 

class LaserPilotInterface : public LaserCommonInterface
{
	Q_OBJECT
public:
	LaserPilotInterface(LaserPowerInterface* PowerLaser);
	~LaserPilotInterface();

	DataLaserStruct GetState();
    QTcpSocket *socketLaser = 0;

private:
    COMMAND_REQUEST HEADER_DATA;

	public slots:
	    void TurnLaserBeamOnOff(bool OnOff);
		void SlotSetLaserMessage(LASER_MESSAGE LASER_PARAM);

};