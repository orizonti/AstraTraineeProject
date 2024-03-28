#include "ChillerWindowDisplay.h"
#include "AdjustableWidget.h"
#include "ui_ChillerWindowDisplay.h"
#include "QDebug"
int CurrentRecord = 0;

ChillerWindowDisplay::ChillerWindowDisplay(QWidget *parent) :
    AdjustableWidget(parent),
    ui(new Ui::ChillerWindowDisplay)
{
    ui->setupUi(this);


    QList<QSerialPortInfo> Ports = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo& Port: Ports)
    ui->boxPortList->addItem(Port.portName());

    timeStart = QTime::currentTime();

}

ChillerWindowDisplay::~ChillerWindowDisplay()
{
    delete ui;
}

void ChillerWindowDisplay::SlotDisplayChillerData(DataChillerStructure ChillerState)
{
    if(ChillerCurrentState == ChillerState) return;

    QTime CurrentTime= QTime::currentTime();
    int minutes = CurrentTime.secsTo(timeStart)/60;
    ui->listChillerOutput->addItem(QString::number(minutes) +" " + ChillerState.DeviceInfoString);

    //=====================================

    QString DataRecord = QString("Обьект - %1 Чиллер %2 Проток %3").arg(ChillerState.TEMP_CHILL1)
                                                                   .arg(ChillerState.TEMP_CHILL2)
                                                                   .arg(ChillerState.WATER_FLOW);
    //ui->listChillerOutput->selectRow(CurrentRecord);
    ui->listChillerOutput->addItem(DataRecord);
    CurrentRecord++; if(CurrentRecord >15) {CurrentRecord = 0; ui->listChillerOutput->clear();};
    //=====================================
    ChillerCurrentState = ChillerState;
}

void ChillerWindowDisplay::ConnectControlSignals(HandleControlInterface* Control)
{
    QObject::connect(ui->ButSendCommand,&QPushButton::clicked,[this,Control](){
     this->ChillerCommand.PORT = ui->boxPortList->currentText();
     this->ChillerCommand.ON_OFF = true;
     this->ChillerCommand.WORK_TEMP = ui->spinSetTemperatureLevel->value();
     Control->SetCommandChiller(ChillerCommand);

    });

    QObject::connect(ui->butReset,&QPushButton::clicked,[this,Control](){
     this->ChillerCommand.ON_OFF = false;
     this->ChillerCommand.WORK_TEMP = ui->spinSetTemperatureLevel->value();
     Control->SetCommandChiller(ChillerCommand);

    });

    QObject::connect(ui->butOpenPort,&QPushButton::clicked,[this,Control](){
     this->ChillerCommand.PORT = ui->boxPortList->currentText();
     Control->SetCommandChiller(ChillerCommand);

    });

    //QObject::connect(ui->spinSetTemperatureLevel,(void(QSpinBox::*)(int))&QSpinBox::valueChanged,[this,Control](int)
    //{
    //});
}