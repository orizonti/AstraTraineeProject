#ifndef IMAGEPROCESSINGDISPLAYWINDOW_H
#define IMAGEPROCESSINGDISPLAYWINDOW_H

#include "ui_imageprocessingdisplaywindow.h"
#include "HandleControlInterface.h"

class ImageProcessingDisplayWindow : public QWidget
{
	Q_OBJECT

public:
	ImageProcessingDisplayWindow(QWidget *parent = 0);
	~ImageProcessingDisplayWindow();
	int DisplayFilterCounter = 0;

	QVector<LabelImage*> Labels;
	void DisplayImage(QImage Image, int NumberChannel);
	void DisplayThreshold(int Threshold, int NumberChannel);
	void ConnectControlSignals(HandleControlInterface* Control);

	public slots:
	void DisplayROIPos(QVector<QPair<double, double> > Coords,QVector<QPair<double, double> > CoordsROI);
signals:
	void SignalDisplayROIPos(QVector<QPair<double, double> > Coords,QVector<QPair<double, double> > CoordsROI);
private:
	
	Ui::ImageProcessingDisplayWindow ui;
};

#endif // IMAGEPROCESSINGDISPLAYWINDOW_H
