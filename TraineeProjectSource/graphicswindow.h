#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#define ERROR_GRAPH_X 0
#define ERROR_GRAPH_Y 1

#define CALMAN_ERROR_X 2 
#define CALMAN_ERROR_Y 3 



#include "ui_graphicswindow.h"
#include "DataAimingErrorStructure.h"
#include "qcustomplot.h"


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

    int MAX_VALUE = 0;
    void CHECK_MAX(QPair<double,double> Coord) { if(std::abs(Coord.first) > MAX_VALUE)MAX_VALUE = Coord.first;
                                                 if(std::abs(Coord.second) > MAX_VALUE)MAX_VALUE = Coord.second;}

    friend void operator>>(SmootheNodeClass& Object, QPair<double,double>& Coord)
    {
        Coord = Object.Avarage;
    };

	friend void operator>>(QPair<double, double> NewValue, SmootheNodeClass& StatObj)
	{
		StatObj.MeasureMassive.enqueue(NewValue);

		StatObj.Avarage.first += NewValue.first/StatObj.Size;
		StatObj.Avarage.second += NewValue.second/StatObj.Size;
        StatObj.CHECK_MAX(NewValue);


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

	double TimePeriod= 0;
	double PlotPeriod= 0;
	double key;

	bool DisplayError = true; bool DisplayKalman = false;
	bool DisplaySKO = false;
	bool DisplayPID = false;
	bool DisplayXAxes = true;
	bool DisplayYAxes = true;

	int FreqFilterCounter = 0;

	QPair<int, int> RangeY;
	SmootheNodeClass SmootheError;
    SmootheNodeClass SmootheKalman;

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
	void ChangeDataLimit(int Channel, double DataLimitup, double DataLimitDown);

	signals:
	void SignalNewData(DataAimingErrorStructure Data);

private:
	Ui::GraphicsWindow ui;

	GraphicsInterface* Graph1;
	GraphicsInterface* Graph2;
	GraphicsInterface* Graph3;


};

#endif // GRAPHICSWINDOW_H
