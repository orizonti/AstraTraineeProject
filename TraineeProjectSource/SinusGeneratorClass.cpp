#include "stdafx.h"
#include "SinusGeneratorClass.h"
#include "windowsinussource.h"
#include <random>
#include <math.h>


SinusGeneratorClass::SinusGeneratorClass(QObject* Obj) : QObject(Obj)
{
	WindowControl = new WindowSinusSource;
	QObject::connect(&this->TimerGenerateSinus, SIGNAL(timeout()), this, SLOT(SlotCalculateNewValue()));

	 AmplitudeRadianX = 30*4.84/1000000;
	 AmplitudeRadianY = 30*4.84/1000000;

	 LastPosRadian = QPair<double, double>(0, 0);
	 LastPosSeconds = QPair<double, double>(0, 0);
	 CurrentPosSeconds = QPair<double, double>(0, 0);
	 CurrentPosSeconds = QPair<double, double>(0, 0);

	 StepInRadian = QPair<double, double>(0, 0);

	WindowControl->ConnectSignals(this);
}


SinusGeneratorClass::~SinusGeneratorClass()
{
	qDebug() << "Delete sinus generator and its window";
	//delete WindowControl;
}

void SinusGeneratorClass::DisplayControlWindow()
{
	WindowControl->show();
}

void SinusGeneratorClass::DisplayControlWindow(QGraphicsScene* Scene)
{
	WindowControl->MoveToScene(Scene);
}


void SinusGeneratorClass::SetCoord(QPair<double,double> Coord)
{
}

QPair<double, double> SinusGeneratorClass::GetCoord()
{
	//return CurrentPosSeconds;
	//return CurrentPosRadian;
	return StepInRadian;
}

void SinusGeneratorClass::SlotSetFrequency(double FreqX,double FreqY)
{
	StepSecondsX = (360.0/500.0) * FreqX;
	StepSecondsY = (360.0/500.0) * FreqY;
	qDebug() << "Step seconds " << StepSecondsX << StepSecondsY;
}

void SinusGeneratorClass::SlotSetAmplitudeSeconds(double AmplX, double AmplY)
{
	qDebug() << "Amp - " << AmplX << AmplY;
	this->AmplitudeRadianX = AmplX*4.84 / 1000000;
	this->AmplitudeRadianY = AmplY*4.84 / 1000000;
}


void SinusGeneratorClass::SlotCalculateNewValue()
{
	CurrentPosRadian.first = std::sin(this->CurrentStepSecondsX * 2 * M_PI / (360.0))*AmplitudeRadianX;
	CurrentPosRadian.second = std::cos(this->CurrentStepSecondsY*2* M_PI /(360.0))*AmplitudeRadianY*0;
	CurrentPosSeconds.first = CurrentPosRadian.first * 1000000.0 / 4.84;
	CurrentPosSeconds.second = CurrentPosRadian.second * 1000000.0 / 4.84;

	qDebug() << "SINUS VALUE- " << CurrentStepSecondsX;
	this->CurrentStepSecondsX += this->StepSecondsX;
	this->CurrentStepSecondsY += this->StepSecondsY;

	StepInRadian.second = CurrentPosRadian.first - LastPosRadian.first;
	StepInRadian.first = CurrentPosRadian.second - LastPosRadian.second;

	if (CurrentStepSecondsX >= 360)
	{
		this->CurrentStepSecondsX = 0;
		this->CurrentStepSecondsY = 0;
	}

	if (Link != 0)
		*this >> *Link;

	LastPosRadian.first = CurrentPosRadian.first;
	LastPosRadian.second = CurrentPosRadian.second;
}

void SinusGeneratorClass::SlotStartGenerate(bool StartStop)
{
	if (StartStop)
	this->TimerGenerateSinus.start(2);
	else
	this->TimerGenerateSinus.stop();

}
