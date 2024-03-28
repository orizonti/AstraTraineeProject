#ifndef PIDWindow2_H
#define PIDWindow2_H

#include "HandleControlInterface.h"
#include "ui_pid_control_window.h"
#include "AdjustableWidget.h"

class PIDWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	PIDWindow(QWidget *parent = 0);
	~PIDWindow();
	void DisplayState(stateblocksenum State);
	void ConnectControlSignals(HandleControlInterface* Control);
	void SetInitialState(double Rate, double Diff, double Int);
private:
	Ui::pid_control_window ui;
};

#endif // PIDWindow2_H
