#include "CommonHeaders.h"
#include "PIDClass.h"

#define TAG "[ PID CONTROL ]" 

PIDClass::PIDClass()
{


	this->LastErrorCoord = QPair<double, double>(-10000, -10000);
	this->StateBlock = BlockAtWork;
	this->ErrorsSumm = QPair<double, double>(0, 0);

	TimeFromLastCommand = std::chrono::high_resolution_clock::now();
	PIDControlOutput = QPair<double, double>(0, 0);
}
PIDClass::~PIDClass()
{

}



void PIDClass::ResetPID()
{
	this->ErrorsSumm = QPair<double, double>(0, 0);
    this->PIDControlOutput = QPair<double, double>(0, 0);
    this->LastErrorCoord = QPair<double, double>(0, 0);

}


QPair<double, double> PIDClass::CalcVelocityToEngine(QPair<double, double> CoordError)
{

	if(CoordError.first == LastErrorCoord.first && CoordError.second == LastErrorCoord.second)
		return  this->PIDControlOutput;

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();
    TimeFromLastCommand = TimePoint;

	if (StepPeriod > 0.01) return  this->PIDControlOutput;

	double DerivateErrorXAxis = 0; double DerivateErrorYAxis = 0;

	this->ErrorsSumm.first  = ErrorsSumm.first  + CoordError.first*StepPeriod;
	this->ErrorsSumm.second = ErrorsSumm.second + CoordError.second*StepPeriod;


	if (LastErrorCoord.first != -10000 && LastErrorCoord.second != -10000)
	{
		DerivateErrorXAxis = (CoordError.first - this->LastErrorCoord.first) / StepPeriod;
		DerivateErrorYAxis = (CoordError.second - this->LastErrorCoord.second) / StepPeriod;
	}
	this->PIDControlOutput.second = CoordError.first*PIDParam.RateParam + ErrorsSumm.first*PIDParam.IntParam + DerivateErrorXAxis*PIDParam.DiffParam;
	this->PIDControlOutput.first  = CoordError.second*PIDParam.RateParam + ErrorsSumm.second*PIDParam.IntParam + DerivateErrorYAxis*PIDParam.DiffParam;
	
	//--------------------------------------------------------->
	this->LastErrorCoord = CoordError;

	return PIDControlOutput;

}


QPair<double, double> PIDClass::GetCoord()
{
	return PIDControlOutput;
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
    qDebug() << TAG << "SET PID PARAM - " << Param.RateParam << Param.IntParam << Param.DiffParam;
	this->PIDParam = Param;
	this->ResetPID();
}



