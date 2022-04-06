#include "stdafx.h"
#include "mainwindowqclass.h"


MainWindowQClass::MainWindowQClass(GraphicsWindow* GraphicsWidget,QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//QObject::connect(ui.cameraButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.commButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.driversButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.driversControlButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.fiberButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.generalButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.imageButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//QObject::connect(ui.laserButton, SIGNAL(toggled(bool)), this, SLOT(SlotChangeViewWindow()));
	//

	LabelImage = new QLabel("Image");
	GraphicsDisplay = GraphicsWidget;
	 MainBlockDisplay              = new MainBlockWindow;
	 ImageProcDisplay        = new ImageProcessingWindow;
	 ShowImageDisplay = new ImageProcessingDisplayWindow;
	 AimingBlockDisplay1         = new AimingBlockWindow;
	 AimingBlockDisplay2         = new AimingBlockWindow;
	 AimingBlockDisplay3         = new AimingBlockWindow;
	 AimingBlockDisplay1->NumberChannel = 1;
	 AimingBlockDisplay2->NumberChannel = 2;
	 AimingBlockDisplay3->NumberChannel = 3;

	 PIDControl = new PIDWindow2;
	 KalmanControl = new KalmanWindow;

	 EngineControlDisplay1 = new EngineControlWindow;
	 EngineControlDisplay2 = new EngineControlWindow;
	 EngineControlDisplay3 = new EngineControlWindow;

	 EngineControlDisplay1->SetNumberChannel(2);
	 EngineControlDisplay2->SetNumberChannel(1);
	 EngineControlDisplay3->SetNumberChannel(3);


	 EngineControlDisplay1->NumberChannel = 1;
	 EngineControlDisplay2->NumberChannel = 2;
	 EngineControlDisplay3->NumberChannel = 3;

	 LaserControlDisplay = new LaserBlockWindow;

	 CameraControlBlockDisplay = new CameraWindow;
	 CameraControlParamDisplay = new CameraControlWindow;
	
	qRegisterMetaType<DataImageProcStructure>("DataImageProcStructure");
	qRegisterMetaType<DataToDisplayStructure>("DataToDisplayStructure");
	qRegisterMetaType<DataTemperatureStructure>("DataTemperatureStructure");
	qRegisterMetaType<DataCamerasStructure>("DataCamerasStructure");
	qRegisterMetaType<DataLaserStruct>("DataLaserStruct");
	qRegisterMetaType<DataAimingErrorStructure>("DataAimingErrorStructure");
	qRegisterMetaType<DataEngineStructure>("DataEngineStructure");
	qRegisterMetaType<DataCoordStructure>("DataCoordStructure");
	qRegisterMetaType<QVector<QPair<double,double>>>("MassCoord");


	QObject::connect(this, SIGNAL(SignalLaserStateDisplay(DataLaserStruct)), this, SLOT(DisplayLaserStateDisplay(DataLaserStruct)));
	QObject::connect(this, SIGNAL(SignalNewImage(DataImageProcStructure)),       this, SLOT(DisplayImage(DataImageProcStructure)));
	QObject::connect(this, SIGNAL(SignalNewAirData(DataTemperatureStructure)),   this, SLOT(DisplayAirData(DataTemperatureStructure)));
	QObject::connect(this, SIGNAL(SignalNewCameraData(DataCamerasStructure)),    this, SLOT(DisplayCameraData(DataCamerasStructure)));
	QObject::connect(this, SIGNAL(SignalNewChillData(DataTemperatureStructure)), this, SLOT(DisplayChillData(DataTemperatureStructure)));

	QObject::connect(this, SIGNAL(SignalNewEngineData(DataEngineStructure)), this, SLOT(DisplayEngineData(DataEngineStructure)));

	QObject::connect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), this, SLOT(DisplayAimingData(DataAimingErrorStructure)));
	QObject::connect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), GraphicsWidget, SLOT(DisplayAimingData(DataAimingErrorStructure)));

	QObject::connect(this, SIGNAL(SignalNewCoordsData(DataCoordStructure)),this,SLOT(DisplayCoordData(DataCoordStructure)));
	QObject::connect(this, SIGNAL(SignalDispalyFullImage(QImage)),this,SLOT(DisplayFullImage(QImage)));


	ImageRGBToDisplay = QImage(256, 256, QImage::Format_RGB888);

	Scene = new QGraphicsScene();
	Scene->setSceneRect(0, 0, 3200, 2400);
	

	int CommonYMargin = 80;
	GraphicWidgetNode* LableImageBlock = new GraphicWidgetNode(Scene, 14, 1323, LabelImage);
	LableImageBlock->resize(1024, 256);
	MainBlock1 = new GraphicWidgetNode(Scene, 689, 530, MainBlockDisplay);

	GraphicWidgetNode* ImageProcWindow = new GraphicWidgetNode(Scene, 344, 363, ImageProcDisplay);

	GraphicWidgetNode* ImageProcDisplayWindow = new GraphicWidgetNode(Scene, 15, 757, ShowImageDisplay);

	GraphicWidgetNode* AimingBlock1 = new GraphicWidgetNode(Scene, 1010, 412,AimingBlockDisplay1);
	GraphicWidgetNode* AimingBlock2 = new GraphicWidgetNode(Scene, 1184, 631,AimingBlockDisplay2);
	GraphicWidgetNode* AimingBlock3 = new GraphicWidgetNode(Scene, 1321, 879,AimingBlockDisplay3);


	GraphicWidgetNode* PIDNode = new GraphicWidgetNode(Scene, 1204, 3,PIDControl);
	//GraphicWidgetNode* CalmanNode = new GraphicWidgetNode(Scene, 1205, 86,KalmanControl);
	

	GraphicWidgetNode* EngineControlBlock1 = new GraphicWidgetNode(Scene, 1570, 426,EngineControlDisplay1);
	GraphicWidgetNode* EngineControlBlock2 = new GraphicWidgetNode(Scene, 1570, 644,EngineControlDisplay2);
					   EngineControlBlock3 = new GraphicWidgetNode(Scene, 1570, 891,EngineControlDisplay3);

	GraphicWidgetNode* GraphicsWindowNode = new GraphicWidgetNode(Scene, 1097, 1215 + CommonYMargin,GraphicsDisplay);

	GraphicWidgetNode* LaserBlockWindow1 = new GraphicWidgetNode(Scene, 910, 40,LaserControlDisplay);

	GraphicWidgetNode* Kamera = new GraphicWidgetNode(Scene, 3, 440,CameraControlBlockDisplay);
	GraphicWidgetNode* KameraControl = new GraphicWidgetNode(Scene, 10, 45,CameraControlParamDisplay);

