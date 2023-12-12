#pragma once
#include "DataDeviceStructureCommon.h"


class DataLaserStruct : public DataDeviceStructure
{
public:
    bool LaserGuid1;
    bool LaserGuid2;
    bool LaserGuid3;
    bool LaserPower1;
    bool LaserPower2;
    bool LaserPower3;
    bool LaserPointer;

	int LaserPowerTemp1;
	int LaserPowerTemp2;
	int LaserPowerTemp3;
	bool LaserPowerChiller1 = false; 
	bool LaserPowerChiller2 = false; 
	bool LaserPowerChiller3 = false; 
};