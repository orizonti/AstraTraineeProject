#include "CommonHeaders.h"
#include "EngineControlClass.h"
using namespace std;
#define TAG "[ ENGINE CTRL ]" 
int EngineControlClass::EngineCount = 0;
void CalcRotateAxis::SetCoord(QPair<double, double> Coord)
{
}

QPair<double, double> CalcRotateAxis::GetCoord()
{
	return QPair<double, double>(0, 0);
}


RotateVectorClass::RotateVectorClass(RotateVectorClass& RotateObject)
{
	this->RotateMatrix = RotateObject.RotateMatrix;
	this->RotateVector = RotateObject.RotateVector;
	this->Z_Coeff = RotateObject.Z_Coeff;
}

RotateVectorClass::RotateVectorClass(double DegreeAngleX, double DegreeAngleY, double DegreeAngleZ)
{
    RotateVector << 0, 0, 0;
	this->SetRotateVector(DegreeAngleX,DegreeAngleY,DegreeAngleZ);

	this->Z_Coeff = cos(M_PI / 180 * RotateVector(0, 0)) / cos(M_PI / 2 - M_PI / 2 * RotateVector(0, 0));
}

//void RotateVectorClass::AddRotate(std::pair<int, double> Rotate)
//{
//	//this->RotateOperations.push_back(Rotate);
//
//
//}
void RotateVectorClass::SetRotateVector(double DegreeAngleX, double DegreeAngleY, double DegreeAngleZ)
{
	//qDebug() << TAG << "Set rotate vector - " << DegreeAngleX << DegreeAngleY << DegreeAngleZ;
		this->RotateMatrix << 1, 0 ,0,
						      0, 1 ,0,
							  0, 0, 1;

	if (DegreeAngleX != RotateVector(0,0))
	{
		this->RotateMatrix(1, 1) = cos(DegreeAngleX*M_PI/180.0);
		this->RotateMatrix(1, 2) = -sin(DegreeAngleX*M_PI/180.0);
		this->RotateMatrix(2, 1) = sin(DegreeAngleX*M_PI/180.0);
		this->RotateMatrix(2, 2) = cos(DegreeAngleX*M_PI/180.0);
	}

	if (DegreeAngleY != RotateVector(1,0))
	{
		this->RotateMatrix(0, 0) = cos(DegreeAngleY*M_PI / 180.0);
		this->RotateMatrix(2, 0) = sin(DegreeAngleY*M_PI / 180.0);
		this->RotateMatrix(0, 2) = -sin(DegreeAngleY*M_PI / 180.0);
		this->RotateMatrix(2, 2) = cos(DegreeAngleY*M_PI / 180.0);
	}

	if (DegreeAngleZ != RotateVector(2,0))
	{
		this->RotateMatrix(0, 0) = cos(DegreeAngleZ*M_PI / 180.0);
		this->RotateMatrix(0, 1) = -sin(DegreeAngleZ*M_PI / 180.0);
		this->RotateMatrix(1, 0) = sin(DegreeAngleZ*M_PI / 180.0);
		this->RotateMatrix(1, 1) = cos(DegreeAngleZ*M_PI / 180.0);
	}



	this->RotateVector(0, 0) = DegreeAngleX;
	this->RotateVector(1, 0) = DegreeAngleY;
	this->RotateVector(2, 0) = DegreeAngleZ;
}

void RotateVectorClass::SetCoord(QPair<double, double> Coord)
{

	Eigen::Matrix<float, 3, 1> InputVector;
							   InputVector << Coord.first, Coord.second, Coord.second*Z_Coeff;

                               
							   //QDebugStream cout(std::cout);
							   //qDebug() << TAG << "Rotate vector input ";
							   //std::cout << InputVector << endl;
							   //qDebug() << TAG << "Z_Coeff - " << Z_Coeff;
    OutputVector = SystemScale * RotateMatrix * InputVector;
							   //qDebug() << TAG << "Rotate vector output ";
							   //std::cout << OutputVector << endl;

}

QPair<double, double> RotateVectorClass::GetCoord()
{
	return QPair<double, double>(this->OutputVector(0, 0), this->OutputVector(1, 0));
}

RotateVectorClass RotateVectorClass::Inverse()
{
	RotateVectorClass TempRotateObject(0,0,0);

	TempRotateObject.RotateMatrix = this->RotateMatrix.inverse().eval();
	TempRotateObject.RotateVector = -1*this->RotateVector;
	TempRotateObject.Z_Coeff = cos(M_PI / 2 - M_PI / 180 * RotateVector(0, 0)) / cos(M_PI / 180 * RotateVector(0, 0));;

							   //QDebugStream cout(std::cout);
							   //qDebug() << TAG << "Inverse matrix ";
							   //std::cout << TempRotateObject.RotateMatrix;
	return TempRotateObject;
}


RotateVectorClass operator*(RotateVectorClass  Rotate1,RotateVectorClass  Rotate2)
{
Rotate1.RotateMatrix = Rotate1.RotateMatrix*Rotate2.RotateMatrix;
Rotate1.RotateVector = Rotate1.RotateVector + Rotate2.RotateVector;
Rotate1.Z_Coeff = 0;
	
				///			   QDebugStream cout(std::cout);
				///			   qDebug() << TAG << "Rotate matrix ";
				///			   std::cout << Rotate1.RotateMatrix;
return Rotate1;
}


