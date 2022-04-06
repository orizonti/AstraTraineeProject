#include "stdafx.h"
#include "LaserPointerInterfaceClass.h"
#include "QSerialPortInfo"

LaserPointerInterfaceClass::LaserPointerInterfaceClass()
{
    qDebug() << "LASER POINTER INTERFACE OPEN PORT - ttyXRUSB0";
    polynom = 0x9B;
    init = 0xFF;
    ComPort = new QSerialPort;
    ComPort->setPortName("ttyXRUSB0");


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
           {
               qDebug() << "AVAILABLE PORT - " << Port.portName();
               //ui->comboBox->addItem(Port.portName());
           }
    	    this->SendCommand(CODE_UMI_ON,0xFF);
    		//	QThread::msleep(300);
			//this->SendCommand(L1_CONTINUOUS_MODE, 0xFF);


    	    qDebug() << "CUMI ON";
    			//QThread::msleep(300);
    		//this->SetPower1065(500);
    		//	QThread::msleep(300);
    		//this->SetPower975(500);
			this->Power675 = 800;
			this->Power1064 = 800;
			this->Power975 = 800;
	        QTimer::singleShot(500, this, SLOT(SetPower675()));
	        QTimer::singleShot(1000, this, SLOT(SetPower1065()));
	        //QTimer::singleShot(200, this, SLOT(SetPower975()));
    		//	QThread::msleep(300);


	            
}

void LaserPointerInterfaceClass::TurnLaserBeamOnOff(bool OnOff)
{

	if (this->OnOff != OnOff)
		this->OnOff = OnOff;
	else
		return;

	qDebug() << "TURN MARKER LASER - " << OnOff;
					//QThread::msleep(150);
					//QThread::msleep(150);
				//this->TurnOnOff975nm(OnOff);
	OnOff675 = OnOff;
	OnOff1064 = OnOff;

	        QTimer::singleShot(500, this, SLOT(TurnOnOff1064nm()));
	        QTimer::singleShot(1000, this, SLOT(TurnOnOff675nm()));

		if (OnOff)
			this->LaserState = BlockAtWork;
		else
			this->LaserState = BlockDisable;

}

DataLaserStruct LaserPointerInterfaceClass::GetState()
{
	return CommonLaserInterfaceClass::GetState();
}

void LaserPointerInterfaceClass::SendCommand(quint8 code, int value)
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

void LaserPointerInterfaceClass::TurnOnOff675nm()
{
	 if(this->OnOff675)
	 {
     this->SendCommand(L1_POWER_ON,0xFF);
	 qDebug() << "Turn 675 on !!!!!!";
	 }
    else
    this->SendCommand(L1_POWER_OFF,0xFF);

}

void LaserPointerInterfaceClass::TurnOnOff975nm()
{
	 if(this->OnOff975)
    this->SendCommand(L2_POWER_ON,0xFF);
    else
    this->SendCommand(L2_POWER_OFF,0xFF);
}

void LaserPointerInterfaceClass::TurnOnOff1064nm()
{
	 if(this->OnOff1064)
    this->SendCommand(L3_POWER_ON,0xFF);
    else
    this->SendCommand(L3_POWER_OFF,0xFF);
}

void LaserPointerInterfaceClass::SetPower675()
{
	   //power is current, must be changed to approximation power of current value
	   this->SendCommand(L1_CURRENT,1000 - this->Power675);
	   qDebug() << "Set power- -" << this->Power675;
}

void LaserPointerInterfaceClass::SetPower975()
{
	   this->SendCommand(L2_CURRENT,1000 - this->Power975);
}

void LaserPointerInterfaceClass::SetPower1065()
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

unsigned char LaserPointerInterfaceClass::crcCalc(char * pcBlock, unsigned int len)
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

void LaserPointerInterfaceClass::SlotReadData()
{
	qDebug() << "READ DATA FROM COM PORT MARKER LASER IS NOT IMPLEMENTED";
}

