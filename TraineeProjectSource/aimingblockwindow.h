#ifndef AIMINGBLOCKWINDOW_H
#define AIMINGBLOCKWINDOW_H

#include "pidwindow2.h"
#include "node.h"
#include "edge.h"
#include "graphicwidgetnode.h"
#include "ui_aimingblockwindow.h"
#include "kalmanwindow.h"
#include "HandleControlInterface.h"

class AimingBlockWindow : public QWidget
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
};

#endif // AIMINGBLOCKWINDOW_H
