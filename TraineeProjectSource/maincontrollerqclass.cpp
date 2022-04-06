#include "stdafx.h"

#include "maincontrollerqclass.h"
#include <functional>
#include <SubstractPair.h>
quint8* MainControllerQClass::ImageBufferFullROI = new quint8[512*2048];

std::pair<double, double> operator+(const std::pair<double, double>& x, const std::pair<double, double>& y)
{
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::pair<double, double> operator-(const std::pair<double, double>& x, const std::pair<double, double>& y)
{
    return std::make_pair(x.first - y.first, x.second - y.second);
}

QPair<double, double> operator+(const QPair<double, double>& x, const QPair<double, double>& y)
{
    return QPair<double,double>(x.first + y.first, x.second + y.second);
}

QPair<double, double> operator-(const QPair<double, double>& x, const QPair<double, double>& y)
{
    return QPair<double,double>(x.first - y.first, x.second - y.second);
}

QPair<double, double> operator*(const QPair<double, double>& x, double Scale)
{
    return QPair<double,double>(x.first*Scale, x.second*Scale);
}


//����������� MainControllerQClass
MainControllerQClass::MainControllerQClass(MainWindowQClass* Window, GraphicsWindow* Window2)										
{
	
	QObject::connect(&this->timerCircle, SIGNAL(timeout()), this, SLOT(SlotMoveByCircle()));
	
	this->StateBlock = BlockAtWork;
	this->WindowDisplay = Window;
	this->GraphicsDisplay = Window2;
	//this->TimerToCheckStateBlocks.moveToThread(Window->thread());
	this->Initialization();
	Delay();

	MainThread = new QThread;
	QObject::connect(this, &QObject::destroyed, MainThread, &QThread::quit);
	QObject::connect(this, &QObject::destroyed, MainThread, &QThread::deleteLater);
	this->moveToThread(MainThread);
	this->timerInnerRotateCalibration.moveToThread(MainThread);


	//QObject::connect(&ErrorRecievePort->TCPServer, SIGNAL(DataReceived()), this, SLOT(SlotReceiveErrorRemoteSensor()));
	QObject::connect(&Window->TimerToCheckStateBlocks, SIGNAL(timeout()), this, SLOT(SlotCheckDisplayDeviceModulesState()),Qt::DirectConnection);
	Window->TimerToCheckStateBlocks.start(30);
	//this->timerInnerRotateCalibration.moveToThread(Window->thread());
//	this->LaserControl->TimerToIterateLasers.moveToThread(MainThread);
    
	MainThread->start(QThread::HighestPriority);

	QObject::connect(this, SIGNAL(SignalStartIterateLasers(bool)), LaserControl.get(), SLOT(SlotStartIterateLasers(bool)),Qt::QueuedConnection);
	QObject::connect(this, SIGNAL(SignalSwitchAllLasers(bool)), LaserControl.get(), SLOT(SlotSwitchAllLasers(bool)),Qt::QueuedConnection);

//	ErrorPort.Reciever = this;
//	SinusControlTest.SetLink(&ErrorPort);
	SinusControlTest.SlotSetAmplitudeSeconds(30,30);
	SinusControlTest.SlotSetFrequency(1, 1);
	//SinusControlTest.SlotStartGenerate(true);

	Control_Camera_Command CameraCommand;
	CameraCommand.TimeExposure = 400;
	CameraCommand.AvarageBackground = 80;
	CameraCommand.SetCommand(COMM_AUTOEXPOSE_ON);
	//	//CameraCommand.SetCommand(COMM_CURTAIN_ON);
	//	//CameraCommand.SetCommand(COMM_NOISE_CORRETION_ON);

	SetCameraParam(CameraCommand);


	//======================= test code to delete ==============================
	return;

	{
			vector<RotateOperationContainer> TestRotations;
			QDebugStream cout(std::cout);
			TestRotations.push_back(RotateOperationContainer()); 

			auto rotation = TestRotations.begin();
			rotation->system_transform_scale = 2.0;
			rotation->AppendOperation(std::make_pair(x_axis,13)); rotation->AppendOperation(std::make_pair(z_axis,-23)); rotation->AppendOperation(std::make_pair(y_axis,29)); rotation++;


			for(auto& RotTest: TestRotations)
			{
				qDebug() << "<< =================================================== >>";
				qDebug()  << "TEST ROTATION" << endl;
				std::cout  << RotTest.RotationToString() << endl;
				qDebug() << "<< =================================================== >>";

			TestVectorRotateEngine.resize(TEST_DATA_COUT+1);
			int NumberPoints = TestVectorRotateEngine.size();
			int CurrentPoint = 0;
			int Radius = 90;
			std::srand(std::time(nullptr)); // use current time as seed for random generator

			auto GenerateCircle = [NumberPoints,CurrentPoint,Radius]() mutable -> QPair<double,double>
			{
			    double current_angle = CurrentPoint*2*M_PI/NumberPoints;
				QPair<double,double> PointOnCircle; PointOnCircle.first = Radius*std::cos(current_angle); PointOnCircle.second = Radius*std::sin(current_angle);
				  PointOnCircle.first += 0.2*double(std::rand())/RAND_MAX;
				  PointOnCircle.second += 0.2*double(std::rand())/RAND_MAX;
				CurrentPoint++;
				return PointOnCircle;
			};

			//TestVectorRotateEngine[0] = QPair<double,double>(300,400);
			TestVectorRotateEngine[0] = QPair<double,double>(250,350);

			std::generate(TestVectorRotateEngine.begin()+1,TestVectorRotateEngine.end(),GenerateCircle);

			QPair<double, double> AbsCoord;
			QPair<double, double> OutputVector;
			TestVectorRotateEngineRemote.clear();

			//TestVectorRotateEngineRemote.push_back(QPair<double,double>(200,150));
			TestVectorRotateEngineRemote.push_back(QPair<double,double>(150,220));
			for(int n = 1; n < TestVectorRotateEngine.size(); n++)
			{
			  auto BasePoint = TestVectorRotateEngine[n]; 
			  BasePoint >> RotTest >> OutputVector; 
			  OutputVector.first += 0.2*double(std::rand())/RAND_MAX;
			  OutputVector.second += 0.2*double(std::rand())/RAND_MAX;
			  TestVectorRotateEngineRemote.push_back(OutputVector);
			}

			for(int n = 1; n < TestVectorRotateEngineRemote.size(); n++)
			{
				TestVectorRotateEngine[n] = TestVectorRotateEngine[n] + TestVectorRotateEngine[0];
				TestVectorRotateEngineRemote[n] = TestVectorRotateEngineRemote[n] + TestVectorRotateEngineRemote[0];
			}

			qDebug() << "===============================================";
			qDebug() << "Base test points - " << TestVectorRotateEngine;
			qDebug() << "Remote test points - " << TestVectorRotateEngineRemote;
			qDebug() << "===============================================";

			int CounterTestRotateEngine = 0;
			int CounterTestRotateEngineAvg = 0;
			QPair<double, double> InputVector;
			
			        RotateDataMeasureEngine FilterMeasureData;
					RotateOperationContainer TestRotOpt;

			        while(CounterTestRotateEngineAvg != TestVectorRotateEngineRemote.size())
					{
					auto Error2 = TestVectorRotateEngineRemote[CounterTestRotateEngineAvg];
					auto relative_coord = TestVectorRotateEngine[CounterTestRotateEngineAvg];

			        //qDebug() << "Input coord - " << relative_coord << "counter - " << CounterTestRotateEngine;
					relative_coord >> FilterMeasureData >> TestRotOpt;
						    Error2 >> FilterMeasureData >> TestRotOpt;

						CounterTestRotateEngine++;
						if(CounterTestRotateEngine == FilterMeasureData.DataFilter.avarage_window_size)
						{
							CounterTestRotateEngine = 0;
							CounterTestRotateEngineAvg++;
							qDebug() << "----------------------------------" << CounterTestRotateEngineAvg;
						}
						QThread::msleep(2);
					}



			//qDebug()  << "REAL ROTATION" << endl;
			//std::cout  << RotTest.RotationToString() << endl;
			//std::cout  << RotTest.MatrixToString() << endl;
			//qDebug()  << "========================================" << endl;

			//qDebug()  << "OPT ROTATION" << endl;
			//std::cout  << TestRotOpt.RotationToString() << endl;
			//std::cout  << TestRotOpt.MatrixToString() << endl;
			//TestRotOpt.Inverse();
			//qDebug()  << "========================================" << endl;
			//qDebug()  << "-------------input - real_rot - output - real_rot - input -----------------" << endl;

			//InputVector = QPair<double,double>(30,20); auto InputVectorInverse = QPair<double,double>(0,0);
			//InputVector >> RotTest >> OutputVector; RotTest.Inverse(); OutputVector >> RotTest >> InputVectorInverse; RotTest.Inverse();
			//qDebug() << "Input - " << InputVector << " Output - " << OutputVector << "Input inverse real - " << InputVectorInverse; 

			//qDebug()  << "-------------input - real_rot - output - opt_rot - input -----------------" << endl;

			//InputVector = QPair<double,double>(30,20); InputVectorInverse = QPair<double,double>(0,0);
			//InputVector >> RotTest >> OutputVector; TestRotOpt.Inverse(); OutputVector >> TestRotOpt >> InputVectorInverse; TestRotOpt.Inverse();
			//qDebug() << "Input - " << InputVector << " Output - " << OutputVector << "Input inverse opt - " << InputVectorInverse; 

			//qDebug()  << "========================================" << endl;
			}
    }
	//==========================================================================

}	//END:��� MainControllerQClass




MainControllerQClass::~MainControllerQClass()	//����������
{
	QObject::disconnect(KLPInterface->CameraInterface.get(), SIGNAL(SignalRecieveNewFrame()), this, SLOT(SlotReceiveImage()));
	this->LaserControl->LPilot1->TurnLaserBeamOnOff(false);
	this->LaserControl->LPilot2->TurnLaserBeamOnOff(false);
	this->LaserControl->LPilot3->TurnLaserBeamOnOff(false);
	this->LaserControl->LaserPointer->TurnLaserBeamOnOff(false);

	//MainThread->wait(2000);
	//MainThread->quit();
	//MainThread->deleteLater();
	qDebug() << "Delete main controller";
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

			KLPInterface->SetSateCommutator(CommutatorState);

		quint8 Command = 0;
        Command |= COMM_AUTOEXPOSE_ON;



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
	
	RemoteControl= std::shared_ptr<RemoteControlClass>(new RemoteControlClass);

	 StateBlock = stateblocksenum::BlockAtInitializaiton;
	

	
	EngineControl1 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface1.get()));
	EngineControl2 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface2.get()));
	EngineControl3 = std::shared_ptr<EngineControlClass>(new EngineControlClass(KLPInterface->EngineInterface3.get()));

	//SinusControlTest.SetLink(EngineControl3.get());


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
	ErrorRecievePort= std::shared_ptr<ErrorRecieverClass>(new ErrorRecieverClass);


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

	this->WindowDisplay->PIDControl->SetInitialState(AimingBlock1->EnginePIDRegulator.PIDParamAxis1.RateParam,
													 AimingBlock1->EnginePIDRegulator.PIDParamAxis1.DiffParam,
													 AimingBlock1->EnginePIDRegulator.PIDParamAxis1.IntParam);
	this->WindowDisplay->KalmanControl->DisplayParam(AimingBlock1->CalmanFilter.Qex, AimingBlock1->CalmanFilter.Qnx, AimingBlock1->CalmanFilter.Qvx);



	SinusGenerator->WindowControl->MoveToScene(WindowDisplay->Scene);
	SinusGenerator->WindowControl->Node->ConnectNode(WindowDisplay->EngineControlBlock3);
	SinusGenerator->SetLink(EngineControl3.get());

    ErrorRecievePort->ErrorPortWindowControl->MoveToScene(WindowDisplay->Scene);
	ErrorRecievePort->ErrorPortWindowControl->Node->ConnectNode(WindowDisplay->MainBlock1);



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

    qDebug() << "Set command delay - " << DelayMks << " channel - " << NumberChannel;

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
				EngineControl1->EngineInterface->SetToNull();
				EngineControl2->EngineInterface->SetToNull();
				EngineControl3->EngineInterface->SetToNull();
			}
			else
			{
			    this->StateBlock = BlockDisable;
				emit SignalSwitchAllLasers(false);
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

		if (LaserControl->LPilot2->IsOnOff()) { newImage >> *ImageProcessor->Proc1; *ImageProcessor >> *AimingBlock1; *AimingBlock1 >> *EngineControl1;}
		if (LaserControl->LPilot1->IsOnOff()) { newImage >> *ImageProcessor->Proc2; *ImageProcessor >> *AimingBlock2; *AimingBlock2 >> *EngineControl2;}
		if (LaserControl->LPilot3->IsOnOff()) { newImage >> *ImageProcessor->Proc3; *ImageProcessor >> *AimingBlock3; *AimingBlock3 >> *EngineControl3;}

		if (LaserControl->LaserPointer->IsOnOff()) newImage >> *ImageProcessor->ProcToPointer;
		}
    

		if (!FLAG_INITIALIZATION_DONE &&
			ImageProcessor->Proc1->AimingState != SpotNoFoundState &&
			ImageProcessor->Proc2->AimingState != SpotNoFoundState &&
			ImageProcessor->Proc3->AimingState != SpotNoFoundState &&
			ImageProcessor->ProcToPointer->AimingState != SpotNoFoundState)
		{
			this->FLAG_INITIALIZATION_DONE = true;
	        emit SignalStartIterateLasers(false);
			emit SignalSwitchAllLasers(true);

					ROI_Channels_Command Camera_ROI;

	                int y_center = 220; int x1 = 703; int x2 = 1017; int x3 = 1314;
			                            int y1 = 248; int y2 = 224; int y3 = 288;
			                            int avarage_y = (y1 + y2 + y3) / 3;
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
			newImage >> *ImageProcessor;


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

void MainControllerQClass::TurnOnOffLaserPilot(int Number, bool OnOff)
{
	this->LaserControl->SlotSwitchPilotBeam(Number, OnOff);
}

void MainControllerQClass::TurnOnOfLaserFire(int Number, bool OnOff)
{
	this->LaserControl->SlotSwitchFireBeam(OnOff);
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

void MainControllerQClass::TurnOnOffLaserPointer(bool OnOff)
{
	this->LaserControl->SlotSwitchPointerBeam(OnOff);
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
		AimingBlocks.at(NumberChannel - 1)->CalmanFilter.StateBlock = State;
		break;
	case PIDBlock:
		AimingBlocks.at(NumberChannel - 1)->EnginePIDRegulator.StateBlock = State;
		break;
	case ImageProcBlock:
		ImageProcessor->Processors.at(NumberChannel - 1)->StateBlock = State;
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
	switch (NumberChannel)
	{
	case 1:
		this->AimingBlock1->DesireAbsCoord.first = ImageProcessor->Proc1->strob_coord.first + x;
		this->AimingBlock1->DesireAbsCoord.second = ImageProcessor->Proc1->strob_coord.second + y;
		break;
	case 2:
		this->AimingBlock2->DesireAbsCoord.first = ImageProcessor->Proc2->strob_coord.first + x;
		this->AimingBlock2->DesireAbsCoord.second = ImageProcessor->Proc2->strob_coord.second + y;
		break;
	case 3:
		this->AimingBlock3->DesireAbsCoord.first = ImageProcessor->Proc3->strob_coord.first + x;
		this->AimingBlock3->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;
		break;
	case 4:
		this->AimingBlock1->DesireAbsCoord.first = ImageProcessor->Proc1->strob_coord.first + x;
		this->AimingBlock1->DesireAbsCoord.second = ImageProcessor->Proc1->strob_coord.second + y;
		this->AimingBlock2->DesireAbsCoord.first = ImageProcessor->Proc2->strob_coord.first + x;
		this->AimingBlock2->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;
		this->AimingBlock3->DesireAbsCoord.first = ImageProcessor->Proc3->strob_coord.first + x;
		this->AimingBlock3->DesireAbsCoord.second = ImageProcessor->Proc3->strob_coord.second + y;

		ErrorPointer.first = x;
		ErrorPointer.second = y;
		break;

	}
}

void MainControllerQClass::Delay()
{
    qDebug() << "Start delay";
    auto StartTimePoint = std::chrono::high_resolution_clock::now();

    double Period = 0;


    QThread::usleep(100);

    auto NewTimePoint = std::chrono::high_resolution_clock::now();

    Period = std::chrono::duration<double>(NewTimePoint - StartTimePoint).count();
    qDebug() << "Period - " << Period;
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

	if(AimingBlock1->isAimingFault()) EngineControl1->ResetToLastSavePosition();
    if(AimingBlock2->isAimingFault()) EngineControl2->ResetToLastSavePosition();
    if(AimingBlock3->isAimingFault()) EngineControl3->ResetToLastSavePosition();


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
	qDebug() << "RESET ENGINE ROTATION  START CALIBRATION";
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
				if (ErrorRecievePort->error_direction == 1 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 1";
					NewDesireCoord =  ImageProcessor->Proc1->spot_coord_abs - Error;
					AimingBlock1->SetDesieredCoord(NewDesireCoord);
				}

				if (ErrorRecievePort->error_direction == 2 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 2";
					NewDesireCoord =  ImageProcessor->Proc2->spot_coord_abs - Error;
					AimingBlock2->SetDesieredCoord(NewDesireCoord);
				}

				if (ErrorRecievePort->error_direction == 3 || ErrorRecievePort->error_direction == 0)
				{
					qDebug() << "Remote error to channel 3";
					NewDesireCoord =  ImageProcessor->Proc3->spot_coord_abs - Error;
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
	AimingBlock1->CalmanFilter.SetMeasureErrorVariance(Qe, Qe);
	AimingBlock1->CalmanFilter.SetModelErrorVariance(Qn, Qn,Qn,Qn);

	AimingBlock2->CalmanFilter.SetMeasureErrorVariance(Qe, Qe);
	AimingBlock2->CalmanFilter.SetModelErrorVariance(Qn, Qn,Qn,Qn);

	AimingBlock3->CalmanFilter.SetMeasureErrorVariance(Qe, Qe);
	AimingBlock3->CalmanFilter.SetModelErrorVariance(Qn, Qn,Qn,Qn);
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
	qDebug() << "Set regim commutator";
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
	qDebug() << "Set threshold control manual - " << OnOff;
}

void MainControllerQClass::SetFrameFilterProcentage(int Procentage)
{
	this->ImageProcessor->Proc1->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc2->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->Proc3->FrameFilterProcentage = Procentage/100.0;
	this->ImageProcessor->ProcToPointer->FrameFilterProcentage = Procentage/100.0;
	qDebug() << "Frame filter procentage - " << this->ImageProcessor->Proc1->FrameFilterProcentage;
}


void MainControllerQClass::TurnOffAxisEngine(bool state,int axis, int channel)
{
	QVector<EngineInterfaceClass*> Channels;
	Channels.append(EngineControl1->EngineInterface); Channels.append(EngineControl2->EngineInterface); Channels.append(EngineControl3->EngineInterface);

	if (axis == 1)
		Channels[channel-1]->VerticalAxisOn = state;
	if (axis == 2)
		Channels[channel-1]->HorizontalAxisOn = state;

	qDebug() << "Channel - " << channel << " aixs - " << axis << " state - " << state;

}

void MainControllerQClass::LoadPreference()
{


	QString RotateParamPath1; 
	QString RotateParamPath2; 
	QString RotateParamPath3; 
			QString IniFile = "/home/broms/TrainerData/TrainerPaths.ini";
			QSettings Settings(IniFile, QSettings::IniFormat);

			Settings.beginGroup("PATHS");
				 RotateParamPath1 = Settings.value("ROTATE_PARAM_1").toString();
				 RotateParamPath2 = Settings.value("ROTATE_PARAM_2").toString();
				 RotateParamPath3 = Settings.value("ROTATE_PARAM_3").toString();

			Settings.endGroup();
			qDebug() << "Load settings - " << RotateParamPath1; qDebug() << "Load settings - " << RotateParamPath2; qDebug() << "Load settings - " << RotateParamPath3;


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

	int x_center = 1024; int y_center = 220;
	int x1 = 703; int x2 = 1017; int x3 = 1314;
	//int y1 = 230; int y2 = 230;  int y3 = 230;
    int y1 = 248; int y2 = 224;  int y3 = 288;
	int avarage_y = (y1 + y2 + y3) / 3;

	AimingBlock1->BeamCenteredPosition = QPair<int, int>(x1,y1);
	AimingBlock2->BeamCenteredPosition = QPair<int, int>(x2,y2);
	AimingBlock3->BeamCenteredPosition = QPair<int, int>(x3,y3);

	AimingBlock1->DesireAbsCoord = AimingBlock1->BeamCenteredPosition;
	AimingBlock2->DesireAbsCoord = AimingBlock2->BeamCenteredPosition;
	AimingBlock3->DesireAbsCoord = AimingBlock3->BeamCenteredPosition;
}
