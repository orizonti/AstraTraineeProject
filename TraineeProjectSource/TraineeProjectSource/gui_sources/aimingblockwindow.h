#ifndef AIMINGBLOCKWINDOW_H
#define AIMINGBLOCKWINDOW_H

#include "pidwindow.h"
#include "ui_aimingblockwindow.h"
#include "kalmanwindow.h"
#include "HandleControlInterface.h"
#include "AdjustableWidget.h"

class AimingBlockWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	AimingBlockWindow(QWidget *parent = 0);
	~AimingBlockWindow();

	int NumberChannel = 1;
    void DisplayState(stateblocksenum State, TypeAiming AimingType, std::tuple<float,float,float> PID);
	void ConnectControlSignals(HandleControlInterface* Control);

private:
	Ui::AimingBlockWindow ui;

public slots:
};

#endif // AIMINGBLOCKWINDOW_H
