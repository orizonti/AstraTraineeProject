#pragma once
#include "PassTwoCoordClass.h"
class AimingControlBest :
	public PassTwoCoordClass
{
public:
	AimingControlBest();
	~AimingControlBest();

	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> Coord);
private:
	int count = 0;
	int test_count = 0;
	QPair <double, double> est_old = { 0.0, 0.0 };
	QPair <double, double> est_new = { 0.0, 0.0 };
	QPair <double, double> delta = { 0.0, 0.0 };
	QPair <double, double> delta_cur = { 0.0, 0.0 };
	QPair <double, double> delta_new = { 0.0, 0.0 };
	QPair <double, double> engine_step = { 0.0, 0.0 };
	QPair <double, double> Spot_shift = { 0.0, 0.0 };

	double Period = 0.05;
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;
};

