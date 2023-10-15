#pragma once
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"
#include <qpair.h>
#include <functional>
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

//class OptimizationTransformParameter
//{
//public:
//	std::vector < QPair<double, double>> OptimizationData;
//	std::vector <QPair<double, double>> OutputOptimizedParameters;
//	int DataSize = 6;
//	void LoadData(QPair<double, double>);
//	void GetOptimizedParameters();
//};

//class  TransformCoordClass : public PassTwoCoordClass
//{
//public:
//	QPair<double, double> GetCoord();
//	void SetCoord(QPair<double, double> Coord);
//	void SwitchToAccumulateData();
//	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, Eigen::Matrix< float, 2, 1 >& Reciever);
//
//private:
//	bool FlagAccumulateDataMode = false;
//	QPair<double, double> TransformedCoord;

//public:
//	virtual TransformCoordClass GetInverse();
//private:
//	virtual void TransformCoord();
//};

class  TransformCoordClass : public PassTwoCoordClass
{
public:
	std::function<void(QPair<double,double>)> TransformCoord;
	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> Coord);
	QPair<double, double> TransformedCoord;
	double Scale = 1;

	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, Eigen::Matrix< float, 2, 1 >& Reciever);
};