#ifndef CAMERACONTROLWINDOW_H
#define CAMERACONTROLWINDOW_H

#include <QWidget>
#include "ui_cameracontrolwindow.h"
#include "HandleControlInterface.h"
#include <QString>
#include "AdjustableWidget.h"



class CameraControlWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	CameraControlWindow(QWidget *parent = 0);
	~CameraControlWindow();

	void ConnectControlSignals(HandleControlInterface* Control);
private:
	Ui::CameraControlWindow ui;

};

#endif // CAMERACONTROLWINDOW_H
