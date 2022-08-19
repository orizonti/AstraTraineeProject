#include "stdafx.h"
#include "AimingClass.h"
#include "SubstractPair.h"


DataAimingErrorStructure AimingClass::GetState()
{
DataAimingErrorStructure displayData;
Substract<double> SubsPair;
displayData.TypeBlock = this->TypeBlock;

  displayData.LastError =  LastErrorChannel;
  displayData.LastErrorFiltered = LastErrorChannel;

  displayData.OutputPID = EnginePIDRegulator.GetCoord();
  displayData.BeginError = ErrorRecord.begin();
  displayData.EndError = CurrentRecord;
  qDebug() << "Current record - " << std::distance(ErrorRecord.begin(),CurrentRecord);
  CurrentRecord = ErrorRecord.begin();


  displayData.OutputKalman.VelocityEstimate = Filter.GetCoord();
  displayData.OutputKalman.CoordEstimate = Filter.GetCoord();
  displayData.OutputKalman.ExtrapolateStep = Filter.GetCoord();
  displayData.CalmanState = BlockDisable;

  displayData.NumberBlock = this->NumberChannel;
  displayData.State = this->StateBlock;
  displayData.PIDState = this->EnginePIDRegulator.StateBlock;

  displayData.AimingState = this->AimingState;

  if(this->AimingState == AimingFast || this->AimingState == AimingTuning)
  displayData.PIDParam = std::make_tuple(AimingFastParam.RateParam,AimingFastParam.DiffParam,AimingFastParam.IntParam);
  else
  displayData.PIDParam = std::make_tuple(AimingSlowParam.RateParam,AimingSlowParam.DiffParam,AimingSlowParam.IntParam);


return displayData;
}

QPair<double, double> AimingClass::GetCoord()
{
   return this->OutputCoord;
}



AimingClass::AimingClass()
{

	//======================================================================

    AimingPort.LinkAdapter(this,&AimingClass::MoveDesieredCoord,&AimingClass::GetCoordDesiered);


	this->AimingSlowParam.Common = 1;
	this->AimingSlowParam.RateParam = 5.1;
	this->AimingSlowParam.IntParam  = 0.0002;
	this->AimingSlowParam.DiffParam = 0.0002;

	this->AimingFastParam.Common = 1;           // for move by velocity one integrator plant
	this->AimingFastParam.RateParam = 16.45;
	this->AimingFastParam.IntParam  = 46.60;
	this->AimingFastParam.DiffParam = 0.0164;
	ErrorRecord.assign(100,QPair<double,double>(0,0));
	CurrentRecord = ErrorRecord.begin();


	this->LoadPIDParamFromFile();
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


	Filter.EnableFiltering(false);
}

void AimingClass::Reset()
{
    this->EnginePIDRegulator.ResetPID();
    this->OutputCoord = QPair<double,double>(0,0);

    if(PIDParamGroupStat.BestStatNumberCoord >= 2)
    AimingFastParam = PID_Param_Table[--PIDParamGroupStat.BestStatNumberCoord];
    else
    this->SetAimingSpeedRegim(AimingSlow);
}

bool AimingClass::isAimingFaultStatistic()
{
   auto Error =  CurrentStatistic.DispersionCoordDistance;

    if(Error > 3)
    {
        qDebug() << "AIMING STATISTIC FAULT ERROR DISPERSION" << Error;
        return true;
    }

    return false;
}
bool AimingClass::isAimingFault()
{
    auto Error = GetAbsError();

    if(Error > 10) return true;

    return false;
}

double AimingClass::GetAbsError()
{
    return std::hypot(LastErrorChannel.first, LastErrorChannel.second);
}

void AimingClass::SetAimingSpeedRegim(TypeAiming Aiming)
{
	AimingState = Aiming;
	if (AimingState == AimingSlow) EnginePIDRegulator.SetPIDParam(AimingSlowParam);
    if (AimingState == AimingFast) EnginePIDRegulator.SetPIDParam(AimingFastParam);
    if (AimingState == AimingTuning) EnginePIDRegulator.SetPIDParam(PID_Param_Table[0]);
}


QPair<double, double> AimingClass::GetCoordDesiered()
{
return DesireRelCoord;
}
void AimingClass::MoveDesieredCoord(QPair<double, double> MoveCoord)
{
  DesireRelCoord = DesireRelCoord + MoveCoord;
}
void AimingClass::SetDesieredCoord(QPair<double, double> NewDesieredCoord)
{
	Substract<double> SubsPair;
	NewDesieredCoord >> SubsPair;
	  DesireRelCoord >> SubsPair >> LastErrorChannel;

	  DesireRelCoord = NewDesieredCoord;
	
}


