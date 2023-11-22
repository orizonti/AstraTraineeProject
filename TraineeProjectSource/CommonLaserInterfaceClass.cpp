#include "CommonHeaders.h"
#include "CommonLaserInterfaceClass.h"



DataLaserStruct CommonLaserInterfaceClass::GetState()
{
	DataLaserStruct DataLaser;
	DataLaser.TypeBlock = this->TypeBlock;
	DataLaser.State = this->LaserState;
	DataLaser.NumberBlock = this->NumberLaser;
	return DataLaser;
}


void CommonLaserInterfaceClass::TurnLaserBeamOnOff(bool OnOff)
{
	qDebug() << "ON OFF LASER METHOD EMPTY";
}



