#include "CommonHeaders.h"
#include "EngineInterfaceClass.h"
#include "KLPInterfaceClass.h"

QByteArray EngineInterfaceClass::CommonBuffer;
KLPInterfaceClass* EngineInterfaceClass::KLPInterface;
OutFcChannelFlags EngineInterfaceClass::EngineChannelNumber = ChannelFc3;

void EngineInterfaceClass::PushCommandToChunk(QByteArray Command)
{
  CommonBuffer.append(Command);

  if(CommonBuffer.size() >= Command.size()*3)
  {
      KLPInterface->WriteCommandData(CommonBuffer,EngineChannelNumber);
      CommonBuffer.clear(); CommonBuffer.resize(0);
  }
}


void ControlEngineCommand::SetPosAngle(float X_Rad, float Y_Rad)
{
	if (X_Rad < 0.003)
		this->Pos_X_Angle = X_Rad;
	else
		this->Pos_X_Angle = 0.003;

	if (Y_Rad < 0.003)
		this->Pos_Y_Angle = Y_Rad;
	else
		this->Pos_Y_Angle = 0.003;
}

EngineInterfaceClass::EngineInterfaceClass(KLPInterfaceClass* KLP, quint32 MessageID, quint32 DeviceID)
{
	this->KLPInterface = KLP;
	this->EngineState.FC_HEADER.MessageId = MessageID;
	this->EngineState.FC_HEADER.DeviceID = DeviceID;
		this->ControlCoord= QPair<double,double>(0,0);
	this->StateBlock = BlockAtWork;
}


EngineInterfaceClass::~EngineInterfaceClass()
{
}




void EngineInterfaceClass::SetCoord(QPair<double, double> Coord)
{

	if (this->StateBlock == BlockDisable)
		return;

         //qDebug() << "Engine input coord -" << Coord.first*(180/M_PI)*60*60 << Coord.second*(180/M_PI)*60*60;


	    if(HorizontalAxisOn)
		this->ControlCoord.first += Coord.first;

		if(VerticalAxisOn)
		this->ControlCoord.second += Coord.second;

		if (abs(ControlCoord.first) > 0.004)
			ControlCoord.first = (ControlCoord.first / abs(ControlCoord.first)) * 0.004;

		if (abs(ControlCoord.second) > 0.004)
			ControlCoord.second = (ControlCoord.second / abs(ControlCoord.second)) * 0.004;

	EngineState.SetPosAngle(ControlCoord.second, ControlCoord.first);

	QByteArray Command;
	QDataStream out(&Command, QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::LittleEndian);

	out << EngineState;

	QByteArray DataRS = Command.mid(16 + 8);

	quint8 CRC = 0;

	boost::crc_basic<8>  crc_ccitt1(0xD5, 0xFF, 0, false, false);
	crc_ccitt1.process_bytes((const void*)DataRS.data(), DataRS.size());
	CRC = crc_ccitt1.checksum();

	out << CRC;

	if(KLPInterface)
    {
        QThread::usleep(this->CommandDelayMks);
        this->KLPInterface->WriteCommandData(Command, this->EngineChannelNumber);
    }


}

void EngineInterfaceClass::SetCoordAbs(QPair<double,double> CoordAbs)
{
    ControlCoord = CoordAbs;
    EngineState.SetPosAngle(CoordAbs.second, CoordAbs.first);

    QByteArray Command;
    QDataStream out(&Command, QIODevice::WriteOnly);

    out.setByteOrder(QDataStream::LittleEndian);

    out << EngineState;

    QByteArray DataRS = Command.mid(16 + 8);

    quint8 CRC = 0;

    boost::crc_basic<8>  crc_ccitt1(0xD5, 0xFF, 0, false, false);
    crc_ccitt1.process_bytes((const void*)DataRS.data(), DataRS.size());
    CRC = crc_ccitt1.checksum();

    out << CRC;

    if(KLPInterface)
    {
        QThread::usleep(this->CommandDelayMks);
        this->KLPInterface->WriteCommandData(Command, this->EngineChannelNumber);
    }
}