//color: rgb(130, 91, 47);
//color: rgb(87, 104, 50);
//color: rgb(74, 90, 72);
//color: rgb(56, 95, 53);
//rgb(54, 28, 22);

			Scene->addItem(new Edge(ImageProcWindow->OutputNode, MainBlock1->InputNode));
			Scene->addItem(new Edge(LaserBlockWindow1->OutputNodeDown, MainBlock1->InputNodeUp));
			Scene->addItem(new Edge(MainBlock1->OutputNode, AimingBlock1->InputNode));
			Scene->addItem(new Edge(MainBlock1->OutputNode, AimingBlock2->InputNode));
			Scene->addItem(new Edge(MainBlock1->OutputNode, AimingBlock3->InputNode));

			Scene->addItem(new Edge(AimingBlock1->InputNodeUp,PIDNode->OutputNodeDown));
	        dynamic_cast<Edge*>(Scene->items().first())->SetColor(QColor(54,28,22));
			Scene->addItem(new Edge(AimingBlock2->InputNodeUp,PIDNode->OutputNodeDown));
	        dynamic_cast<Edge*>(Scene->items().first())->SetColor(QColor(54,28,22));
			Scene->addItem(new Edge(AimingBlock3->InputNodeUp,PIDNode->OutputNodeDown));
	        dynamic_cast<Edge*>(Scene->items().first())->SetColor(QColor(54,28,22));

			//Scene->addItem(new Edge(CalmanNode->OutputNode,PIDNode->InputNode));
        	dynamic_cast<Edge*>(Scene->items().first())->SetColor(QColor(54,28,22));
			Scene->addItem(new Edge(AimingBlock1->OutputNode, EngineControlBlock1->InputNode));
			Scene->addItem(new Edge(AimingBlock2->OutputNode, EngineControlBlock2->InputNode));
			Scene->addItem(new Edge(AimingBlock3->OutputNode, EngineControlBlock3->InputNode));
			Scene->addItem(new Edge(AimingBlock3->OutputNodeDown, GraphicsWindowNode->InputNodeUp));

			Scene->addItem(new Edge(Kamera->OutputNode, ImageProcWindow->InputNode));
			Scene->addItem(new Edge(KameraControl->OutputNodeDown, Kamera->InputNodeUp));

			Scene->addItem(new Edge(ImageProcWindow->OutputNodeDown, ImageProcDisplayWindow->InputNodeUp));
			Scene->addItem(new Edge(MainBlock1->OutputNodeDown, LableImageBlock->InputNodeUp));
			Scene->addItem(GraphicsWindowNode);


	ui.graphicsView->setScene(Scene);
	ui.graphicsView->centerOn(20, 20);
}




