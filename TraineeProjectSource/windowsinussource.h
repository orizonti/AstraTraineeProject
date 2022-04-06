#ifndef WINDOWSINUSSOURCE_H
#define WINDOWSINUSSOURCE_H

#include <QWidget>
#include "ui_windowsinussource.h"
#include "graphicwidgetnode.h"
#include "SinusGeneratorClass.h"
#include "QSpinBox";
#include "QDoubleSpinBox";

class WindowSinusSource : public QWidget
{
	Q_OBJECT
public:
	WindowSinusSource(QWidget *parent = 0);
	~WindowSinusSource();

	void MoveToScene(QGraphicsScene* Scene);
	void MoveToPos(int X_POS, int Y_POS);
	void ConnectToWidgetOnScene(GraphicWidgetNode* Node);
	int X_POS = 1970;
	int Y_POS = 1230;

	void ConnectSignals(SinusGeneratorClass* SinusGenerator);
	GraphicWidgetNode* Node = 0;
private:
	Ui::WindowSinusSource ui;
};

#endif // WINDOWSINUSSOURCE_H