void EngineInterfaceClass::SetToNull()
{

	EngineState.SetPosAngle(0,0);

	QByteArray Command;
	QDataStream out(&Command, QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::LittleEndian);

	out << EngineState;

	QByteArray DataRS = Command.mid(16 + 8);

	quint8 CRC = 0;

	// ��������� �������� CRC-CCITT
	boost::crc_basic<8>  crc_ccitt1(0xD5, 0xFF, 0, false, false);
	crc_ccitt1.process_bytes((const void*)DataRS.data(), DataRS.size());
	CRC = crc_ccitt1.checksum();

	out << CRC;

		this->ControlCoord.first = 0;
		this->ControlCoord.second = 0;

	if(KLPInterface)
    {
        QThread::usleep(350);
        this->KLPInterface->WriteCommandData(Command,this->EngineChannelNumber);
        QThread::usleep(350);
        this->KLPInterface->WriteCommandData(Command,this->EngineChannelNumber);
        QThread::usleep(350);
        this->KLPInterface->WriteCommandData(Command,this->EngineChannelNumber);
    }
}

void EngineInterfaceClass::ResetEngine()
{

	QByteArray WriteCommand;
	ResetCommandCommutator SendCommand;
	SendCommand.FC_HEADER.DeviceID = EngineState.FC_HEADER.DeviceID;
	SendCommand.FC_HEADER.MessageId = EngineState.FC_HEADER.MessageId;

              QDataStream out(&WriteCommand,QIODevice::WriteOnly);
              out.setByteOrder(QDataStream::LittleEndian);
              out << SendCommand;

		 OutFcChannelFlags fcChannels = this->EngineChannelNumber;
		 this->KLPInterface->WriteCommandData(WriteCommand, fcChannels);


}

QPair<double, double> EngineInterfaceClass::GetCoord()
{
	return ControlCoord;
}


void operator<<(QDataStream &out, ControlEngineCommand &SendCommand)
{
	out.setFloatingPointPrecision(QDataStream::SinglePrecision);
	out << SendCommand.FC_HEADER;

	out << quint64(0);

	out << SendCommand.Pos_X_DAC
		<< SendCommand.Pos_Y_DAC;


	out << SendCommand.Pos_X_Angle
		<< SendCommand.Pos_Y_Angle;

	out << SendCommand.ControlRegim;
}



void EngineInterfaceClass::RecieveEngineStatus(QDataStream& DataEngine)
{
	DataEngine >> Status_Engine;
}


void operator<<(QDataStream &out, ResetCommandEngine &SendPocket)
{

     out << SendPocket.FC_HEADER;


     out << quint64(0);
     out << SendPocket.HEADER.MessageID << SendPocket.HEADER.DeviceID << SendPocket.HEADER.LenghtData << SendPocket.HEADER.Reserv<<
     out << SendPocket.ResetRegim;
}


void operator>>(QDataStream &in, Status_EngineStruct &SendPocket)
{
	
	in.setFloatingPointPrecision(QDataStream::SinglePrecision);
	in >> SendPocket.RegimFlags
		>> SendPocket.StateFlags
		>> SendPocket.TempSensor1
		>> SendPocket.TempSensor2
		>> SendPocket.PosAngleX
		>> SendPocket.PosAngleY
		>> SendPocket.PosADC_X
		>> SendPocket.PosADC_Y
		>> SendPocket.ValueToDAC_X
		>> SendPocket.ValueToDAC_Y
		>> SendPocket.EdgeMinX
		>> SendPocket.EdgeMaxY
		>> SendPocket.EdgeMinY
		>> SendPocket.EdgeMaxY
		>> SendPocket.ABCDVersion;

	//qDebug() << "Pos - " << SendPocket.PosAngleX<<  SendPocket.PosAngleY << endl;
    //qDebug() << "Pos sec - " << SendPocket.PosAngleX*1000000.0/4.84<<  SendPocket.PosAngleY*1000000.0/4.84 << endl;
	//qDebug() << "ability - " << bin << SendPocket.StateFlags;
	//qDebug() << "Temp1 - " << SendPocket.TempSensor1 << endl;
	//qDebug() << "Temp2 - " << SendPocket.TempSensor2 << endl;
		/*<< "Pos ADC X - " << SendPocket.PosADC_X << endl
		<< "Pos ADC Y - " << SendPocket.PosADC_Y << endl
		<< "Min Max X " << SendPocket.EdgeMinX << SendPocket.EdgeMaxX << endl
		<< "Min Max Y " << SendPocket.EdgeMinY << SendPocket.EdgeMaxY << endl
		<< "Regim -  " << bin << SendPocket.RegimFlags << endl*/


}
