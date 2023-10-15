#pragma once
#include "DataLaserStruct.h"
#include "QObject"


class CommonLaserInterfaceClass : public QObject
{
	Q_OBJECT
public:
	stateblocksenum LaserState = BlockDisable;
	typeblocksenum TypeBlock = LasersBlock;
	int NumberLaser = 1;

	virtual DataLaserStruct GetState();
	bool IsOnOff(){ return OnOff; };
	bool OnOff = false;


public slots:
    virtual void TurnLaserBeamOnOff(bool OnOff);
signals:
	void SignalToLaser(bool OnOff);
};



