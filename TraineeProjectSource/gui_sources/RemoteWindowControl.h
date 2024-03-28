#pragma once

#include <QWidget>
#include "ui_RemoteCommandDisplay.h"
#include "AdjustableWidget.h"


class RemoteWindowControl : public AdjustableWidget
{
	Q_OBJECT

public:
	RemoteWindowControl(QWidget *parent = Q_NULLPTR);
	~RemoteWindowControl();

public slots:
    void SlotPrintRemoteCommand(QString Command);

private:
	Ui::RemoteCommandDisplay ui;
};
