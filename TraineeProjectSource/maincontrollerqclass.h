#pragma once
#include "ChillSystemClass.h"
#include "AirSystemClass.h"
#include "RemoteControlClass.h"
#include "AimingClass.h"
#include "LaserControlClass.h"
#include "EngineControlClass.h"
#include "mainwindowqclass.h"
#include "ImageProcessingClass.h"
#include "HandleControlInterface.h"
#include "ErrorRecieverClass.h"
#include "CameraInterfaceClass.h"
#include "KLPInterfaceClass.h"
#include "graphicswindow.h"
#include "SinusGeneratorClass.h"
#include "windowsinussource.h"
#include "RotateOperationContainer.h"
#include <memory> 
#include "ErrorPortControl.h"


enum StateMainController {Init = 0,FindChannels,WorkMode};

class MainControllerQClass;

class MainControllerQClass
	: public HandleControlInterface
{
	Q_OBJECT
public:
	 MainControllerQClass(MainWindowQClass* Window, GraphicsWindow* Window2);
	~MainControllerQClass();
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	typeblocksenum TypeBlock = MainContoller;

	SinusGeneratorClass SinusControlTest;
	QTimer timerCircle;
	QTimer timerInnerRotateCalibration;
	QPair<int, int> ErrorPointer = QPair<int,int>(0,0);
	static quint8* ImageBufferFullROI;


	bool FLAG_INITIALIZATION_DONE = false;
	int CounterCircle = 0;
	bool ShowAdjustCrosshair = true;


    //to delete 
	std::vector<QPair<double,double>> TestVectorRotateEngine;
	std::vector<QPair<double,double>> TestVectorRotateEngineAbs;
	std::vector<QPair<double,double>> TestVectorRotateEngineRemote;

	int CounterTestRotateEngine = 0;
	int CounterTestRotateEngineAvg = 0;
	//QTimer timer_to_test_measure_engine;
	//=======================================================

public slots:
	void SlotFindSpot_MoveEngineToWorkPos();  // working mode slots
	void SlotReceiveImage();
	void SlotReceiveErrorRemoteSensor();
	void SlotCheckDisplayDeviceModulesState();
	void SlotInnerRotateCalibration();


public slots:
	void SlotSetAimingCoord(int x, int y, int NumberChannel);
	void SlotStartStopWork(bool StartStop);
	void SlotMoveByCircle();
	void SlotStartMoveByCircle(bool OnOff) override;
	void SetAdjustModeWithCrossHair(bool OnOff);
	void StartSystemRotationCalibration();

public:
    void SetEngineCommandDelay(int DelayMks, int NumberChannel);
	void RotateEngineAxis(int Channel, double AngleDegree);
	void MoveEngine(int Direction,double X_Pos,double Y_Pos, int Channel);
	void MoveEngineToNull(int Channel);
	void TurnOffAxisEngine(bool state,int axis, int channel);

	void SetLaserFireFrequency(int Channel, int Frequency);
	void ResetAll();
	void SetPowerSupplyOnCommutator(bool OnOff);

	void SaveEnginePosToFile();
	QPair<double,double> MoveEnginesToStartPos(int Channel);

	void SetPIDParam(double Common,double Rate, double Int, double diff);
	void SetCalmanParam(double Qnx, double Qex,double Qvex);
	void SetImageThresHold(int Thres, int Channel);
	void SetFrameFilterProcentage(int Procentage);

	void TurnOnOffLaserPointer(bool OnOff);
	void InitialaizeROIProcess();
	void TurnOnOffChiller(bool OnOff);
	void TurnOnOffAir(bool OnOff);
	void LoadPreference();



	 void SetBlockState(typeblocksenum TypeBlock, int NumberChannel, stateblocksenum State);
	 void SetCameraParam(Control_Camera_Command Command);
     void SetCameraROI(ROI_Channels_Command ROI);
	 void ChangeAimingType(TypeAiming Aiming,int Channel);
	 void ChangeCalmanParam(double Qe, double Qn);
	 void SetThresholdControlManual(bool OnOff);
//================================================================
	void TurnOnOffLaserPilot(int Number, bool OnOff);
	void TurnOnOfLaserFire(int Number, bool OnOff);
	void TurnOnOffAllLasers(bool OnOff);

signals:
	void SignalImageReceived();
	void SignalStartIterateLasers(bool);
	void SignalSwitchAllLasers(bool);
private:
	ImageProcessingClass &GetFreeImageProcessor();
	bool Initialization();
	void Delay();
private:

	StateMainController State = Init;

	QThread* MainThread;

	MainWindowQClass*  WindowDisplay;
	GraphicsWindow* GraphicsDisplay;

	QVector<EngineControlClass*> EngineBlocks;
	QVector<AimingClass*>        AimingBlocks;

	std::shared_ptr<ChillSystemClass> ChillSystem;


	std::shared_ptr<AirSystemClass>        AirSystem;
	std::shared_ptr<RemoteControlClass>   RemoteControl;
	std::shared_ptr<AimingClass>          AimingBlock1;
	std::shared_ptr<AimingClass>          AimingBlock2;
	std::shared_ptr<AimingClass>          AimingBlock3;
	std::shared_ptr<AimingClass>          AimingBlockPointer;
	std::shared_ptr<LaserControlClass>    LaserControl;
	std::shared_ptr<ErrorRecieverClass>   ErrorRecievePort;
	std::shared_ptr<KLPInterfaceClass>    KLPInterface;
	std::shared_ptr<ImageProcessingClass> ImageProcessor;

	std::shared_ptr<EngineControlClass>   EngineControl1;
	std::shared_ptr<EngineControlClass>   EngineControl2;
	std::shared_ptr<EngineControlClass>   EngineControl3;
	std::shared_ptr<SinusGeneratorClass>   SinusGenerator;
};

