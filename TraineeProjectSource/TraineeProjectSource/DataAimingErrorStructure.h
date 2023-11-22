#pragma once
#include "DataDeviceStructureCommon.h"

struct KalmanOutputData
{
	QPair<double, double> CoordEstimate;
	QPair<double, double> VelocityEstimate;
	QPair<double, double> AccelerationEstimate;

	QPair<double, double> ExtrapolateStep;

};


class DataAimingErrorStructure : public CommonDeviceStructure
{
public:
	QPair<double, double> LastError;
	QPair<double, double> LastErrorFiltered;
	QPair<double, double> OutputPID;
	KalmanOutputData OutputKalman;

	stateblocksenum PIDState = BlockDisable;
	stateblocksenum CalmanState = BlockDisable;

	std::tuple<float,float,float> PIDParam;
    TypeAiming AimingState;
    std::vector<QPair<double,double>>::iterator BeginError;
    std::vector<QPair<double,double>>::iterator EndError;


};