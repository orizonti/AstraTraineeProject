#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
//#include "CommonHeaders.h"
#include <QString>
#include <QPair>
#include <QImage>


class DataDeviceStructure
{
public:
	int NumberBlock;
	typeblocksenum TypeBlock;
	stateblocksenum State = BlockDisable;
	QString DeviceInfoString;
};