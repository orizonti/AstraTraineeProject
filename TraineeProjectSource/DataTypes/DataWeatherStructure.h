#pragma once
#include "DataDeviceStructureCommon.h"


class DataWeatherStructure : public DataDeviceStructure
{
public:
    quint8  Temp1;
    quint16 Presure1;
    quint8  Humidity1;

    quint8  Temp2;
    quint16 Presure2;
    quint8  Humidity2;
};