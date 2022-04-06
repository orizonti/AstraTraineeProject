#ifndef MAINWINDOWQCLASS_H
#define MAINWINDOWQCLASS_H
#include "ImageStruct.h"
#include "mainwindowqclass.h"
#include "DataToDisplayStructure.h"
#include "DataAimingErrorStructure.h"
#include "DataCamerasStructure.h"
#include "DataImageProcStructure.h"
#include "DataLaserStruct.h"
#include "DataTemperatureStructure.h"
#include "DataEngineStructure.h"



#include "ui_mainwindowqclass.h"
#include "HandleControlInterface.h"

#include "graphicswindow.h"

#include "pidwindow2.h"
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


class MainWindowQClass : public QMainWindow
{
	Q_OBJECT //������-�������� ��� �������������� ����������� Qt

public:
	MainWindowQClass(GraphicsWindow* GraphicsWidget,QWidget *parent = 0);
	~MainWindowQClass();

public:
	Ui::MainWindowQClass ui;
public:
	friend void operator>>(const DataToDisplayStructure& DataToDisplay,MainWindowQClass &MainWindow);
	
	QTimer TimerToCheckStateBlocks;

	void ConnectControlSignals(HandleControlInterface* Control);
	void SetWidgetToScene(QWidget* Wid);
	void ConvertImage(QImage& GrayImage, QImage& ColorImage);

	MainBlockWindow* MainBlockDisplay;
	ImageProcessingWindow* ImageProcDisplay        ;
	ImageProcessingDisplayWindow* ShowImageDisplay ;
	AimingBlockWindow* AimingBlockDisplay1         ;
	AimingBlockWindow* AimingBlockDisplay2         ;
	AimingBlockWindow* AimingBlockDisplay3         ;
	PIDWindow2* PIDControl;
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
private:
	//���������� (��������� ������ QImage) ��� �������� � ������ ����������� 
	QImage ImageToDisplay;
	QImage ImageRGBToDisplay;
	QImage ImageGrayToDisplay;

	const QString& GetBlockState(stateblocksenum State);

	GraphicsWindow* GraphicsDisplay;

	QVector<QLabel*> LabelImageMass;

public slots:
	void SlotChangeViewWindow();
	

	void DisplayImage(DataImageProcStructure Data);
		
	void DisplayCoordData(DataCoordStructure Data);


	void DisplayAirData(DataTemperatureStructure Data);
	void DisplayCameraData(DataCamerasStructure Data);
	void DisplayChillData(DataTemperatureStructure Data);
	void DisplayLaserStateDisplay(DataLaserStruct Data);

	void DisplayAimingData(DataAimingErrorStructure Data);

	void DisplayEngineData(DataEngineStructure Data);
	void DisplayFullImage(QImage Image);


signals:

	void SignalNewControlData(DataToDisplayStructure Data);
	void SignalNewImage(DataImageProcStructure Data);
	void SignalNewAirData(DataTemperatureStructure Data);
	void SignalNewCameraData(DataCamerasStructure Data);
	void SignalNewChillData(DataTemperatureStructure Data);
	void SignalNewAimingData(DataAimingErrorStructure Data);
	void SignalNewEngineData(DataEngineStructure Data);
	void SignalNewCoordsData(DataCoordStructure Data);
	void SignalLaserStateDisplay(DataLaserStruct Data);
	void SignalDispalyFullImage(QImage Image);
};

#endif // MAINWINDOWQCLASS_H

