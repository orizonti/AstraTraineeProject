#include "CommonHeaders.h"
#include "LaserPointerInterface.h"
#include "QSerialPortInfo"

LaserPointerInterface::LaserPointerInterface()
{
    qDebug() << "LASER POINTER INTERFACE OPEN PORT - ttyXRUSB0";
    polynom = 0x9B;
    init = 0xFF;
    ComPort = new QSerialPort;
    ConnectToPort("ttyXRUSB0");



    this->Power675 = 700;
    this->Power1064 = 700;
    this->Power975 = 700;
    QTimer::singleShot(500, this, SLOT(SetPower675()));
    QTimer::singleShot(1000, this, SLOT(SetPower1065()));
    //QTimer::singleShot(200, this, SLOT(SetPower975()));
}

LaserPointerInterface::LaserPointerInterface(LaserPointerInterface& CopyInterface)
{
    ComPort = CopyInterface.ComPort;
    this->Power675 = 700;
    this->Power1064 = 700;
    this->Power975 = 700;
}

LaserPointerInterface::LaserPointerInterface(QString PortName)
{
    ComPort = new QSerialPort;
    ConnectToPort(PortName);
    this->Power675 = 700;
    this->Power1064 = 700;
    this->Power975 = 700;
    QTimer::singleShot(500, this, SLOT(SetPower675()));
    QTimer::singleShot(1000, this, SLOT(SetPower1065()));
    //QTimer::singleShot(200, this, SLOT(SetPower975()));
}

void LaserPointerInterface::ConnectToPort(QString PortName)
{
    ComPort->setPortName(PortName);
    bool FLAG_OPEN = false;
    FLAG_OPEN = ComPort->open(QSerialPort::ReadWrite);
    ComPort->setBaudRate(115200);
    ComPort->setDataBits(QSerialPort::Data8);
    ComPort->setParity(QSerialPort::NoParity);
    ComPort->setStopBits(QSerialPort::OneStop);
    ComPort->setFlowControl(QSerialPort::NoFlowControl);

    if (FLAG_OPEN)
    {
        qDebug() << "PORT OPEN - " << ComPort->portName();
        QObject::connect(ComPort,SIGNAL(readyRead()),this,SLOT(SlotReadData()));
    }

    QList<QSerialPortInfo> Ports = QSerialPortInfo::availablePorts();

    for(QSerialPortInfo& Port: Ports)
        qDebug() << "AVAILABLE PORT - " << Port.portName();

    this->SendCommand(CODE_UMI_ON,0xFF);


}

void LaserPointerInterface::TurnLaserBeamOnOff(bool OnOff)
{

	if (this->OnOff != OnOff)
		this->OnOff = OnOff;
	else
		return;

	qDebug() << "TURN MARKER LASER - " << OnOff;
	OnOff675 = OnOff;
	OnOff1064 = OnOff;

	        QTimer::singleShot(500, this, SLOT(TurnOnOff1064nm()));
	        QTimer::singleShot(1000, this, SLOT(TurnOnOff675nm()));

		if (OnOff)
			this->LaserState = BlockAtWork;
		else
			this->LaserState = BlockDisable;

}

DataLaserStruct LaserPointerInterface::GetState()
{
	return LaserCommonInterface::GetState();
}

void LaserPointerInterface::SendCommand(quint8 code, int value)
{
	if (data.size() > 0) data.clear();
	if (message.size() > 0) message.clear();
	//���������
	data.append(0x01);
	data.append(0x07);
	data.append(0x04);
	data.append(crcCalc(data.data(), data.length()));
	//---------------------------------
	message.append(0x47);
	message.append(code);
	message.append((value) >> 8);
	message.append((value) & 0xFF);
	//---------------------------------
	data.append(message);
	data.append(crcCalc(message.data(), message.length()));
	ComPort->write(data);

	ComPort->flush();

}

void LaserPointerInterface::TurnOnOff675nm()
{
	 if(this->OnOff675)
	 {
     this->SendCommand(L1_POWER_ON,0xFF);
	 qDebug() << "Turn 675 on !!!!!!";
	 }
    else
    this->SendCommand(L1_POWER_OFF,0xFF);

}

void LaserPointerInterface::TurnOnOff975nm()
{
	 if(this->OnOff975)
    this->SendCommand(L2_POWER_ON,0xFF);
    else
    this->SendCommand(L2_POWER_OFF,0xFF);
}

void LaserPointerInterface::TurnOnOff1064nm()
{
	 if(this->OnOff1064)
    this->SendCommand(L3_POWER_ON,0xFF);
    else
    this->SendCommand(L3_POWER_OFF,0xFF);
}

void LaserPointerInterface::SetPower675()
{
	   //power is current, must be changed to approximation power of current value
	   this->SendCommand(L1_CURRENT,1000 - this->Power675);
}

void LaserPointerInterface::SetPower975()
{
	   this->SendCommand(L2_CURRENT,1000 - this->Power975);
}

void LaserPointerInterface::SetPower1065()
{
	   this->SendCommand(L3_CURRENT,1000 - this->Power1064);
}

unsigned char LaserCommandStruct::crcCalc(char * pcBlock, unsigned int len)
{
    unsigned char crc = init;

    for(int b = 0; b < len; b++){
        crc ^= pcBlock[b];
        for(int i = 0; i < 8; i++){
            if((crc & 0x80) != 0){
                crc = (crc << 1) ^ polynom;
            }else{
                crc <<= 1;
            }
        }
    }
    return crc;
}

unsigned char LaserPointerInterface::crcCalc(char * pcBlock, unsigned int len)
{
	unsigned char crc = init;

	for (int b = 0; b < len; b++) {
		crc ^= pcBlock[b];
		for (int i = 0; i < 8; i++) {
			if ((crc & 0x80) != 0) {
				crc = (crc << 1) ^ polynom;
			}
			else {
				crc <<= 1;
			}
		}
	}
	return crc;

}

void LaserPointerInterface::SlotReadData()
{
	qDebug() << "READ DATA FROM COM PORT MARKER LASER IS NOT IMPLEMENTED";
}

