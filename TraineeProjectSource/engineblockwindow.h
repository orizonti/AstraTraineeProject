#ifndef ENGINEBLOCKWINDOW_H
#define ENGINEBLOCKWINDOW_H

#include "ui_engineblockwindow.h"

class EngineBlockWindow : public QWidget
{
	Q_OBJECT

public:
	EngineBlockWindow(QWidget *parent = 0);
	~EngineBlockWindow();

private:
	Ui::EngineBlockWindow ui;
};

#endif // ENGINEBLOCKWINDOW_H
