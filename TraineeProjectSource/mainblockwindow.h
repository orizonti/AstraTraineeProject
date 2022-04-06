#ifndef MAINBLOCKWINDOW_H
#define MAINBLOCKWINDOW_H

#include "ui_mainblockwindow.h"
#include "HandleControlInterface.h"

class MainBlockWindow : public QWidget
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
