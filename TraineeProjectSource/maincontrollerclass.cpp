#include "CommonHeaders.h"

#include "DataDeviceStructureCommon.h"
#include "maincontrollerclass.h"
#include <functional>
#include <SubstractPair.h>
quint8* MainControllerClass::ImageBufferFullROI = new quint8[512*2048];
#define TAG "[ MAIN CTRL   ]" 


MainControllerClass::MainControllerClass(MainWindowClass* Window, GraphicsWindow* Window2)										
{
	QObject::connect(&this->timerCircle, SIGNAL(timeout()), this, SLOT(SlotMoveByCircle()));
	
	this->StateBlock = BlockAtWork;
	this->WindowDisplay = Window;
	this->GraphicsDisplay = Window2;
	this->Initialization();
	Delay();

	MainThread = new QThread;
	//QObject::connect(this, &MainControllerClass::WorkFinished, MainThread, &QThread::quit);
	//QObject::connect(this, &MainControllerClass::WorkFinished, MainThread, &QThread::deleteLater);

    //QObject::connect(this, &MainControllerClass::WorkFinished, Window, &QWidget::deleteLater);
    //QObject::connect(this, &MainControllerClass::WorkFinished, Window2, &QWidget::deleteLater);

	this->moveToThread(MainThread);
	this->timerInnerRotateCalibration.moveToThread(MainThread);


	QObject::connect(&Window->TimerToCheckStateBlocks, SIGNAL(timeout()), this, SLOT(SlotCheckDisplayDeviceModulesState()),Qt::DirectConnection);
	Window->TimerToCheckStateBlocks.start(30);

	MainThread->start(QThread::HighestPriority);

	QObject::connect(this, SIGNAL(SignalStartIterateLasers(bool)), LaserControl.get(), SLOT(SlotStartIterateLasers(bool)),Qt::QueuedConnection);
	QObject::connect(this, SIGNAL(SignalSwitchAllLasers(bool)), LaserControl.get(), SLOT(SlotSwitchAllLasers(bool)),Qt::QueuedConnection);


	Control_Camera_Command CameraCommand;
	CameraCommand.TimeExposure = 400;
	CameraCommand.AvarageBackground = 80;
	CameraCommand.SetCommand(COMM_AUTOEXPOSE_ON);

	SetCameraParam(CameraCommand);
    //QObject::connect(&AimingPort->TCPServer, SIGNAL(DataReceived()), this, SLOT(SlotReceiveErrorRemoteSensor()));

    QObject::connect(&SinusAimingBlockTest,SIGNAL(SignalNewDataAvailable()),this,SLOT(SlotReciveErrorTest()));
    SinusAimingBlockTest.SetRelativeOutput(false); SinusAimingBlockTest.SlotSetFrequency(2);
    SinusAimingBlockTest.SlotStartGenerate(true);

    AimingBlock1->SetDesieredCoord(QPair<double,double>(0,0));
    AimingBlock2->SetDesieredCoord(QPair<double,double>(0,0));
    AimingBlock3->SetDesieredCoord(QPair<double,double>(0,0));

    this->WindowDisplay->SlotSetInterfaceSize(1);
	return;
}	




MainControllerClass::~MainControllerClass()	//����������
{
}


void MainControllerClass::SlotCheckDisplayDeviceModulesState()
{
	Substract<double> SubsPair;


	DataImageProcAllChannels DataImageProc = ImageProcessor->GetDataAllChannels();

		  AimingBlock1->DesireAbsCoord >> SubsPair;
	ImageProcessor->Proc1->strob_coord >> SubsPair >> DataImageProc.Channel1.LastAimingCoord;
		  AimingBlock2->DesireAbsCoord >> SubsPair;
	ImageProcessor->Proc2->strob_coord >> SubsPair >> DataImageProc.Channel2.LastAimingCoord;
		  AimingBlock3->DesireAbsCoord >> SubsPair;
	ImageProcessor->Proc3->strob_coord >> SubsPair >> DataImageProc.Channel3.LastAimingCoord;
	DataImageProc.Channel4.LastAimingCoord = ErrorPointer;
	//=================================================


	DataEngineStructure EnginesData;
	EnginesData.TypeBlock = EngineControl1->TypeBlock;
	EnginesData.Engine1 = EngineControl1->GetEnginesState();
	EnginesData.Engine2 = EngineControl2->GetEnginesState();
	EnginesData.Engine3 = EngineControl3->GetEnginesState();
	//=================================================
    EnginesData   >> *WindowDisplay;
	DataImageProc >> *WindowDisplay;    // Вывод изображения с отметками лаезрного пятна и желаемых координат

	AimingBlock1->GetState() >> *WindowDisplay;     // Отображение ошибки наведения, выхода фильтра и ПИД регулятора, состояния блоков
	AimingBlock2->GetState() >> *WindowDisplay;     // данные идут на окно с графиками
	AimingBlock3->GetState() >> *WindowDisplay;     //

	LaserControl->LPilot1->GetState() >> *WindowDisplay;  // Состояние лазерных блоков 
	LaserControl->LPilot2->GetState() >> *WindowDisplay;  // иден на окно управления лазерами 
	LaserControl->LPilot3->GetState() >> *WindowDisplay;  // меняет красное и зеленое положение
	LaserControl->LaserPointer->GetState() >> *WindowDisplay;  //

	KLPInterface->CameraInterface->GetState() >> *WindowDisplay;
	ChillSystem->GetState() >> *WindowDisplay;
    //======================================================
	EnginesData >> *RemoteControl;
	LaserControl->GetLasersState() >> *RemoteControl;
    //======================================================

    this->DisplayFullImage(); //TEMP SULUTION DELETE OR REWORK LATER
}


