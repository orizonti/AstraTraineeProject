#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "DataToDisplayStructure.h"
#include <qtcpserver.h>

class RemoteControlClass
{
public:
	DataToDisplayStructure GetState();
	typeblocksenum TypeBlock = typeblocksenum::RemoteControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
private:
	QTcpServer ServerForRemoteMachine;
};