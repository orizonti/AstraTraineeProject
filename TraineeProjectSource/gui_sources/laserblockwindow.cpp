
#include "CommonHeaders.h"
#include "laserblockwindow.h"

QString TAG = "[LASER   WIND]"; 
LaserBlockWindow::LaserBlockWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
	 ui.ButTurnToWorkLaser1->setChecked(true);
	 ui.ButTurnToWorkLaser2->setChecked(true);
	 ui.ButTurnToWorkLaser3->setChecked(true);
	 ui.ButTurnToWorkPointer->setChecked(true);
}

LaserBlockWindow::~LaserBlockWindow()
{
}



void LaserBlockWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	QVector<QPushButton*> Buttons;
	Buttons.append(ui.ButTurnToWorkLaser1);
	Buttons.append(ui.ButTurnToWorkLaser2);
	Buttons.append(ui.ButTurnToWorkLaser3);

	QVector<QPushButton*> ButtonsPower;
	ButtonsPower.append(ui.ButTurnToWorkPower1);
	ButtonsPower.append(ui.ButTurnToWorkPower2);
	ButtonsPower.append(ui.ButTurnToWorkPower3);

	QPushButton* ButConnect;

	QVector<QPushButton*>::Iterator ButtonIterator = Buttons.begin();
	for (int n_channel = 0; n_channel <= 2; n_channel++) //POWER CHANNELS 1 2 3
	{
			ButConnect = *ButtonIterator;
			ButtonIterator++;

			connect(ButConnect, &QPushButton::toggled,
				[=]()
			{
					Control->TurnOnOffLaser(n_channel + 11, ButConnect->isChecked());
			});
	}

	ButtonIterator = ButtonsPower.begin();
	for (int n_channel = 0; n_channel <= 2; n_channel++) //GUID CHANNELS 11 12 13
	{
			ButConnect = *ButtonIterator;
			ButtonIterator++;

			connect(ButConnect, &QPushButton::toggled,
				[=]()
			{
				    qInfo() << TAG << "TURN  POWER BUTTON";
					Control->TurnOnOffLaser(n_channel + 1, ButConnect->isChecked());
			});
	}



	connect(ui.ButTurnToWorkPointer, &QPushButton::toggled,
		[this, Control]()
	{
		Control->TurnOnOffLaser(4, ui.ButTurnToWorkPointer->isChecked());
	});

	connect(ui.butStartAllLasers, &QPushButton::toggled,
		[this, Control]()
	{
		Control->TurnOnOffAllLasers(ui.butStartAllLasers->isChecked());
	});
}
void LaserBlockWindow::DisplayState(stateblocksenum State,int NumberChannel)
{
	QPushButton* But = 0;

	switch (NumberChannel)
	{
	case 1: But = ui.ButTurnToWorkPower1; break;
	case 2: But = ui.ButTurnToWorkPower2; break;
	case 3: But = ui.ButTurnToWorkPower3; break;
	case 4: But = ui.ButTurnToWorkPointer; break;
	case 11: But = ui.ButTurnToWorkLaser1; break;
	case 12: But = ui.ButTurnToWorkLaser2; break;
	case 13: But = ui.ButTurnToWorkLaser3; break;
	}

	if (But != 0)
	{
	But->blockSignals(true);
	if (State == BlockDisable) But->setChecked(false);
	if (State == BlockAtWork)  But->setChecked(true);
	But->blockSignals(false);
	}
}