void MainControllerClass::DisplayFullImage()
{
    PIXEL_WORD NEW_PIXELS(KLPInterface->CameraInterface->ImageBufferFullROI);
    uchar* Image = (uchar*)ImageBufferFullROI;
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 2048; x = x + 4)
		{
			{
				++NEW_PIXELS;
				*(Image) = NEW_PIXELS.pixel1;
				*(Image + 1) = NEW_PIXELS.pixel2;
				*(Image + 2) = NEW_PIXELS.pixel3;
				*(Image + 3) = NEW_PIXELS.pixel4;
				Image += 4;
			}
		}
	}
	QImage ImageD = QImage(ImageBufferFullROI, 2048, 512, 2048, QImage::Format_Grayscale8);
	if(this->ShowAdjustCrosshair)
	{
	QPen pen; pen.setWidth(1);
	pen.setColor(QColor(200, 200, 200));
	QFont Font("Times", 18, QFont::Bold);
	QPainter paint;
	paint.begin(&ImageD);
	paint.setPen(pen);
	paint.setFont(Font);
	paint.drawLine(1024, 256 - 20, 1024, 256 + 20);
	paint.drawLine(1024 - 20, 256, 1024 + 20, 256);

	paint.drawLine(1024, 206 - 20, 1024, 206 + 20);
	paint.drawLine(1024 - 20, 206, 1024 + 20, 206);
	paint.end();
	}
	ImageD = ImageD.scaled(1024, 256);
	emit WindowDisplay->SignalDispalyFullImage(ImageD);
}


bool MainControllerClass::Initialization()
{
	QString info_string;
	QDebug  debug_out(&info_string);

	qDebug() << TAG << "                   KLP INTERFACE CREATE !!!!!";
	KLPInterface = std::shared_ptr<KLPInterfaceClass>(new KLPInterfaceClass);

	Regim_CommutatorCommand CommutatorState;
							CommutatorState.TurnOnOffSupplyAll(true);

			KLPInterface->SetSateCommutator(CommutatorState); QThread::msleep(100);
            KLPInterface->SetSateCommutator(CommutatorState);

		quint8 Command = 0;
        Command |= COMM_AUTOEXPOSE_ON;
        QThread::msleep(100);
		Control_Camera_Command CameraCommand;
        CameraCommand.SetSizeImage(2048,512);
		CameraCommand.TimeExposure = 150;
		CameraCommand.AvarageBackground = 256;
	    CameraCommand.SetCommand(Command);

	        KLPInterface->CameraInterface->SendCommand(CameraCommand);

	this->ImageProcessor = std::shared_ptr<ImageProcessingClass>(new ImageProcessingClass);
	this->ImageProcessor->Proc1->FlagThresholdAutoControl = false;
	this->ImageProcessor->Proc2->FlagThresholdAutoControl = false;
	this->ImageProcessor->Proc3->FlagThresholdAutoControl = false;
	

	ChillSystem = std::shared_ptr<ChillerInterface>(new ChillerInterface);
	

	StateBlock = stateblocksenum::BlockAtInitializaiton;
	
	EngineControl1 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface1.get()));
	EngineControl2 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface2.get()));
	EngineControl3 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface3.get()));
	SetEngineCommandDelay(1,0);
    SetEngineCommandDelay(2,0);
    SetEngineCommandDelay(3,100);

	AimingBlock1= std::shared_ptr<AimingClass>(new AimingClass);
	AimingBlock2= std::shared_ptr<AimingClass>(new AimingClass);
	AimingBlock3= std::shared_ptr<AimingClass>(new AimingClass);
	
	LoadPreference();

	AimingBlock1->NumberChannel = 1;
	AimingBlock2->NumberChannel = 2;
	AimingBlock3->NumberChannel = 3;

	AimingBlockPointer= std::shared_ptr<AimingClass>(new AimingClass);
	SinusGenerator = std::shared_ptr<SinusGeneratorClass>(new SinusGeneratorClass);
	LaserControl    = std::shared_ptr<LaserControlClass>(new LaserControlClass);
	RemoteControl= std::shared_ptr<RemoteControlInterface>(new RemoteControlInterface(this));


	WindowDisplay->ConnectControlSignals((HandleControlInterface*)this);


	//ImageProcessor->Proc2->StateBlock = BlockDisable;
	//ImageProcessor->Proc3->StateBlock = BlockDisable;
	//ImageProcessor->ProcToPointer->StateBlock = BlockDisable;

	
	EngineControl1->StateBlock = BlockDisable;
	EngineControl2->StateBlock = BlockDisable;
	EngineControl3->StateBlock = BlockDisable;
	//AimingBlock1->StateBlock = BlockDisable;
	//AimingBlock2->StateBlock = BlockDisable;
	//AimingBlock3->StateBlock = BlockDisable;


	EngineBlocks.append(EngineControl1.get());
	EngineBlocks.append(EngineControl2.get());
	EngineBlocks.append(EngineControl3.get());

	AimingBlocks.append(AimingBlock1.get());
	AimingBlocks.append(AimingBlock2.get());
	AimingBlocks.append(AimingBlock3.get());


	SinusGenerator->SetLink(&AimingBlock3->AimingPort);

	WindowDisplay->AddWidgetToDisplay(SinusGenerator->WindowControl);
	WindowDisplay->AddWidgetToDisplay(SinusAimingBlockTest.WindowControl);

	WindowDisplay->AddWidgetToDisplay((AdjustableWidget*)RemoteControl->DisplayRemoteCommand);
	WindowDisplay->AddWidgetToDisplay(RemoteControl->AimingPort.ErrorPortWindowControl);

    qDebug() << TAG << "END INIT";


	return true;
}

void MainControllerClass::SetEngineCommandDelay(int DelayMks, int NumberChannel)
{

    if(NumberChannel == 1) EngineControl1->EngineInterface->CommandDelayMks = DelayMks;
    if(NumberChannel == 2) EngineControl2->EngineInterface->CommandDelayMks = DelayMks;
    if(NumberChannel == 3) EngineControl3->EngineInterface->CommandDelayMks = DelayMks;

}

