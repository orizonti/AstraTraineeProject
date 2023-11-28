#include "CommonHeaders.h"
#include "CalmanFilterClass.h"
#define TAG "[   KALMAN   ]" 

CalmanFilterCoordClass::CalmanFilterCoordClass()
{
	QDebugStream cout(std::cout);

	Initialaize();

	Eigen::Matrix<float, 2, 1> Vec; Vec << 0,0;

	SetControlVec(Vec);
}

Eigen::Matrix<float, 2, 1> CalmanFilterCoordClass::FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec)
{
	if (this->StateBlock == BlockDisable)
	{
		Sk(0,0) = MeasureVec(0, 0);
		Sk(1,0) = MeasureVec(1, 0);
	return Sk;
	}

	Sk = F1*Sk + B1*this->ControlVek;           //Экстраполяция вектора состояния
	P1 = F1*P1*F1T + Rn;  //Экстраполяция ковариации ошибки
	Zk = H1*Sk;           //Ожидаемое наблюдение
    KK = P1*H1T;   //Коэффициент калмана
	KK = KK*(H1*P1*H1T +Re).inverse();
	Rk = Zk - MeasureVec; //Ошибка ожидаемого наблюдения
	Sk = Sk - KK*Rk;      //Коррекция вектора состояния  
	P1 = (I - KK*H1)*P1;
	

	return Sk;


}

void CalmanFilterCoordClass::SetCoord(QPair<double, double> Coord)
{

	Eigen::Matrix<float, 2, 1> MeasureVec;
	                                MeasureVec << Coord.first, Coord.second;
	 FilterCoord(MeasureVec);
}

QPair<double, double> CalmanFilterCoordClass::GetCoord()
{
	return QPair<double, double>(this->Sk(0, 0), this->Sk(1, 0));
}

void CalmanFilterCoordClass::SetModelErrorVariance(float X_V, float Y_V)
{
	Qnx = X_V;
	Qny = Y_V;
	Rn(0, 0) = X_V;
	Rn(1, 1) = Y_V;
}
void CalmanFilterCoordClass::SetMeasureErrorVariance(float X_E, float Y_E)
{

	Qex = X_E;
	Qey = Y_E;

	Re(0, 0) = X_E;
	Re(1, 1) = Y_E;

	KK(0, 0) = 0;
	KK(1, 0) = 0;
	KK(0, 1) = 0;
	KK(1, 1) = 0;

	//qDebug() << TAG << "===========================";
	//std::cout << "--- NewKK ---- \n";
	//std::cout << KK <<"\n";
	//std::cout << "-------------\n";
	//qDebug() << TAG << "===========================";
}

void CalmanFilterCoordClass::Initialaize()
{

	 F1 << 1, 0,
	       0, 1;
	 F1T = F1.transpose();
	 
	 Rn << Qnx,0,
	       0,Qny;

	 H1 << 1,0,
	       0,1;

	 P1 << 0,0,
		   0,0;

	 I  << 1,0,
		   0,1;

	 H1T = H1.transpose();

	 Re << Qex, 0,
	       0  ,Qey;

	 B1 << Tp,  0,
	       0,   Tp;

	 Sk << 0,
	       0;
	 
	Uk << 0,
	      0;

	ControlVek << 0,
		          0;

	 KK << 0,0,
	       0,0;
	//std::cout << "--- Re ---- \n";
	//std::cout << Re <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- Rn ---- \n";
	//std::cout << Rn <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- P1 ---- \n";
	//std::cout << P1 <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- B1 ---- \n";
	//std::cout << B1 <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- Sk ---- \n";
	//std::cout << Sk <<"\n";
	//std::cout << "-------------\n";

	//qDebug() << TAG << "===========================";
	StateBlock = BlockAtWork;
}

void CalmanFilterCoordClass::SetInterval(float Interval)
{

	Tp = Interval;	
	Initialaize();
}

void CalmanFilterCoordClass::SetControlVec(Eigen::Matrix<float, 2, 1> Control)
{
	ControlVek = Control;
}


CalmanFilterClass::CalmanFilterClass()
{
	QDebugStream cout(std::cout);
	Initialaize();

	Eigen::Matrix<float, 2, 1> Vec; Vec << 0,0;

	SetControlVec(Vec);
	
	this->StateBlock = BlockAtWork;
}

Eigen::Matrix<float, 4, 1> CalmanFilterClass::FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec)
{
	QDebugStream cout(std::cout);
	if (this->StateBlock == BlockDisable)
	{
		Sk(0,0) = MeasureVec(0, 0);
		Sk(1,0) = MeasureVec(1, 0);
		Sk(2,0) = 0;
		Sk(3,0) = 0;
	return Sk;
	}

	Sk = F1*Sk + B1*this->ControlVek;           //Экстраполяция вектора состояния
	P1 = F1*P1*F1T + Rn;  //Экстраполяция ковариации ошибки
	Zk = H1*Sk;           //Ожидаемое наблюдение
    KK = P1*H1T;   //Коэффициент калмана
	KK = KK*(H1*P1*H1T +Re).inverse();
	Rk = Zk - MeasureVec; //Ошибка ожидаемого наблюдения
	Sk = Sk - KK*Rk;      //Коррекция вектора состояния  
	P1 = (I - KK*H1)*P1;


	return Sk;
}

