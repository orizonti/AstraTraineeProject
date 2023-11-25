#include "CommonHeaders.h"
#include "LaserCommonInterface.h"



DataLaserStruct LaserCommonInterface::GetState()
{
	DataLaserStruct DataLaser;
	DataLaser.TypeBlock = this->TypeBlock;
	DataLaser.State = this->LaserState;
	DataLaser.NumberBlock = this->NumberLaser;
	return DataLaser;
}


void LaserCommonInterface::TurnLaserBeamOnOff(bool OnOff)
{
	qDebug() << "ON OFF LASER METHOD EMPTY";
}



