#ifndef ENGINECONTROLWINDOW_H
#define ENGINECONTROLWINDOW_H


#include "ui_enginecontrolwindow.h"
#include "HandleControlInterface.h"
#include "DataEngineStructure.h"

class EngineControlWindow : public QWidget
{
	Q_OBJECT

public:
	EngineControlWindow(QWidget *parent = 0);
	~EngineControlWindow();

	void DisplayState(EngineData DataStructure);
	void ConnectControlSignals(HandleControlInterface* Control);
	void SetNumberChannel(int NumberChannel);
	int NumberChannel = 1;
	int current_x_pos;
	int current_y_pos;
private:
	Ui::EngineControlWindow ui;

};

#endif // ENGINECONTROLWINDOW_H
