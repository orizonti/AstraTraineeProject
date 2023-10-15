
#include "stdafx.h"
#include "camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

CameraWindow::~CameraWindow()
{

}

void CameraWindow::DisplayState(stateblocksenum State)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);

		
	ui.checkWorkBlock->blockSignals(false);
}

void CameraWindow::ConnectControlSignals(HandleControlInterface* Control)
{

			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				if (ui.checkWorkBlock->isChecked())
				{
					Control->SetBlockState(CamerasControlBlock,0,BlockAtWork);
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Пуск"));
				}
				else
				{
					Control->SetBlockState(CamerasControlBlock,0,BlockDisable);
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Стоп"));
				}
			});


}

void CameraWindow::DisplayCameraData(DataCamerasStructure Data)
{
	FramePeriodMeasure.push_back(Data.FramePeriodFULL);
	FrameROIPeriodMeasure.push_back(Data.FramePeriodROI);


    double avarage_frame_full, avarage_frame_roi;
	if(FrameROIPeriodMeasure.size() >= 10)
    {
     avarage_frame_full = double(std::accumulate(FramePeriodMeasure.begin(), FramePeriodMeasure.end(),0))/FramePeriodMeasure.size();
     avarage_frame_roi = double(std::accumulate(FrameROIPeriodMeasure.begin(), FrameROIPeriodMeasure.end(),0))/FramePeriodMeasure.size();
    }

	ui.labelFrameRate->setText(QString::fromUtf8("Период - %1 мс").arg(avarage_frame_full,5,'g',2));
	ui.labelFrameRateROI->setText(QString::fromUtf8("Период строб - %1 мс").arg(avarage_frame_roi,5,'g',2));

	if (avarage_frame_roi > 5)
		ui.label_2->setStyleSheet("QLabel {border: 2px solid line black; background-color: rgb(208, 0, 0);}");
	else
		ui.label_2->setStyleSheet("QLabel {border: 2px solid line black; background-color: rgb(255, 170, 0);}");

	if (FramePeriodMeasure.size() > 100)
	{
		FramePeriodMeasure.pop_front();
		FrameROIPeriodMeasure.pop_front();
	}
}