void MainControllerClass::RotateEngineAxis(int Channel, double AngleDegree) 
{
	EngineControlClass* Engine = this->EngineControl1.get();
				switch (Channel)
				{
				case 1: Engine = this->EngineControl1.get(); break;
				case 2: Engine = this->EngineControl2.get(); break;
				case 3: Engine = this->EngineControl3.get(); break;
				}

				//qDebug() << TAG << "========================================";
				//Engine->RotateAxis.SetRotateAngle(AngleDegree);
				//Engine->RotateAxisInverse.SetRotateAngle(-AngleDegree);
				//qDebug() << TAG << "ROTATE ENGINE CHANNEL - " << Channel << "ANGLE - " << AngleDegree;
				//qDebug() << TAG << "Rotate dont work";
				//qDebug() << TAG << "========================================";

}

void MainControllerClass::StartStopWork(bool StartStop)
{
	//qDebug() << TAG << "SLOT START STOP WORK";
	if (!FLAG_INITIALIZATION_DONE)
	{
		//qDebug() << TAG << "START INITIALIZATION";
	QObject::connect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotFindSpot_MoveEngineToWorkPos()),Qt::QueuedConnection);

	EngineControl1->StateBlock = BlockAtWork;
	EngineControl2->StateBlock = BlockAtWork;
	EngineControl3->StateBlock = BlockAtWork;

	AimingBlock1->StateBlock = BlockAtWork;
	AimingBlock2->StateBlock = BlockAtWork;
	AimingBlock3->StateBlock = BlockAtWork;

	//this->MoveEngineToWorkPos(1);
	//QThread::msleep(50);
	//this->MoveEngineToWorkPos(2);
	//QThread::msleep(50);
	//this->MoveEngineToWorkPos(3);

	emit SignalStartIterateLasers(true);
	}


	if (FLAG_INITIALIZATION_DONE)
	{
			if (StartStop)
			{
			this->StateBlock = BlockAtWork;
			this->AimingBlock1->EnginePIDRegulator.ResetPID();
			this->AimingBlock2->EnginePIDRegulator.ResetPID();
			this->AimingBlock3->EnginePIDRegulator.ResetPID();
			}
			else
			{
			    qDebug() << TAG << "Stop work process";
			    this->StateBlock = BlockDisable;
                this->AimingBlock1->EnginePIDRegulator.ResetPID(); AimingBlock1->StateBlock = BlockDisable;
                this->AimingBlock2->EnginePIDRegulator.ResetPID(); AimingBlock2->StateBlock = BlockDisable;
                this->AimingBlock3->EnginePIDRegulator.ResetPID(); AimingBlock3->StateBlock = BlockDisable;
                EngineControl1->EngineInterface->SetToNull();
                EngineControl2->EngineInterface->SetToNull();
                EngineControl3->EngineInterface->SetToNull();
				emit SignalSwitchAllLasers(false);
				this->FLAG_INITIALIZATION_DONE = false;

                //KLPInterface->DeinitializeInterface();
                //QThread::msleep(100);
			}
	}

    if(this->StateBlock == BlockAtInitializaiton && StartStop == false)
    {
			//qDebug() << TAG << "BREAK INITIALIZATION AND OFF";
	        emit SignalStartIterateLasers(false);
			emit SignalSwitchAllLasers(false);

    }

}

