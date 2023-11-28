#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageProcessingClass.h"
#include <QObject>


class HandleControlInterface: public QObject
{
	//Q_OBJECT
	public :
	virtual void ResetAll() = 0;

	virtual void TurnOnOffLaser(int Channel, bool OnOff) = 0;
	virtual void TurnOnOffAllLasers(bool OnOff) = 0;


	virtual void TurnOnOffChiller(bool OnOff) = 0;

	virtual void SlotStartMoveByCircle(bool OnOff) = 0;

	virtual void MoveEngine(int Direction,double X_Pos,double Y_Pos, int Channel) = 0;
	virtual void MoveEngineToNull(int Channel) = 0;
	virtual void TurnOffAxisEngine(bool, int,int) = 0;


	virtual void RotateEngineAxis(int Channel, double AngleDegree) = 0;
	virtual void SetBlockState(typeblocksenum TypeBlock, int NumberChannel, stateblocksenum State) = 0;

	virtual void SlotStartStopWork(bool StartStop) = 0;
	virtual void SetPIDParam(double Common,double Rate, double Int, double diff) = 0;
	virtual QPair<double,double> MoveEnginesToStartPos(int Channel) = 0;
	virtual void SetImageThresHold(int Thres,int Channel) = 0;

	virtual void SetCameraParam(Control_Camera_Command Command) = 0;
	virtual void SetCameraROI(ROI_Channels_Command ROI) = 0;
	virtual void SlotSetAimingCoord(int x, int y, int NumberChannel) = 0;
	virtual void ChangeCalmanParam(double Qe,double Qn) = 0;
	virtual void SaveEnginePosToFile() = 0;
	virtual void SetAdjustModeWithCrossHair(bool OnOff) = 0;
	virtual void SetThresholdControlManual(bool OnOff) = 0;
	virtual void SetPowerSupplyOnCommutator(bool OnOff) = 0;
	virtual void SetFrameFilterProcentage(int Procentage) = 0;
	virtual void StartSystemRotationCalibration() = 0;
	virtual void LoadPreference() = 0;
    virtual void SetEngineCommandDelay(int DelayMks, int NumberChannel) = 0;

    virtual void ChangeAimingType(TypeAiming Aiming,int Channel) = 0;
    virtual void TurnOnOffKalmanFilter(bool OnOff, int Channel) = 0;

};

