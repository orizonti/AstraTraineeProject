#include "stdafx.h"
#include "ErrorPortControl.h"
#include "ErrorRecieverClass.h"

ErrorPortControl::ErrorPortControl(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

//	void SlotSetActiveChannel();
//	void SlotResetBlock();
//	void SlotSetWorkMode();
	QObject::connect(ui.butResetRotationModules,SIGNAL(clicked()),this,SLOT(SlotResetBlock()));

	QObject::connect(ui.butSetAimingMode,SIGNAL(clicked()),this,SLOT(SlotSetWorkMode()));
	QObject::connect(ui.butSetRegistrationMode,SIGNAL(clicked()),this,SLOT(SlotSetWorkMode()));


	QObject::connect(ui.butDirectErrorToAll,SIGNAL(clicked()),this,SLOT(SlotSetActiveChannel()));
	QObject::connect(ui.butDirectErrorToChannel1,SIGNAL(clicked()),this,SLOT(SlotSetActiveChannel()));
	QObject::connect(ui.butDirectErrorToChannel2,SIGNAL(clicked()),this,SLOT(SlotSetActiveChannel()));
	QObject::connect(ui.butDirectErrorToChannel3,SIGNAL(clicked()),this,SLOT(SlotSetActiveChannel()));
}

ErrorPortControl::~ErrorPortControl()
{
}


void ErrorPortControl::MoveToScene(QGraphicsScene* Scene)
{
	Node = new GraphicWidgetNode(Scene, 300, 300, this);
	Node->setPos(X_POS, Y_POS);
}

void ErrorPortControl::MoveToPos(int X, int Y)
{
	Node->setPos(X, Y);
}

void ErrorPortControl::ConnectToWidgetOnScene(GraphicWidgetNode* Node)
{
}

void ErrorPortControl::SlotSetActiveChannel()
{
	qDebug() << "Set direction";
	if(ui.butDirectErrorToAll->isChecked())
    this->ErrorPortHandleControl->SlotSetActiveChannel(0);	

	if(ui.butDirectErrorToChannel1->isChecked())
    this->ErrorPortHandleControl->SlotSetActiveChannel(1);	
	if(ui.butDirectErrorToChannel2->isChecked())
    this->ErrorPortHandleControl->SlotSetActiveChannel(2);	
	if(ui.butDirectErrorToChannel3->isChecked())
    this->ErrorPortHandleControl->SlotSetActiveChannel(3);	
}
void ErrorPortControl::SlotResetBlock()
{
	this->ErrorPortHandleControl->SlotResetRotationBlocks();
}
void ErrorPortControl::SlotSetWorkMode()
{
	if(ui.butSetRegistrationMode->isChecked())
		this->ErrorPortHandleControl->SlotSetMode(1);

	if(ui.butSetAimingMode->isChecked())
		this->ErrorPortHandleControl->SlotSetMode(2);
}