void MainControllerClass::SlotFindSpot_MoveEngineToWorkPos()
{

	if (this->StateBlock == BlockDisable) // SYSTEM OFF, STOP PROCESSAimingInFullImage
	{
		LaserControl->TimerToIterateLasers.stop();
		QObject::disconnect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotFindSpot_MoveEngineToWorkPos())); return;
	}


	ImageStruct newImage = KLPInterface->CameraInterface->GetNewImage();
	State = FindChannels;
	StateBlock = BlockAtInitializaiton;


		if (!FLAG_INITIALIZATION_DONE && newImage.x_size == 2048)         //FIND SPOT AND START AIMING IN FULL IMAGE
		{
		    // FIND SPOT AND MOVING TO DESIRE POS WHILE StatProcessorLong is loading in Processor objects
		if (LaserControl->LPilot2->IsOnOff()) { newImage >> *ImageProcessor->Proc1; *ImageProcessor >> *AimingBlock1; *AimingBlock1 >> *EngineControl1;}
		if (LaserControl->LPilot1->IsOnOff()) { newImage >> *ImageProcessor->Proc2; *ImageProcessor >> *AimingBlock2; *AimingBlock2 >> *EngineControl2;}
		if (LaserControl->LPilot3->IsOnOff()) { newImage >> *ImageProcessor->Proc3; *ImageProcessor >> *AimingBlock3; *AimingBlock3 >> *EngineControl3;}

		if (LaserControl->LaserPointer->IsOnOff()) newImage >> *ImageProcessor->ProcToPointer;
		}
    

	    if(ImageProcessor->Proc1->StateBlock == BlockDisable) {ImageProcessor->Proc1->AimingState = NotAiming; ImageProcessor->Proc1->ROI_MODE = 2;};
        if(ImageProcessor->Proc2->StateBlock == BlockDisable) {ImageProcessor->Proc2->AimingState = NotAiming; ImageProcessor->Proc2->ROI_MODE = 2;};
        if(ImageProcessor->Proc3->StateBlock == BlockDisable) {ImageProcessor->Proc3->AimingState = NotAiming; ImageProcessor->Proc3->ROI_MODE = 2;};


        if (!FLAG_INITIALIZATION_DONE &&
            ImageProcessor->Proc1->AimingState != SpotNoFoundState &&
            ImageProcessor->Proc2->AimingState != SpotNoFoundState &&
            ImageProcessor->Proc3->AimingState != SpotNoFoundState &&
            ImageProcessor->ProcToPointer->AimingState != SpotNoFoundState)
		{
            // SpotNotFound state while StatProcessorLong is not loaded and Dispersion > 32 in image Processors
			this->FLAG_INITIALIZATION_DONE = true;
	        emit SignalStartIterateLasers(false);
			emit SignalSwitchAllLasers(true);


					ROI_Channels_Command Camera_ROI;


                    //int y_center = 220;
                    int y1 = AimingBlock1->BeamCenteredPosition.second;
                    int y2 = AimingBlock2->BeamCenteredPosition.second;
                    int y3 = AimingBlock3->BeamCenteredPosition.second;
                    int y_center = (y1 + y2 + y3) / 3;
					Camera_ROI.X1 = AimingBlock1->BeamCenteredPosition.first - 128;
					Camera_ROI.X2 = AimingBlock2->BeamCenteredPosition.first - 128; 
					Camera_ROI.X3 = AimingBlock3->BeamCenteredPosition.first - 128; 
					Camera_ROI.X4 = AimingBlock3->BeamCenteredPosition.first + 300;
					Camera_ROI.Y1 = y_center - 128; Camera_ROI.Y2 = Camera_ROI.Y1; Camera_ROI.Y3 = Camera_ROI.Y1; Camera_ROI.Y4 = Camera_ROI.Y1;
					Camera_ROI.SetSizeROI(256, 256);
					bool result  = this->KLPInterface->CameraInterface->SetROI(Camera_ROI);

					ImageProcessor->Proc1->strob_coord.first = Camera_ROI.X1; ImageProcessor->Proc1->strob_coord.second = Camera_ROI.Y1;
					ImageProcessor->Proc2->strob_coord.first = Camera_ROI.X2; ImageProcessor->Proc2->strob_coord.second = Camera_ROI.Y1;
					ImageProcessor->Proc3->strob_coord.first = Camera_ROI.X3; ImageProcessor->Proc3->strob_coord.second = Camera_ROI.Y1;

				ImageProcessor->Proc1->SwitchToAimingInStrob();
				ImageProcessor->Proc2->SwitchToAimingInStrob();
				ImageProcessor->Proc3->SwitchToAimingInStrob();

				ImageProcessor->ProcToPointer->SwitchToAimingInFullImage();

				AimingBlock1->StateBlock = BlockDisable;
				AimingBlock2->StateBlock = BlockDisable;
				AimingBlock3->StateBlock = BlockDisable;

			return;
		}

        if (FLAG_INITIALIZATION_DONE && (ImageProcessor->Proc1->ROI_MODE == 1 || ImageProcessor->Proc2->ROI_MODE == 1 || ImageProcessor->Proc3->ROI_MODE == 1))
        {
             newImage >> *ImageProcessor;
            *ImageProcessor >> *AimingBlock1; *AimingBlock1 >> *EngineControl1;
            *ImageProcessor >> *AimingBlock2; *AimingBlock2 >> *EngineControl2;
            *ImageProcessor >> *AimingBlock3; *AimingBlock3 >> *EngineControl3;
        }

        if (FLAG_INITIALIZATION_DONE && (ImageProcessor->Proc1->ROI_MODE == 2 && ImageProcessor->Proc2->ROI_MODE == 2 && ImageProcessor->Proc3->ROI_MODE == 2))
		{
				AimingBlock1->StateBlock = BlockAtWork;
				AimingBlock2->StateBlock = BlockAtWork;
				AimingBlock3->StateBlock = BlockAtWork;


			QObject::disconnect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotFindSpot_MoveEngineToWorkPos()));
			QObject::connect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotReceiveImage()), Qt::QueuedConnection);
			qDebug() << TAG << "INITIZALIZATION END";
		}

}
QPair<double,double> MainControllerClass::MoveEngineToWorkPos(int Channel)
{
	switch (Channel)
	{
	case 1: AimingBlock1->DesireAbsCoord = AimingBlock1->BeamCenteredPosition;
	case 2: AimingBlock2->DesireAbsCoord = AimingBlock2->BeamCenteredPosition;
	case 3: AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
	}

	return AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
}


void MainControllerClass::MoveEngineToNull(int Channel)
{
	EngineControlClass* Engine;
				switch (Channel)
				{
				case 1: Engine = this->EngineControl1.get(); break;
				case 2: Engine = this->EngineControl2.get(); break;
				case 3: Engine = this->EngineControl3.get(); break;
				}
		Engine->EngineInterface->SetToNull();
		this->AimingBlock1->EnginePIDRegulator.ResetPID();
		this->AimingBlock2->EnginePIDRegulator.ResetPID();
		this->AimingBlock3->EnginePIDRegulator.ResetPID();
		return;
}

void MainControllerClass::MoveEngine(int Direction, double X_Pos,double Y_Pos, int Channel)
{
	EngineControlClass* Engine = this->EngineControl1.get();
				switch (Channel)
				{
				case 1:
					Engine = this->EngineControl1.get();
				break;
				case 2:
					Engine = this->EngineControl2.get();
				break;
				case 3:
					Engine = this->EngineControl3.get();
				break;
				}


                qDebug() << TAG << "MOVE ENGINE SLOT";
				QPair<double, double> StepPosRad;
				QPair<double, double> DesirePos = QPair<double,double>(0,0);
				QPair<double, double> CurrentPos = Engine->GetLastCoord();

				//CurrentPos.first = CurrentPos.first / 2;
				//CurrentPos.second = CurrentPos.second / sqrt(2);

				//CurrentPos >> Engine->RotateAxisInverse >> CurrentPos;
				CurrentPos >> Engine->RotationAxisInverse >> CurrentPos;

                                  // devide on 200 to convert slider POS to angle seconds
				DesirePos.first = (-X_Pos/200)/(60*60)*M_PI/180;
				DesirePos.second = (-Y_Pos/200)/(60*60)*M_PI/180;
								  // convert angle seconds to radian

				StepPosRad.first = DesirePos.first - CurrentPos.first;
				StepPosRad.second = DesirePos.second - CurrentPos.second;
				Engine->SlotMoveOnStep(StepPosRad);
}

void MainControllerClass::TurnOnOffAllLasers(bool OnOff) { emit SignalSwitchAllLasers(OnOff); }

