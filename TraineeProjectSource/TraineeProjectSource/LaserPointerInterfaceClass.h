#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "CommonLaserInterfaceClass.h"
#include <QSerialPort>

#define CODE_UMI_ON             0x01
#define LASERS_OFF              0x00
#define L1_CURRENT				0x0B
#define L1_IMPULSE_VALUE        0x0C
#define L1_POWER_ON             0x0D
#define L1_POWER_OFF            0x0E
#define L1_CONTINUOUS_MODE      0x0F
#define L1_IMPULSE_MODE         0x10
#define L2_CURRENT				0x15
#define L2_IMPULSE_VALUE        0x16
#define L2_POWER_ON             0x17
#define L2_POWER_OFF            0x18
#define L2_CONTINUOUS_MODE      0x19
#define L2_IMPULSE_MODE         0x1A
#define L3_CURRENT				0x1F
#define L3_IMPULSE_VALUE        0x20
#define L3_POWER_ON             0x21
#define L3_POWER_OFF            0x22
#define L3_CONTINUOUS_MODE      0x23
#define L3_IMPULSE_MODE         0x24

#define GET_STATE               0x28

#define A_UMI					0x01
#define A_CURRENT_IMPULSE		0x20
#define A_MODE					0x40
#define A_L1_POWER				0x04
#define A_L2_POWER				0x08
#define A_L3_POWER				0x10
#define A_STATE					0x02


class LaserCommandStruct
{
public:
    LaserCommandStruct()
    {
        polynom = 0x9B;
        init = 0xFF;
        char* Data = (char*)this;
        ControlSummHeader = this->crcCalc(Data,3);
    }

    void SetMessage(quint8 code, int value)
    {
        this->Command = code;
        this->ParamLowByte = value >> 8;
        this->ParamHightByte = value & 0xFF;

        char* Data = (char*)(this+4);


        ControlSummHeader = this->crcCalc(Data,4);
    }
    unsigned char polynom, init;
    unsigned char crcCalc(char*, unsigned int);

        quint8 AddressSender = 0x1;
        quint8 AddressReciever = 0x7;
        quint8 MessageLength = 0x4;

        quint8 ControlSummHeader = 0x0;

        quint8 MessageCode = 0x47;
        quint8 Command = 0x0;

        quint8 ParamLowByte = 0x0;
        quint8 ParamHightByte = 0x0;

        quint8 ControlSummMessage = 0x0;

friend void operator<<(QDataStream& out, LaserCommandStruct& LaserCommand);
};


class LaserPointerInterfaceClass : public CommonLaserInterfaceClass
{
	Q_OBJECT
private:
	typeblocksenum TypeBlock;
	stateblocksenum StateBlock;
public:
	LaserPointerInterfaceClass();
    LaserPointerInterfaceClass(QString PortName);
    LaserPointerInterfaceClass(LaserPointerInterfaceClass& CopyInterface);
	void TurnLaserBeamOnOff(bool OnOff);

	DataLaserStruct GetState();
	QSerialPort* ComPort;
	LaserCommandStruct CommandToSend;

	double Power675 = 0;
	double Power1064 = 0;
	double Power975 = 0;

	bool OnOff675 = false;
	bool OnOff1064 = false;
	bool OnOff975 = false;


	void SendCommand(quint8 code, int value);

private:
	QByteArray data, message, rx;
	QString ComPortName;
	unsigned char polynom, init;

	unsigned char crcCalc(char * pcBlock, unsigned int len);

	public slots:
	void SlotReadData();

	void TurnOnOff675nm();
	void TurnOnOff975nm();
	void TurnOnOff1064nm();

	void SetPower675();
	void SetPower975();
	void SetPower1065();

	void ConnectToPort(QString PortName);
};


