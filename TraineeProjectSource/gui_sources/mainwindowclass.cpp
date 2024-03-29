#include "CommonHeaders.h"
#include "mainwindowclass.h"
#include <QAction>
#include <QObject>
#include <QGraphicsItem>
#include "link_line.h"
#define TAG "[ MAIN   WIND ]" 


MainWindowClass::MainWindowClass(GraphicsWindow* GraphicsWidget,QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    WidgetsPositionList.resize(2);
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

	 PIDControl = new PIDWindow;
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
	 ChillerWindow = new ChillerWindowDisplay;
	
	qRegisterMetaType<DataImageProcStructure>("DataImageProcStructure");
	qRegisterMetaType<DataDeviceStructure>("DataDeviceStructure");
	qRegisterMetaType<DataChillerStructure>("DataChillerStructure");
	qRegisterMetaType<DataWeatherStructure>("DataWeatherStructure");
	qRegisterMetaType<DataCamerasStructure>("DataCamerasStructure");
	qRegisterMetaType<DataLaserStruct>("DataLaserStruct");
	qRegisterMetaType<DataAimingErrorStructure>("DataAimingErrorStructure");
	qRegisterMetaType<DataEngineStructure>("DataEngineStructure");
	qRegisterMetaType<DataCoordStructure>("DataCoordStRucture");
	qRegisterMetaType<QVector<QPair<double,double>>>("MassCoord");


	QObject::connect(this, SIGNAL(SignalNewWeatherData(DataWeatherStructure)),   this, SLOT(DisplayWeatherData(DataWeatherStructure)));
	QObject::connect(this, SIGNAL(SignalNewChillData(DataChillerStructure)), this, SLOT(DisplayChillData(DataChillerStructure)));

	QObject::connect(this, SIGNAL(SignalLaserStateDisplay(DataLaserStruct)), this, SLOT(DisplayLaserStateDisplay(DataLaserStruct)));
	QObject::connect(this, SIGNAL(SignalNewImage(DataImageProcStructure)),       this, SLOT(DisplayImage(DataImageProcStructure)));
	QObject::connect(this, SIGNAL(SignalNewCameraData(DataCamerasStructure)),    this, SLOT(DisplayCameraData(DataCamerasStructure)));

	QObject::connect(this, SIGNAL(SignalNewEngineData(DataEngineStructure)), this, SLOT(DisplayEngineData(DataEngineStructure)));

	QObject::connect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), this, SLOT(DisplayAimingData(DataAimingErrorStructure)));
	QObject::connect(this, SIGNAL(SignalNewAimingData(DataAimingErrorStructure)), GraphicsWidget, SLOT(DisplayAimingData(DataAimingErrorStructure)));

	QObject::connect(this, SIGNAL(SignalNewCoordsData(DataCoordStructure)),this,SLOT(DisplayCoordData(DataCoordStructure)));
	QObject::connect(this, SIGNAL(SignalDispalyFullImage(QImage)),this,SLOT(DisplayFullImage(QImage)));

	QObject::connect(ui.actionGuiSizeSmall, &QAction::triggered,this, &MainWindowClass::SlotChangeInterfaceSize);
	QObject::connect(ui.actionGuiSizeBig, &QAction::triggered,this, &MainWindowClass::SlotChangeInterfaceSize);
	


	ImageRGBToDisplay = QImage(256, 256, QImage::Format_RGB888);

	Scene = new QGraphicsScene();
	Scene->setSceneRect(0, 0, 3200, 2400);
	


    LoadWidgetsPosition();
	this->ModuleWidgets.append(new GraphicWidgetNode(Scene, 14, 1323, LabelImage)); ModuleWidgets[0]->resize(1024, 256);

    this->AddWidgetToDisplay(MainBlockDisplay); this->AddWidgetToDisplay(ImageProcDisplay); this->AddWidgetToDisplay(ShowImageDisplay);
    this->AddWidgetToDisplay(AimingBlockDisplay1); this->AddWidgetToDisplay(AimingBlockDisplay2); this->AddWidgetToDisplay(AimingBlockDisplay3);

    this->AddWidgetToDisplay(PIDControl);
    this->AddWidgetToDisplay(EngineControlDisplay1); this->AddWidgetToDisplay(EngineControlDisplay2); this->AddWidgetToDisplay(EngineControlDisplay3);
    this->AddWidgetToDisplay(GraphicsDisplay); this->AddWidgetToDisplay(LaserControlDisplay); this->AddWidgetToDisplay(CameraControlBlockDisplay);

    this->AddWidgetToDisplay(CameraControlParamDisplay);
    this->AddWidgetToDisplay(ChillerWindow);

	LoadWidgetsLinks();

	ui.graphicsView->setScene(Scene);
	ui.graphicsView->centerOn(20, 20);

}


