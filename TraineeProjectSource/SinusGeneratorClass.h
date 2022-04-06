#pragma once
#include "PassTwoCoordClass.h"
#include "graphicwidgetnode.h"

class WindowSinusSource;

class SinusGeneratorClass :
	public QObject, public PassTwoCoordClass
{
	Q_OBJECT
public:
	SinusGeneratorClass(QObject* Obj = 0);
	~SinusGeneratorClass();


	void DisplayControlWindow();
	void DisplayControlWindow(QGraphicsScene* Scene);


	WindowSinusSource* WindowControl = 0;
	
	double CurrentStepSecondsX = 0;
	double CurrentStepSecondsY = 0;

	QPair<double, double> StepInRadian;
	QPair<double, double> CurrentPosRadian;
	QPair<double, double> CurrentPosSeconds;
	QPair<double, double> LastPosRadian;
	QPair<double, double> LastPosSeconds;

	double StepSecondsX = 1300; // 0.5 Hz with 1ms sample period
	double StepSecondsY = 1300; // 0.5 Hz with 1ms sample period

	double BiasDegreeX = 0;
	double BiasDegreeY = 0;

	double AmplitudeRadianX = 0.0005;
	double AmplitudeRadianY = 0.0005;

	QTimer TimerGenerateSinus;

	void SetCoord(QPair<double,double> Coord);
	QPair<double,double> GetCoord();

	public slots:
	void SlotSetFrequency(double FreqX,double FreqY);
	void SlotSetAmplitudeSeconds(double AmplX, double AmplY);
	void SlotCalculateNewValue();
	void SlotStartGenerate(bool StartStop);
};

