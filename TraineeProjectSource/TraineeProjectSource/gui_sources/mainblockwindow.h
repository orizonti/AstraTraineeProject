#ifndef MAINBLOCKWINDOW_H
#define MAINBLOCKWINDOW_H

#include "ui_mainblockwindow.h"
#include "HandleControlInterface.h"
#include "AdjustableWidget.h"

class MainBlockWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	MainBlockWindow(QWidget *parent = 0);
	~MainBlockWindow();
	void ConnectControlSignals(HandleControlInterface* Control);
	
private:
	Ui::MainBlockWindow ui;
signals:
	void SignalResetBlocks(bool OnOff);
};

#endif // MAINBLOCKWINDOW_H
