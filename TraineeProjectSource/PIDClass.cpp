#include "stdafx.h"
#include "PIDClass.h"

PIDClass::PIDClass()
{

	this->MaxAccelAxis1 = 20*4.84/1000000;
	this->MaxAccelAxis2 = 20*4.84/1000000;

	this->LastErrorCoord = QPair<double, double>(-10000, -10000);
	this->StateBlock = BlockAtWork;
	this->ErrorsSumm = QPair<double, double>(0, 0);

	TimeFromLastCommand = std::chrono::high_resolution_clock::now();
	PIDAcelerationCoord = QPair<double, double>(0, 0);
}
PIDClass::~PIDClass()
{

}



void PIDClass::ResetPID()
{
	qDebug() << "RESET PID";
	this->ErrorsSumm = QPair<double, double>(0, 0);
    this->PIDAcelerationCoord = QPair<double, double>(0, 0);
    this->LastErrorCoord = QPair<double, double>(0, 0);

}


QPair<double, double> PIDClass::CalcVelocityToEngine(QPair<double, double> CoordError)
{

	if(CoordError.first == LastErrorCoord.first && CoordError.second == LastErrorCoord.second)
		return  this->PIDAcelerationCoord;

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();
    TimeFromLastCommand = TimePoint;

	if (StepPeriod > 0.01) return  this->PIDAcelerationCoord;

	double DerivateErrorXAxis = 0; double DerivateErrorYAxis = 0;

	this->ErrorsSumm.first  = ErrorsSumm.first  + CoordError.first*StepPeriod;
	this->ErrorsSumm.second = ErrorsSumm.second + CoordError.second*StepPeriod;


	if (LastErrorCoord.first != -10000 && LastErrorCoord.second != -10000)
	{
		DerivateErrorXAxis = (CoordError.first - this->LastErrorCoord.first) / StepPeriod;
		DerivateErrorYAxis = (CoordError.second - this->LastErrorCoord.second) / StepPeriod;
	}
	this->PIDAcelerationCoord.second = CoordError.first*PIDParamAxis1.RateParam + ErrorsSumm.first*PIDParamAxis1.IntParam + DerivateErrorXAxis*PIDParamAxis1.DiffParam;
	this->PIDAcelerationCoord.first  = CoordError.second*PIDParamAxis2.RateParam + ErrorsSumm.second*PIDParamAxis2.IntParam + DerivateErrorYAxis*PIDParamAxis2.DiffParam;
	
	//--------------------------------------------------------->
	this->LastErrorCoord = CoordError;

	return PIDAcelerationCoord;

}


QPair<double, double> PIDClass::GetCoord()
{
	return PIDAcelerationCoord;
}

void PIDClass::SetCoord(QPair<double, double> Coord)
{
	auto CoordNew = Coord;
	CoordNew.second = Coord.first; //X
	CoordNew.first = Coord.second; //Y
	//CoordNew.second = 0;
	//CoordNew.first = 0;
	this->CalcVelocityToEngine(CoordNew);
}

void PIDClass::SetPIDParam(PIDParamStruct Param)
{
	this->PIDParamAxis1 = Param;
	this->PIDParamAxis2 = Param;
	this->ResetPID();
}



