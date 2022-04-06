#include "stdafx.h"
#include "AimingClass.h"
#include "SubstractPair.h"


DataAimingErrorStructure AimingClass::GetState()
{
DataAimingErrorStructure displayData;
Substract<double> SubsPair;
displayData.TypeBlock = this->TypeBlock;

	LastAbsCoord >> SubsPair;
  DesireAbsCoord >> SubsPair >> displayData.LastError;


  displayData.LastErrorFiltered = LastErrorChannel;

  //displayData.OutputPID = EnginePIDRegulator.GetCoord();
  displayData.OutputPID = EnginePIDRegulator.ErrorsSumm;

 
  displayData.OutputKalman.VelocityEstimate = CalmanFilter.GetVelocityEstimate();
  displayData.OutputKalman.CoordEstimate = CalmanFilter.GetCoord();
  displayData.OutputKalman.ExtrapolateStep = CalmanFilter.GetExtrapolateStep();

  displayData.NumberBlock = this->NumberChannel;
  displayData.State = this->StateBlock;
  displayData.CalmanState = this->CalmanFilter.StateBlock;
  displayData.PIDState = this->EnginePIDRegulator.StateBlock;


return displayData;
}

QPair<double, double> AimingClass::GetCoord()
{
    if(!isAimingFault())
	return this->OutputCoord;

    return QPair<double,double>(0,0);
}



AimingClass::AimingClass()
{

	//======================================================================

	this->AimingSlowParam.Common = 1;              
	this->AimingSlowParam.RateParam = 5.1;
	this->AimingSlowParam.IntParam  = 0.0002;
	this->AimingSlowParam.DiffParam = 0.0002;



	this->AimingFastParam.Common = 1;           // for move by velocity one integrator plant
	this->AimingFastParam.RateParam = 16.45;
	this->AimingFastParam.IntParam  = 46.60;
	this->AimingFastParam.DiffParam = 0.0164;

//	this->AimingFastParam.Common = 1;           // for move by velocity one integrator plant
//	this->AimingFastParam.RateParam = 50.093;
//	this->AimingFastParam.IntParam  = 460.7834;
//	this->AimingFastParam.DiffParam = 0.04963;

	//==================================================================

	EnginePIDRegulator.SetPIDParam(AimingSlowParam);

	this->StateBlock = stateblocksenum::BlockAtWork;
	this->NumberChannel = 1;
	this->TypeBlock = typeblocksenum::AimingBlock;
	this->LastErrorChannel = QPair<double,double>(0,0);
	this->LastErrorChannel = QPair<double,double>(0,0);
	this->DesireAbsCoord = QPair<double, double>(0, 0);

	this->PixToRadian.TransformCoord = [this](QPair<double,double> CoordError)
							{
								PixToRadian.TransformedCoord.first = (CoordError.first * PixToRadian.Scale) * M_PI / (60.0 * 60.0 * 180.0);
								PixToRadian.TransformedCoord.second = (CoordError.second * PixToRadian.Scale) * M_PI / (60.0 * 60.0 * 180.0);
							};

	this->RadianToPix.TransformCoord = [this](QPair<double,double> CoordError)
							{
								RadianToPix.TransformedCoord.first = (CoordError.first*(60.0*60.0*180.0)/M_PI)/PixToRadian.Scale;
								RadianToPix.TransformedCoord.second = (CoordError.second*(60.0*60.0*180.0)/M_PI)/PixToRadian.Scale;
							};


}

void AimingClass::SetAimingSpeedRegim(TypeAiming Aiming)
{
	AimingState = Aiming;
    qDebug() << "Aiming bloc - " << this->NumberChannel << " aiming speed - " << (int)Aiming;
	if (AimingState == AimingSlow)
		EnginePIDRegulator.SetPIDParam(AimingSlowParam);
		
	if(AimingState == AimingFast)
		EnginePIDRegulator.SetPIDParam(AimingFastParam);
}


bool AimingClass::isAimingFault()
{
  auto Error = GetAbsError();

  if(Error > 30)
      return true;

  return false;
}

double AimingClass::GetAbsError()
{
	return std::hypot(LastErrorChannel.first, LastErrorChannel.second);
}

void AimingClass::SetDesieredCoord(QPair<double, double> NewDesieredCoord)
{
	Substract<double> SubsPair;
	NewDesieredCoord >> SubsPair;
	  DesireAbsCoord >> SubsPair >> LastErrorChannel;

	  DesireAbsCoord = NewDesieredCoord;
	
}

void AimingClass::SetCoord(QPair<double, double> Coord)
{

	Substract<double> SubsPair;
	if (DesireAbsCoord != QPair<double, double>(0, 0) && this->StateBlock != BlockDisable)
	{


			       Coord >> SubsPair;
		  DesireAbsCoord >> SubsPair >> LastErrorChannel>> EnginePIDRegulator>> PixToRadian >> OutputCoord;
		  LastAbsCoord = Coord;


        //DesireAbsCoord >> SubsPair >> LastErrorChannel>> PixToRadian >> EnginePIDRegulator >> RadianToPix >> CalmanFilter.ControlVek;
        //EnginePIDRegulator >> OutputCoord;
	}
}

AimingClass::~AimingClass()
{
}

ImageProcessingClass& operator>>(ImageProcessingClass& ImageProcessor, AimingClass& AimingBlock)
{
	if (AimingBlock.StateBlock == BlockAtWork && ImageProcessor.GetProcessor(AimingBlock.NumberChannel)->FlagSpotFound)
	{
	ImageProcessor.GetLastCoordChannel(AimingBlock.NumberChannel) >> AimingBlock;// PASS ABS COORD SPOT 
	}

					
return ImageProcessor;
} 
