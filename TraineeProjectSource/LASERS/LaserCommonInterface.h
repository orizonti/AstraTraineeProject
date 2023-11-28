#pragma once
#include "DataLaserStruct.h"
#include "QObject"

enum LASERS { POWER_LASER1 = 1, POWER_LASER2 = 2, POWER_LASER3 = 3, POINTER_LASER = 4, GUID_LASER1 = 11, GUID_LASER2 = 12, GUID_LASER3 = 13}; 
enum LASER_GROUPS {POWER_GROUP = 1, GUID_GROUP, POINTER_GROUP};

class LASER_GROUP
{
	public:
	LASER_GROUP(int Number);
	int NumberLaser;
	bool operator==(LASER_GROUPS TEST_GROUP);
	
	QString NAME();
};

class LaserCommonInterface : public QObject
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