void CalmanFilterClass::SetCoord(QPair<double,double> Coord)
{
	Eigen::Matrix<float, 2, 1> MeasureVec;
	                                MeasureVec << Coord.first, Coord.second;

	 if(StateDimension == 3)
	 FilterCoord(MeasureVec);

	 if (StateDimension == 2)
	 {
	 this->CalmanCoordState.SetControlVec(this->ControlVek);
	 this->CalmanCoordState.FilterCoord(MeasureVec);
	 }
}

QPair<double, double> CalmanFilterClass::GetCoord()
{
	 if(StateDimension == 3)
	 return QPair<double, double>(this->Sk(0, 0), this->Sk(1, 0));

	 if (StateDimension == 2)
	 return CalmanCoordState.GetCoord();
}

void CalmanFilterClass::SetState(stateblocksenum State)
{
	this->StateBlock = State;
	this->CalmanCoordState.StateBlock = State;
}

QPair<double, double> CalmanFilterClass::GetVelocityEstimate()
{
	return QPair<double, double>(this->Sk(2, 0), this->Sk(3, 0));
}

QPair<double, double> CalmanFilterClass::GetExtrapolateStep()
{

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();

	if (StepPeriod < 0.0018)
		return QPair<double,double>(0,0);

	TimeFromLastCommand = TimePoint;

	if (StepPeriod >= 0.1)
		return QPair<double,double>(0,0);

	StepPeriod = 0;

     LastStepToEngine = QPair<double, double>(-Sk(0, 0) - Sk(2, 0)*StepPeriod , Sk(1, 0) + Sk(3, 0)*StepPeriod);

	return LastStepToEngine;
}


void CalmanFilterClass::SetModelErrorVariance(float X_V, float Y_V, float Vx_V, float Vy_V)
{
	//qDebug() << TAG << "Set model error variance in calman";
	Qnx = X_V;
	Qny = Y_V;
	Qvx = Vx_V;
	Qvy = Vy_V;

	QDebugStream cout(std::cout);
	 Eigen::Matrix< float, 4, 4 > NewRn;
	 NewRn << Qnx,0,0,0,
	          0,Qny,0,0,
	          0,0,Qvx,0,
	          0,0,0,Qvy;
	 Rn = NewRn;

	//qDebug() << TAG << "===========================";
	//std::cout << "--- Re ---- \n";
	//std::cout << Rn <<"\n";
	//std::cout << "-------------\n";
	//qDebug() << TAG << "===========================";

	CalmanCoordState.SetModelErrorVariance(X_V, Y_V);

}
void CalmanFilterClass::SetMeasureErrorVariance(float X_E, float Y_E)
{
	QDebugStream cout(std::cout);

	//qDebug() << TAG << "Set measure error variance in calman";
	Qex = X_E;
	Qey = Y_E;
	CalmanCoordState.SetMeasureErrorVariance(X_E, Y_E);

	Eigen::Matrix< float, 2, 2 > NewRe;
	NewRe << Qex, 0,
	         0  ,Qey;
	Re = NewRe;

	//qDebug() << TAG << "===========================";
	//std::cout << "--- Re ---- \n";
	//std::cout << Re <<"\n";
	//std::cout << "-------------\n";
	//qDebug() << TAG << "===========================";

	Eigen::Matrix< float, 4, 2 > NewKK;

	 NewKK << 0, 0,
	    	  0, 0,
			  0, 0,
			  0, 0;
	 KK = NewKK;
}
void CalmanFilterClass::Initialaize()
{
//	qDebug() << TAG << "INITIALIZATION CALMAN";

	 F1 << 1, 0, Tp, 0,
	       0, 1, 0, Tp,
	       0, 0, 1, 0,
	       0, 0, 0, 1;
	 F1T = F1.transpose();
	
	 
	 Rn << Qnx,0,0,0,
	       0,Qny,0,0,
	       0,0,Qvx,0,
	       0,0,0,Qvy;
	 Re << Qex, 0,
	       0  ,Qey;

	 H1 << 1,0,0,0,
	       0,1,0,0;


	 P1 << Qnx, 0, 0, 0,
	       0, Qny, 0, 0,
	       0, 0, Qvy, 0,
	       0, 0, 0, Qvy;

	 I  << 1, 0, 0, 0,
	       0, 1, 0, 0,
	       0, 0, 1, 0,
	       0, 0, 0, 1;
	

	 H1T = H1.transpose();


	 B1 << Tp*Tp/2,0,
	       0, Tp*Tp/2,
	       Tp,  0,
	       0,   Tp;


	 Sk << 0,
	       0,
	       0,
	       0;

	 KK << 0, 0,
		   0, 0,
		   0, 0,
		   0, 0;
	 

	ControlVek << 0,
		          0;

	//std::cout << "--- Re ---- \n";
	//std::cout << Re <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- Rn ---- \n";
	//std::cout << Rn <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- P1 ---- \n";
	//std::cout << P1 <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- B1 ---- \n";
	//std::cout << B1 <<"\n";
	//std::cout << "-------------\n";
	//std::cout << "--- Sk ---- \n";
	//std::cout << Sk <<"\n";
	//std::cout << "-------------\n";
	//this->StateBlock = BlockAtWork;
}

void CalmanFilterClass::SetInterval(float Interval)
{
	Tp = Interval;	
	Initialaize();
}

void CalmanFilterClass::SetControlVec(Eigen::Matrix<float, 2, 1> Control)
{
	ControlVek = Control;
}
