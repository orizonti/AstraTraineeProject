#pragma once
#include "DataToDisplayStructure.h"
#include "stateblocksenum.h"
#include <QPair>

struct EngineData
{
	QPair<double, double> LastPosChannel;
	QPair<int, int> DesirePosition;
	QPair<double, double> MinPosition;
	QPair<double, double> MaxPosition;
	stateblocksenum State = BlockDisable;
};

class DataEngineStructure : public DataToDisplayStructure
{
public:

	DataEngineStructure(){};
	~DataEngineStructure(){};

	EngineData Engine1;
	EngineData Engine2;
	EngineData Engine3;

};
