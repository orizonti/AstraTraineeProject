
#include "CommonHeaders.h"
#include "laserblockwindow.h"

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

	QPushButton* ButConnect;
	QVector<QPushButton*>::Iterator ButtonIterator = Buttons.begin();

	for (int n_channel = 0; n_channel <= 2; n_channel++)
	{
			ButConnect = *ButtonIterator;
			ButtonIterator++;

			connect(ButConnect, &QPushButton::toggled,
				[=]()
			{
					Control->TurnOnOffLaserPilot(n_channel + 1, ButConnect->isChecked());
			});
	}


	connect(ui.ButTurnToWorkPointer, &QPushButton::toggled,
		[this, Control]()
	{
		Control->TurnOnOffLaserPointer(ui.ButTurnToWorkPointer->isChecked());
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
	case 1: But = ui.ButTurnToWorkLaser1; break;
	case 2: But = ui.ButTurnToWorkLaser2; break;
	case 3: But = ui.ButTurnToWorkLaser3; break;
	case 4: But = ui.ButTurnToWorkPointer; break;
	}

	if (But != 0)
	{
	But->blockSignals(true);

	if (State == BlockDisable)
		But->setChecked(false);
	if (State == BlockAtWork)
		But->setChecked(true);

		
	But->blockSignals(false);
	}
}
