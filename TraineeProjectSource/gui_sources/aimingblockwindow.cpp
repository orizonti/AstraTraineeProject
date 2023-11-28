
#include "CommonHeaders.h"
#include "aimingblockwindow.h"
#define TAG "[ AIM  WINDOW ]" 

AimingBlockWindow::AimingBlockWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
    
}


AimingBlockWindow::~AimingBlockWindow()
{
}

    

void AimingBlockWindow::DisplayState(stateblocksenum State, TypeAiming AimingType, std::tuple<float,float,float> PID)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable) ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)  ui.checkWorkBlock->setChecked(true);

	if(AimingType == AimingFast) ui.checkMoveFastPID->setChecked(true);
    if(AimingType == AimingSlow) ui.checkMoveSlowPID->setChecked(true);
    if(AimingType == AimingTuning) ui.checkTuningMode->setChecked(true);

    ui.labelPidParam->setText(QString("%1 %3 %2").arg(std::get<0>(PID),4).arg(std::get<1>(PID),4).arg(std::get<2>(PID),4));
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
			RadioBut.append(ui.checkMoveSlowPID); RadioBut.append(ui.checkMoveFastPID); RadioBut.append(ui.checkTuningMode);

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
                    case 1: Control->ChangeAimingType(AimingSlow, NumberChannel); break;
                    case 2: Control->ChangeAimingType(AimingFast, NumberChannel); break;
                    case 3: Control->ChangeAimingType(AimingTuning, NumberChannel); break;
                    }
                }
            });
        }

    QCheckBox* But = ui.checkBoxFilterOnOff;
    int channel = this->NumberChannel;

    connect(ui.checkBoxFilterOnOff, &QCheckBox::toggled,
    [But,Control,channel]()
    {
        Control->TurnOnOffKalmanFilter(But->isChecked(), channel);
    });
}
