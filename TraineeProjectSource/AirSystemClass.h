#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "DataTemperatureStructure.h"


class AirSystemClass
{
public:
	DataTemperatureStructure GetState();
    void SlotTurnOnOff(bool OnOff);
	typeblocksenum TypeBlock = typeblocksenum::AirControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
};