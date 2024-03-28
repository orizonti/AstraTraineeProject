#pragma once

#ifndef REMOTE_PROTOCOL_H
#define REMOTE_PROTOCOL_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDataStream>
#include <QFile>
#include <QSocketNotifier>
#include <qnamespace.h>
#include <qsocketnotifier.h>
#include <iostream>
#include <typeinfo>

enum KLP_PACKET_TYPES
{
    PACK_UNDEFINED = -1,
    PACK_REQUEST   = 0,      //команда запроса
    PACK_ACK       = 1,      //подтверждение принятия команды
    PACK_REPLY     = 2,      //ответ (результат выполнения)
    PACK_STATE     = 3       //выдача вектора состояния
}; 


//Номера команд
enum KLP_CMD_TYPES
{
    CMD_UNDEFINED  = -1,
    CMD_STATE      =  0,
    CMD_CAMERA     =  10,       //управление ТМ-КЮ
    CMD_ENGINES    =  11,       //управление УПП
    CMD_POINTLASER =  12,       //управление УМИ
    CMD_PILOTLASER =  13,       //управление ЛС
    CMD_POWERLASER =  14,       //управление ЛС
    CMD_AIMING     =  50,

};
enum KLP_ERROR_TYPES
{
    ERROR_UNDEFINED            = -1,
    ERROR_NO_ERRORS            = 0,
    ERROR_UNKNOWN_COMMAND      = 1,
    ERROR_CAMERA_COONNECT   = 10,
    ERROR_ENGINES_CONNECT       = 20,
    ERROR_ENGINE1_FAULT       = 21,
    ERROR_ENGINE2_FAULT       = 22,
    ERROR_ENGINE3_FAULT       = 23,
    ERROR_LASER_POINTER = 30,
    ERROR_LASER_GUID = 30,
    ERROR_LASER_POWER = 40
}; 
class KLP_PACKETS_GROUP
{
  public:
  static bool isValid(int n_type) {return n_type == PACK_UNDEFINED || (n_type >= 0 && n_type <= 3);}
  QString operator()(int n_type) {if(n_type > 4) return "NONE"; return GROUP_MAP[n_type]; };
  QString operator()(KLP_PACKET_TYPES type) {int n = static_cast<int>(type); if(n > 4) return "NONE"; return GROUP_MAP[n]; };
  std::map<int,QString> GROUP_MAP = {{-1, "UNDEF"}, {0,"REQ" },{1,"ACK" },{2, "REPL"},{3, "STATE"}};
};
class KLP_CMD_GROUP_LIST
{
  public:
  static bool isValid(int n_type) {return (n_type == CMD_UNDEFINED || n_type == CMD_STATE  || n_type == CMD_AIMING || (n_type >= 10 && n_type <= 14));}
  QString operator()(int n_type) {if(n_type > 50) return "NONE"; return GROUP_MAP[n_type]; };
  QString operator()(KLP_CMD_TYPES type) {int n = static_cast<int>(type); if(n > 14 && n !=50) return "NONE"; return GROUP_MAP[n]; };
  std::map<int,QString> GROUP_MAP = {{-1, "UNDEFINED"},{0, "GET_STATE"},
                                     {10, "CAMERA"   },{11, "ENGINES" },
                                     {12, "POINTER_LASER"},{13, "PILOT_LASER"},{14, "POWER_LASER"}, {50,"AIMIMIG" }};
};
extern KLP_CMD_GROUP_LIST KLP_CMD_GROUP;

struct STATE_STRUCT
{
STATE_STRUCT();

struct ChannelsState {uint8_t Channel1: 1 = 0; uint8_t Channel2: 1 = 0; uint8_t Channel3: 1 = 0;};

  uint8_t  WorkMode = 0;
  uint16_t WorkTime = 0;
  uint8_t CameraState;
  ChannelsState EnginesState;
  uint8_t       PointerLaserState;
  ChannelsState GuidLaserState;
  ChannelsState PowerLaserState;
  ChannelsState PowerLaserConnectionState;
  float PowerLaserTemp1 = 11.0;
  float PowerLaserTemp2 = 12.0;
  float PowerLaserTemp3 = 13.0;

  uint8_t Chiller = 1;
  float ChillerTemp1 = 23.0;
  float ChillerTemp2 = 23.0;

  float Temperature = 67;
  float Moisture = 39;
  float Pressure = 7;
  
  friend void operator<<(QDataStream& out_stream, STATE_STRUCT& data);
  friend void operator>>(QDataStream& out_stream, STATE_STRUCT& data);
  void PrintStruct();
};

