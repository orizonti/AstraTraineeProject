#include "CommonHeaders.h"

#include "maincontrollerqclass.h"
#include <functional>
#include <SubstractPair.h>
quint8* MainControllerQClass::ImageBufferFullROI = new quint8[512*2048];



//����������� MainControllerQClass
MainControllerQClass::MainControllerQClass(MainWindowQClass* Window, GraphicsWindow* Window2)										
{
    qDebug() << "TEST REMOTE STRING 222";	
	QObject::connect(&this->timerCircle, SIGNAL(timeout()), this, SLOT(SlotMoveByCircle()));
	
	this->StateBlock = BlockAtWork;
	this->WindowDisplay = Window;
	this->GraphicsDisplay = Window2;
	this->Initialization();
	Delay();

	MainThread = new QThread;
	//QObject::connect(this, &MainControllerQClass::WorkFinished, MainThread, &QThread::quit);
	//QObject::connect(this, &MainControllerQClass::WorkFinished, MainThread, &QThread::deleteLater);

    //QObject::connect(this, &MainControllerQClass::WorkFinished, Window, &QWidget::deleteLater);
    //QObject::connect(this, &MainControllerQClass::WorkFinished, Window2, &QWidget::deleteLater);

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
    //QObject::connect(&ErrorRecievePort->TCPServer, SIGNAL(DataReceived()), this, SLOT(SlotReceiveErrorRemoteSensor()));

    QObject::connect(&SinusAimingBlockTest,SIGNAL(SignalNewDataAvailable()),this,SLOT(SlotReciveErrorTest()));
    SinusAimingBlockTest.SetRelativeOutput(false); SinusAimingBlockTest.SlotSetFrequency(2);
    SinusAimingBlockTest.SlotStartGenerate(true);

    AimingBlock1->SetDesieredCoord(QPair<double,double>(0,0));
    AimingBlock2->SetDesieredCoord(QPair<double,double>(0,0));
    AimingBlock3->SetDesieredCoord(QPair<double,double>(0,0));

	//======================= test code to delete ==============================
	return;
	//==========================================================================
}	//END:��� MainControllerQClass




MainControllerQClass::~MainControllerQClass()	//����������
{
}




