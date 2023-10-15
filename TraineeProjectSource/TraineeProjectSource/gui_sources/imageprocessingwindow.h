#ifndef IMAGEPROCESSINGWINDOW_H
#define IMAGEPROCESSINGWINDOW_H

#include "ui_imageprocessingwindow.h"
#include "HandleControlInterface.h"
#include "AdjustableWidget.h"

class ImageProcessingWindow : public AdjustableWidget
{
	Q_OBJECT

public:
	ImageProcessingWindow(QWidget *parent = 0);
	~ImageProcessingWindow();

	void DisplayState(stateblocksenum State,int NumberChannel);
	void ConnectControlSignals(HandleControlInterface* Control);
	void DisplayProcessingData(DataImageProcAllChannels Data);

	std::deque<double> FramePeriodReceive;
	std::deque<double> FramePeriodProcess;
private:
	Ui::ImageProcessingWindow ui;
};

#endif // IMAGEPROCESSINGWINDOW_H
