#pragma once
#include "DataDeviceStructureCommon.h"


class DataLaserStruct : public DataDeviceStructure
{
public:
	int CurrentPower;
	int CurrentTemperature;
	bool ChillerOn = false; 
};