void MainControllerQClass::SlotCheckDisplayDeviceModulesState()
{


	DataImageProcAllChannels DataImageProc = ImageProcessor->GetDataAllChannels();
	Substract<double> SubsPair;
	   AimingBlock1->DesireAbsCoord >> SubsPair;
	   ImageProcessor->Proc1->strob_coord >> SubsPair >> DataImageProc.Channel1.LastAimingCoord;

	   AimingBlock2->DesireAbsCoord >> SubsPair;
	   ImageProcessor->Proc2->strob_coord >> SubsPair >> DataImageProc.Channel2.LastAimingCoord;

	   AimingBlock3->DesireAbsCoord >> SubsPair;
	   ImageProcessor->Proc3->strob_coord >> SubsPair >> DataImageProc.Channel3.LastAimingCoord;

	   DataImageProc.Channel4.LastAimingCoord = ErrorPointer;




	DataEngineStructure EnginesData;
	EnginesData.TypeBlock = EngineControl1->TypeBlock;

	EnginesData.Engine1 = EngineControl1->GetEnginesState();
	EnginesData.Engine2 = EngineControl2->GetEnginesState();
	EnginesData.Engine3 = EngineControl3->GetEnginesState();

	AimingBlock1->GetState() >> *WindowDisplay;     // Отображение ошибки наведения, выхода фильтра и ПИД регулятора, состояния блоков
	AimingBlock2->GetState() >> *WindowDisplay;     // данные идут на окно с графиками
	AimingBlock3->GetState() >> *WindowDisplay;     //

	     LaserControl->LPilot1->GetState() >> *WindowDisplay;  // Состояние лазерных блоков 
	     LaserControl->LPilot2->GetState() >> *WindowDisplay;  // иден на окно управления лазерами 
	     LaserControl->LPilot3->GetState() >> *WindowDisplay;  // меняет красное и зеленое положение
	LaserControl->LaserPointer->GetState() >> *WindowDisplay;  //


	DataImageProc >> *WindowDisplay;    // Вывод изображения с отметками лаезрного пятна и желаемых координат

    EnginesData >> *WindowDisplay;

	KLPInterface->CameraInterface->GetState() >> *WindowDisplay;


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




bool MainControllerQClass::Initialization()
{
	QString info_string;
	QDebug  debug_out(&info_string);

	//qDebug() << "                   KLP INTERFACE CREATE !!!!!";
	KLPInterface = std::shared_ptr<KLPInterfaceClass>(new KLPInterfaceClass);

	Regim_CommutatorCommand CommutatorState;
							CommutatorState.TurnOnOffSupply(true);

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
	

	ChillSystem = std::shared_ptr<ChillSystemClass>(new ChillSystemClass);
	
	AirSystem   = std::shared_ptr<AirSystemClass>(new AirSystemClass);
	
	RemoteControl= std::shared_ptr<RemoteControlClass>(new RemoteControlClass(this));

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
	ErrorRecievePort= std::shared_ptr<RemoteAimingClass>(new RemoteAimingClass);


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

	//SinusGenerator->WindowControl->MoveToScene(WindowDisplay->Scene,300,300);
	//SinusGenerator->WindowControl->Node->ConnectNode(WindowDisplay->EngineControlBlock3);
	//SinusAimingBlockTest.WindowControl->MoveToScene(WindowDisplay->Scene,300,400);
	 WindowDisplay->AddWidgetToDisplay(SinusGenerator->WindowControl);
	 WindowDisplay->AddWidgetToDisplay(SinusAimingBlockTest.WindowControl);

    //ErrorRecievePort->ErrorPortWindowControl->MoveToScene(WindowDisplay->Scene);
	//ErrorRecievePort->ErrorPortWindowControl->Node->ConnectNode(WindowDisplay->MainBlock1);
	 WindowDisplay->AddWidgetToDisplay(ErrorRecievePort->ErrorPortWindowControl);



	//this->KLPInterface->StatusRequest();


	return true;
}

void MainControllerQClass::SetEngineCommandDelay(int DelayMks, int NumberChannel)
{

    if(NumberChannel == 1)
        EngineControl1->EngineInterface->CommandDelayMks = DelayMks;
    if(NumberChannel == 2)
        EngineControl2->EngineInterface->CommandDelayMks = DelayMks;
    if(NumberChannel == 3)
        EngineControl3->EngineInterface->CommandDelayMks = DelayMks;

}

void MainControllerQClass::RotateEngineAxis(int Channel, double AngleDegree) 
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

				//qDebug() << "========================================";
				//Engine->RotateAxis.SetRotateAngle(AngleDegree);
				//Engine->RotateAxisInverse.SetRotateAngle(-AngleDegree);
				//qDebug() << "ROTATE ENGINE CHANNEL - " << Channel << "ANGLE - " << AngleDegree;
				//qDebug() << "Rotate dont work";
				//qDebug() << "========================================";

}

void MainControllerQClass::SlotStartStopWork(bool StartStop)
{
	//qDebug() << "SLOT START STOP WORK";
	if (!FLAG_INITIALIZATION_DONE)
	{
		//qDebug() << "START INITIALIZATION";
	QObject::connect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotFindSpot_MoveEngineToWorkPos()),Qt::QueuedConnection);

	EngineControl1->StateBlock = BlockAtWork;
	EngineControl2->StateBlock = BlockAtWork;
	EngineControl3->StateBlock = BlockAtWork;

	AimingBlock1->StateBlock = BlockAtWork;
	AimingBlock2->StateBlock = BlockAtWork;
	AimingBlock3->StateBlock = BlockAtWork;

	//this->MoveEnginesToStartPos(1);
	//QThread::msleep(50);
	//this->MoveEnginesToStartPos(2);
	//QThread::msleep(50);
	//this->MoveEnginesToStartPos(3);

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
			    qDebug() << "Stop work process";
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
			//qDebug() << "BREAK INITIALIZATION AND OFF";
	        emit SignalStartIterateLasers(false);
			emit SignalSwitchAllLasers(false);

    }

}

void MainControllerQClass::SlotFindSpot_MoveEngineToWorkPos()
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
			qDebug() << "INITIZALIZATION END";
		}

}
QPair<double,double> MainControllerQClass::MoveEnginesToStartPos(int Channel)
{


	switch (Channel)
	{
	case 1:
	AimingBlock1->DesireAbsCoord = AimingBlock1->BeamCenteredPosition;
	case 2:
	AimingBlock2->DesireAbsCoord = AimingBlock2->BeamCenteredPosition;
	case 3:
	AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
	}

	return AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
}