MainWindowClass::~MainWindowClass()
{
}

void MainWindowClass::DisplayImage(DataImageProcStructure Data)
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

void MainWindowClass::DisplayCoordData(DataCoordStructure Data)
{
	this->ShowImageDisplay->DisplayROIPos(Data.Coords, Data.CoordsROI);
}

const QString& MainWindowClass::GetBlockState(stateblocksenum State)
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

void MainWindowClass::DisplayCameraData(DataCamerasStructure DataStructure)
{
	this->CameraControlBlockDisplay->DisplayState(DataStructure.State);
}

void MainWindowClass::DisplayWeatherData(DataWeatherStructure DataStructure)
{

}

void MainWindowClass::DisplayRemoteCommand(QStringList& LogCommands)
{
}

void MainWindowClass::DisplayChillData(DataChillerStructure Data)
{
  this->ChillerWindow->SlotDisplayChillerData(Data);
}

void MainWindowClass::DisplayLaserStateDisplay(DataLaserStruct Data)
{
	this->LaserControlDisplay->DisplayState(Data.State, Data.NumberBlock);
}

void MainWindowClass::DisplayAimingData(DataAimingErrorStructure DataStructure)
{
	if (DataStructure.NumberBlock == 1)
	this->AimingBlockDisplay1->DisplayState(DataStructure.State,DataStructure.AimingState,DataStructure.PIDParam);

	if (DataStructure.NumberBlock == 2)
	this->AimingBlockDisplay2->DisplayState(DataStructure.State,DataStructure.AimingState,DataStructure.PIDParam);

	if (DataStructure.NumberBlock == 3)
	this->AimingBlockDisplay3->DisplayState(DataStructure.State,DataStructure.AimingState,DataStructure.PIDParam);

	this->PIDControl->DisplayState(DataStructure.PIDState);
	//this->KalmanControl->DisplayState(DataStructure.CalmanState);

}

void MainWindowClass::DisplayEngineData(DataEngineStructure DataStructure)
{
	this->EngineControlDisplay1->DisplayState(DataStructure.Engine1);
	this->EngineControlDisplay2->DisplayState(DataStructure.Engine2);
	this->EngineControlDisplay3->DisplayState(DataStructure.Engine3);
}

void MainWindowClass::DisplayFullImage(QImage Image)
{
	this->LabelImage->setPixmap(QPixmap::fromImage(Image));
}