void MainControllerClass::ResetAll()
{
	this->KLPInterface->ResetCommutator(); QThread::msleep(100);
	this->EngineControl1->EngineInterface->ResetEngine(); QThread::msleep(100);
	this->EngineControl2->EngineInterface->ResetEngine(); QThread::msleep(100);
	this->EngineControl3->EngineInterface->ResetEngine(); QThread::msleep(100);
	this->KLPInterface->CardSoftReset();
}

void MainControllerClass::SaveEnginePosToFile()
{
	QString IniFile = "E:/ENGINE_POS.ini";
	//qDebug() << TAG << "Save settings to - " << IniFile;
	QSettings Settings(IniFile, QSettings::IniFormat);

	Settings.beginGroup("ENGINE_POS");
		Settings.setValue("ENGINE1_X", this->EngineControl1->GetLastCoord().first);
		Settings.setValue("ENGINE1_Y", this->EngineControl1->GetLastCoord().second);

		Settings.setValue("ENGINE2_X", this->EngineControl2->GetLastCoord().first);
		Settings.setValue("ENGINE2_Y", this->EngineControl2->GetLastCoord().second);

		Settings.setValue("ENGINE3_X", this->EngineControl3->GetLastCoord().first);
		Settings.setValue("ENGINE3_Y", this->EngineControl3->GetLastCoord().second);
	Settings.endGroup();
	Settings.sync();
}


void MainControllerClass::SetPIDParam(double Common, double Rate, double Int, double diff)
{
 AimingBlock1->AimingFastParam.Common = Common;
 AimingBlock1->AimingFastParam.RateParam = Rate;
 AimingBlock1->AimingFastParam.IntParam = Int;
 AimingBlock1->AimingFastParam.DiffParam = diff;
 
 AimingBlock2->AimingFastParam.Common = Common;
 AimingBlock2->AimingFastParam.RateParam = Rate;
 AimingBlock2->AimingFastParam.IntParam = Int;
 AimingBlock2->AimingFastParam.DiffParam = diff;
 
 AimingBlock3->AimingFastParam.Common = Common;
 AimingBlock3->AimingFastParam.RateParam = Rate;
 AimingBlock3->AimingFastParam.IntParam = Int;
 AimingBlock3->AimingFastParam.DiffParam = diff;
 
 if(AimingBlock1->AimingState == AimingFast) AimingBlock1->EnginePIDRegulator.SetPIDParam(AimingBlock1->AimingFastParam);
 if(AimingBlock2->AimingState == AimingFast) AimingBlock2->EnginePIDRegulator.SetPIDParam(AimingBlock2->AimingFastParam);
 if(AimingBlock3->AimingState == AimingFast) AimingBlock3->EnginePIDRegulator.SetPIDParam(AimingBlock3->AimingFastParam);
}


void MainControllerClass::SetImageThresHold(int Thres,int Channel)
{
	if(Channel == 1) ImageProcessor->Proc1->Threshold = Thres;
	if(Channel == 2) ImageProcessor->Proc2->Threshold = Thres;
	if(Channel == 3) ImageProcessor->Proc3->Threshold = Thres;
	if(Channel == 4) ImageProcessor->ProcToPointer->Threshold = Thres;
}

void MainControllerClass::TurnOnOffLaser(int NumberLaser, bool OnOff)
{
	if(LASER_GROUP(NumberLaser) == GUID_GROUP) this->LaserControl->SlotSwitchPilotBeam(NumberLaser, OnOff);
	if(LASER_GROUP(NumberLaser) == POWER_GROUP) this->LaserControl->SlotSwitchPowerBeam(NumberLaser, OnOff);

	if(LASER_GROUP(NumberLaser) == GUID_GROUP) 
	{
    if(NumberLaser == GUID_LASER1) ImageProcessor->Proc1->StopProcessing(OnOff);
    if(NumberLaser == GUID_LASER2) ImageProcessor->Proc2->StopProcessing(OnOff);
    if(NumberLaser == GUID_LASER3) ImageProcessor->Proc3->StopProcessing(OnOff);
	}

    if(LASER_GROUP(NumberLaser) == POINTER_GROUP) 
	{
	ImageProcessor->ProcToPointer->StopProcessing(OnOff);
	this->LaserControl->SlotSwitchPointerBeam(OnOff);
	}
}


void MainControllerClass::SetCommandChiller(CommandChillerStructure Command)
{
	this->ChillSystem->ResetComPort(Command.PORT);  //REST PORT IF PORT DIFFERENCES
	this->ChillSystem->SlotSetWorkTemperature(Command.WORK_TEMP);
	this->ChillSystem->SlotTurnOnOff(Command.ON_OFF);
}

void MainControllerClass::SlotMoveByCircle()
{
	CounterCircle++;
	double x = 50*std::sin(2*3.14*CounterCircle/360);
	double y = 50*std::cos(2*3.14*CounterCircle/360);
	this->SetAimingCoord(x + 128, y + 128, 4);

	if (CounterCircle == 360) CounterCircle = 0;
}

void MainControllerClass::StartCircleMoving(bool OnOff)
{
 if(OnOff) this->timerCircle.start(10); else this->timerCircle.stop();
}

void MainControllerClass::TurnOnOffCamera(bool OnOff)
{
	qDebug() << "CAMERA TURN ON OFF DOESN'T WORK";
}
void MainControllerClass::SetBlockState(typeblocksenum TypeBlock, int NumberChannel, stateblocksenum State)
{
	switch (TypeBlock)
	{
	case EngineControlBlock: EngineBlocks.at(NumberChannel-1)->StateBlock = State; break;
	case CamerasControlBlock: KLPInterface->CameraInterface->SetState(State); break;
	case AimingBlock: AimingBlocks.at(NumberChannel - 1)->StateBlock = State; break;
	case PIDBlock: AimingBlocks.at(NumberChannel - 1)->EnginePIDRegulator.StateBlock = State; break;
	case ImageProcBlock: ImageProcessor->Processors.at(NumberChannel - 1)->StateBlock = State; break;
	case ChillControlBlock: break;
	case CalmanFilterBlock:
		//AimingBlocks.at(NumberChannel - 1)->CalmanFilter.StateBlock = State;
		break;
	default: break;
	}

}

