#pragma once

#include <QWidget>
#include "ui_ErrorPortControl.h"
#include "AdjustableWidget.h"


class ErrorRecieverHandleInterface;

class ErrorPortControl : public AdjustableWidget
{
	Q_OBJECT

public:
	ErrorPortControl(QWidget *parent = Q_NULLPTR);
	~ErrorPortControl();

	ErrorRecieverHandleInterface* ErrorPortHandleControl = 0;

	void SetHandleControl(ErrorRecieverHandleInterface* HandleControlInterface) { ErrorPortHandleControl = HandleControlInterface;};

public slots:
	void SlotSetActiveChannel();
	void SlotResetBlock();
	void SlotSetWorkMode();

private:
	Ui::ErrorPortControl ui;
};
