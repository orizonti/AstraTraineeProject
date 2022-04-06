#pragma once
#include "DataToDisplayStructure.h"

struct KalmanOutputData
{
	QPair<double, double> CoordEstimate;
	QPair<double, double> VelocityEstimate;
	QPair<double, double> AccelerationEstimate;

	QPair<double, double> ExtrapolateStep;

};

class DataAimingErrorStructure : public DataToDisplayStructure
{
public:
	QPair<double, double> LastError;
	QPair<double, double> LastErrorFiltered;
	QPair<double, double> OutputPID;
	KalmanOutputData OutputKalman;

	stateblocksenum PIDState = BlockDisable;
	stateblocksenum CalmanState = BlockDisable;
};