void MainControllerClass::SetAimingCoord(int x, int y, int NumberChannel)
{
	auto PointerCoord = ImageProcessor->ProcToPointer->spot_coord_abs;
	switch (NumberChannel)
	{
	case 1:
		this->AimingBlock1->DesireAbsCoord.first = ImageProcessor->Proc1->strob_coord.first + x;
		this->AimingBlock1->DesireAbsCoord.second = ImageProcessor->Proc1->strob_coord.second + y;
        this->AimingBlock1->DesireRelCoord = AimingBlock1->DesireAbsCoord - PointerCoord;
		break;
	case 2:
		this->AimingBlock2->DesireAbsCoord.first = ImageProcessor->Proc2->strob_coord.first + x;
		this->AimingBlock2->DesireAbsCoord.second = ImageProcessor->Proc2->strob_coord.second + y;
        this->AimingBlock2->DesireRelCoord = AimingBlock2->DesireAbsCoord - PointerCoord;
		break;
	case 3:
		this->AimingBlock3->DesireAbsCoord.first = ImageProcessor->Proc3->strob_coord.first + x;
		this->AimingBlock3->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;
		this->AimingBlock3->DesireRelCoord = AimingBlock3->DesireAbsCoord - PointerCoord;
		break;
	case 4:
		this->AimingBlock1->DesireAbsCoord.first = ImageProcessor->Proc1->strob_coord.first + x;
		this->AimingBlock1->DesireAbsCoord.second = ImageProcessor->Proc1->strob_coord.second + y;
		this->AimingBlock2->DesireAbsCoord.first = ImageProcessor->Proc2->strob_coord.first + x;
		this->AimingBlock2->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;
		this->AimingBlock3->DesireAbsCoord.first = ImageProcessor->Proc3->strob_coord.first + x;
		this->AimingBlock3->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;

		this->AimingBlock1->DesireRelCoord = AimingBlock1->DesireAbsCoord - PointerCoord;
        this->AimingBlock2->DesireRelCoord = AimingBlock2->DesireAbsCoord - PointerCoord;
        this->AimingBlock3->DesireRelCoord = AimingBlock3->DesireAbsCoord - PointerCoord;

		ErrorPointer.first = x;
		ErrorPointer.second = y;
		break;

	}
}

void MainControllerClass::Delay()
{
    auto StartTimePoint = std::chrono::high_resolution_clock::now();
    QThread::usleep(100);
    auto NewTimePoint = std::chrono::high_resolution_clock::now();
}

void MainControllerClass::SlotReciveErrorTest()
{
    auto Error = SinusAimingBlockTest.GetCoord();
    Error >> *AimingBlock1;                //Send new coord spot to aiming
    Error >> *AimingBlock2;
    Error >> *AimingBlock3;
}

void MainControllerClass::SlotReceiveImage()
{
	if (this->StateBlock == BlockDisable) return;
	ImageStruct newImage = KLPInterface->CameraInterface->GetNewImage();

		newImage >> *ImageProcessor;

    *ImageProcessor >> *AimingBlock1;                //Send new coord spot to aiming
	*ImageProcessor >> *AimingBlock2;
	*ImageProcessor >> *AimingBlock3;

	*AimingBlock1 >> *EngineControl1;                 //Calculate control signal and move engine
    *AimingBlock2 >> *EngineControl2;
	*AimingBlock3 >> *EngineControl3;

    if(EngineControl1->isEngineFault()) {AimingBlock1->Reset(); EngineControl1->ResetToLastSavePosition();};
    if(EngineControl2->isEngineFault()) {AimingBlock2->Reset(); EngineControl2->ResetToLastSavePosition();};
    if(EngineControl3->isEngineFault()) {AimingBlock3->Reset(); EngineControl3->ResetToLastSavePosition();};

    if(!AimingBlock1->isAimingFault()) EngineControl1->SavePosition();
    if(!AimingBlock2->isAimingFault()) EngineControl2->SavePosition();
    if(!AimingBlock3->isAimingFault()) EngineControl3->SavePosition();
}

void MainControllerClass::SlotInnerRotateCalibration()
{

	if (EngineControl1->RotationAxis.output_to_optimize_rotation.size() == TEST_DATA_COUT)
	{
		qDebug() << TAG << "STOP INNER ROTATE CALIBRATION";
		timerInnerRotateCalibration.stop();
		QObject::disconnect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
	}

		AimingBlock1->SetDesieredCoord(EngineControl1->RotationAxis.MeasureFilter.DataFilter.WaitInputCoord + AimingBlock1->BeamCenteredPosition);
		auto CurrentPos1 = EngineControl1->EngineInterface->GetCoord();
		CurrentPos1 = CurrentPos1 * double(180 * 60 * 60 / 3.14);
		//qDebug() << TAG << "Current coord - " << CurrentPos1.first << CurrentPos1.second;
		//auto RelativeCoord = ImageProcessor->Proc1->spot_coord_abs - AimingBlock1->BeamCenteredPosition;
		ImageProcessor->Proc1->spot_coord_abs >> EngineControl1->RotationAxis.MeasureFilter >> EngineControl1->RotationAxis;
		CurrentPos1 >> EngineControl1->RotationAxis.MeasureFilter >> EngineControl1->RotationAxis;
}

void MainControllerClass::StartRotationCalibrationProcess()
{
	EngineControl1->RotationAxis.Reset();
	EngineControl2->RotationAxis.Reset();
	EngineControl3->RotationAxis.Reset();

	QObject::connect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
	timerInnerRotateCalibration.start(40);
}



