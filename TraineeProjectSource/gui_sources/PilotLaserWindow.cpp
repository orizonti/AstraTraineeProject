#include "stdafx.h"
#include "PilotLaserWindow.h"

PilotLaserWindow::PilotLaserWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

PilotLaserWindow::~PilotLaserWindow()
{
}

void PilotLaserWindow::PrintInput(QString input)
{
	//ui.listAnswerInput.addItem(input);
}

void PilotLaserWindow::PrintOutput(QString output)
{
}

void PilotLaserWindow::PrintState(QString state, int State)
{
}
