#include "CommonHeaders.h"
#include "pid_control_window.h"
#define TAG "[ PID    WIND ]" 

PIDWindow::PIDWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);

	QFile file("/home/broms/DEVELOPMENT/DATA/TrainerData/PIDParams.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

    //ui.PIDPreference->clear();
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
        //ui.PIDPreference->addItem(line);
	}
	file.close();
}

PIDWindow::~PIDWindow()
{

}
void PIDWindow::DisplayState(stateblocksenum State)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);

		
	ui.checkWorkBlock->blockSignals(false);
}

void PIDWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	
			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				if (ui.checkWorkBlock->isChecked())
				{
					Control->SetBlockState(PIDBlock,1,BlockAtWork);
					Control->SetBlockState(PIDBlock,2,BlockAtWork);
					Control->SetBlockState(PIDBlock,3,BlockAtWork);
				}
				else
				{
					Control->SetBlockState(PIDBlock,1,BlockDisable);
					Control->SetBlockState(PIDBlock,2,BlockDisable);
					Control->SetBlockState(PIDBlock,3,BlockDisable);
				}
			});

			connect(ui.ButSetPIDParam, &QPushButton::clicked,
				[=]()
			{
                    QString preference = ui.PIDPreference->currentItem()->text();
					QStringList list_preference = preference.split(" ");
					double Common = 1;
					double rate_param = list_preference.at(0).toDouble();
					double int_param = list_preference.at(1).toDouble();
					double diff_param = list_preference.at(2).toDouble();
					qDebug() << TAG << "SET PID PARAM - " << rate_param << int_param << diff_param;

				Control->SetPIDParam(Common, rate_param, int_param, diff_param);
				
			});

			
			connect(ui.butLoadPreference, &QPushButton::clicked,
				[=]()
			{
					
					qDebug() << TAG << "Load file PIDParams";
					QFile file("/home/broms/DEVELOPMENT/DATA/TrainerData/PIDParams.txt");
					if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
						return;

                    ui.PIDPreference->clear();
					QTextStream in(&file);
					while (!in.atEnd()) 
					{
						QString line = in.readLine();
						qDebug() << TAG << "Load - " << line;
                        ui.PIDPreference->addItem(line);
					}
			});


}


void PIDWindow::SetInitialState(double Rate, double Diff, double Int)
{
}
