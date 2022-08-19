#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageProcessingClass.h"
#include "DataAimingErrorStructure.h"
#include "PassTwoCoordClass.h"
#include "TransformCoordClass.h"
#include "PIDClass.h"
#include "KalmanFilterClass.h"


template <class T>
class PortAdapter : public PassTwoCoordClass
{
public:
    PortAdapter(){};
    void LinkAdapter(T* LinkObject,std::function<void(T&,QPair<double,double>)> SetFunction, std::function<QPair<double,double>(T&)> GetFunction)
    { InputFunction = SetFunction; OutputFunction = GetFunction; Receiver = LinkObject; };

    T* Receiver =  nullptr;

    std::function<void(T&,QPair<double,double>)> InputFunction = nullptr;
    std::function<QPair<double,double>(T&)> OutputFunction = nullptr;

    void SetCoord(QPair<double,double> coord) { if(InputFunction != nullptr) InputFunction(*Receiver,coord);};
    QPair<double,double> GetCoord() { if(OutputFunction != nullptr) return OutputFunction(*Receiver);};

};



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

	void SetAimingSpeedRegim(TypeAiming Aiming);
	double GetAbsError();
	bool isAimingFault();
	bool isAimingFaultStatistic();
	void Reset();

	std::vector<QPair<double,double>> ErrorRecord;
    std::vector<QPair<double,double>>::iterator CurrentRecord;

	DataAimingErrorStructure GetState();

	QPair<double, double> GetCoord();
    QPair<double, double> GetCoordDesiered();
	void SetCoord(QPair<double, double> NewDesieredCoord);
	void SetDesieredCoord(QPair<double, double> Coord);
    void MoveDesieredCoord(QPair<double, double> MoveCoord);

    void LoadPIDParamFromFile();
    void SlotFilterEnable(bool OnOff);
    std::vector<PIDParamStruct> PID_Param_Table;

    StatisticGroup PIDParamGroupStat = StatisticGroup(10,200);
    Statistic CurrentStatistic = Statistic(200);

	PortAdapter<AimingClass> AimingPort;

	PIDParamStruct AimingSlowParam;
	PIDParamStruct AimingFastParam;

	PIDClass EnginePIDRegulator;
	KalmanFilterClass Filter;

	QPair<double, double> BeamCenteredPosition;
	QPair<double, double> DesireAbsCoord = QPair<double,double>(0,0);
    QPair<double, double> DesireRelCoord = QPair<double,double>(0,0);

	QPair<double, double> LastErrorChannel;
	QPair<double, double> LastVelocityVector;
	QPair<double, double> LastAccelerationVector;
	QPair<double, double> OutputCoord;


	TransformCoordClass PixToRadian;
	TransformCoordClass RadianToPix;
	//Statistic StatProcessor;
};