struct COMMAND_CAMERA_CONTROL{ uint8_t OnOff = 0; };
struct COMMAND_ENGINE_CONTROL{ uint8_t OnOff = 0; };
struct COMMAND_GUID_LASER    { uint8_t OnOff = 0; };
struct COMMAND_POINT_LASER   { uint8_t OnOff = 0; };
struct COMMAND_AIMING_COORD  { float X = 0; float Y = 0; };
struct COMMAND_POWER_LASER   { uint8_t OnOff = 0; uint8_t Channel = 0; uint16_t WorkTime = 0;};

template<typename T>  
QString CommandToString(T& Command) { return QString("VAL: %1").arg((uint8_t)Command.OnOff); };

template<> QString CommandToString(COMMAND_AIMING_COORD& Command);
template<> QString CommandToString(COMMAND_POWER_LASER& Command);

//struct DIOD_CONTROL { uint8_t DIOD1 :1; uint8_t DIOD2 :1; uint8_t DIOD3 :1; } DiodOnOff;
class MESSAGE_HEADER
{
  public:
    uint16_t HEADER = 0x8220; 
    uint32_t MESSAGE_ID = 0x0; 
    uint8_t  MESSAGE_TYPE = PACK_STATE; 
    uint8_t  CMD_TYPE = CMD_STATE; 
    uint32_t DATA_SIZE = 1; 

    friend void operator>>(QDataStream& stream, MESSAGE_HEADER& Header);
    friend void operator<<(QDataStream& stream, MESSAGE_HEADER& Header);
    bool isValid() { return HEADER == 0x8220; }
};

template<typename T>
class MessageStruct
{
  public:
    MessageStruct();
	public:
    MESSAGE_HEADER HEADER;
    T DATA; 
    uint8_t ERROR_ID = ERROR_NO_ERRORS; 

  public:
	bool isMessasge() {return (HEADER.isValid()); };
  template<typename M> friend void operator>>(QDataStream& stream, MessageStruct<M>& Message);
  template<typename M> friend void operator<<(QDataStream& stream, MessageStruct<M>& Message);

  QByteArray toByteArray();
  QString toString();
  int GetSize() {return this->toByteArray().size();};

};

class MessageStructEmpty
{
	public:
    MESSAGE_HEADER HEADER;
    uint8_t ERROR_ID = ERROR_NO_ERRORS; 

  QByteArray toByteArray()
  {
    QByteArray  RawData; QDataStream out_stream(&RawData, QIODevice::ReadWrite); out_stream.setByteOrder(QDataStream::LittleEndian);
    out_stream << this->HEADER; out_stream << this->ERROR_ID; return RawData;
  }
  int GetSize() {return this->toByteArray().size();};
};



template<typename T>
QByteArray MessageStruct<T>::toByteArray()
{
QByteArray  RawData;
QDataStream out_stream(&RawData, QIODevice::ReadWrite);
            out_stream.setByteOrder(QDataStream::LittleEndian);
out_stream << this->HEADER;
out_stream.writeRawData(reinterpret_cast<char*>(&DATA), sizeof(DATA));
out_stream << this->ERROR_ID;
return RawData;
};

template<typename T> QString MessageStruct<T>::toString() { }

template<typename T> MessageStruct<T>::MessageStruct(){ std::fill((char*)this->DATA ,(char*)(this->DATA+sizeof(T)-1),0); };

void operator<<(QDataStream& stream, MessageStruct<STATE_STRUCT>& Message);
void operator>>(QDataStream& stream, MessageStruct<STATE_STRUCT>& Message);


template<typename T>
void operator>>(QDataStream& stream, MessageStruct<T>& Message)
{
  const std::type_info& ti = typeid(T);
  qDebug() << "COMMAND REC: " << ti.name();
  stream >> Message.HEADER; 
  stream.readRawData(reinterpret_cast<char*>(&Message.DATA), sizeof(Message.DATA));
  stream >> Message.ERROR_ID; 
}

template<typename M> void operator<<(QDataStream& stream, MessageStruct<M>& Message)
{
  stream << Message.HEADER; 
  stream.writeRawData(reinterpret_cast<char*>(&Message.DATA), sizeof(Message.DATA));
  stream << Message.ERROR_ID; 
}

template<> MessageStruct<COMMAND_ENGINE_CONTROL>::MessageStruct();
template<> MessageStruct<COMMAND_AIMING_COORD>::MessageStruct();

template<> MessageStruct<COMMAND_GUID_LASER>::MessageStruct();
template<> MessageStruct<COMMAND_POWER_LASER>::MessageStruct();
template<> MessageStruct<COMMAND_POINT_LASER>::MessageStruct();

template<> MessageStruct<COMMAND_CAMERA_CONTROL>::MessageStruct();
template<> MessageStruct<STATE_STRUCT>::MessageStruct();
template<> QByteArray MessageStruct<STATE_STRUCT>::toByteArray();
#endif // REMOTE_PROTOCOL_H