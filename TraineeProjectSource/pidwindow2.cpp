#include "stdafx.h"
#include "pidwindow2.h"

PIDWindow2::PIDWindow2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QFile file("/home/broms/TrainerData/PIDParams.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	ui.listPIDPreference->clear();
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
		qDebug() << "Load - " << line;
		ui.listPIDPreference->addItem(line);
	}
}

PIDWindow2::~PIDWindow2()
{

}
void PIDWindow2::DisplayState(stateblocksenum State)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);

		
	ui.checkWorkBlock->blockSignals(false);
}

void PIDWindow2::ConnectControlSignals(HandleControlInterface* Control)
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
					QString preference = ui.listPIDPreference->currentItem()->text();
					QStringList list_preference = preference.split(" ");
					double Common = 1;
					double rate_param = list_preference.at(0).toDouble();
					double int_param = list_preference.at(1).toDouble();
					double diff_param = list_preference.at(2).toDouble();
					qDebug() << "SET PID PARAM - " << rate_param << int_param << diff_param;

				Control->SetPIDParam(Common, rate_param, int_param, diff_param);
				
			});

			
			connect(ui.butLoadPreference, &QPushButton::clicked,
				[=]()
			{
					
					qDebug() << "Load file PIDParams";
					QFile file("E:/TrainerData/PIDParams.txt");
					if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
						return;

				    ui.listPIDPreference->clear();
					QTextStream in(&file);
					while (!in.atEnd()) 
					{
						QString line = in.readLine();
						qDebug() << "Load - " << line;
						ui.listPIDPreference->addItem(line);
					}
			});


}


void PIDWindow2::SetInitialState(double Rate, double Diff, double Int)
{
}
