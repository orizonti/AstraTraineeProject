#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include "ui_camerawindow.h"
#include "HandleControlInterface.h"

class CameraWindow : public QWidget
{
	Q_OBJECT

public:
	CameraWindow(QWidget *parent = 0);
	~CameraWindow();
	std::deque<double> FramePeriodMeasure;
	std::deque<double> FrameROIPeriodMeasure;

	void DisplayState(stateblocksenum State);
	void ConnectControlSignals(HandleControlInterface* Control);
	void DisplayCameraData(DataCamerasStructure Data);
private:
	Ui::CameraWindow ui;
};

#endif // CAMERAWINDOW_H
