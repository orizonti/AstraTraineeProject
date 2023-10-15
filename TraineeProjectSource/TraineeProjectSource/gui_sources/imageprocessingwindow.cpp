
#include "stdafx.h"
#include "imageprocessingwindow.h"

ImageProcessingWindow::ImageProcessingWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

ImageProcessingWindow::~ImageProcessingWindow()
{

}

void ImageProcessingWindow::DisplayState(stateblocksenum State,int NumberChannel)
{
	QCheckBox* Check = 0;
	switch (NumberChannel)
	{
	case 1:
		Check = ui.checkWorkBlock1;
		break;
	case 2:
		Check = ui.checkWorkBlock2;
		break;
	case 3:
		Check = ui.checkWorkBlock3;
		break;
	case 4:
		Check = ui.checkWorkBlock4;
		break;
	}


	if (Check != 0)
	{
	Check->blockSignals(true);
	if (State == BlockDisable)
		Check->setChecked(false);
	if (State == BlockAtWork)
		Check->setChecked(true);
		
	Check->blockSignals(false);
	}
}


void ImageProcessingWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	QVector<QCheckBox*> CheckStateBoxes;
	CheckStateBoxes.append(ui.checkWorkBlock1);
	CheckStateBoxes.append(ui.checkWorkBlock2);
	CheckStateBoxes.append(ui.checkWorkBlock3);
	CheckStateBoxes.append(ui.checkWorkBlock4);
	
	QCheckBox* CheckState = 0;
	for (int n = 1; n <= 4; n++)
	{
		CheckState = CheckStateBoxes.at(n - 1);
	connect(CheckState, &QCheckBox::stateChanged,
		[=]()
	{
		if (CheckState->isChecked())
			Control->SetBlockState(ImageProcBlock, n, BlockAtWork);
		else
			Control->SetBlockState(ImageProcBlock, n, BlockDisable);
	});
	}
}



void ImageProcessingWindow::DisplayProcessingData(DataImageProcAllChannels Data)
{

	FramePeriodReceive.push_back(Data.ReceivePeriod);
	FramePeriodProcess.push_back(Data.ProcessPeriod*1000);

	double avarage_frame_receive = double(std::accumulate(FramePeriodReceive.begin(), FramePeriodReceive.end(),0))/FramePeriodReceive.size();
	double avarage_frame_process = double(std::accumulate(FramePeriodProcess.begin(), FramePeriodProcess.end(),0))/FramePeriodProcess.size();

	ui.labelPeriodReceive->setText(QString::fromLocal8Bit("Прием     - %1 мс").arg(avarage_frame_receive, 4, 'g', 2));
	ui.labelPeriodProcess->setText(QString::fromLocal8Bit("Обработка - %1 мс").arg(avarage_frame_process/1000.0, 4, 'g', 5));

	if (avarage_frame_receive < avarage_frame_process)
		ui.label_2->setStyleSheet("QLabel {border: 2px solid line black; background-color: rgb(208, 0, 0);}");
	else
		ui.label_2->setStyleSheet("QLabel {border: 2px solid line black; background-color: rgb(255, 170, 0);}");

	if (FramePeriodProcess.size() >= 100)
	{
		FramePeriodProcess.pop_front();
		FramePeriodReceive.pop_front();
	}
}
