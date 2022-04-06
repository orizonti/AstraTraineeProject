#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"
#include "DataEngineStructure.h"
#include "EngineInterfaceClass.h"
#include "KLPInterfaceClass.h"
#include "AimingClass.h"
#include "RotateOperationContainer.h"



class CalcRotateAxis : public PassTwoCoordClass
{
public:

	void SetCoord(QPair<double,double> Coord);
	QPair<double,double> GetCoord();

	double AngleRadRotate = 0;
	int SpotDx = 0;
	int SpotDy = 0;

};

class RotateVectorClass : public PassTwoCoordClass
{
public:
	RotateVectorClass(RotateVectorClass& RotateObject);
	RotateVectorClass() 
	{
		RotateMatrix << 1, 0, 0,
					    0, 1, 0,
				        0, 0, 1;
		RotateVector << 0, 0, 0;
	};
	RotateVectorClass(double DegreeAngleX, double DegreeAngleY, double DegreeAngleZ);

	Eigen::Matrix< float, 3, 3 > RotateMatrix;
	Eigen::Matrix< float, 3, 1 > OutputVector;
	Eigen::Matrix< float, 3, 1 > RotateVector;
	double Z_Coeff = 0;
	double SystemScale = 1;
	std::vector<std::pair<int, double>> RotateOperations;

	void SetRotateVector(double DegreeAngleX, double DegreeAngleY, double DegreeAngleZ);

	void SetCoord(QPair<double,double> Coord);
	QPair<double,double> GetCoord();
	RotateVectorClass Inverse();
	void operator=(RotateVectorClass && Matrix);
	void operator=(RotateVectorClass & Matrix);

	friend RotateVectorClass operator*(RotateVectorClass  Rotate1,RotateVectorClass  Rotate2);

};


class EngineControlClass :public QObject,public PassTwoCoordClass
{
    Q_OBJECT
public:

	typeblocksenum TypeBlock = typeblocksenum::EngineControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;

	EngineControlClass(EngineInterfaceClass* KLP, QObject* parrent = 0);
	~EngineControlClass();
	EngineData GetEnginesState();
	QPair<double, double> GetLastCoord();
	void friend operator>>(AimingClass& Sender, EngineControlClass& Reciever);
	void SetCoord(QPair<double, double> Coord);
	QPair<double,double> GetCoord();

    void ResetToLastSavePosition();


	EngineInterfaceClass* EngineInterface;
	QPair<double, double> NullWorkPos;
	QPair<double,double> SetToStartPos();
	RotateVectorClass RotateAxis;  // copensation of engine rotate position
	RotateVectorClass RotateAxisInverse;  // copensation of engine rotate position

	RotateOperationContainer RotationAxis;
	RotateOperationContainer RotationAxisInverse;

	int EngineNumber = 0;
	static int EngineCount;


private:

	double StepPeriod = 0;
	QPair<double, double> StepChannel;
	QPair<double, double> VelVector;
	QPair<double, double> LastSavePosition;

	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;
    std::chrono::time_point<std::chrono::high_resolution_clock> TimeSavePosition;


	public slots:
	void SlotMoveOnStep(QPair<double, double> StepVector);

	void SlotMoveWithVelocity(QPair<double, double> VelVector);
	void SlotMoveWithAcceleration(QPair<double, double> AccelVector);
    

};
