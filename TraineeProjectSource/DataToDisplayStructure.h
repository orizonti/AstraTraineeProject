#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include <QString>


class DataToDisplayStructure
{
public:
	int NumberBlock;
	typeblocksenum TypeBlock;
	stateblocksenum State =BlockDisable;
	QString CycleInfoString;
};