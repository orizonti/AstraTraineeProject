#ifndef PIDWIndow_H
#define PIDWIndow_H

#include "HandleControlInterface.h"
#include "ui_PIDWIndow.h"
#include "AdjustableWidget.h"

class PIDWIndow : public AdjustableWidget
{
	Q_OBJECT

public:
	PIDWIndow(QWidget *parent = 0);
	~PIDWIndow();
	void DisplayState(stateblocksenum State);
	void ConnectControlSignals(HandleControlInterface* Control);
	void SetInitialState(double Rate, double Diff, double Int);
private:
	Ui::PIDWIndow ui;
};

#endif // PIDWIndow_H
