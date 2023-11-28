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
	qDebug() <<"[LASER COMMON]" << LASER_GROUP(NumberLaser).NAME().toStdString().c_str()<< "TURN " << OnOff;
}

LASER_GROUP::LASER_GROUP(int Number)
{
  NumberLaser = Number;
}
bool LASER_GROUP::operator==(LASER_GROUPS TEST_GROUP)
{
	if(NumberLaser < 4)  return (POWER_GROUP == TEST_GROUP);
	if(NumberLaser > 10) return (GUID_GROUP == TEST_GROUP);
	if(NumberLaser == 4) return (POINTER_GROUP == TEST_GROUP);
}


QString LASER_GROUP::NAME()
{
	if(NumberLaser < 4)  return QString("LASER_POWER: %1").arg(NumberLaser);
	if(NumberLaser > 10) return QString("LASER_GUID:  %1").arg(NumberLaser-10);
						 return QString("LASER_POINT: %1").arg(NumberLaser);
}
