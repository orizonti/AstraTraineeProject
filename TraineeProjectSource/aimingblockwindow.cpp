
#include "stdafx.h"
#include "aimingblockwindow.h"

AimingBlockWindow::AimingBlockWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


}

AimingBlockWindow::~AimingBlockWindow()
{

}

void AimingBlockWindow::DisplayState(stateblocksenum State)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);

		
	ui.checkWorkBlock->blockSignals(false);
}

void AimingBlockWindow::ConnectControlSignals(HandleControlInterface* Control)
{
			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				if (ui.checkWorkBlock->isChecked())
				{
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Работа"));
					Control->SetBlockState(AimingBlock,this->NumberChannel,BlockAtWork);
				}
				else
				{
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Отключено"));
					Control->SetBlockState(AimingBlock, this->NumberChannel, BlockDisable);
				}
			});

			QVector<QCheckBox*> RadioBut;
			RadioBut.append(ui.checkMoveSlowPID);
			RadioBut.append(ui.checkMoveFastPID);


			int TypeAiming = 0;
				for (QCheckBox* But : RadioBut)
				{
					
					TypeAiming++;
					connect(But, &QCheckBox::toggled,
						[=]()
					{
						if (But->isChecked())
						{
							switch (TypeAiming)
							{
							case 1:
								Control->ChangeAimingType(AimingSlow, NumberChannel);
								break;
							case 2:
								Control->ChangeAimingType(AimingFast, NumberChannel);
								break;
							}

						}
					});
				}
}
