#ifndef ENGINEBLOCKWINDOW_H
#define ENGINEBLOCKWINDOW_H

#include "ui_engineblockwindow.h"
#include "AdjustableWidget.h"

class EngineBlockWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	EngineBlockWindow(QWidget *parent = 0);
	~EngineBlockWindow();

private:
	Ui::EngineBlockWindow ui;
};

#endif // ENGINEBLOCKWINDOW_H
