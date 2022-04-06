#include "stdafx.h"
#include "AimingControlBest.h"


AimingControlBest::AimingControlBest()
{
}


AimingControlBest::~AimingControlBest()
{
}

void AimingControlBest::SetCoord(QPair<double, double> Coord)
{
	engine_step = QPair<double,double>(0,0);

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();

	if (StepPeriod >= 0.1)
	{
		TimeFromLastCommand = TimePoint;
		return;
	}

	  Period = 0.05; //работает идут большие переколебания
	//Period = 0.02; //работает, система на границе устойчивости
	//Period = 0.01; //не работает, не устойчива
	//Period = 0.008; //не работает не устойчива



	if (StepPeriod >= Period)
		TimeFromLastCommand = TimePoint;
	else
		return;





    this->Spot_shift = Coord;

	est_new.first = Spot_shift.first + delta_cur.first;
	est_new.second = Spot_shift.second + delta_cur.second;

	delta_new.first = est_new.first + (est_new.first - est_old.first);
	delta_new.second = est_new.second + (est_new.second - est_old.second);
	
	//engine_step.second = (delta_cur.first - delta_new.first);
	engine_step.first = (delta_cur.first - delta_new.first);


	test_count++;
	if (test_count < 30)
	{

		qDebug() << "ERROR pix - " << Coord.first << "EST - " << est_new.first << "NEW POS -" << delta_new.first << "STEP - " << engine_step.first << "PERIOD - " << StepPeriod <<" ms";
		//qDebug() << "error second  - " << Coord.second << "est - "<< est_new.second <<"new pos -"<< delta_new.second  << "step - " << engine_step.first;

	}

	est_old = est_new;
	delta_cur = delta_new;
	//engine_step.first = delta_new.second;

	//engine_step.first = (delta_cur.first - delta_new.first);
	//engine_step.second = (delta_cur.second - delta_new.second);

//	engine_step.first = (delta_new.first - delta_cur.first);
//	engine_step.second = (delta_new.second - delta_cur.second);


}

QPair<double, double> AimingControlBest::GetCoord()
{
		return engine_step;
}