void MainControllerQClass::MoveEngineToNull(int Channel)
{
	EngineControlClass* Engine;
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

		//qDebug() << "Main controller set enginge to NULL";
		Engine->EngineInterface->SetToNull();
		this->AimingBlock1->EnginePIDRegulator.ResetPID();
		this->AimingBlock2->EnginePIDRegulator.ResetPID();
		this->AimingBlock3->EnginePIDRegulator.ResetPID();
		return;
}

void MainControllerQClass::MoveEngine(int Direction, double X_Pos,double Y_Pos, int Channel)
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


                qDebug() << "MOVE ENGINE SLOT";
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

void MainControllerQClass::TurnOnOffAllLasers(bool OnOff)
{
		emit SignalSwitchAllLasers(OnOff);
}

void MainControllerQClass::ResetAll()
{

	this->KLPInterface->ResetCommutator();
	QThread::msleep(100);
	this->EngineControl1->EngineInterface->ResetEngine();
	QThread::msleep(100);
	this->EngineControl2->EngineInterface->ResetEngine();
	QThread::msleep(100);
	this->EngineControl3->EngineInterface->ResetEngine();
	QThread::msleep(100);
	//qDebug() << "RESET ALL";
	this->KLPInterface->CardSoftReset();
}

void MainControllerQClass::SaveEnginePosToFile()
{
	QString IniFile = "E:/ENGINE_POS.ini";
	//qDebug() << "Save settings to - " << IniFile;
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


void MainControllerQClass::SetPIDParam(double Common, double Rate, double Int, double diff)
{

	//qDebug() << "Set new PID param  rate - " << Rate<< "int - " << Int<< "diff " << diff;


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


	
	if (AimingBlock1->AimingState == AimingFast)
	AimingBlock1->EnginePIDRegulator.SetPIDParam(AimingBlock1->AimingFastParam);

	if (AimingBlock2->AimingState == AimingFast)
	AimingBlock2->EnginePIDRegulator.SetPIDParam(AimingBlock2->AimingFastParam);

	if (AimingBlock3->AimingState == AimingFast)
	AimingBlock3->EnginePIDRegulator.SetPIDParam(AimingBlock3->AimingFastParam);
}

void MainControllerQClass::SetCalmanParam(double Qnx, double Qex, double Qvex)
{
	//qDebug() << "SET CALMAN PARAMM DOT WORK";
}

void MainControllerQClass::SetImageThresHold(int Thres,int Channel)
{
	//qDebug() << "SET THRESHOLD TO IMAGE PROCESSORS - " << Thres << "to channel - " << Channel;

	if(Channel == 1)
	ImageProcessor->Proc1->Threshold = Thres;
	if(Channel == 2)
	ImageProcessor->Proc2->Threshold = Thres;
	if(Channel == 3)
	ImageProcessor->Proc3->Threshold = Thres;
	if(Channel == 4)
	ImageProcessor->ProcToPointer->Threshold = Thres;
}

void MainControllerQClass::TurnOnOffLaserPilot(int Number, bool OnOff)
{
    this->LaserControl->SlotSwitchPilotBeam(Number, OnOff);


    if(Number == 1) ImageProcessor->Proc1->StopProcessing(OnOff);
    if(Number == 2) ImageProcessor->Proc2->StopProcessing(OnOff);
    if(Number == 3) ImageProcessor->Proc3->StopProcessing(OnOff);
}

void MainControllerQClass::TurnOnOfLaserFire(int Number, bool OnOff)
{
    this->LaserControl->SlotSwitchFireBeam(OnOff);
}
void MainControllerQClass::TurnOnOffLaserPointer(bool OnOff)
{

    ImageProcessor->ProcToPointer->StopProcessing(OnOff);
	this->LaserControl->SlotSwitchPointerBeam(OnOff);
	qDebug() << "Stop processing pointer - " << OnOff;
}

void MainControllerQClass::TurnOnOffChiller(bool OnOff)
{
	this->ChillSystem->SlotTurnOnOff(OnOff);
}

void MainControllerQClass::TurnOnOffAir(bool OnOff)
{
	this->AirSystem->SlotTurnOnOff(OnOff);
}

void MainControllerQClass::SlotMoveByCircle()
{
	CounterCircle++;
	double x = 50*std::sin(2*3.14*CounterCircle/360);
	double y = 50*std::cos(2*3.14*CounterCircle/360);


	this->SlotSetAimingCoord(x + 128, y + 128, 4);

	if (CounterCircle == 360)
		CounterCircle = 0;
	//qDebug() << "Circle - " << x << y << "radius - " << std::sqrt(x*x + y*y);
}

void MainControllerQClass::SlotStartMoveByCircle(bool OnOff)
{
	//qDebug() << "MOVE BY CIRCLE - " << OnOff;
	if(OnOff)
	this->timerCircle.start(10);
	else
	this->timerCircle.stop();
}

void MainControllerQClass::SetBlockState(typeblocksenum TypeBlock, int NumberChannel, stateblocksenum State)
{
	//qDebug() << "Set block -  " << TypeBlock << "number channel - " << NumberChannel << "State - " << State;
	switch (TypeBlock){
	case EngineControlBlock:
		EngineBlocks.at(NumberChannel-1)->StateBlock = State;
		break;
	case ChillControlBlock:
		break;
	case CamerasControlBlock:
		KLPInterface->CameraInterface->SetState(State);
		break;
	case AimingBlock:
		AimingBlocks.at(NumberChannel - 1)->StateBlock = State;
		break;
	case CalmanFilterBlock:
		//AimingBlocks.at(NumberChannel - 1)->CalmanFilter.StateBlock = State;
		break;
	case PIDBlock:
		AimingBlocks.at(NumberChannel - 1)->EnginePIDRegulator.StateBlock = State;
		break;
	case ImageProcBlock:
		ImageProcessor->Processors.at(NumberChannel - 1)->StateBlock = State;
		qDebug() << "Set processor state - " << State << " number channel - " << NumberChannel;
		break;
	default:
		break;
	}

}


void MainControllerQClass::SetLaserFireFrequency(int Channel, int Frequency)
{
	// TODO: Implement Method
	throw "Not Implemented Exception: void MainControllerQClass::SetLaserFireFrequency(int Channel, int Frequency)";
}



void MainControllerQClass::SlotSetAimingCoord(int x, int y, int NumberChannel)
{
	//qDebug() << "Set aiming point - " << x << y << "to Channel - " << NumberChannel;
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

void MainControllerQClass::Delay()
{
    auto StartTimePoint = std::chrono::high_resolution_clock::now();
    QThread::usleep(100);
    auto NewTimePoint = std::chrono::high_resolution_clock::now();
}

void MainControllerQClass::SlotReciveErrorTest()
{
    auto Error = SinusAimingBlockTest.GetCoord();
    Error >> *AimingBlock1;                //Send new coord spot to aiming
    Error >> *AimingBlock2;
    Error >> *AimingBlock3;
}

void MainControllerQClass::SlotReceiveImage()
{

	if (this->StateBlock == BlockDisable)
		return;


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

void MainControllerQClass::SlotInnerRotateCalibration()
{

	if (EngineControl1->RotationAxis.output_to_optimize_rotation.size() == TEST_DATA_COUT)
	{
		qDebug() << "STOP INNER ROTATE CALIBRATION";
		timerInnerRotateCalibration.stop();
		QObject::disconnect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
	}

		AimingBlock1->SetDesieredCoord(EngineControl1->RotationAxis.MeasureFilter.DataFilter.WaitInputCoord + AimingBlock1->BeamCenteredPosition);
		auto CurrentPos1 = EngineControl1->EngineInterface->GetCoord();
		CurrentPos1 = CurrentPos1 * double(180 * 60 * 60 / 3.14);
		//qDebug() << "Current coord - " << CurrentPos1.first << CurrentPos1.second;
		//auto RelativeCoord = ImageProcessor->Proc1->spot_coord_abs - AimingBlock1->BeamCenteredPosition;
		ImageProcessor->Proc1->spot_coord_abs >> EngineControl1->RotationAxis.MeasureFilter >> EngineControl1->RotationAxis;
		CurrentPos1 >> EngineControl1->RotationAxis.MeasureFilter >> EngineControl1->RotationAxis;
}

void MainControllerQClass::StartSystemRotationCalibration()
{
	EngineControl1->RotationAxis.Reset();
	EngineControl2->RotationAxis.Reset();
	EngineControl3->RotationAxis.Reset();

	QObject::connect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
	timerInnerRotateCalibration.start(40);
}



void MainControllerQClass::SlotReceiveErrorRemoteSensor()
{
	if (this->StateBlock == BlockDisable)
		return;

		QPair<double, double> Error;
		QPair<double, double> NewDesireCoord;

		*ErrorRecievePort >> Error;
		if(ErrorRecievePort->isValid())
		{
		        auto PointerCoord = ImageProcessor->ProcToPointer->spot_coord_abs;
				if (ErrorRecievePort->error_direction == 1 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 1";
					NewDesireCoord =  ImageProcessor->Proc1->spot_coord_abs - PointerCoord - Error;
					AimingBlock1->SetDesieredCoord(NewDesireCoord);
				}

				if (ErrorRecievePort->error_direction == 2 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 2";
					NewDesireCoord =  ImageProcessor->Proc2->spot_coord_abs - PointerCoord - Error;
					AimingBlock2->SetDesieredCoord(NewDesireCoord);
				}

				if (ErrorRecievePort->error_direction == 3 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 3";
					NewDesireCoord =  ImageProcessor->Proc3->spot_coord_abs - PointerCoord - Error;
					AimingBlock3->SetDesieredCoord(NewDesireCoord);
				}
	QObject::disconnect(&timerInnerRotateCalibration, SIGNAL(timeout()), this, SLOT(SlotInnerRotateCalibration()));
		}


        //=======================================================================================================================================
		if (ErrorRecievePort->error_direction == 1 && !ErrorRecievePort->isValid())
		{
			AimingBlock1->SetDesieredCoord(ErrorRecievePort->RemoteToBaseTransform.MeasureFilter.DataFilter.WaitInputCoord + AimingBlock1->BeamCenteredPosition);

			auto abs_coord = ImageProcessor->Proc1->spot_coord_abs;
				 abs_coord >> ErrorRecievePort->RemoteToBaseTransform.MeasureFilter >> ErrorRecievePort->RemoteToBaseTransform;
				     Error >> ErrorRecievePort->RemoteToBaseTransform.MeasureFilter >> ErrorRecievePort->RemoteToBaseTransform;
		}


}

void MainControllerQClass::InitialaizeROIProcess()
{
	return;
};


	
	
void MainControllerQClass::ChangeAimingType(TypeAiming Aiming,int Channel)
{
	if (Channel == 1)
		AimingBlock1->SetAimingSpeedRegim(Aiming);
	if(Channel == 2)
		AimingBlock2->SetAimingSpeedRegim(Aiming);
	if(Channel == 3)
		AimingBlock3->SetAimingSpeedRegim(Aiming);
}

void MainControllerQClass::ChangeCalmanParam(double Qe, double Qn)
{
}


void MainControllerQClass::SetCameraParam(Control_Camera_Command Command)
{
	qDebug() << "SET CAMERA PARAM";
	if(KLPInterface)
	KLPInterface->CameraInterface->SendCommand(Command);
}

void MainControllerQClass::SetCameraROI(ROI_Channels_Command ROI)
{
	if(KLPInterface)
	KLPInterface->CameraInterface->SetROI(ROI);
}

void MainControllerQClass::SetAdjustModeWithCrossHair(bool OnOff)
{
	qDebug() << "Crosshair - " << OnOff;
	this->ShowAdjustCrosshair = OnOff;
}

void MainControllerQClass::SetPowerSupplyOnCommutator(bool OnOff)
{
	qDebug() << "POWER SUPPLY ON";
	Regim_CommutatorCommand CommutatorState;
							CommutatorState.TurnOnOffSupply(OnOff);

			KLPInterface->SetSateCommutator(CommutatorState);
}

void MainControllerQClass::SetThresholdControlManual(bool OnOff)
{
	this->ImageProcessor->Proc1->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->Proc2->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->Proc3->FlagThresholdAutoControl = !OnOff;
	this->ImageProcessor->ProcToPointer->FlagThresholdAutoControl = !OnOff;
}

void MainControllerQClass::SetFrameFilterProcentage(int Procentage)
{
	this->ImageProcessor->Proc1->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc2->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc3->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->ProcToPointer->FrameFilterProcentage = Procentage/100.0;
}


void MainControllerQClass::TurnOffAxisEngine(bool state,int axis, int channel)
{
	QVector<EngineInterfaceClass*> Channels;
	Channels.append(EngineControl1->EngineInterface); Channels.append(EngineControl2->EngineInterface); Channels.append(EngineControl3->EngineInterface);

	if (axis == 1)
		Channels[channel-1]->VerticalAxisOn = state;
	if (axis == 2)
		Channels[channel-1]->HorizontalAxisOn = state;

}

void MainControllerQClass::LoadPreference()
{


    qDebug() << "================================================";
    qDebug() << "MAIN CONTROLLER LOAD PREFERENCE";
	QString RotateParamPath1;
	QString RotateParamPath2; 
	QString RotateParamPath3; 
			QString IniFile = "/home/broms/DEVELOPMENT/DATA/TrainerData/TrainerPaths.ini";
			QSettings Settings(IniFile, QSettings::IniFormat);

			Settings.beginGroup("PATHS");
				 RotateParamPath1 = Settings.value("ROTATE_PARAM_1").toString();
				 RotateParamPath2 = Settings.value("ROTATE_PARAM_2").toString();
				 RotateParamPath3 = Settings.value("ROTATE_PARAM_3").toString();

			Settings.endGroup();
			qDebug() << "LOAD SETTINGS - " << RotateParamPath1;
			qDebug() << "LOAD SETTINGS - " << RotateParamPath2;
			qDebug() << "LOAD SETTINGS - " << RotateParamPath3;


    EngineControl1->RotationAxis.LoadRotationFromFile(RotateParamPath1);
    EngineControl2->RotationAxis.LoadRotationFromFile(RotateParamPath2);
    EngineControl3->RotationAxis.LoadRotationFromFile(RotateParamPath3);

	EngineControl1->RotateAxisInverse = EngineControl1->RotateAxis.Inverse();
	EngineControl2->RotateAxisInverse = EngineControl2->RotateAxis.Inverse();
	EngineControl3->RotateAxisInverse = EngineControl3->RotateAxis.Inverse();

    EngineControl1->RotationAxisInverse = EngineControl1->RotationAxis; EngineControl1->RotationAxisInverse.Inverse();
    EngineControl2->RotationAxisInverse = EngineControl2->RotationAxis; EngineControl2->RotationAxisInverse.Inverse();
    EngineControl3->RotationAxisInverse = EngineControl3->RotationAxis; EngineControl3->RotationAxisInverse.Inverse();

	AimingBlock1->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;
	AimingBlock2->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;
	AimingBlock3->PixToRadian.Scale = EngineControl1->RotationAxis.system_transform_scale;

	AimingBlock1->RadianToPix.Scale = EngineControl1->RotationAxis.system_transform_scale;
	AimingBlock2->RadianToPix.Scale = EngineControl1->RotationAxis.system_transform_scale;
	AimingBlock3->RadianToPix.Scale = EngineControl1->RotationAxis.system_transform_scale;

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
    qDebug() << "DESIRE RELATIVE " << AimingBlock1->DesireRelCoord << " CHANNEL - " << 1;
    qDebug() << "DESIRE RELATIVE " << AimingBlock2->DesireRelCoord << " CHANNEL - " << 2;
    qDebug() << "DESIRE RELATIVE " << AimingBlock3->DesireRelCoord << " CHANNEL - " << 3;
    qDebug() << "================================================";
}

void MainControllerQClass::SlotFinishWork()
{
    qDebug() << "MAIN WINDOW CLOSED START TO FINISH WORK";
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
    qDebug() << "MAIN CONTROLLER STOPPED";
}

void MainControllerQClass::TurnOnOffKalmanFilter(bool OnOff, int Channel)
{
    switch (Channel)
    {
        case 1:
            AimingBlock1->SlotFilterEnable(OnOff);
        case 2:
            AimingBlock2->SlotFilterEnable(OnOff);
        case 3:
            AimingBlock3->SlotFilterEnable(OnOff);
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
    qDebug() << "GENERATE INIT SERIES SIZE - " << INPUT_VECTOR_SIZE;
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

void TestSignals::StartGenerateSignal(int time_ms)
{
    timerSignalGenerate.start(time_ms);
}
void TestSignals::StopGenerate()
{
    timerSignalGenerate.stop();
}
//====================================TEST SIGNALS========================================
