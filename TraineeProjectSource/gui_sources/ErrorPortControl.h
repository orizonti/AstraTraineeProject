#pragma once

#include <QWidget>
#include "ui_ErrorPortControl.h"
#include "graphicwidgetnode.h"
#include "AdjustableWidget.h"

class ErrorRecieverHandleInterface;

class ErrorPortControl : public AdjustableWidget
{
	Q_OBJECT

public:
	ErrorPortControl(QWidget *parent = Q_NULLPTR);
	~ErrorPortControl();

	void MoveToScene(QGraphicsScene* Scene);
	void MoveToPos(int X_POS, int Y_POS);
	void ConnectToWidgetOnScene(GraphicWidgetNode* Node);
	int X_POS = 821;
	int Y_POS = 1026;

	ErrorRecieverHandleInterface* ErrorPortHandleControl = 0;

	void SetHandleControl(ErrorRecieverHandleInterface* HandleControlInterface) { ErrorPortHandleControl = HandleControlInterface;};

	GraphicWidgetNode* Node = 0;
public slots:
	void SlotSetActiveChannel();
	void SlotResetBlock();
	void SlotSetWorkMode();

private:
	Ui::ErrorPortControl ui;
};
