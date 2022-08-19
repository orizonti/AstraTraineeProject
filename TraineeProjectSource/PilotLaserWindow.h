#pragma once

#include <QWidget>
#include "ui_PilotLaserWindow.h"
#include "QString"


class PilotLaserWindow : public QWidget
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
