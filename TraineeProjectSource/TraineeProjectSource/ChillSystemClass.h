#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "DataTemperatureStructure.h"


class ChillSystemClass
{
public:
	void SlotTurnOnOff(bool OnOff);
	DataTemperatureStructure GetState();
private:
	typeblocksenum TypeBlock = typeblocksenum::ChillControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
public:
	
};