#pragma once
#include "DataLaserStruct.h"


class CommonLaserInterfaceClass : public QObject
{
	Q_OBJECT
public:
	stateblocksenum LaserState = BlockDisable;
	typeblocksenum TypeBlock = LasersBlock;
	int NumberLaser = 1;

	virtual DataLaserStruct GetState();
	virtual void TurnLaserBeamOnOff(bool OnOff);
	bool IsOnOff(){ return OnOff; };
	bool OnOff = false;

signals:
	void SignalToLaser(bool OnOff);
};



