#include "RemoteControlProtocol.h"

void operator>>(QDataStream& stream, MESSAGE_HEADER& Header)
{
     stream >> Header.HEADER; stream >> Header.MESSAGE_ID; stream >> Header.MESSAGE_TYPE; stream >> Header.CMD_TYPE; stream >> Header.DATA_SIZE; 
}

void operator<<(QDataStream& stream, MESSAGE_HEADER& Header)
{
     stream << Header.HEADER; stream << Header.MESSAGE_ID; stream << Header.MESSAGE_TYPE; stream << Header.CMD_TYPE; stream << Header.DATA_SIZE; 
}

void operator>>(QDataStream& stream, MessageStruct<STATE_STRUCT>& Message)
{
  stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
  stream >> Message.HEADER; stream >> Message.DATA; stream >> Message.ERROR_ID; }

void operator<<(QDataStream& stream, MessageStruct<STATE_STRUCT>& Message)
{
  stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
  stream << Message.HEADER; stream << Message.DATA; stream << Message.ERROR_ID; }


void operator<<(QDataStream& out_stream, STATE_STRUCT& data)
{
qDebug() << "STATE STRUCT TO BYTEARRAY";
out_stream.setByteOrder(QDataStream::LittleEndian);
out_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
out_stream << data.WorkMode;
out_stream << data.WorkTime;
out_stream << *(uint8_t*)(&(data.CameraState));
out_stream << *(uint8_t*)(&(data.EnginesState));
out_stream << *(uint8_t*)(&(data.PointerLaserState));
out_stream << *(uint8_t*)(&(data.GuidLaserState));
out_stream << *(uint8_t*)(&(data.PowerLaserState));
out_stream << *(uint8_t*)(&(data.PowerLaserConnectionState));
out_stream << data.PowerLaserTemp1;
out_stream << data.PowerLaserTemp2;
out_stream << data.PowerLaserTemp3;
out_stream << data.Chiller;
out_stream << data.ChillerTemp1;
out_stream << data.ChillerTemp2;
out_stream << data.Temperature;
out_stream << data.Moisture;
out_stream << data.Pressure;
qDebug() << "TEMP    : " << data.Temperature;
qDebug() << "MOISTURE: " << data.Moisture;
}
void operator>>(QDataStream& out_stream, STATE_STRUCT& data)
{
out_stream.setByteOrder(QDataStream::LittleEndian);
out_stream >> data.WorkMode;
out_stream >> data.WorkTime;
out_stream >> *(uint8_t*)(&data.CameraState);
out_stream >> *(uint8_t*)(&data.EnginesState);
out_stream >> *(uint8_t*)(&data.PointerLaserState);
out_stream >> *(uint8_t*)(&data.GuidLaserState);
out_stream >> *(uint8_t*)(&data.PowerLaserState);
out_stream >> *(uint8_t*)(&data.PowerLaserConnectionState);
out_stream >> data.PowerLaserTemp1;
out_stream >> data.PowerLaserTemp2;
out_stream >> data.PowerLaserTemp3;
out_stream >> data.Chiller;
out_stream >> data.ChillerTemp1;
out_stream >> data.ChillerTemp2;

out_stream >> data.Temperature;
out_stream >> data.Moisture;
out_stream >> data.Pressure;
}


void STATE_STRUCT::PrintStruct()
{
qDebug() << "WorkMode  " << WorkMode;
qDebug() << "WorTime   " << WorkTime;
qDebug() << "Camera    " << *(uint8_t*)(&(CameraState));
qDebug() << "Engines   " << *(uint8_t*)(&(EnginesState));
qDebug() << "Pointer   " << *(uint8_t*)(&(PointerLaserState));
qDebug() << "GuidLaser " << *(uint8_t*)(&(GuidLaserState));
qDebug() << "PowerLaser" << *(uint8_t*)(&(PowerLaserState));
qDebug() << "PowerLaser" << *(uint8_t*)(&(PowerLaserConnectionState));
qDebug() << "PowerTemp1" << PowerLaserTemp1;
qDebug() << "PowerTemp2" << PowerLaserTemp2;
qDebug() << "PowerTemp3" << PowerLaserTemp3;
qDebug() << "Chiller   " << Chiller;
qDebug() << "Temp      " << Temperature;
qDebug() << "Moisture  " << Moisture;
qDebug() << "Presure   " << Pressure;
qDebug() << "==============================";
}

STATE_STRUCT::STATE_STRUCT()
{
  std::fill((char*)(&WorkMode), (char*)(&Pressure),0);
}

template<> QByteArray MessageStruct<STATE_STRUCT>::toByteArray()
{
qDebug() <<"STATE TO BYTEARRAY";
QByteArray  RawData;
QDataStream out_stream(&RawData, QIODevice::ReadWrite);
            out_stream.setByteOrder(QDataStream::LittleEndian);
            out_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
            
out_stream << this->HEADER; out_stream << this->DATA; out_stream << this->ERROR_ID; return RawData;
};
//=========================================================================
template<> MessageStruct<COMMAND_ENGINE_CONTROL>::MessageStruct() { HEADER.CMD_TYPE = CMD_ENGINES; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<COMMAND_GUID_LASER>::MessageStruct()     { HEADER.CMD_TYPE = CMD_POWERLASER; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<COMMAND_AIMING_COORD>::MessageStruct()   { HEADER.CMD_TYPE = CMD_AIMING; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<COMMAND_POWER_LASER>::MessageStruct()    { HEADER.CMD_TYPE = CMD_POINTLASER; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<COMMAND_POINT_LASER>::MessageStruct()    { HEADER.CMD_TYPE = CMD_POINTLASER; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<COMMAND_CAMERA_CONTROL>::MessageStruct() { HEADER.CMD_TYPE = CMD_CAMERA; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
template<> MessageStruct<STATE_STRUCT>::MessageStruct()           { HEADER.CMD_TYPE = CMD_STATE; HEADER.DATA_SIZE = this->toByteArray().size() - 13; };
//=========================================================================