void MainControllerClass::SlotReceiveErrorRemoteSensor()
{
    if(this->StateBlock == BlockDisable) return;

	QPair<double, double> Error;
	QPair<double, double> NewDesireCoord;
	auto& AimingPort = RemoteControl->AimingPort;

	AimingPort >> Error;
	if(AimingPort.isValid())
	{
			auto PointerCoord = ImageProcessor->ProcToPointer->spot_coord_abs;
			if (AimingPort.error_direction == 1 || AimingPort.error_direction == 0)
			{
				qDebug() << TAG << "Remote error to channel 1";
				NewDesireCoord =  ImageProcessor->Proc1->spot_coord_abs - PointerCoord - Error;
				AimingBlock1->SetDesieredCoord(NewDesireCoord);
			}

			if (AimingPort.error_direction == 2 || AimingPort.error_direction == 0)
			{
				qDebug() << TAG << "Remote error to channel 2";
				NewDesireCoord =  ImageProcessor->Proc2->spot_coord_abs - PointerCoord - Error;
				AimingBlock2->SetDesieredCoord(NewDesireCoord);
			}

			if (AimingPort.error_direction == 3 || AimingPort.error_direction == 0)
			{
				qDebug() << TAG << "Remote error to channel 3";
				NewDesireCoord =  ImageProcessor->Proc3->spot_coord_abs - PointerCoord - Error;
				AimingBlock3->SetDesieredCoord(NewDesireCoord);
			}
    QObject::disconnect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
    }


	//=======================================================================================================================================
	if (AimingPort.error_direction == 1 && !AimingPort.isValid())
	{
		AimingBlock1->SetDesieredCoord(AimingPort.RemoteToBaseTransform.MeasureFilter.DataFilter.WaitInputCoord + AimingBlock1->BeamCenteredPosition);

		auto abs_coord = ImageProcessor->Proc1->spot_coord_abs;
				abs_coord >> AimingPort.RemoteToBaseTransform.MeasureFilter >> AimingPort.RemoteToBaseTransform;
					Error >> AimingPort.RemoteToBaseTransform.MeasureFilter >> AimingPort.RemoteToBaseTransform;
	}


}
	
void MainControllerClass::SetAimingType(TypeAiming Aiming,int Channel)
{
	if(Channel == 1) AimingBlock1->SetAimingSpeedRegim(Aiming);
	if(Channel == 2) AimingBlock2->SetAimingSpeedRegim(Aiming);
	if(Channel == 3) AimingBlock3->SetAimingSpeedRegim(Aiming);
}
void MainControllerClass::ChangeCalmanParam(double Qe, double Qn) { }

void MainControllerClass::SetCameraParam(Control_Camera_Command Command)
{
 if(KLPInterface) KLPInterface->CameraInterface->SendCommand(Command);
}

void MainControllerClass::SetCameraROI(ROI_Channels_Command ROI)
{
 if(KLPInterface) KLPInterface->CameraInterface->SetROI(ROI);
}

void MainControllerClass::SetAdjustModeWithCrossHair(bool OnOff) { this->ShowAdjustCrosshair = OnOff; }

void MainControllerClass::TurnOnOffPowerCommutator(bool OnOff)
{
	Regim_CommutatorCommand CommutatorState;
							CommutatorState.TurnOnOffSupplyAll(OnOff);

	KLPInterface->SetSateCommutator(CommutatorState);
}
void MainControllerClass::TurnOnOffEngines(bool OnOff)
{

}

void MainControllerClass::SetThresholdControlManual(bool OnOff)
{
	this->ImageProcessor->Proc1->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->Proc2->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->Proc3->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->ProcToPointer->FlagThresholdAutoControl = !OnOff;
}

void MainControllerClass::SetFrameFilterProcentage(int Procentage)
{
	this->ImageProcessor->Proc1->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc2->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc3->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->ProcToPointer->FrameFilterProcentage = Procentage/100.0;
}


void MainControllerClass::TurnOnOffAxisEngine(bool state,int axis, int channel)
{
	QVector<EngineInterfaceClass*> Channels;
	Channels.append(EngineControl1->EngineInterface); Channels.append(EngineControl2->EngineInterface); Channels.append(EngineControl3->EngineInterface);
	if (axis == 1) Channels[channel-1]->VerticalAxisOn = state;
	if (axis == 2) Channels[channel-1]->HorizontalAxisOn = state;
}

void MainControllerClass::LoadPreference()
{
  qDebug() << TAG << "================================================";
  qDebug() << TAG << "[ MAIN CONTROLLER LOAD PREFERENCE ]";

  QSettings Settings("/home/broms/DEVELOPMENT/DATA/TrainerData/TrainerSetting.ini", QSettings::IniFormat);
  EngineControl1->LoadSettings(Settings);
  EngineControl2->LoadSettings(Settings);
  EngineControl3->LoadSettings(Settings);
  AimingBlock1->LoadSettings(Settings);
  AimingBlock2->LoadSettings(Settings);
  AimingBlock3->LoadSettings(Settings);
  

  AimingBlock1->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;
  AimingBlock2->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;
  AimingBlock3->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;
  
  AimingBlock1->RadianToPix.Scale = AimingBlock1->PixToRadian.Scale;
  AimingBlock2->RadianToPix.Scale = AimingBlock2->PixToRadian.Scale;
  AimingBlock3->RadianToPix.Scale = AimingBlock3->PixToRadian.Scale;
  
  //int x_center = 1024; int y_center = 220;
  int x1 = 701; int x2 = 1016; int x3 = 1315;
  int y1 = 244; int y2 = 221;  int y3 = 283;
  auto PointerCenteredCoord = QPair<double,double>(1027,468);
  
  AimingBlock1->BeamCenteredPosition = QPair<int, int>(x1,y1);
  AimingBlock2->BeamCenteredPosition = QPair<int, int>(x2,y2);
  AimingBlock3->BeamCenteredPosition = QPair<int, int>(x3,y3);
  
  AimingBlock1->DesireAbsCoord = AimingBlock1->BeamCenteredPosition;
  AimingBlock2->DesireAbsCoord = AimingBlock2->BeamCenteredPosition;
  AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
  
  AimingBlock1->DesireRelCoord = AimingBlock1->BeamCenteredPosition - PointerCenteredCoord;
  AimingBlock2->DesireRelCoord = AimingBlock2->BeamCenteredPosition - PointerCenteredCoord;
  AimingBlock3->DesireRelCoord = AimingBlock3->BeamCenteredPosition - PointerCenteredCoord;

  qDebug() << TAG << "DESIRE RELATIVE " << AimingBlock1->DesireRelCoord << " CHANNEL - " << 1;
  qDebug() << TAG << "DESIRE RELATIVE " << AimingBlock2->DesireRelCoord << " CHANNEL - " << 2;
  qDebug() << TAG << "DESIRE RELATIVE " << AimingBlock3->DesireRelCoord << " CHANNEL - " << 3;
  qDebug() << TAG << "================================================";
}

