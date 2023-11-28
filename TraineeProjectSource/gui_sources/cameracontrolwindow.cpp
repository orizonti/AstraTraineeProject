#include "CommonHeaders.h"
#include "cameracontrolwindow.h"
#define TAG "[ CAM  WINDOW ]" 

CameraControlWindow::CameraControlWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}


CameraControlWindow::~CameraControlWindow()
{

}

void CameraControlWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	connect(ui.ButSetParamToDevice, &QPushButton::clicked,
		[this, Control]()
	{


    quint8 Command = 0;

    quint32 WidthImage = 0;
    quint32 HeightImage =0;



    if(this->ui.ButAutoExpose->isChecked())
        Command |= COMM_AUTOEXPOSE_ON;


        WidthImage = 2048;
        HeightImage = 512;

		Control_Camera_Command CameraCommand;
        CameraCommand.SetSizeImage(WidthImage,HeightImage);
		CameraCommand.TimeExposure = ui.SpinExposeTimeMs->text().toInt();
		CameraCommand.AvarageBackground = ui.SpinAvarageBackground->text().toInt();

		if (ui.ButAutoExpose->isChecked())
			CameraCommand.SetCommand(Command);

		Control->SetCameraParam(CameraCommand);
	});


	connect(ui.ButSetROI, &QPushButton::clicked, 
	[this,Control]()
	{   
	ROI_Channels_Command ROI_Command;
	ROI_Command.W1 = ui.SpinWidth1->value();
	ROI_Command.W2 = ui.SpinWidth2->value();
	ROI_Command.W3 = ui.SpinWidth3->value();
	ROI_Command.W4 = ui.SpinWidth4->value();

	ROI_Command.Y1 = ui.SpinY1->value();
	ROI_Command.Y2 = ui.SpinY1->value();
	ROI_Command.Y3 = ui.SpinY1->value();
	ROI_Command.Y4 = ui.SpinY1->value();

	ROI_Command.X1 = ui.SpinX1->value();
	ROI_Command.X2 = ui.SpinX2->value();
	ROI_Command.X3 = ui.SpinX3->value();
	ROI_Command.X4 = ui.SpinX4->value();

	qInfo() << TAG << "GET ROI IN LAMBDA";
	Control->SetCameraROI(ROI_Command);
	});
}



