#pragma once

#include <QWidget>
#include "ui_PilotLaserWindow.h"
#include "QString"
#include "AdjustableWidget.h"


class PilotLaserWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	PilotLaserWindow(QWidget *parent = Q_NULLPTR);
	~PilotLaserWindow();
	void PrintInput(QString input);
	void PrintOutput(QString output);
	void PrintState(QString state, int State);

private:
	Ui::PilotLaserWindow ui;
};
