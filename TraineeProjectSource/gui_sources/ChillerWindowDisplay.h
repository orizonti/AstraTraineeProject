#ifndef ChillerWindowDisplay_H
#define ChillerWindowDisplay_H

#include <QDebug>
#include <QThread>
#include <QtWidgets/QPushButton>

#include <QDialogButtonBox>
#include <QWidget>
//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>
#include <QTime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include "AdjustableWidget.h"
#include "chillerinterface.h"
#include "HandleControlInterface.h"


namespace Ui {
class ChillerWindowDisplay;
}

class ChillerWindowDisplay : public AdjustableWidget
{
    Q_OBJECT

public:
    explicit ChillerWindowDisplay(QWidget *parent = 0);

    int CurrentRecord = 0;
    QTime timeStart;

    ~ChillerWindowDisplay();
	void ConnectControlSignals(HandleControlInterface* Control);
    CommandChillerStructure ChillerCommand;
    DataChillerStructure ChillerCurrentState;

private:
    Ui::ChillerWindowDisplay *ui;


public slots:
     void SlotDisplayChillerData(DataChillerStructure ChillerState);
};

#endif // ChillerWindowDisplay_H
