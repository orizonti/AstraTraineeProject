#pragma once
#include "DataDeviceStructureCommon.h"


class DataChillerStructure : public DataDeviceStructure
{
public:
    quint8  Temp1;
    quint16 Presure1;
    quint8  Humidity1;
};