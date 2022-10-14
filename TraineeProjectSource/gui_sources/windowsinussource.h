#ifndef WINDOWSINUSSOURCE_H
#define WINDOWSINUSSOURCE_H

#include <QWidget>
#include "ui_windowsinussource.h"
#include "graphicwidgetnode.h"
#include "SinusGeneratorClass.h"
#include "QSpinBox";
#include "QDoubleSpinBox";
#include "AdjustableWidget.h"

class WindowSinusSource : public AdjustableWidget
{
	Q_OBJECT
public:
	WindowSinusSource(QWidget *parent = 0);
	~WindowSinusSource();

	void ConnectSignals(SinusGeneratorClass* SinusGenerator);
private:
	Ui::WindowSinusSource ui;
};

#endif // WINDOWSINUSSOURCE_H
