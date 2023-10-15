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
	bool RELATIVE_OUTPUT = true;

	double CurrentStepSecondsX = 0;
	double CurrentStepSecondsY = 0;
	QPair<double, double> CurrentPos;
	QPair<double, double> LastPos;
    QPair<double, double> StepPos;
    QPair<double, double> Noize;
	double StepSecondsX = 1; // 0.5 Hz with 1ms sample period
	double StepSecondsY = 1; // 0.5 Hz with 1ms sample period
	double AmplitudeToAngleSeconds = 4.84 / 1000000;

	bool ENABLE_CHANNEL1 = true;
    bool ENABLE_CHANNEL2 = true;
    bool ENABLE_NOIZE = false;

	double Amplitude = 30;
    double AmplitudeNoize = 3;

	QTimer TimerGenerateSinus;

	void SetCoord(QPair<double,double> Coord);
	QPair<double,double> GetCoord();

	public slots:
    void SetRelativeOutput(bool flag) {RELATIVE_OUTPUT = flag;}
	void SlotSetFrequency(double Freq);
	void SlotSetAmplitude(double Ampl);
    void SlotSetAmplitudeNoize(double Ampl);
    void SlotEnableChannel(bool Enable , int Channel);

	void SlotCalculateNewValue();
	void SlotStartGenerate(bool StartStop);

	signals:
    void SignalNewDataAvailable();
};

