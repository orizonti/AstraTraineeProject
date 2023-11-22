
#include "CommonHeaders.h"
#include "kalmanwindow.h"

KalmanWindow::KalmanWindow(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

KalmanWindow::~KalmanWindow()
{
}

void KalmanWindow::DisplayState(stateblocksenum State)
{
	ui.checkWorkBlock->blockSignals(true);
	if (State == BlockDisable)
		ui.checkWorkBlock->setChecked(false);
	if (State == BlockAtWork)
		ui.checkWorkBlock->setChecked(true);

		
	ui.checkWorkBlock->blockSignals(false);
}

void KalmanWindow::DisplayParam(double VarE, double VarM, double VarVM)
{
	ui.lineVarE->setText(QString::number(VarE));
	ui.lineVarM->setText(QString::number(VarM));
	ui.lineVarVM->setText(QString::number(VarM));
}

void KalmanWindow::ConnectControlSignals(HandleControlInterface* Control)
{
			connect(ui.checkWorkBlock, &QCheckBox::stateChanged,
				[=]()
			{
				if (ui.checkWorkBlock->isChecked())
				{
					Control->SetBlockState(CalmanFilterBlock,1,BlockAtWork);
					Control->SetBlockState(CalmanFilterBlock,2,BlockAtWork);
					Control->SetBlockState(CalmanFilterBlock,3,BlockAtWork);
				}
				else
				{
					Control->SetBlockState(CalmanFilterBlock,1,BlockDisable);
					Control->SetBlockState(CalmanFilterBlock,2,BlockDisable);
					Control->SetBlockState(CalmanFilterBlock,3,BlockDisable);
				}
			});


			connect(ui.lineVarE, &QLineEdit::textChanged,
				[this,Control]()
			{
				Control->ChangeCalmanParam(ui.lineVarE->text().toDouble(), ui.lineVarM->text().toDouble());
			});

			connect(ui.lineVarM, &QLineEdit::textChanged,
				[this,Control]()
			{
				Control->ChangeCalmanParam(ui.lineVarE->text().toDouble(), ui.lineVarM->text().toDouble());
			});
}
