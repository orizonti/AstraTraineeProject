#ifndef CHILLERINTERFACE_H
#define CHILLERINTERFACE_H

#include "DataChillerStructure.h"
#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include <QThread>
#include <QDataStream>
#include <QDebug>
#include <DataChillerStructure.h>

enum MESSAGE_TYPE
{

    GET_ALL_PACKET = 0x0101,
    SET_COMMAND = 0x0202, SET_COMMAND_RESPONSE = 0x0303, MESSAGE = 0x0404,
    RESET_MC = 0x0505
};

enum HEADER_IDENT
{
    MC_HEADER_IDENT = 0x2323,
    PC_HEADER_IDENT = 0x3232
};


struct HEADER_STRUCT
{
    uint16_t IDENT;
    uint16_t MESSAGE_TYPE;
    uint16_t DATA_SIZE;
};

struct UART_PACKET_COMMAND
{
    HEADER_STRUCT HEADER;
    uint8_t Data[8];
};

struct UART_PACKET_DATA
{
    HEADER_STRUCT HEADER;
    uint8_t Data[64];
};

union CommandPacket
{
uint8_t Bytes[16];
UART_PACKET_COMMAND Packet;
};



class ChillerInterface : public QObject
{
        Q_OBJECT
public:
ChillerInterface();
~ChillerInterface();

QSerialPort* Port;
void ResetComPort(QString PortName);
//=======================
int FRAME_NUMBER;
int SCAN_NUMBER;
quint8 MODE = 13;
int DataRequestCurrentRecord = 0;
//=======================

QTimer TimerDataRec;
QTimer TimerResetController;

int TemperatureLevel;
quint8 FLAG_CHILLER_WORK = 32;
DataChillerStructure ChillerState;

QByteArray DataToProcess;
QByteArray InputDataBuffer;
quint16 BytesReceived;
DataChillerStructure GetState() { return ChillerState;};
void DataToStore();

public slots:
void SlotReadData();
void SlotControllerDataRequest(); //COMMAND TO CONTROLLER TO SEND CHILLER STATE

void SlotTurnOnOff(bool OnOff);
void SlotSetWorkTemperature(int Temperature);

void SlotResetController();
void SlotStartChilling();

};

#endif // CHILLERINTERFACE_H
