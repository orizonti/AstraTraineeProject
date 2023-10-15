#pragma once
#include "PassTwoCoordClass.h"
#include "PIDParamStruct.h"
#include <chrono>
#include "stateblocksenum.h"
#include <QTime>


class PIDClass : public PassTwoCoordClass
{
public:
	PIDClass();
	~PIDClass();

	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	
	QPair<double, double> CalcVelocityToEngine(QPair<double, double> CoordError);
	QPair<double, double> GetCoord();
	void ResetPID();
	void SetCoord(QPair<double, double> Coord);
	void SetPIDParam(PIDParamStruct Param);


	//QString PIDLog;
	//QString PIDLog2;
	//int n_log = 0;

	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, Eigen::Matrix< float, 2, 1 >& Reciever);
	friend PassTwoCoordClass& operator >> (PassTwoCoordClass& Sender, QPair<double, double>& Coord);

	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;
	PIDParamStruct PIDParam;
	QPair<double, double> ErrorsSumm;
private:
    //double MaxAccelAxis1 = 20*4.84/1000000;
    //double MaxAccelAxis2 = 20*4.84/1000000;
	QPair<double, double> PIDControlOutput;
	QPair<double, double> LastErrorCoord;
    //QTime timeAiming;
};