AimingClass::~AimingClass()
{
}

ImageProcessingClass& operator>>(ImageProcessingClass& ImageProcessor, AimingClass& AimingBlock)
{
    if(AimingBlock.StateBlock != BlockAtWork) return ImageProcessor;
    if(ImageProcessor.GetProcessor(AimingBlock.NumberChannel)->StateBlock != BlockAtWork) return ImageProcessor;


    if (ImageProcessor.GetProcessor(AimingBlock.NumberChannel)->FlagSpotFound)
	{

        Substract<double> SubsPair;
	ImageProcessor.GetLastCoordChannel(AimingBlock.NumberChannel) >> SubsPair;// PASS ABS COORD SPOT
                    ImageProcessor.GetLastCoordChannel(4)  >> SubsPair >> AimingBlock;

	}

					
return ImageProcessor;
}

void AimingClass::SetCoord(QPair<double, double> Coord)
{

    Substract<double> SubsPair;
    if (DesireAbsCoord != QPair<double, double>(0, 0) && this->StateBlock != BlockDisable)
    {
                 Coord >> SubsPair;
        DesireRelCoord >> SubsPair >> LastErrorChannel >> EnginePIDRegulator>> PixToRadian >> OutputCoord;

        std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
        LastErrorChannel >> Filter;
        std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint2 = std::chrono::high_resolution_clock::now();

        auto StepPeriod = std::chrono::duration<double>((TimePoint2 - TimePoint)).count();
        //qDebug() << "Aiming filter period - " << StepPeriod*1000;

        *CurrentRecord = LastErrorChannel; CurrentRecord++; if(CurrentRecord == ErrorRecord.end()) CurrentRecord = ErrorRecord.begin();


        //PID PARAM TUNING BY TABLE
        if(AimingState  != AimingTuning) return;


        if(PIDParamGroupStat.IsStatisticsLoaded()) {AimingState = AimingFast; return;};
        if(isAimingFaultStatistic())
        {
            PIDParamGroupStat.PerformAvailableData();
            AimingFastParam = PID_Param_Table[PIDParamGroupStat.BestStatNumberCoord];
            AimingState = AimingFast;
            return;
        };

        LastErrorChannel >> PIDParamGroupStat; LastErrorChannel >> CurrentStatistic;
        if( PID_Param_Table[PIDParamGroupStat.BestStatNumberCoord] != AimingFastParam  )
        {
            AimingFastParam = PID_Param_Table[PIDParamGroupStat.BestStatNumberCoord];
            this->EnginePIDRegulator.SetPIDParam(AimingFastParam);
        }
        //===========================================================


    }
}

void AimingClass::LoadPIDParamFromFile()
{

    QFile file("/home/broms/TrainerData/PIDParams.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    qDebug() << "LOAD PID PARAMETERS FROM - " << file.fileName();
    qDebug() << "=========================";

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        if(line.contains("==")) continue;

        QStringList list_preference = line.split(" ");

        if(list_preference.size() < 3) continue;

        double Common = 1;
        double rate_param = list_preference.at(0).toDouble();
        double int_param = list_preference.at(1).toDouble();
        double diff_param = list_preference.at(2).toDouble();


        this->PID_Param_Table.push_back(PIDParamStruct(rate_param,diff_param,int_param));

    }

    AimingFastParam = PID_Param_Table.front();
    PIDParamGroupStat = StatisticGroup(11,1500);

    double dispersion_threshold = 1.6;
    PIDParamGroupStat.FindBestStatisticCoord = [dispersion_threshold](std::map<int,Statistic>::iterator BeginStatistic,std::map<int,Statistic>::iterator EndStatistic) -> int
    {
        int min_pos = 1;
        auto current_stat = BeginStatistic;
        std::vector<float> dispersions;

        while(current_stat != EndStatistic) { dispersions.push_back(current_stat->second.AmplitudeCoordDeviation); current_stat++;};
        std::reverse(dispersions.begin(), dispersions.end());

        auto compare_to_threshold = [dispersion_threshold](double i){ return i < dispersion_threshold; };
        auto min_element = std::find_if(dispersions.begin(), dispersions.end(),compare_to_threshold);
             min_pos = std::distance(dispersions.begin(),min_element);
             min_pos = dispersions.size() - min_pos;
             qDebug() << "FOUND BEST PID WITH ERROR AMPLITUDE  - " << *min_element  << " NUMBER - " << min_pos  << " SIZE - " << dispersions.size();


        return min_pos-1;
    };
    file.close();
}

void AimingClass::SlotFilterEnable(bool OnOff)
{
  qDebug() << "KALMAN FILTER ENABLED - " << OnOff;
  Filter.EnableFiltering(OnOff);
}
