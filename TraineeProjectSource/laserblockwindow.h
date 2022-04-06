#ifndef LASERBLOCKWINDOW_H
#define LASERBLOCKWINDOW_H

#include "ui_laserblockwindow.h"
#include "HandleControlInterface.h"

class LaserBlockWindow : public QWidget
{
	Q_OBJECT

public:
	LaserBlockWindow(QWidget *parent = 0);
	~LaserBlockWindow();

	void DisplayState(stateblocksenum State,int NumberChannel);
	void ConnectControlSignals(HandleControlInterface* Control);
private:
	Ui::LaserBlockWindow ui;
};

#endif // LASERBLOCKWINDOW_H