void RotateVectorClass::operator=(RotateVectorClass & Matrix)
{
	this->RotateMatrix = Matrix.RotateMatrix;
	this->RotateVector = Matrix.RotateVector;
	this->Z_Coeff = Matrix.Z_Coeff;
}

void RotateVectorClass::operator=(RotateVectorClass && Matrix)
{
	this->RotateMatrix = Matrix.RotateMatrix;
	this->RotateVector = Matrix.RotateVector;
	this->Z_Coeff = Matrix.Z_Coeff;
}


EngineControlClass::EngineControlClass(EngineInterfaceClass* Interface, QObject* parrent) : QObject(parrent)
{
	this->StateBlock = BlockAtWork;
	EngineInterface = Interface;

	VelVector = QPair<double, double>(0, 0);
	this->NullWorkPos = QPair<double, double>(0, 0);

	EngineControlClass::EngineCount++;
	this->EngineNumber = EngineCount;
}


EngineControlClass::~EngineControlClass()
{
}


EngineData EngineControlClass::GetEnginesState()
{

	EngineData Data;
	Data.MaxPosition.first = EngineInterface->Status_Engine.EdgeMaxX;
	Data.MaxPosition.second = EngineInterface->Status_Engine.EdgeMaxY;
	Data.MinPosition.first = EngineInterface->Status_Engine.EdgeMinX;
	Data.MinPosition.second = EngineInterface->Status_Engine.EdgeMinY;

	Data.DesirePosition.first = this->EngineInterface->ControlCoord.first*1000000/4.848;
	Data.DesirePosition.second = this->EngineInterface->ControlCoord.second*1000000/4.848;
	
	Data.LastPosChannel.first = this->EngineInterface->Status_Engine.PosAngleX*1000000/4.848;
	Data.LastPosChannel.second = this->EngineInterface->Status_Engine.PosAngleY*1000000/4.848;
	Data.State = this->StateBlock;

	return Data;
}

QPair<double, double> EngineControlClass::GetLastCoord()
{
	return EngineInterface->GetCoord();
}

void EngineControlClass::SetCoord(QPair<double, double> Coord)
{
	this->SlotMoveOnStep(Coord);
}

QPair<double, double> EngineControlClass::GetCoord()
{
	return EngineInterface->GetCoord();
}

QPair<double,double> EngineControlClass::SetToStartPos()
{
	qDebug() << TAG << "SET TO START POS- " << this->NullWorkPos;
	this->EngineInterface->SetToNull();
	this->thread()->msleep(200);
	this->EngineInterface->SetCoord(this->NullWorkPos);
	return NullWorkPos;

}


void EngineControlClass::SlotMoveOnStep(QPair<double, double> StepVector)
{

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();

	TimeFromLastCommand = TimePoint;
	QPair<double, double> Step;
	StepVector >> RotationAxis >> *EngineInterface;
}
void EngineControlClass::SavePosition()
{
    if(!isEngineFault()) LastSavePosition = EngineInterface->ControlCoord;
}

void EngineControlClass::SlotMoveWithVelocity(QPair<double, double> VelVector)
{

	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();
	TimeFromLastCommand = TimePoint;



	QPair<double, double> StepVector(VelVector.first*StepPeriod, VelVector.second*StepPeriod);

	if(!isEngineFault()) { StepVector >> RotationAxis >> *EngineInterface; };
}

bool EngineControlClass::isEngineFault()
{
    QPair<double,double> AbsCoord;

    AbsCoord.first = abs(this->EngineInterface->ControlCoord.first*1000000/4.848);
    AbsCoord.second = abs(this->EngineInterface->ControlCoord.second*1000000/4.848);

    if(AbsCoord.first > 450 || AbsCoord.second > 450)
    {
        qDebug() << TAG << "ENGINE FAULT - " << AbsCoord << "CHANNEL - " << this->EngineNumber;
        return true;
    }

  return false;
}

void EngineControlClass::ResetToLastSavePosition()
{
    qDebug() << TAG << "ENGINE - " << this->EngineNumber << " RESTORE FROM FAULT";
    EngineInterface->SetCoordAbs(LastSavePosition);
}

void EngineControlClass::SlotMoveWithAcceleration(QPair<double, double> AccelVector)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();

	StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();
	TimeFromLastCommand = TimePoint;


	VelVector.first += AccelVector.first*StepPeriod;
	VelVector.second += AccelVector.second*StepPeriod;

	
	//qDebug() << TAG << "CONVERT ACCELERATION - " <<AccelVector.first << VelVector.first <<"STEP_PERIOD - " << StepPeriod;

	QPair<double, double> StepVector(VelVector.first*StepPeriod, VelVector.second*StepPeriod); // CALCULATION PROLONGATION STEP TO MOVE ENGINE
	StepVector >> RotationAxis >> *EngineInterface;
}


void operator>>(AimingClass& Sender, EngineControlClass& Reciever)
{
	if (Sender.StateBlock == BlockAtWork)
	{

		if (Reciever.StateBlock == BlockAtWork)
			Reciever.SlotMoveWithVelocity(Sender.GetCoord());
	}

}

