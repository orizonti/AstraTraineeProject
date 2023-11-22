#include "CommonHeaders.h"
#include "RemoteAimingWindowControl.h"
#include "RemoteControlClass.h"

RemoteAimingWindowControl::RemoteAimingWindowControl(QWidget *parent)
	: AdjustableWidget(parent)
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

RemoteAimingWindowControl::~RemoteAimingWindowControl()
{
}




void RemoteAimingWindowControl::SlotSetActiveChannel()
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
void RemoteAimingWindowControl::SlotResetBlock()
{
	this->ErrorPortHandleControl->SlotResetRotationBlocks();
}
void RemoteAimingWindowControl::SlotSetWorkMode()
{
	if(ui.butSetRegistrationMode->isChecked())
		this->ErrorPortHandleControl->SlotSetMode(1);

	if(ui.butSetAimingMode->isChecked())
		this->ErrorPortHandleControl->SlotSetMode(2);
}
