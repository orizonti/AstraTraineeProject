#include "CommonHeaders.h"
#include "RemoteWindowControl.h"
#include "RemoteControlInterface.h"

#define TAG "[ REMOTE DISP ]" 
RemoteWindowControl::RemoteWindowControl(QWidget *parent)
	: AdjustableWidget(parent)
{
	ui.setupUi(this);
}

RemoteWindowControl::~RemoteWindowControl()
{
}

void RemoteWindowControl::SlotPrintRemoteCommand(QString Command)
{
    ui.listRemoteCommands->addItem(Command);

    if(ui.listRemoteCommands->count() > 10)
	ui.listRemoteCommands->clear();
}


