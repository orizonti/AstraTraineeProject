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
    GraphicsDisplay->graph(ERROR_GRAPH_X)->setAntialiasedFill(false);

    GraphicsDisplay->addGraph(); // red line
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setPen(QPen(Qt::red));
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setBrush(QBrush(QColor(214, 71, 0,80)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setPen(QPen(Qt::black));
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setBrush(QBrush(QColor(210, 210, 210,140)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setPen(QPen(Qt::black));
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setBrush(QBrush(QColor(240, 255, 200,140)));


    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setPen(QPen(Qt::blue));
    GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setBrush(QBrush(QColor(0, 170, 255,80)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setPen(QPen(Qt::red));
    GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setBrush(QBrush(QColor(214, 71, 0,80)));

	
    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(PID_ACCELERATION_X)->setPen(QPen(Qt::green));
    GraphicsDisplay->graph(PID_ACCELERATION_X)->setBrush(QBrush(QColor(0, 200, 0,80)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(PID_ACCELERATION_Y)->setPen(QPen(Qt::black));
    GraphicsDisplay->graph(PID_ACCELERATION_Y)->setBrush(QBrush(QColor(100, 100, 100,80)));


    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(ERROR_SKO_X)->setPen(QPen(Qt::black));
    GraphicsDisplay->graph(ERROR_SKO_X)->setBrush(QBrush(QColor(100, 100, 100,80)));

    GraphicsDisplay->addGraph();
    GraphicsDisplay->graph(ERROR_SKO_Y)->setPen(QPen(Qt::green));
    GraphicsDisplay->graph(ERROR_SKO_Y)->setBrush(QBrush(QColor(0, 200, 0,80)));


    GraphicsDisplay->graph(ERROR_GRAPH_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(ERROR_GRAPH_Y)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_ERROR_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_ERROR_Y)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setChannelFillGraph(0);
    GraphicsDisplay->graph(PID_ACCELERATION_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(PID_ACCELERATION_Y)->setChannelFillGraph(0);

    GraphicsDisplay->graph(ERROR_SKO_X)->setChannelFillGraph(0);
    GraphicsDisplay->graph(ERROR_SKO_Y)->setChannelFillGraph(0);

				//    Graph->addGraph(); // blue dot
				//    Graph->graph(3)->setPen(QPen(Qt::blue));
				//    Graph->graph(3)->setLineStyle(QCPGraph::lsNone);
				//    Graph->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
				//    Graph->addGraph(); // red dot
				//    Graph->graph(4)->setPen(QPen(Qt::red));
				//    Graph->graph(4)->setLineStyle(QCPGraph::lsNone);
				//    Graph->graph(4)->setScatterStyle(QCPScatterStyle::ssDisc);

				//    Graph->addGraph();
				//    Graph->graph(5)->setPen(QPen(Qt::green));
				//    Graph->graph(5)->setLineStyle(QCPGraph::lsNone);
				//    Graph->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

																	//    Graph->graph(7)->setLineStyle(QCPGraph::lsNone);
																	//    Graph->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);


    //GraphicsDisplay->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    
    //GraphicsDisplay->xAxis->setAutoTickStep(false);
	GraphicsDisplay->xAxis->setTickLength(1);
	GraphicsDisplay->xAxis->ticker()->setTickCount(10);
    GraphicsDisplay->axisRect()->setupFullAxesBox();

 /*   connect(GraphicsDisplay->xAxis, SIGNAL(rangeChanged(QCPRange)), GraphicsDisplay->xAxis2, SLOT(setRange(QCPRange)));
    connect(GraphicsDisplay->yAxis, SIGNAL(rangeChanged(QCPRange)), GraphicsDisplay->yAxis2, SLOT(setRange(QCPRange)));*/
    GraphicsDisplay->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}


GraphicsWindow::GraphicsWindow(QWidget *parent)
	: QWidget(parent)
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


	QVector<QLineEdit*> linesLimit;
	linesLimit.append(ui.lineEditMaxValUp1);
	linesLimit.append(ui.lineEditMaxValDown1);
	linesLimit.append(ui.lineEditMaxValUp2);
	linesLimit.append(ui.lineEditMaxValDown2);
	linesLimit.append(ui.lineEditMaxValUp3);
	linesLimit.append(ui.lineEditMaxValDown3);

	int number = 0;
	QLineEdit* Line;
	QLineEdit* Line2;
	for (int c = 0; c <= 2; c++)
	{
		   
			Line = linesLimit.at(c*2);
			Line2 = linesLimit.at(c*2+1);
						 QObject::connect(Line, &QLineEdit::textChanged, [this,Line,Line2,c]()
						 {
						 ChangeDataLimit(c + 1, Line->text().toInt(), Line2->text().toInt());
						 });
						 QObject::connect(Line2, &QLineEdit::textChanged, [this,Line,Line2,c]()
						 {
						 ChangeDataLimit(c + 1, Line->text().toInt(), Line2->text().toInt());
						 });

	}

	QVector<QCheckBox*> checkBoxMassive;

	checkBoxMassive.append(ui.checkShowError1);
	checkBoxMassive.append(ui.checkShowKalman1);
	checkBoxMassive.append(ui.checkShowPID1);

	checkBoxMassive.append(ui.checkShowError2);
	checkBoxMassive.append(ui.checkShowKalman2);
	checkBoxMassive.append(ui.checkShowPID2);

	checkBoxMassive.append(ui.checkShowError3);
	checkBoxMassive.append(ui.checkShowKalman3);
	checkBoxMassive.append(ui.checkShowPID3);


	QVector<GraphicsInterface*> DisplayGraphics;
	DisplayGraphics.append(this->Graph1);
	DisplayGraphics.append(this->Graph2);
	DisplayGraphics.append(this->Graph3);

	GraphicsInterface* Display;
	int NumberChannel = 0;
	int NumberDataChannel = 0;
	for (int n = 0; n < 9; n++)
	{

	if (n % 3 == 0)
	{
			NumberChannel++;

	}
	NumberDataChannel = n+1 - 3*(NumberChannel-1);

	Display = DisplayGraphics.at(NumberChannel-1);
	QCheckBox* checkBox = checkBoxMassive.at(n);
	QObject::connect(checkBox, &QCheckBox::stateChanged, [NumberDataChannel,Display,checkBox]()
	                                                     {
																	if (NumberDataChannel == 1)
																	Display->DisplayError = checkBox->isChecked();
																	if (NumberDataChannel == 2)
																	Display->DisplayKalman = checkBox->isChecked();
																	if (NumberDataChannel == 3)
																	Display->DisplayPID = checkBox->isChecked();
		                                                    
	                                                     }
	);
	}
	
	//QVector<QCheckBox*> checkBoxMassiveSKOBut;
	//checkBoxMassiveSKOBut.append(ui.checkShowErrorSKO1);
	//checkBoxMassiveSKOBut.append(ui.checkShowErrorSKO2);
	//checkBoxMassiveSKOBut.append(ui.checkShowErrorSKO3);

	QCheckBox* checkBox = ui.checkShowErrorSKO1;

	GraphicsInterface* Display1= DisplayGraphics.at(0);
	GraphicsInterface* Display2= DisplayGraphics.at(1);
	GraphicsInterface* Display3= DisplayGraphics.at(2);

	QObject::connect(checkBox, &QCheckBox::stateChanged, [NumberDataChannel,Display1,Display2,Display3,checkBox]()
	                                                     {
																	Display1->DisplaySKO = checkBox->isChecked();
																	Display2->DisplaySKO = checkBox->isChecked();
																	Display3->DisplaySKO = checkBox->isChecked();
		                                                    
	                                                     }
	);


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
			
//	        for(int n = 1; n <= 3; n++)
//	        {

//				QPushButton* But = Buttons.at(n - 1);
//			QObject::connect(But, &QPushButton::toggled, [n,this,Buttons]()
//			{
//				if(Buttons.takeAt(n-1)->isChecked())
//				ui.stackedWidget->setCurrentIndex(n);

//			});

//	        }

}

GraphicsInterface::~GraphicsInterface()
{
	qDebug() << "Delete graphics interface";
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

void GraphicsWindow::ChangeDataLimit(int Channel, int DataLimitup, int DataLimitDown)
{

	if (Channel == 1)
		Graph1->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
//	if (Channel == 2)
//		Graph2->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
//	if (Channel == 3)
//		Graph3->RangeY = QPair<double, double>(DataLimitup, DataLimitDown);
}


void operator>>(DataAimingErrorStructure Data, GraphicsInterface& Display)
{
	Display.DisplayGraph(Data);
}

void GraphicsInterface::DisplayGraph(DataAimingErrorStructure& Data)
{
	
	TimePeriod = TimeMeasurePeriod.restart();
	TimeFromStartMs += TimePeriod;
    key = TimeFromStartMs/1000;   //convert milliseconds to seconds
	QTime time; 
	time.start();
	
//	FreqFilterCounter++;
//	if (FreqFilterCounter > 10)
//		FreqFilterCounter = 0;
//	else
//		return;false

	Data.LastError >> SmootheNode;
//	Data.LastError >> Dispersion;
	SmootheNode.GetAvarage() >> Dispersion;

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

		GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setVisible(true);
		GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setVisible(true);

		}
		else
		{
		GraphicsDisplay->graph(CALMAN_ERROR_X)->setVisible(false);
		GraphicsDisplay->graph(CALMAN_ERROR_Y)->setVisible(false);

		GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setVisible(false);
		GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setVisible(false);
		}

			if (DisplayPID)
			{
			GraphicsDisplay->graph(PID_ACCELERATION_X)->setVisible(true);
			GraphicsDisplay->graph(PID_ACCELERATION_Y)->setVisible(true);

			}
			else
			{
			GraphicsDisplay->graph(PID_ACCELERATION_X)->setVisible(false);
			GraphicsDisplay->graph(PID_ACCELERATION_Y)->setVisible(false);
			}

			if (DisplaySKO)
			{
			GraphicsDisplay->graph(ERROR_SKO_X)->setVisible(true);
			GraphicsDisplay->graph(ERROR_SKO_Y)->setVisible(true);

			}
			else
			{
			GraphicsDisplay->graph(ERROR_SKO_X)->setVisible(false);
			GraphicsDisplay->graph(ERROR_SKO_Y)->setVisible(false);
			}

										if (!DisplayXAxes)
										{
																GraphicsDisplay->graph(ERROR_GRAPH_X)->setVisible(false);
																GraphicsDisplay->graph(CALMAN_ERROR_X)->setVisible(false);
																GraphicsDisplay->graph(CALMAN_VELOCITY_X)->setVisible(false);
																GraphicsDisplay->graph(PID_ACCELERATION_X)->setVisible(false);
																GraphicsDisplay->graph(ERROR_SKO_X)->setVisible(false);
										}

										if (!DisplayYAxes)
										{
															GraphicsDisplay->graph(ERROR_GRAPH_Y)->setVisible(false);
															GraphicsDisplay->graph(CALMAN_ERROR_Y)->setVisible(false);
															GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->setVisible(false);
															GraphicsDisplay->graph(PID_ACCELERATION_Y)->setVisible(false);
															GraphicsDisplay->graph(ERROR_SKO_Y)->setVisible(false);
										}

//=====================================================================================
//	GraphicsDisplay->graph(ERROR_GRAPH_X)->addData(key, Data.LastError.first);  // If data not smooth that bring bring time laps at paint graph 5-10ms
//	GraphicsDisplay->graph(ERROR_GRAPH_Y)->addData(key, Data.LastError.second);

	GraphicsDisplay->graph(ERROR_GRAPH_X)->addData(key, SmootheNode.GetAvarage().first);
	GraphicsDisplay->graph(ERROR_GRAPH_Y)->addData(key, SmootheNode.GetAvarage().second);
	
	GraphicsDisplay->graph(ERROR_SKO_X)->addData(key, Dispersion.SKO.first);
	GraphicsDisplay->graph(ERROR_SKO_Y)->addData(key, Dispersion.SKO.second);


//	// rescale value (vertical) axis to fit the current data:
	GraphicsDisplay->graph(ERROR_GRAPH_X)->rescaleValueAxis(true);
	GraphicsDisplay->graph(ERROR_GRAPH_Y)->rescaleValueAxis(true);

	GraphicsDisplay->graph(ERROR_SKO_X)->rescaleValueAxis(true);
	GraphicsDisplay->graph(ERROR_SKO_Y)->rescaleValueAxis(true);
////=====================================================================================

//	
////=====================================================================================
	GraphicsDisplay->graph(CALMAN_ERROR_X)->addData(key, Data.OutputKalman.CoordEstimate.first);
	GraphicsDisplay->graph(CALMAN_ERROR_Y)->addData(key, Data.OutputKalman.CoordEstimate.second);

	GraphicsDisplay->graph(CALMAN_ERROR_X)->rescaleValueAxis(true);
	GraphicsDisplay->graph(CALMAN_ERROR_Y)->rescaleValueAxis(true);




//	GraphicsDisplay->graph(CALMAN_VELOCITY_X)->addData(key, Data.OutputKalman.VelocityEstimate.first);
//	GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->addData(key, Data.OutputKalman.VelocityEstimate.second);

//	GraphicsDisplay->graph(CALMAN_VELOCITY_X)->rescaleValueAxis(true);
//	GraphicsDisplay->graph(CALMAN_VELOCITY_Y)->rescaleValueAxis(true);
////=====================================================================================


////=====================================================================================
//	//GraphicsDisplay->graph(PID_ACCELERATION_X)->addData(key, PIDAcceleration.first*24.4*1000);
//	//GraphicsDisplay->graph(PID_ACCELERATION_Y)->addData(key, PIDAcceleration.second*24.4*1000);

//	GraphicsDisplay->graph(PID_ACCELERATION_X)->addData(key, Data.OutputPID.first);
//	GraphicsDisplay->graph(PID_ACCELERATION_Y)->addData(key, Data.OutputPID.second);


///*			GraphicsDisplay->graph(PID_ACCELERATION_X)->removeDataBefore(key - 10);
//			GraphicsDisplay->graph(PID_ACCELERATION_Y)->removeDataBefore(key - 10)*/;

//	GraphicsDisplay->graph(PID_ACCELERATION_X)->rescaleValueAxis(true);
//	GraphicsDisplay->graph(PID_ACCELERATION_Y)->rescaleValueAxis(true);
////=====================================================================================








	// make key axis range scroll with the data (at a constant range size of 8):
	GraphicsDisplay->xAxis->setRange(key, 5, Qt::AlignRight);
	GraphicsDisplay->yAxis->setRange(RangeY.first,RangeY.second);
	GraphicsDisplay->replot();
	int time_ms = time.elapsed();

	if(time_ms > 4)
	qDebug() << "Graph time - " << time_ms << "!!!!";

}
