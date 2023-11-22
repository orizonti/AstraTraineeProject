#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "DataChillerStructure.h"


class ChillSystemClass
{
public:
	void SlotTurnOnOff(bool OnOff);
	DataChillerStructure GetState();
private:
	typeblocksenum TypeBlock = typeblocksenum::ChillControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
public:
	
};