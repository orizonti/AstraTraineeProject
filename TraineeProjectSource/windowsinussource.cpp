#include "stdafx.h"
#include "windowsinussource.h"

WindowSinusSource::WindowSinusSource(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

WindowSinusSource::~WindowSinusSource()
{

}

void WindowSinusSource::MoveToScene(QGraphicsScene* Scene)
{
	Node = new GraphicWidgetNode(Scene, 300, 300, this);
	Node->setPos(X_POS, Y_POS);
}

void WindowSinusSource::MoveToPos(int X, int Y)
{
	Node->setPos(X, Y);
}

void WindowSinusSource::ConnectToWidgetOnScene(GraphicWidgetNode* Node)
{
}

void WindowSinusSource::ConnectSignals(SinusGeneratorClass* SinusGenerator)
{

	QVector<QSpinBox*> Spins;
	Spins.append(ui.SpinAmpX);
	Spins.append(ui.SpinAmpY);

	QVector<QDoubleSpinBox*> SpinsDouble;
	SpinsDouble.append(ui.SpinFreqX);
	SpinsDouble.append(ui.SpinFreqY);


	for (QSpinBox* Spin : Spins)
	{
	connect(Spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[this, SinusGenerator]()
	    {
		SinusGenerator->SlotSetAmplitudeSeconds(ui.SpinAmpX->value(), ui.SpinAmpY->value());
		});
	}

	for (QDoubleSpinBox* Spin : SpinsDouble)
	{
	connect(Spin, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		[this, SinusGenerator]()
	    {
		SinusGenerator->SlotSetFrequency(ui.SpinFreqX->value(), ui.SpinFreqY->value());
		});
	}

			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				SinusGenerator->SlotStartGenerate(ui.checkWorkBlock->isChecked());
			});

}
