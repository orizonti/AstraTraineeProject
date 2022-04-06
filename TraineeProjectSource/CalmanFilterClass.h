#pragma once

#include <iostream>
#include "DebugStream.h"
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"


class CalmanFilterCoordClass :public PassTwoCoordClass
{
public:

	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	CalmanFilterCoordClass();
	Eigen::Matrix<float, 2, 1> FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec);

	void SetCoord(QPair<double, double> Coord);
	QPair<double,double> GetCoord();
    	
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;

	float Tp = 0.002;
	float Qnx = 0.05;
	float Qny = 0.05;
	float Qvx = 0.05;
	float Qvy = 0.05;


	float Qex = 2;
	float Qey = 2;

	Eigen::Matrix< float, 2, 2 > F1;
	Eigen::Matrix< float, 2, 2 > F1T;
	Eigen::Matrix< float, 2, 2 > Rn;

	Eigen::Matrix< float, 2, 2 > H1;
	Eigen::Matrix< float, 2, 2 > H1T;
	Eigen::Matrix< float, 2, 2 > Re;

	Eigen::Matrix< float, 2, 2 > B1;


	Eigen::Matrix< float, 2, 1 > Sk;
	Eigen::Matrix< float, 2, 1 > Uk;

	Eigen::Matrix< float, 2, 1 > Zk;
	Eigen::Matrix< float, 2, 1 > ControlVek;
	Eigen::Matrix< float, 2, 1 > Rk;
	Eigen::Matrix< float, 2, 2 > P1;
	

	Eigen::Matrix< float, 2, 2 > KK;

	Eigen::Matrix< float, 2, 2 > I;

	void SetModelErrorVariance(float X_V, float Y_V);
	void SetMeasureErrorVariance(float X_E, float Y_E);
	void Initialaize();
	void SetInterval(float Interval);
	void SetControlVec(Eigen::Matrix< float, 2, 1 > Control);


	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >> (PassTwoCoordClass& Sender, QPair<double, double>& Coord);

};

class CalmanFilterClass :public PassTwoCoordClass
{
public:
	CalmanFilterClass();

	int StateDimension = 2;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;

	CalmanFilterCoordClass CalmanCoordState;

	Eigen::Matrix<float, 4, 1> FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec);

	void SetCoord(QPair<double, double> Coord);
	QPair<double,double> GetCoord();

	QPair<double, double> LastStepToEngine;

	void SetState(stateblocksenum State);

	QPair<double, double> GetVelocityEstimate();
	QPair<double, double> GetExtrapolateStep();
    	
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;

	float Tp = 0.002;
	float Qnx = 0.05;
	float Qny = 0.05;
	float Qvx = 0.05;
	float Qvy = 0.05;


	float Qex = 2;
	float Qey = 2;
	Eigen::Matrix< float, 4, 4 > F1;
	Eigen::Matrix< float, 4, 4 > F1T;
	Eigen::Matrix< float, 4, 4 > Rn;

	Eigen::Matrix< float, 2, 4 > H1;
	Eigen::Matrix< float, 4, 2 > H1T;
	Eigen::Matrix< float, 2, 2 > Re;

	Eigen::Matrix< float, 4, 2 > B1;


	Eigen::Matrix< float, 4, 1 > Sk;

	Eigen::Matrix< float, 2, 1 > Zk;
	Eigen::Matrix< float, 2, 1 > ControlVek;
	Eigen::Matrix< float, 2, 1 > Rk;
	Eigen::Matrix< float, 4, 4 > P1;
	

	Eigen::Matrix< float, 4, 2 > KK;
	Eigen::Matrix< float, 4, 4 > I;


	void SetModelErrorVariance(float X_V, float Y_V, float Vx_V, float Vy_V);
	void SetMeasureErrorVariance(float X_E, float Y_E);
	void Initialaize();
	void SetInterval(float Interval);
	void SetControlVec(Eigen::Matrix< float, 2, 1 > Control);


	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >> (PassTwoCoordClass& Sender, QPair<double, double>& Coord);

};
