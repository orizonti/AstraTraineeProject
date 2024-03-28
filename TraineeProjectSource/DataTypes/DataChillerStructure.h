#pragma once
#include "DataDeviceStructureCommon.h"
#include "stateblocksenum.h"
#include <QDebug>


class DataChillerStructure : public DataDeviceStructure
{
public:
int NUMBER_MESSAGE = 0;
float TEMP_CHILL1 = 0;
float TEMP_CHILL2 = 0;
int WATER_FLOW = 0;

void PUT_WATER_PARAM(int TEMP1, int TEMP1_DEC, int TEMP2, int TEMP2_DEC, int FLOW)
{
    float DEC_VAL = TEMP1_DEC; while(DEC_VAL > 1) DEC_VAL /= 10;
    TEMP_CHILL1 =  TEMP1 + DEC_VAL;
          DEC_VAL = TEMP2_DEC; while(DEC_VAL > 1) DEC_VAL /= 10;
    TEMP_CHILL2 =  TEMP2 + DEC_VAL;
    qDebug() << "CHILL WATER PARAM: " << TEMP_CHILL1 << TEMP_CHILL2;

    NUMBER_MESSAGE++; }

void PUT_MESSAGE(QString Message) { DeviceInfoString = Message;  NUMBER_MESSAGE++;}
void SET_STATE(stateblocksenum new_state) {State = new_state; NUMBER_MESSAGE++;}
bool operator==(DataChillerStructure& Object){ return this->NUMBER_MESSAGE == Object.NUMBER_MESSAGE;}

};

struct CommandChillerStructure
{
    int WORK_TEMP = 20;
   bool ON_OFF    = false;
   QString PORT;
};