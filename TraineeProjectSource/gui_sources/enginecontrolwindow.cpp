#include "CommonHeaders.h"
#include "enginecontrolwindow.h"
#define TAG "[ ENGCTRL WIND]" 

EngineControlWindow::EngineControlWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

EngineControlWindow::~EngineControlWindow()
{
}


void EngineControlWindow::ConnectControlSignals(HandleControlInterface* Control)
{
	QVector<QSlider*> Sliders2;
	Sliders2.append(ui.SliderEngine1X);
	Sliders2.append(ui.SliderEngine1X);
	Sliders2.append(ui.SliderEngine1Y);
	Sliders2.append(ui.SliderEngine1Y);

	QVector<QLineEdit*> LinesOutput;
 	
	LinesOutput.append(ui.lineXPos1);
	LinesOutput.append(ui.lineXPos1);
	LinesOutput.append(ui.lineYPos1);
	LinesOutput.append(ui.lineYPos1);
	if(NumberChannel == 3)
	    ui.lineEditCommandDelay->setText(QString::number(100));
	else
        ui.lineEditCommandDelay->setText(QString::number(0));



    connect(ui.lineEditCommandDelay, &QLineEdit::textChanged,
            [=]()
            {
                    Control->SetEngineCommandDelay(ui.lineEditCommandDelay->text().toInt(),NumberChannel);
            });


	connect(ui.butTurnOffVertical, &QPushButton::toggled, 
	[=]()             
	{
			if (ui.butTurnOffVertical->isChecked())
			Control->TurnOnOffAxisEngine(true,1,NumberChannel);
			else
			Control->TurnOnOffAxisEngine(false,1,NumberChannel);
	});

	connect(ui.butTurnOffHorizontal, &QPushButton::toggled, 
	[=]()            
	{
			if (ui.butTurnOffHorizontal->isChecked())
			Control->TurnOnOffAxisEngine(true,2,NumberChannel);
			else
			Control->TurnOnOffAxisEngine(false,2,NumberChannel);
	});
				

	QVector<QSlider*>::iterator IterSlider = Sliders2.begin();
	QVector<QLineEdit*>::iterator IterLines = LinesOutput.begin();

	QSlider* SliderConnect;
	QLineEdit* Line;

		for (int dir = 0; dir <= 1; dir++)
		{
			SliderConnect = *IterSlider;
			Line = *IterLines;
			IterSlider++;
			IterSlider++;

			IterLines++;
			IterLines++;

			connect(SliderConnect, &QSlider::valueChanged, 
			[=]()
			{   
				double X_Pos = Sliders2.at(0)->value();
				double Y_Pos = Sliders2.at(2)->value();
				Control->MoveEngine(dir, X_Pos,Y_Pos, NumberChannel);

				if (dir == 0)
					Line->setText(QString::number(X_Pos/200));
				if (dir == 1)
					Line->setText(QString::number(Y_Pos/200));
			
			});
		}

		
	QVector<QPushButton*> ButtonsMoveLine;
	ButtonsMoveLine.append(ui.ButMovEng1Left);
	ButtonsMoveLine.append(ui.ButMovEng1Right);
	ButtonsMoveLine.append(ui.ButMovEng1Down);
	ButtonsMoveLine.append(ui.ButMovEng1Up);
	

	for (int n = 1; n <= 4; n++)
	{
	QSharedPointer<QTimer> Timer = QSharedPointer<QTimer>(new QTimer);


	QPushButton* ButMoveLine = ButtonsMoveLine.at(n-1);     //By Button start timer that move Slider by step that move engines
				connect(ButMoveLine, &QPushButton::pressed, //timer live in lambda end delete by shared pointer when lambda delete 
				[Timer,ButMoveLine]()
	            {
					 Timer->start(1);
				});

				connect(ButMoveLine, &QPushButton::released, 
				[Timer,ButMoveLine]()
	            {
					Timer->stop();
				});

				int step = -20;
				if (n % 2)
					step = 20;

				QSlider* Slider = Sliders2.at(n-1);
				QLineEdit* Line = LinesOutput.at(n-1);


				connect(Timer.data(), &QTimer::timeout, //Connect timer to move slider method for moving engine
				[Slider,step,Line]()
				{
					int value = Slider->value();
					Slider->setValue(value - step);
					//qInfo() << TAG << "Move line - " << value;
					Line->setText(QString::number(value/200));
				});

	}



				connect(ui.ButEngineToNull1, &QPushButton::clicked, 
				[=]()             //Set to NULL slider and thus set engine to NULL
	            {
					qInfo() << TAG << "Set tu null method";
					ui.SliderEngine1X->setValue(0);
					ui.SliderEngine1Y->setValue(0);
				    Control->MoveEngineToNull(NumberChannel);
					ui.lineXPos1->setText(QString::number(0));
					ui.lineYPos1->setText(QString::number(0));
				});

				
			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				if (ui.checkWorkBlock->isChecked())
				{
					Control->SetBlockState(EngineControlBlock,NumberChannel,BlockAtWork);
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Работа"));
				}
				else
				{
					Control->SetBlockState(EngineControlBlock,NumberChannel,BlockDisable);
              		ui.checkWorkBlock->setText(QString::fromLocal8Bit("Пуск"));
				}
			});

}


void EngineControlWindow::DisplayState(EngineData DataStructure)
{


	ui.checkWorkBlock->blockSignals(true);
	if (DataStructure.State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (DataStructure.State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);
	ui.checkWorkBlock->blockSignals(false);

		
	ui.LabelCurrentXPos1->setText(QString::number(DataStructure.LastPosChannel.second,'f',4));
	ui.LabelCurrentYPos1->setText(QString::number(DataStructure.LastPosChannel.first,'f',4));

}

void EngineControlWindow::SetNumberChannel(int NumberChannel)
{
	ui.LabelNumberChannel->setText(QString::number(NumberChannel));

}
