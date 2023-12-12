#include "CommonHeaders.h"
#include "imageprocessingdisplaywindow.h"

ImageProcessingDisplayWindow::ImageProcessingDisplayWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
	Labels.append(ui.ROI_1_Label);
	Labels.append(ui.ROI_2_Label);
	Labels.append(ui.ROI_3_Label);
	Labels.append(ui.ROI_Long_Label);

}

ImageProcessingDisplayWindow::~ImageProcessingDisplayWindow()
{

}

void ImageProcessingDisplayWindow::DisplayImage(QImage Image, int NumberChannel)
{
		Labels.at(NumberChannel-1)->setPixmap(QPixmap::fromImage(Image));
}


void ImageProcessingDisplayWindow::DisplayROIPos(QVector<QPair<double, double> > Coords, QVector<QPair<double, double> > CoordsROI)
{
	QImage LabelImage = QImage(768,192,QImage::Format_RGB888);
	LabelImage.fill(QColor(69, 75, 70));
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(2);
	QPainter paint;
	auto RelativeCoord = Coords;
	for(int n = 0; n < 3; n++)
    {
	   RelativeCoord[n] = RelativeCoord[n] - RelativeCoord[3];
    }

	int n = 1;
	paint.begin(&LabelImage);
	paint.setPen(pen);

	QColor red = QColor(Qt::cyan);
	QColor blue = QColor(Qt::yellow);
	QColor green = QColor(Qt::green);
	QColor red2 = QColor(Qt::red);
	   
	QVector<QColor> Colors; 

	Colors.append(red);
	Colors.append(blue);
	Colors.append(green);
	Colors.append(red2);
	QVector<QColor>::Iterator ItColor = Colors.begin();

	QString CoordText;
	for (QPair<double, double> Coord : RelativeCoord)
	{
	paint.drawEllipse(Coord.first / 4, Coord.second / 4, 5, 5);
	CoordText = QString("x - %1 y - %2").arg(Coord.first,0,'g',4).arg(Coord.second,0,'g',4);
	paint.drawText(5,25*n+40, CoordText);

	pen.setColor(*ItColor);
	ItColor++;
	paint.setPen(pen);
	n++;
	}

	for (QPair<double, double> CoordROI : CoordsROI)
	{
	paint.drawRect(CoordROI.first / 4, CoordROI.second / 4, 256/4, 256/4);
	}
	paint.end();

	ui.label_16->setPixmap(QPixmap::fromImage(LabelImage));
}

void ImageProcessingDisplayWindow::ConnectControlSignals(HandleControlInterface* Control)
{

	for (int n = 1; n <= 4; n++)
	{
		LabelImage* ClickLabel = Labels.at(n - 1);

				connect(ClickLabel, &LabelImage::SignalPressedPos, 
				[=]()          
	            {
					Control->SetAimingCoord(ClickLabel->X_Pressed, ClickLabel->Y_Pressed, n);
				});
	}

	QVector<QSpinBox*> SpinBoxes; 
	SpinBoxes.append(ui.spinThresImage);
	SpinBoxes.append(ui.spinThresImage_2);
	SpinBoxes.append(ui.spinThresImage_3);
	SpinBoxes.append(ui.spinThresImage_4);


			int Number = 1;
			for (auto SpinBox : SpinBoxes)
			{
				connect(SpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), 
				[=](int Value)
				{   
					if(ui.checkBoxThresManual->isChecked())
					Control->SetImageThresHold(Value,Number);

				});
				Number++;
			}

			connect(ui.checkBoxThresManual, static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled), 
			[=](bool OnOff)
			{   
					Control->SetThresholdControlManual(OnOff);
			
			});

			connect(ui.lineEditFilterProcentage, static_cast<void (QLineEdit::*)()>(&QLineEdit::editingFinished),
				[=]()
				{
					Control->SetFrameFilterProcentage(ui.lineEditFilterProcentage->text().toInt());

				});
}

void ImageProcessingDisplayWindow::DisplayThreshold(int Threshold, int NumberChannel)
{
	DisplayFilterCounter++;
	if (!ui.checkBoxThresManual->isChecked() && DisplayFilterCounter > 120 && DisplayFilterCounter <= 124)
	{
	if(NumberChannel == 1)
	ui.spinThresImage->setValue(Threshold);
	if(NumberChannel == 2)
	ui.spinThresImage_2->setValue(Threshold);
	if(NumberChannel == 3)
	ui.spinThresImage_3->setValue(Threshold);
	if(NumberChannel == 4)
	{
	ui.spinThresImage_4->setValue(Threshold);
	DisplayFilterCounter = 0;
	}
	}

}
