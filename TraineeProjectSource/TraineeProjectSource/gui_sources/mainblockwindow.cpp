
#include "stdafx.h"
#include "mainblockwindow.h"

MainBlockWindow::MainBlockWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

MainBlockWindow::~MainBlockWindow()
{
qDebug() << "DELETE MAIN BLOCK WINDOW";
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
		Control->SlotStartMoveByCircle(true);
		else
		Control->SlotStartMoveByCircle(false);
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

	connect(ui.butRotateCalibration, &QPushButton::clicked, Control, &HandleControlInterface::StartSystemRotationCalibration,Qt::QueuedConnection);

	connect(this, SIGNAL(SignalResetBlocks(bool)), Control, SLOT(SlotStartStopWork(bool)));

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
		Control->SetPowerSupplyOnCommutator(true);
		else
		Control->SetPowerSupplyOnCommutator(false);
	});
}
