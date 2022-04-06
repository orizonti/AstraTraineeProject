#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#define ERROR_GRAPH_X 0
#define ERROR_GRAPH_Y 1

#define CALMAN_ERROR_X 2 
#define CALMAN_ERROR_Y 3 

#define CALMAN_VELOCITY_X 4 
#define CALMAN_VELOCITY_Y 5 

#define PID_ACCELERATION_X 6
#define PID_ACCELERATION_Y 7

#define ERROR_SKO_X 8
#define ERROR_SKO_Y 9


#include "ui_graphicswindow.h"
#include "DataAimingErrorStructure.h"
#include "qcustomplot.h"


class DispersionCalc
{
public:
	QQueue<QPair<double, double>> MeasureMassive;

	QQueue<QPair<double, double>> DispValueMassive;


	int Size = 40;
	QPair<double, double> Avarage;
	QPair<double, double> SKO;
	QPair<double, double> SquareDeviant;


	friend void operator>>(QPair<double, double> NewValue, DispersionCalc& StatObj)
	{
		StatObj.MeasureMassive.enqueue(NewValue);

//		StatObj.Avarage.first += NewValue.first/StatObj.Size;
//		StatObj.Avarage.second += NewValue.second/StatObj.Size;


		if (StatObj.MeasureMassive.size() > StatObj.Size)
		{
		//	QPair<double,double> FirstValue =  StatObj.MeasureMassive.dequeue();
			StatObj.MeasureMassive.dequeue();
			
		//StatObj.Avarage.first -= FirstValue.first/StatObj.Size;
		//StatObj.Avarage.second -= FirstValue.second/StatObj.Size;
		//StatObj.SquareDeviant.first = pow(NewValue.first - StatObj.Avarage.first, 2);
		//StatObj.SquareDeviant.second = pow(NewValue.second - StatObj.Avarage.second, 2);
		//StatObj.DispValueMassive.enqueue(StatObj.SquareDeviant);
		StatObj.CalcAvarage();
		StatObj.CalcSKO();
		}

//		if(StatObj.DispValueMassive.size() >= StatObj.Size)
//		StatObj.DispValueMassive.dequeue();


	};



	QPair<double, double> GetAvarage();
	QPair<double, double> GetDispersion();

	QPair<double, double> Summ;

	void CalcAvarage()
	{
		Summ = QPair<double, double>(0, 0);
		for(QPair<double,double> value:MeasureMassive)
		{
		Summ.first += value.first;
		Summ.second += value.second;
		}

		Avarage.first = Summ.first / MeasureMassive.size();
		Avarage.second = Summ.second / MeasureMassive.size();
	}

	void CalcSKO()
	{
		
		SKO = QPair<double, double>(0, 0);

		for(QPair<double,double> value:MeasureMassive)
		{
			SKO.first += pow((value.first - Avarage.first), 2);
			SKO.second += pow((value.second - Avarage.second), 2);
		}


		SKO.first = sqrt(SKO.first/MeasureMassive.size());
		SKO.second = sqrt(SKO.second/MeasureMassive.size());
	}

};
class SmootheNodeClass
{
public:
	QQueue<QPair<double, double>> MeasureMassive;

	int Size = 10;
	QPair<double, double> Avarage;

		QPair<double, double> GetAvarage()
		{
			return Avarage;
		};

	friend void operator>>(QPair<double, double> NewValue, SmootheNodeClass& StatObj)
	{
		StatObj.MeasureMassive.enqueue(NewValue);

		StatObj.Avarage.first += NewValue.first/StatObj.Size;
		StatObj.Avarage.second += NewValue.second/StatObj.Size;


		if (StatObj.MeasureMassive.size() > StatObj.Size)
		{
			QPair<double,double> FirstValue =  StatObj.MeasureMassive.dequeue();
			
		StatObj.Avarage.first -= FirstValue.first/StatObj.Size;
		StatObj.Avarage.second -= FirstValue.second/StatObj.Size;
		}
	};

};

class GraphicsInterface : public QObject
{
	Q_OBJECT
public:
	GraphicsInterface(QCustomPlot* Graphics);
	~GraphicsInterface();

	friend void operator>>(DataAimingErrorStructure Data, GraphicsInterface& Display);

	QCustomPlot* GraphicsDisplay;
	void AdjustGraph();

	QTime TimeMeasurePeriod;
	double TimeFromStartMs;

	double TimePeriod;
	double key;

	bool DisplayError = true;
	bool DisplayKalman = false;
	bool DisplaySKO = false;
	bool DisplayPID = false;
	bool DisplayXAxes = true;
	bool DisplayYAxes = true;

	int FreqFilterCounter = 0;

	QPair<int, int> RangeY;
	SmootheNodeClass SmootheNode;
	DispersionCalc Dispersion;

	public slots:
	void DisplayGraph(DataAimingErrorStructure& Data);


};


class GraphicsWindow : public QWidget
{
	Q_OBJECT

public:
	GraphicsWindow(QWidget *parent = 0);
	~GraphicsWindow();


public slots:
	void DisplayAimingData(DataAimingErrorStructure Data);
	void ChangeDataLimit(int Channel, int DataLimitup, int DataLimitDown);

	signals:
	void SignalNewData(DataAimingErrorStructure Data);

private:
	Ui::GraphicsWindow ui;

	GraphicsInterface* Graph1;
	GraphicsInterface* Graph2;
	GraphicsInterface* Graph3;


};

#endif // GRAPHICSWINDOW_H
