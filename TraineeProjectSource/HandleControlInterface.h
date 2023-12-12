#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageProcessingClass.h"
#include <QObject>


class HandleControlInterface: public QObject
{
	//Q_OBJECT
	public:
	virtual void ResetAll() = 0;
	virtual void StartStopWork(bool StartStop) = 0;
	virtual void SetBlockState(typeblocksenum TypeBlock, int NumberChannel, stateblocksenum State) = 0;
    //=======================================================================
	//POWER MODULES CONTROL
	virtual void TurnOnOffPowerCommutator(bool OnOff) = 0;
	virtual void TurnOnOffLaser(int Channel, bool OnOff) = 0;
	virtual void TurnOnOffAllLasers(bool OnOff) = 0;
	virtual void TurnOnOffEngines(bool OnOff) = 0;
	virtual void TurnOnOffChiller(bool OnOff) = 0;
    //=======================================================================
	//ENGINE CONTROL
	virtual void MoveEngine(int Direction,double X_Pos,double Y_Pos, int Channel) = 0;
	virtual void MoveEngineToNull(int Channel) = 0;
	virtual QPair<double,double> MoveEngineToWorkPos(int Channel) = 0;
    //=======================================================================
	//CALIBRATION
	virtual void StartCircleMoving(bool OnOff) = 0;
	virtual void StartRotationCalibrationProcess() = 0;
    //=======================================================================
	//CAMERA IMAGE PROC CONTROL
    virtual void TurnOnOffCamera(bool OnOff) = 0;
	virtual void SetImageThresHold(int Thres,int Channel) = 0;
	virtual void SetCameraParam(Control_Camera_Command Command) = 0;
	virtual void SetCameraROI(ROI_Channels_Command ROI) = 0;
	virtual void SetThresholdControlManual(bool OnOff) = 0;
	virtual void SetFrameFilterProcentage(int Procentage) = 0;
    //=======================================================================
	//AIMING CONTROL
    virtual void SetEngineCommandDelay(int DelayMks, int NumberChannel) = 0;
	virtual void SetAimingCoord(int x, int y, int NumberChannel) = 0;
    virtual void SetAimingType(TypeAiming Aiming,int Channel) = 0;
	virtual void SetPIDParam(double Common,double Rate, double Int, double diff) = 0;
    virtual void TurnOnOffKalmanFilter(bool OnOff, int Channel) = 0;
	virtual void TurnOnOffAxisEngine(bool, int,int) = 0;
    //=======================================================================
	virtual void LoadPreference() = 0;
	virtual void SaveEnginePosToFile() = 0;
    //=======================================================================
	//NOT USED TO DELETE
	virtual void SetAdjustModeWithCrossHair(bool OnOff) = 0;
	virtual void ChangeCalmanParam(double Qe,double Qn) = 0;
	virtual void RotateEngineAxis(int Channel, double AngleDegree) = 0;
};

