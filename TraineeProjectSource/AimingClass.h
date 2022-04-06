#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageProcessingClass.h"
#include "DataAimingErrorStructure.h"
#include "PassTwoCoordClass.h"
#include "TransformCoordClass.h"
#include "PIDClass.h"
#include "CalmanFilterClass.h"







class AimingClass : public PassTwoCoordClass
{
public:
    
	AimingClass();
	~AimingClass();

	int NumberChannel;
	typeblocksenum TypeBlock = typeblocksenum::AimingBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	TypeAiming AimingState = AimingSlow;

	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend ImageProcessingClass& operator>>(ImageProcessingClass& ImageProcessor, AimingClass& AimingBlock);

	bool isAimingFault();

	void SetAimingSpeedRegim(TypeAiming Aiming);
	double GetAbsError();

	DataAimingErrorStructure GetState();

	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> NewDesieredCoord);
	void SetDesieredCoord(QPair<double, double> Coord);

	PIDParamStruct AimingSlowParam;
	PIDParamStruct AimingFastParam;

	PIDClass EnginePIDRegulator;

	QPair<double, double> BeamCenteredPosition;
	QPair<double, double> DesireAbsCoord = QPair<double,double>(0,0);
    
	QPair<double, double> LastErrorChannel;
	QPair<double, double> LastAbsCoord;
	QPair<double, double> LastVelocityVector;
	QPair<double, double> LastAccelerationVector;
	QPair<double, double> OutputCoord;


	CalmanFilterClass CalmanFilter;
	TransformCoordClass PixToRadian;
	TransformCoordClass RadianToPix;
	//Statistic StatProcessor;



};