//����������
MainWindowQClass::~MainWindowQClass()
{

	QObject::disconnect(this, SIGNAL(SignalNewImage(DataImageProcStructure)),       this, SLOT(DisplayImage(DataImageProcStructure)));
	QObject::disconnect(this, SIGNAL(SignalNewAirData(DataTemperatureStructure)),   this, SLOT(DisplayAirData(DataTemperatureStructure)));
	QObject::disconnect(this, SIGNAL(SignalNewCameraData(DataCamerasStructure)),    this, SLOT(DisplayCameraData(DataCamerasStructure)));
	QObject::disconnect(this, SIGNAL(SignalNewChillData(DataTemperatureStructure)), this, SLOT(DisplayChillData(DataTemperatureStructure)));

	QObject::disconnect(this, SIGNAL(SignalNewEngineData(DataEngineStructure)), this, SLOT(DisplayEngineData(DataEngineStructure)));

	QObject::disconnect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), this, SLOT(DisplayAimingData(DataAimingErrorStructure)));
	QObject::disconnect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), GraphicsDisplay, SLOT(DisplayAimingData(DataAimingErrorStructure)));


	QObject::disconnect(this, SIGNAL(SignalNewCoordsData(DataCoordStructure)),this,SLOT(DisplayCoordData(DataCoordStructure)));
	qDebug() << "DELETE MAIN WINDOW";
}




//����� �����������
void MainWindowQClass::DisplayImage(DataImageProcStructure Data)
{

		ImageGrayToDisplay = Data.Image;
		ImageGrayToDisplay.detach();
		this->ConvertImage(ImageGrayToDisplay, ImageRGBToDisplay);

	QPen pen; pen.setWidth(2);
	pen.setColor(Qt::red);
	QPainter paint;

	paint.begin(&ImageRGBToDisplay);
	paint.setPen(pen);
	paint.drawEllipse(Data.LastCoordInROI.first,Data.LastCoordInROI.second, 5, 5);
	paint.drawRect(Data.ROIInStrob);

	pen.setColor(Qt::green);
	paint.setPen(pen);
	paint.drawEllipse(Data.LastAimingCoord.first,Data.LastAimingCoord.second, 8, 8);



	paint.end();

	this->ShowImageDisplay->DisplayImage(ImageRGBToDisplay, Data.NumberBlock);
	this->ShowImageDisplay->DisplayThreshold(Data.Threshold, Data.NumberBlock);
	//this->ShowImageDisplay->DisplayImage(ImageGrayToDisplay, Data.NumberBlock);
	this->ImageProcDisplay->DisplayState(Data.State, Data.NumberBlock);
}

void MainWindowQClass::DisplayCoordData(DataCoordStructure Data)
{
	this->ShowImageDisplay->DisplayROIPos(Data.Coords, Data.CoordsROI);
}

const QString& MainWindowQClass::GetBlockState(stateblocksenum State)
{
	switch (State) {
	default:
		return "State unknown.\n";
	case BlockReadyToWork:
		return "Block is ready to work.\n";
		break;
	case BlockFault:
		return "Block fault.\n";
		break;
	case BlockDisable:
		return "Block disabled.\n";
		break;
	case BlockAtWork:
		return "Block is working.\n";
		break;
	}
}

//����� ������ � ������ �������
void MainWindowQClass::DisplayAirData(DataTemperatureStructure DataStructure)
{

}

//����� ���������� �����
void MainWindowQClass::DisplayCameraData(DataCamerasStructure DataStructure)
{
	this->CameraControlBlockDisplay->DisplayState(DataStructure.State);
}

void MainWindowQClass::DisplayChillData(DataTemperatureStructure Data)
{
}

void MainWindowQClass::DisplayLaserStateDisplay(DataLaserStruct Data)
{
	this->LaserControlDisplay->DisplayState(Data.State, Data.NumberBlock);
}

//����� ������ ������� ���������
void MainWindowQClass::DisplayAimingData(DataAimingErrorStructure DataStructure)
{
	if (DataStructure.NumberBlock == 1)
	this->AimingBlockDisplay1->DisplayState(DataStructure.State);

	if (DataStructure.NumberBlock == 2)
	this->AimingBlockDisplay2->DisplayState(DataStructure.State);

	if (DataStructure.NumberBlock == 3)
	this->AimingBlockDisplay3->DisplayState(DataStructure.State);

	this->PIDControl->DisplayState(DataStructure.PIDState);
	//this->KalmanControl->DisplayState(DataStructure.CalmanState);

}

//����� ������ ��������
void MainWindowQClass::DisplayEngineData(DataEngineStructure DataStructure)
{
	this->EngineControlDisplay1->DisplayState(DataStructure.Engine1);
	this->EngineControlDisplay2->DisplayState(DataStructure.Engine2);
	this->EngineControlDisplay3->DisplayState(DataStructure.Engine3);
}

