#pragma once

#include <QWidget>
#include "ui_RemoteAimingWindowControl.h"
#include "AdjustableWidget.h"


class RemoteAimingHandleInterface;

class RemoteAimingWindowControl : public AdjustableWidget
{
	Q_OBJECT

public:
	RemoteAimingWindowControl(QWidget *parent = Q_NULLPTR);
	~RemoteAimingWindowControl();

	RemoteAimingHandleInterface* ErrorPortHandleControl = 0;

	void SetHandleControl(RemoteAimingHandleInterface* HandleControlInterface) { ErrorPortHandleControl = HandleControlInterface;};

public slots:
	void SlotSetActiveChannel();
	void SlotResetBlock();
	void SlotSetWorkMode();

private:
	Ui::RemoteAimingWindowControl ui;
};
