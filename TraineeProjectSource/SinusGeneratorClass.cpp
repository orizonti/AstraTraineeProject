#include "CommonHeaders.h"
#include "SinusGeneratorClass.h"
#include "windowsinussource.h"
#include <random>
#include <math.h>

#define TAG "[ SINUS GEN   ]" 

SinusGeneratorClass::SinusGeneratorClass(QObject* Obj) : QObject(Obj)
{
	WindowControl = new WindowSinusSource;
	QObject::connect(&this->TimerGenerateSinus, SIGNAL(timeout()), this, SLOT(SlotCalculateNewValue()));

     qDebug() << TAG << "CREATE SINUS GENERATOR";
	 LastPos = QPair<double, double>(0, 0);
	 CurrentPos = QPair<double, double>(0, 0);
     StepPos = QPair<double, double>(0, 0);

	    int Freq = 1;
        StepSecondsX = (360.0/500.0) * Freq;
        StepSecondsY = (360.0/500.0) * Freq;


	WindowControl->ConnectSignals(this);
}


SinusGeneratorClass::~SinusGeneratorClass()
{
}

void SinusGeneratorClass::DisplayControlWindow()
{
	WindowControl->show();
}


void SinusGeneratorClass::SetCoord(QPair<double,double> Coord)
{
}

QPair<double, double> SinusGeneratorClass::GetCoord()
{
    if(RELATIVE_OUTPUT)
	return StepPos + Noize;

    return CurrentPos + Noize;
}

void SinusGeneratorClass::SlotSetFrequency(double Freq)
{
	StepSecondsX = (360.0/500.0) * Freq;
	StepSecondsY = (360.0/500.0) * Freq;
}

void SinusGeneratorClass::SlotSetAmplitude(double Ampl)
{
	this->Amplitude = Ampl;
}

void SinusGeneratorClass::SlotSetAmplitudeNoize(double Ampl)
{
    qDebug() << TAG << "Noize amplitude - " << Ampl;
    this->AmplitudeNoize = Ampl;
}
void SinusGeneratorClass::SlotEnableChannel(bool Enable , int Channel)
{
    qDebug() << TAG << "Enable channel - " << Channel << Enable;
    if(Channel == 1) ENABLE_CHANNEL1 = Enable;
    if(Channel == 2) ENABLE_CHANNEL2 = Enable;
    if(Channel == 3) ENABLE_NOIZE = Enable;
}


void SinusGeneratorClass::SlotCalculateNewValue()
{
	CurrentPos.first = std::sin(this->CurrentStepSecondsX * 2 * M_PI / (360.0))*Amplitude;
	CurrentPos.second = std::cos(this->CurrentStepSecondsY * 2 * M_PI /(360.0))*Amplitude;
    StepPos = CurrentPos - LastPos; LastPos = CurrentPos;

    this->CurrentStepSecondsX += this->StepSecondsX; this->CurrentStepSecondsY += this->StepSecondsY;

	if (CurrentStepSecondsX >= 360) { this->CurrentStepSecondsX = 0; this->CurrentStepSecondsY = 0; }

	if (Link != 0) *this >> *Link;

	if(ENABLE_NOIZE)
    {
        Noize.first = AmplitudeNoize*std::rand()/RAND_MAX - AmplitudeNoize/2;
        Noize.second = AmplitudeNoize*std::rand()/RAND_MAX - AmplitudeNoize/2;
    }
	else
    {
        Noize.first = 0; Noize.second =0;
    }

	emit SignalNewDataAvailable();

}

void SinusGeneratorClass::SlotStartGenerate(bool StartStop)
{
	if (StartStop) this->TimerGenerateSinus.start(2);
	else this->TimerGenerateSinus.stop();
}