void MainWindowQClass::DisplayFullImage(QImage Image)
{

 

	this->LabelImage->setPixmap(QPixmap::fromImage(Image));
}


void operator>>(const DataToDisplayStructure& DataToDisplay, MainWindowQClass &MainWindow)
{

	switch (DataToDisplay.TypeBlock){
	case EngineControlBlock:
		emit MainWindow.SignalNewEngineData(static_cast<const DataEngineStructure&>(DataToDisplay));
		break;
	case ChillControlBlock:
		 emit MainWindow.SignalNewChillData(static_cast<const DataTemperatureStructure&>(DataToDisplay));
		break;
	case AirControlBlock:
	 emit MainWindow.SignalNewAirData(static_cast<const DataTemperatureStructure&>(DataToDisplay));
		break;
	case CamerasControlBlock:
		 emit MainWindow.SignalNewCameraData(static_cast<const DataCamerasStructure&>(DataToDisplay));
		 MainWindow.CameraControlBlockDisplay->DisplayCameraData(static_cast<const DataCamerasStructure&>(DataToDisplay));
		break;
	case AimingBlock:
		 emit MainWindow.SignalNewAimingData(static_cast<const DataAimingErrorStructure&>(DataToDisplay));
		break;
	case ImageProcBlock:

		 //emit MainWindow.SignalNewImage(static_cast<DataImageProcStructure&>(DataToDisplay));

		 emit MainWindow.SignalNewImage(static_cast<const DataImageProcAllChannels&>(DataToDisplay).Channel1);
		 emit MainWindow.SignalNewImage(static_cast<const DataImageProcAllChannels&>(DataToDisplay).Channel2);
		 emit MainWindow.SignalNewImage(static_cast<const DataImageProcAllChannels&>(DataToDisplay).Channel3);
		 emit MainWindow.SignalNewImage(static_cast<const DataImageProcAllChannels&>(DataToDisplay).Channel4);

		 emit MainWindow.SignalNewCoordsData(static_cast<const DataImageProcAllChannels&>(DataToDisplay).AllChannelsCoord);

		 MainWindow.ImageProcDisplay->DisplayProcessingData(static_cast<const DataImageProcAllChannels&>(DataToDisplay));
		break;
	case LasersBlock:
		 emit MainWindow.SignalLaserStateDisplay(static_cast<const DataLaserStruct&>(DataToDisplay));
		break;
	default:
		break;
	}
}




void MainWindowQClass::SlotChangeViewWindow()
{
	
}

void MainWindowQClass::ConnectControlSignals(HandleControlInterface* Control)
{
	this->EngineControlDisplay1->ConnectControlSignals(Control);
	this->EngineControlDisplay2->ConnectControlSignals(Control);
	this->EngineControlDisplay3->ConnectControlSignals(Control);

	this->AimingBlockDisplay1->ConnectControlSignals(Control);
	this->AimingBlockDisplay2->ConnectControlSignals(Control);
	this->AimingBlockDisplay3->ConnectControlSignals(Control);

	this->ShowImageDisplay->ConnectControlSignals(Control);
	this->CameraControlParamDisplay->ConnectControlSignals(Control);
	this->CameraControlBlockDisplay->ConnectControlSignals(Control);

	this->LaserControlDisplay->ConnectControlSignals(Control);

	this->MainBlockDisplay->ConnectControlSignals(Control);

	this->ImageProcDisplay->ConnectControlSignals(Control);
	PIDControl->ConnectControlSignals(Control);
	//KalmanControl->ConnectControlSignals(Control);

}

void MainWindowQClass::SetWidgetToScene(QWidget* Wid)
{
    
}

void MainWindowQClass::ConvertImage(QImage& GrayImage, QImage& ColorImage)
{
	uchar* R = 0;
	uchar* G = 0;
	uchar* B = 0;

	quint16* gray_line = 0;
	quint16* gray_pixel = 0;
	uchar* color_line = 0;
    
	for (int ii = 0; ii < GrayImage.height(); ii++) 
	{

        gray_line = reinterpret_cast<quint16*>(GrayImage.scanLine(ii));
		color_line = ColorImage.scanLine(ii);

		for (int jj = 0; jj < GrayImage.width(); jj++) {

			 gray_pixel = gray_line + jj;

			 R = color_line + jj*3;
			 G = color_line + jj*3 + 1;
			 B = color_line + jj*3 + 2;

			 *R = *gray_pixel/256;
			 *G = *gray_pixel/256;
			 *B = *gray_pixel/256;
		}
	}
}
