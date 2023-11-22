#pragma once
#include "DataDeviceStructureCommon.h"


class DataLaserStruct : public DataDeviceStructure
{
public:

	int CurrentFrequency;
	int CurrentPower;
	int CurrentTemperature;
};