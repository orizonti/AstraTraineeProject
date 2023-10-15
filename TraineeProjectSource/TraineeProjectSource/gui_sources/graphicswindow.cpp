#include "stdafx.h"
#include "graphicswindow.h"


GraphicsInterface::GraphicsInterface(QCustomPlot* Graphics)
{
	GraphicsDisplay = Graphics;
	this->AdjustGraph();
	this->TimeFromStartMs = 0;
}

void GraphicsInterface::AdjustGraph()
{
    QPen pen(QColor(74, 148, 0)); pen.setWidth(5);
	
    GraphicsDisplay->addGraph(); // blue line
    GraphicsDisplay->graph(ERROR_GRAPH_X)->setPen(QPen(Qt::blue));
    GraphicsDisplay->graph(ERROR_GRAPH_X)->setBrush(QBrush(QColor(0, 170, 255,80)));
    //GraphicsDisplay->graph(ERROR_GRAPH_X)->setAntialiasedFill(false);

    GraphicsDisplay->addGraph(); // red line
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setPen(QPen(Qt::red));
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setBrush(QBrush(QColor(214, 71, 0,80)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setPen(QPen(Qt::black,2));
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setBrush(QBrush(QColor(110, 210, 210,100)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setPen(QPen(Qt::black,2));
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setBrush(QBrush(QColor(110, 255, 200,100)));


    GraphicsDisplay->graph(ERROR_GRAPH_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setChannelFillGraph(0);

	GraphicsDisplay->xAxis->setTickLength(1);
	GraphicsDisplay->xAxis->ticker()->setTickCount(10);
    GraphicsDisplay->axisRect()->setupFullAxesBox();

    GraphicsDisplay->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}


GraphicsWindow::GraphicsWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);       
	QBrush brh(QColor(170, 170, 170));
	
	ui.graphWidget1->setStyleSheet("QWidget{ border: 2px solid line black }");
	ui.graphWidget1->setBackground(brh);

	ui.graphWidget2->setStyleSheet("QWidget{ border: 2px solid line black }");
	ui.graphWidget2->setBackground(brh);

	ui.graphWidget3->setStyleSheet("QWidget{ border: 2px solid line black }");
	ui.graphWidget3->setBackground(brh);

	Graph1 = new GraphicsInterface(ui.graphWidget1);
	Graph2 = new GraphicsInterface(ui.graphWidget2);
	Graph3 = new GraphicsInterface(ui.graphWidget3);


	QVector<QDoubleSpinBox*> linesLimit;
	linesLimit.append(ui.spinEditMaxValUp1);
	linesLimit.append(ui.spinEditMinValDown1);
	linesLimit.append(ui.spinEditMaxValUp2);
	linesLimit.append(ui.spinEditMinValDown2);
	linesLimit.append(ui.spinEditMaxValUp3);
	linesLimit.append(ui.spinEditMinValDown3);

	int number = 0;
	QDoubleSpinBox* Line;
	QDoubleSpinBox* Line2;
	for (int c = 0; c <= 2; c++)
	{
		   
			Line = linesLimit.at(c*2);
			Line2 = linesLimit.at(c*2+1);
						 QObject::connect(Line, &QDoubleSpinBox::textChanged, [this,Line,Line2,c]()
						 {
						 ChangeDataLimit(c + 1, Line->value(), Line2->value());
						 });
						 QObject::connect(Line2, &QDoubleSpinBox::textChanged, [this,Line,Line2,c]()
						 {
						 ChangeDataLimit(c + 1, Line->value(), Line2->value());
						 });

	}

	QVector<QCheckBox*> checkBoxMassive;

	checkBoxMassive.append(ui.checkShowError1);
	checkBoxMassive.append(ui.checkShowKalman1);

	checkBoxMassive.append(ui.checkShowError2);
	checkBoxMassive.append(ui.checkShowKalman2);

	checkBoxMassive.append(ui.checkShowError3);
	checkBoxMassive.append(ui.checkShowKalman3);


	QVector<GraphicsInterface*> DisplayGraphics;
	DisplayGraphics.append(this->Graph1);
	DisplayGraphics.append(this->Graph2);
	DisplayGraphics.append(this->Graph3);

	GraphicsInterface* Display;
    auto CurrentDisplay =DisplayGraphics.begin();
	int NumberChannel = 0;

	for(auto checkBox: checkBoxMassive)
    {

	    NumberChannel++; Display = *CurrentDisplay;
        QObject::connect(checkBox, &QCheckBox::stateChanged, [NumberChannel,Display,checkBox]()
        {
            if (NumberChannel == 1) {Display->DisplayError = checkBox->isChecked();};
            if (NumberChannel == 2) {Display->DisplayKalman = checkBox->isChecked();};

        });
        if(NumberChannel == 2) {NumberChannel = 0; CurrentDisplay++;};
    }



    QVector<QCheckBox*> checkBoxesShowAxes;
    checkBoxesShowAxes.append(ui.checkXShow1);
    checkBoxesShowAxes.append(ui.checkYShow1);
    checkBoxesShowAxes.append(ui.checkXShow2);
	checkBoxesShowAxes.append(ui.checkYShow2);
	checkBoxesShowAxes.append(ui.checkXShow3);
	checkBoxesShowAxes.append(ui.checkYShow3);


	for (int n = 1; n <= 3; n++)
	{
		Display = DisplayGraphics.at(n - 1);
		for (int n_ax = 0; n_ax < 2; n_ax++)
		{
			QCheckBox* checkBox = checkBoxesShowAxes.at((n-1)*2 + n_ax);
			QObject::connect(checkBox, &QCheckBox::stateChanged, [n_ax, Display, checkBox]()
			{
					if (n_ax == 0)
						Display->DisplayXAxes = checkBox->isChecked();
					if (n_ax == 1)
						Display->DisplayYAxes = checkBox->isChecked();


			});

		}
	}

			QVector<QPushButton*> Buttons;
			Buttons.append(ui.ButGraphChannel1);
			Buttons.append(ui.ButGraphChannel2);
			Buttons.append(ui.ButGraphChannel3);
			
	        for(int n = 1; n <= 3; n++)
	        {

				QPushButton* But = Buttons.at(n - 1);
			QObject::connect(But, &QPushButton::toggled, [n,this,But]()
			{
				if(But->isChecked())
				this->ui.stackedWidget->setCurrentIndex(n-1);

			});

	        }

}

GraphicsInterface::~GraphicsInterface()
{
	this->GraphicsDisplay->clearGraphs();
}
GraphicsWindow::~GraphicsWindow()
{


	delete Graph1;
	delete Graph2;
	delete Graph3;

}

void GraphicsWindow::DisplayAimingData(DataAimingErrorStructure Data)
{
	if (ui.ButStopGraph->isChecked())
		return;
	
	if (Data.NumberBlock == 1 && Data.State == BlockAtWork)
		Data >> *Graph1;
	if (Data.NumberBlock == 2 && Data.State == BlockAtWork)
		Data >> *Graph2;
	if (Data.NumberBlock == 3 && Data.State == BlockAtWork)
		Data >> *Graph3;


}

void GraphicsWindow::ChangeDataLimit(int Channel, double DataLimitup, double DataLimitDown)
{

	if (Channel == 1)
		Graph1->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
	if (Channel == 2)
		Graph2->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
	if (Channel == 3)
		Graph3->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
}


void operator>>(DataAimingErrorStructure Data, GraphicsInterface& Display)
{
	Display.DisplayGraph(Data);
}

void GraphicsInterface::DisplayGraph(DataAimingErrorStructure& Data)
{
	
	TimePeriod = TimeMeasurePeriod.restart();
	TimeFromStartMs += TimePeriod;
	PlotPeriod += TimePeriod;
    key = TimeFromStartMs/1000;   //convert milliseconds to seconds

	Data.LastError >> SmootheError;
    Data.OutputKalman.CoordEstimate >> SmootheKalman;



	if (DisplayError)
	{
	GraphicsDisplay->graph(ERROR_GRAPH_X)->setVisible(true);
	GraphicsDisplay->graph(ERROR_GRAPH_Y)->setVisible(true);

	}
	else
	{
	GraphicsDisplay->graph(ERROR_GRAPH_X)->setVisible(false);
	GraphicsDisplay->graph(ERROR_GRAPH_Y)->setVisible(false);
	}

    if (DisplayKalman)
    {
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setVisible(true);
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setVisible(true);
    }
    else
    {
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setVisible(false);
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setVisible(false);
    }


        if (!DisplayXAxes)
        {
            GraphicsDisplay->graph(ERROR_GRAPH_X)->setVisible(false);
            GraphicsDisplay->graph(CALMAN_ERROR_X)->setVisible(false);
        }

        if (!DisplayYAxes)
        {
            GraphicsDisplay->graph(ERROR_GRAPH_Y)->setVisible(false);
            GraphicsDisplay->graph(CALMAN_ERROR_Y)->setVisible(false);
        }

//=====================================================================================

    //GraphicsDisplay->graph(ERROR_GRAPH_X)->addData(key, Data.LastError.first);
    //GraphicsDisplay->graph(ERROR_GRAPH_Y)->addData(key, Data.LastError.second);
    double Tp = 0.002;
    double new_key = key;
    for(auto CurrentError = Data.BeginError; CurrentError != Data.EndError; CurrentError++)
    {
      GraphicsDisplay->graph(ERROR_GRAPH_X)->addData(new_key, CurrentError->first);
      GraphicsDisplay->graph(ERROR_GRAPH_Y)->addData(new_key, CurrentError->second);
      new_key += Tp;
    }


//	GraphicsDisplay->graph(ERROR_GRAPH_X)->rescaleValueAxis(true);
//	GraphicsDisplay->graph(ERROR_GRAPH_Y)->rescaleValueAxis(true);
//
//////=====================================================================================
//	GraphicsDisplay->graph(CALMAN_ERROR_X)->addData(key, Data.OutputKalman.CoordEstimate.first);
//	GraphicsDisplay->graph(CALMAN_ERROR_Y)->addData(key, Data.OutputKalman.CoordEstimate.second);
//
//	GraphicsDisplay->graph(CALMAN_ERROR_X)->rescaleValueAxis(true);
//	GraphicsDisplay->graph(CALMAN_ERROR_Y)->rescaleValueAxis(true);

    //if(RangeY.second < SmootheError.MAX_VALUE)
    //{
    //    RangeY.second = SmootheError.MAX_VALUE;
    //    RangeY.first = -SmootheError.MAX_VALUE;
    //    GraphicsDisplay->yAxis->setRange(RangeY.first,RangeY.second);
    //};

	// make key axis range scroll with the data (at a constant range size of 8):
    if(PlotPeriod >= 30)
    {
        GraphicsDisplay->xAxis->setRange(key, 5, Qt::AlignRight);
        GraphicsDisplay->replot();
        PlotPeriod = 0;
    }


}
