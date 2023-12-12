
#include "CommonHeaders.h"
#include "mainblockwindow.h"
#define TAG "[ MAINBLK WIND]" 

MainBlockWindow::MainBlockWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

MainBlockWindow::~MainBlockWindow()
{
qInfo() << TAG << "DELETE MAIN BLOCK WINDOW";
}

void MainBlockWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	connect(ui.ButTurnToWorkMode, &QPushButton::toggled,
		[=]()
	{
		if (ui.ButTurnToWorkMode->isChecked())
		{
              		ui.ButTurnToWorkMode->setText(QString::fromLocal8Bit("Пуск"));
			emit SignalResetBlocks(true);
		}
		else
		{
              		ui.ButTurnToWorkMode->setText(QString::fromLocal8Bit("Стоп"));
			emit SignalResetBlocks(false);
		}
	});

	connect(ui.butStartMoveCircle, &QPushButton::toggled,
		[=]()
	{

		if (ui.butStartMoveCircle->isChecked())
		Control->StartCircleMoving(true);
		else
		Control->StartCircleMoving(false);
	});

	connect(ui.butResetAll, &QPushButton::clicked,
		[=]()
	{
		Control->ResetAll();
	});

	connect(ui.butLoadPreference, &QPushButton::clicked,
		[=]()
	{
		Control->LoadPreference();
	});

	connect(ui.butSaveEnginePos, &QPushButton::clicked,
		[=]()
	{
		Control->SaveEnginePosToFile();
	});

	connect(ui.butRotateCalibration, &QPushButton::clicked, Control, &HandleControlInterface::StartRotationCalibrationProcess,Qt::QueuedConnection);

	connect(this, SIGNAL(SignalResetBlocks(bool)), Control, SLOT(StartStopWork(bool)));

	connect(ui.ButSetAdjustMode, &QPushButton::toggled,
		[=]()
	{

		if (ui.ButSetAdjustMode->isChecked())
		Control->SetAdjustModeWithCrossHair(true);
		else
		Control->SetAdjustModeWithCrossHair(false);
	});

	connect(ui.ButSetPowerSupplyCommutator, &QPushButton::toggled,
		[=]()
	{

		if (ui.ButSetPowerSupplyCommutator->isChecked())
		Control->TurnOnOffPowerCommutator(true);
		else
		Control->TurnOnOffPowerCommutator(false);
	});
}
