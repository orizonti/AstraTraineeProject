#ifndef KALMANWINDOW_H
#define KALMANWINDOW_H

#include "ui_kalmanwindow.h"
#include "HandleControlInterface.h"
#include "AdjustableWidget.h"

class KalmanWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	KalmanWindow(QWidget *parent = 0);
	~KalmanWindow();

	void DisplayState(stateblocksenum State);
	void DisplayParam(double VarE, double VarM, double VarVM);
	void ConnectControlSignals(HandleControlInterface* Control);
private:
	Ui::KalmanWindow ui;
};

#endif // KALMANWINDOW_H