void MainControllerClass::SlotFinishWork()
{
    qDebug() << TAG << "MAIN WINDOW CLOSED START TO FINISH WORK";
    EngineControl1->EngineInterface->SetToNull();
    EngineControl2->EngineInterface->SetToNull();
    EngineControl3->EngineInterface->SetToNull();
    LaserControl->SlotSwitchAllLasers(false);

    QObject::disconnect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotReceiveImage()));
    KLPInterface->DeinitializeInterface();

    WindowDisplay->deleteLater();
    this->deleteLater();


    MainThread->quit();
    MainThread->deleteLater();
    //emit WorkFinished();
    qDebug() << TAG << "MAIN CONTROLLER STOPPED";
}

void MainControllerClass::TurnOnOffKalmanFilter(bool OnOff, int Channel)
{
 switch (Channel)
 {
 	case 1: AimingBlock1->SlotFilterEnable(OnOff);
 	case 2: AimingBlock2->SlotFilterEnable(OnOff);
 	case 3: AimingBlock3->SlotFilterEnable(OnOff);
 }
}

//====================================TEST SIGNALS========================================
TestSignals::~TestSignals()
{
    timerSignalGenerate.stop();
    QObject::disconnect(&timerSignalGenerate,SIGNAL(timeout()),this,SLOT(GenerateNewData()));
}
TestSignals::TestSignals()
{
    INPUT_VECTOR_SIZE = 30;
    GenerateInitSeries();
    QObject::connect(&timerSignalGenerate,SIGNAL(timeout()),this,SLOT(GenerateNewData()));
}
TestSignals::TestSignals(int size)
{
    INPUT_VECTOR_SIZE = size;
    GenerateInitSeries();
    QObject::connect(&timerSignalGenerate,SIGNAL(timeout()),this,SLOT(GenerateNewData()));
}
TestSignals::TestSignals(const TestSignals& copy)
{
    INPUT_VECTOR_SIZE = copy.INPUT_VECTOR_SIZE;
    time_series = copy.time_series;
    signals_noize = copy.signals_noize;
    signals_noize_free = copy.signals_noize_free;
    derivate_noize_free = copy.derivate_noize_free;
}
QPair<double, double> TestSignals::GetCoord()
{
    QPair<double, double> Coord;
    Coord.first = signals_noize[0].back();
    Coord.second = signals_noize[1].back();
    return Coord;
}
void TestSignals::GenerateInitSeries()
{
    qDebug() << TAG << "GENERATE INIT SERIES SIZE - " << INPUT_VECTOR_SIZE;
    time_series.resize(INPUT_VECTOR_SIZE); time_series.assign(INPUT_VECTOR_SIZE, 0.0);

    for (int n = 1; n < INPUT_VECTOR_SIZE; n++) time_series[n] = time_series[n - 1] + 0.002;

    for (auto Freq: Frequences) {

        signals_noize.push_back(vector<qreal>());
        signals_noize_free.push_back(vector<qreal>());
        derivate_noize_free.push_back(vector<qreal>());

        for (int n = 0; n < INPUT_VECTOR_SIZE; n++)
        {
            signals_noize_free.back().push_back(Amplitude * std::sin(Freq * time_series[n]) );
            signals_noize.back().push_back( signals_noize_free.back()[n] * NoizeAmplitude*double(rand())/RAND_MAX - NoizeAmplitude/2 );
        }


    }
    qreal previous_value = 0;
    qreal derivate = 0;
    qreal Tp = 0.002;
    for(const auto& Value: signals_noize_free[0]) {derivate = (Value - previous_value)/Tp; derivate_noize_free[0].push_back(derivate); previous_value = Value;};
    for(const auto& Value: signals_noize_free[1]) {derivate = (Value - previous_value)/Tp; derivate_noize_free[1].push_back(derivate); previous_value = Value;};
    derivate_noize_free[0].front() = derivate_noize_free[0][1];
    derivate_noize_free[1].front() = derivate_noize_free[1][1];



}
void TestSignals::GenerateNewData()
{
    time_series.push_back(time_series.back() + 0.002);

    if(time_series.back() > 4*INPUT_VECTOR_SIZE*0.002) time_series.erase(time_series.begin());


    auto signal_noize_free = signals_noize_free.begin();
    auto signal_noize = signals_noize.begin();
    auto derivate_series = derivate_noize_free.begin();

    qreal Tp = 0.002;
    qreal derivate; qreal previous_value;
    for(auto Freq: Frequences)
    {

        previous_value = signal_noize_free->back();

        signal_noize_free->push_back(Amplitude*std::sin(Freq*time_series.back()));
        signal_noize->push_back(signal_noize_free->back() + NoizeAmplitude*double(rand())/RAND_MAX - NoizeAmplitude/2);

        derivate = (signal_noize_free->back() - previous_value)/Tp;
        derivate_series->push_back(derivate);
        //=================================================
        signal_noize->erase(signal_noize->begin());
        signal_noize_free->erase(signal_noize_free->begin());
        derivate_series->erase(derivate_series->begin());

        signal_noize_free++; signal_noize++; derivate_series++;

    }
    emit SignalNewDataAvailable();
}

void TestSignals::StartGenerateSignal(int time_ms) { timerSignalGenerate.start(time_ms); }
void TestSignals::StopGenerate() { timerSignalGenerate.stop(); }

//====================================TEST SIGNALS========================================