void operator>>(const DataDeviceStructure& DataToDisplay, MainWindowClass &MainWindow)
{

	switch (DataToDisplay.TypeBlock){
	case EngineControlBlock:
		emit MainWindow.SignalNewEngineData(static_cast<const DataEngineStructure&>(DataToDisplay));
		break;
	case ChillControlBlock:
		 emit MainWindow.SignalNewChillData(static_cast<const DataChillerStructure&>(DataToDisplay));
		break;
	case WeatherControlBlock:
	 emit MainWindow.SignalNewWeatherData(static_cast<const DataWeatherStructure&>(DataToDisplay));
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





void MainWindowClass::ConnectControlSignals(HandleControlInterface* Control)
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
	this->PIDControl->ConnectControlSignals(Control);
	this->ChillerWindow->ConnectControlSignals(Control);

	//KalmanControl->ConnectControlSignals(Control);

}

void MainWindowClass::SetWidgetToScene(QWidget* Wid)
{
    
}

void MainWindowClass::ConvertImage(QImage& GrayImage, QImage& ColorImage)
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
void MainWindowClass::closeEvent(QCloseEvent *event)
{
qInfo() << TAG << "MAIN WINDOW CLOSED";
this->SaveWidgetsPosition();
emit SignalMainWindowClosed();
QThread::msleep(2000);
Scene->clear();
QMainWindow::closeEvent(event);
Scene->deleteLater();
}


void MainWindowClass::SlotChangeInterfaceSize()
{
   QAction* Action = dynamic_cast<QAction*>(QObject::sender());
   if(Action->objectName() == "actionGuiSizeSmall") {SlotSetInterfaceSize(0);};
   if(Action->objectName() == "actionGuiSizeBig")   {SlotSetInterfaceSize(1);};

    //QList<QGraphicsItem*> items = Scene->items();
	//qInfo() << TAG << "SAVE GROUP POSITIONS - " << CurrentGuiSize;
	//for(auto Item: items)
	//{
	//	if (GraphicWidgetNode* node = dynamic_cast<GraphicWidgetNode*>(Item); node != nullptr)
	//	{
	//	WidgetsPositionList[CurrentGuiSize][node->NumberWidget].first = node->NodePositionX;
	//	WidgetsPositionList[CurrentGuiSize][node->NumberWidget].second = node->NodePositionY;

	//	qInfo() <<"GROUP: " << CurrentGuiSize <<"NUMBER - " << qSetFieldWidth(4) << node->NumberWidget << 
	//	" X: " << WidgetsPositionList[CurrentGuiSize][node->NumberWidget].first  << 
	//	" Y: " << WidgetsPositionList[CurrentGuiSize][node->NumberWidget].second;
	//	}
	//}
	//qInfo() << TAG << "===========================" ;
}

void MainWindowClass::SetGuiFontSize(int GuiSize)
{
	int FontSize = 8; if(GuiSize == 1) FontSize = 12;
    QList<QGraphicsItem*> items = Scene->items();
	qInfo() << TAG << "SET GUID FONT SIZE FOR: " << items.count();
	for(auto Item: items)
	{
		if (GraphicWidgetNode* node = dynamic_cast<GraphicWidgetNode*>(Item); node != nullptr)
		{
			if (AdjustableWidget* widget = dynamic_cast<AdjustableWidget*>(node->WindowNode); widget != nullptr)
			widget->SlotSetWindowSize(FontSize);

			if (AdjustableLabel* label = dynamic_cast<AdjustableLabel*>(node->WindowNode); label != nullptr)
			label->SlotSetWindowSize(FontSize);
		}
	}
}

void MainWindowClass::SlotSetInterfaceSize(int GuiSize)
{
	CurrentGuiSize = GuiSize;
    SetGuiFontSize(CurrentGuiSize);
    SetWidgetsPosition(CurrentGuiSize);

    QTimer::singleShot(30,this,&MainWindowClass::SlotUpdateScene);
}

void MainWindowClass::SetWidgetsPosition(int group_number)
{

    QList<QGraphicsItem*> items = Scene->items();
	for(auto Item: items)
	{
	   if (GraphicWidgetNode* node = dynamic_cast<GraphicWidgetNode*>(Item); node != nullptr)
	   {
          node->SetScenePosition(WidgetsPositionList[group_number][node->NumberWidget].first,WidgetsPositionList[group_number][node->NumberWidget].second);  	
	   }
	}
}


void MainWindowClass::SaveWidgetsPosition()
{
qInfo() << TAG << "    [  SAVE WIDGETS POSITION  ]";
QString FileName = "/home/broms/TrainerData/WidgetsPosition.txt";

if(QFile::exists("/home/broms/DATA/TrainerData/WidgetsPosition.txt")) 
FileName = "/home/broms/DATA/TrainerData/WidgetsPosition.txt";
QFile data(FileName);
data.open(QFile::WriteOnly); data.flush();


QString outString;
QTextStream out(&outString);


    QList<QGraphicsItem*> items = Scene->items();
	for(auto Item: items)
	{
		if (GraphicWidgetNode* node = dynamic_cast<GraphicWidgetNode*>(Item); node != nullptr)
		{
		WidgetsPositionList[CurrentGuiSize][node->NumberWidget].first = node->NodePositionX;
		WidgetsPositionList[CurrentGuiSize][node->NumberWidget].second = node->NodePositionY;
		}
	}

    int number = 0;
	out <<"          NUMBER      POSITION" << Qt::endl;
    for(auto group: WidgetsPositionList)
	{
	  qInfo() << TAG << "==============================" << Qt::endl;
	  qInfo() << TAG << "GROUP: "<< number << Qt::endl;
      for(int n = 0; n < group.size(); n++)
	  {
	    out << qSetFieldWidth(10) << Qt::right << n << group[n].first << group[n].second  << Qt::endl;
        qInfo() << TAG <<"NUMBER: " << n << "POSITION: " << group[n].first << group[n].second << Qt::endl;
	  }
	  qInfo() << TAG << "==============================" << Qt::endl;
      number++;
	  out << "==============================" << Qt::endl;
	}

data.write(outString.toUtf8());
data.close();
}


void MainWindowClass::LoadWidgetsPosition()
{

    qInfo() << TAG << "=====================================";
    qInfo() << TAG << "LOAD WIDGETS POSITION";
	
	QString FileName = "/home/broms/DATA/TrainerData/WidgetsPosition.txt";

	if(QFile::exists("/home/broms/DATA/TrainerData/WidgetsPosition.txt")) 
	FileName = "/home/broms/DATA/TrainerData/WidgetsPosition.txt";
	        
	QFile file(FileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    int positions_group = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QTextStream stream(&line);

        if(line.contains("==")) 
		{
			qInfo() << TAG << "================================";
			positions_group++;
			continue;
		}

        int number; int POS_X;int POS_Y;
		stream >> number >> POS_X >> POS_Y;
        qInfo() << TAG <<"NUMBER: " << number << "POSITION: " << POS_X << POS_Y << Qt::endl;
		WidgetsPositionList[positions_group].append(QPair<int,int>(POS_X,POS_Y));
    }
}

void MainWindowClass::SlotUpdateScene()
{
    for(auto Node: ModuleWidgets)
		Node->UpdateWidget();

    Scene->update(Scene->sceneRect());
	ui.graphicsView->repaint();
}

void MainWindowClass::AddWidgetToDisplay(AdjustableWidget* widget)
{
    auto Position = WidgetsPositionList[CurrentGuiSize][this->ModuleWidgets.size()];
	this->ModuleWidgets.append(new GraphicWidgetNode(Scene, Position.first, Position.second+40,widget));
}

void MainWindowClass::AddWidgetToDisplay(AdjustableLabel* widget)
{
    auto Position = WidgetsPositionList[CurrentGuiSize][this->ModuleWidgets.size()];
	this->ModuleWidgets.append(new GraphicWidgetNode(Scene, Position.first, Position.second+40,widget));
}

void MainWindowClass::SaveWidgetsLinks()
{

}
void MainWindowClass::LoadWidgetsLinks()
{

  qInfo() << TAG << "    <<<  LOAD WIDGET LINKS";
  QString WidgetLinks = "2  1  : 1  0 \n"
						"12 3  : 1  2 \n"
						"1  1  : 4  0 \n"
						"1  1  : 5  0 \n"
						"1  1  : 6  0 \n"
						"4  2  : 7  3 \n"
						"5  2  : 7  3 \n"
						"6  2  : 7  3 \n"
						"4  1  : 8  0 \n"
						"5  1  : 9  0 \n"
						"6  1  : 10 0 \n"
						"6  3  : 11 2 \n"
						"13 1  : 2  0 \n"
						"14 3  : 13 2 \n"
						"2  3  : 3  2 \n"
						"1  3  : 0  2 \n";
            
QString FileName = "/home/broms/DATA/TrainerData/WidgetLinks.txt";
QFile file(FileName);

if (file.open(QIODevice::ReadOnly | QIODevice::Text))
WidgetLinks = file.readAll();


	QTextStream in_stream(&WidgetLinks);
	int module1, node1 , module2 , node2;
	QString delimeter;
	while(!in_stream.atEnd())
	{
		in_stream >> module1 >> node1 >> delimeter >> module2 >> node2;	

		if(delimeter == ":")
		Scene->addItem(new LinkLine(ModuleWidgets[module1]->VisualNodes[node1], ModuleWidgets[module2]->VisualNodes[node2]));
	}
	
	//dynamic_cast<LinkLine*>(Scene->items().first())->SetColor(QColor(54,28,22));
	//dynamic_cast<LinkLine*>(Scene->items().first())->SetColor(QColor(54,28,22));
	//dynamic_cast<LinkLine*>(Scene->items().first())->SetColor(QColor(54,28,22));
	//dynamic_cast<LinkLine*>(Scene->items().first())->SetColor(QColor(54,28,22));
	////Scene->addItem(GraphicsWindowNode);
}