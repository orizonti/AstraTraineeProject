#ifndef PIDWINDOW2_H
#define PIDWINDOW2_H

#include "HandleControlInterface.h"
#include "ui_pidwindow2.h"

class PIDWindow2 : public QWidget
{
	Q_OBJECT

public:
	PIDWindow2(QWidget *parent = 0);
	~PIDWindow2();
	void DisplayState(stateblocksenum State);
	void ConnectControlSignals(HandleControlInterface* Control);
	void SetInitialState(double Rate, double Diff, double Int);
private:
	Ui::PIDWindow2 ui;
};

#endif // PIDWINDOW2_H
