#ifndef MAINWINDOWQCLASS_H
#define MAINWINDOWQCLASS_H
//#include "ImageStruct.h"
#include "DataDeviceStructureCommon.h"
#include "DataAimingErrorStructure.h"
#include "DataCamerasStructure.h"
#include "DataImageProcStructure.h"
#include "DataLaserStruct.h"
#include "DataWeatherStructure.h"
#include "DataEngineStructure.h"
#include "DataChillerStructure.h"
#include "DataDeviceStructureCommon.h"



#include "ui_mainwindowqclass.h"
#include "HandleControlInterface.h"

#include "graphicswindow.h"

#include "pidwindow.h"
#include "engineblockwindow.h"
#include "camerawindow.h"
#include "aimingblockwindow.h"
#include "graphicwidgetnode.h"
#include "kalmanwindow.h"
#include "imageprocessingdisplaywindow.h"
#include "imageprocessingwindow.h"
#include "mainblockwindow.h"
#include "laserblockwindow.h"
#include "enginecontrolwindow.h"
#include "cameracontrolwindow.h"
#include "imageprocessingdisplaywindow.h"
#include "AdjustableWidget.h"


class MainWindowQClass : public QMainWindow
{
	Q_OBJECT 

public:
	MainWindowQClass(GraphicsWindow* GraphicsWidget,QWidget *parent = 0);
	~MainWindowQClass();

public:
	Ui::MainWindowQClass ui;
public:
	friend void operator>>(const DataDeviceStructure& DataToDisplay,MainWindowQClass &MainWindow);
	
	QTimer TimerToCheckStateBlocks;

	void SetWidgetToScene(QWidget* Wid);
	void ConvertImage(QImage& GrayImage, QImage& ColorImage);

	void ConnectControlSignals(HandleControlInterface* Control);

	void AddWidgetToDisplay(AdjustableWidget* widget);
	void AddWidgetToDisplay(AdjustableLabel* widget);

private:
	void SaveWidgetsPosition();
	void LoadWidgetsPosition();
    void SetWidgetsPosition(int group_number);
	void SetGuiFontSize(int FontSize);

	void SaveWidgetsLinks();
	void LoadWidgetsLinks();

	MainBlockWindow* MainBlockDisplay;
	ImageProcessingWindow* ImageProcDisplay        ;
	ImageProcessingDisplayWindow* ShowImageDisplay ;
	AimingBlockWindow* AimingBlockDisplay1         ;
	AimingBlockWindow* AimingBlockDisplay2         ;
	AimingBlockWindow* AimingBlockDisplay3         ;
	PIDWIndow* PIDControl;
	KalmanWindow* KalmanControl;

	QLabel* LabelImage;


	EngineControlWindow* EngineControlDisplay1;
	EngineControlWindow* EngineControlDisplay2;
	EngineControlWindow* EngineControlDisplay3;

	GraphicWidgetNode* EngineControlBlock3;
	GraphicWidgetNode* MainBlock1;

	LaserBlockWindow* LaserControlDisplay;

	CameraWindow* CameraControlBlockDisplay;
	CameraControlWindow* CameraControlParamDisplay;

	QGraphicsScene* Scene;
protected:
    void closeEvent(QCloseEvent *event) override;
private:
	QImage ImageToDisplay;
	QImage ImageRGBToDisplay;
	QImage ImageGrayToDisplay;

	const QString& GetBlockState(stateblocksenum State);

	GraphicsWindow* GraphicsDisplay;

	QVector<QLabel*> LabelImageMass;
	QVector<QVector<QPair<int,int>>> WidgetsPositionList;

	QList<GraphicWidgetNode*> ModuleWidgets;

    int CurrentGuiSize = 0;
private slots:
    void SlotUpdateScene(); // repaint scene when widget size has changed

public slots:
    void SlotChangeInterfaceSize();
    void SlotSetInterfaceSize(int GuiSize);

	void DisplayImage(DataImageProcStructure Data);
	void DisplayCoordData(DataCoordStructure Data);


	void DisplayWeatherData(DataWeatherStructure Data);
	void DisplayCameraData(DataCamerasStructure Data);
	void DisplayChillData(DataChillerStructure Data);
	void DisplayLaserStateDisplay(DataLaserStruct Data);

	void DisplayAimingData(DataAimingErrorStructure Data);

	void DisplayEngineData(DataEngineStructure Data);
	void DisplayFullImage(QImage Image);


signals:

	void SignalNewControlData(DataDeviceStructure Data);
	void SignalNewImage(DataImageProcStructure Data);
	void SignalNewCameraData(DataCamerasStructure Data);
	void SignalNewChillData(DataChillerStructure Data);
	void SignalNewWeatherData(DataWeatherStructure Data);
	void SignalNewAimingData(DataAimingErrorStructure Data);
	void SignalNewEngineData(DataEngineStructure Data);
	void SignalNewCoordsData(DataCoordStructure Data);
	void SignalLaserStateDisplay(DataLaserStruct Data);
	void SignalDispalyFullImage(QImage Image);
	void SignalMainWindowClosed();
};

#endif // MAINWINDOWQCLASS_H

