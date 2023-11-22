#pragma once
#include "DataDeviceStructureCommon.h"


class DataLaserStruct : public CommonDeviceStructure
{
public:

	int CurrentFrequency;
	int CurrentPower;
	int CurrentTemperature;
};