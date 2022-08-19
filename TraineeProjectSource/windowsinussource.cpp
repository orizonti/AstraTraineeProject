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

void WindowSinusSource::MoveToScene(QGraphicsScene* Scene, int POSX, int POSY)
{
	Node = new GraphicWidgetNode(Scene, POSX, POSX, this);
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


    connect(ui.SpinAmp,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
    [this, SinusGenerator]()
    {
        SinusGenerator->SlotSetAmplitude(ui.SpinAmp->value());
    });

	connect(ui.SpinFreq, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		[this, SinusGenerator]()
	    {
		SinusGenerator->SlotSetFrequency(ui.SpinFreq->value());
		});
    connect(ui.spinNoizeAmplitude, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this, SinusGenerator]()
            {
                SinusGenerator->SlotSetAmplitudeNoize(ui.spinNoizeAmplitude->value());
            });


	//SinusGenerator->SlotSetFrequency(ui.SpinFreqY->value(),ui.SpinFreq->value());
    //SinusGenerator->SlotSetAmplitude(ui.SpinAmpY->value(),ui.SpinAmp->value());

    //spinNoizeAmplitude

    connect(ui.checkChannel1, &QCheckBox::stateChanged,
            [=]()
            {
                SinusGenerator->SlotEnableChannel(ui.checkChannel1->isChecked(),1);
            });
    connect(ui.checkChannel2, &QCheckBox::stateChanged,
            [=]()
            {
                SinusGenerator->SlotEnableChannel(ui.checkChannel2->isChecked(),2);
            });
    connect(ui.checkNoize, &QCheckBox::stateChanged,
            [=]()
            {
                SinusGenerator->SlotEnableChannel(ui.checkNoize->isChecked(),3);
            });

    connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
        [=]()
    {
        SinusGenerator->SlotStartGenerate(ui.checkWorkBlock->isChecked());
    });

}
