#include "CommonHeaders.h"
#include <mutex>
#include <qiodevice.h>
#include <qdir.h>
#include <QFileDialog>
#include <QFile>
#include <QTime>

#define TAG "[ KLP INTEFACE]" 
#include "KLPInterfaceClass.h"
void* KLPInterfaceClass::ReadDataBuffer1 = 0;
void* KLPInterfaceClass::ReadDataBuffer2 = 0;

void* KLPInterfaceClass::WriteDataBuffer1 = 0;
void* KLPInterfaceClass::WriteDataBuffer2 = 0;

std::shared_ptr<CameraInterfaceClass> KLPInterfaceClass::CameraInterface;
std::shared_ptr<EngineInterfaceClass> KLPInterfaceClass::EngineInterface1;
std::shared_ptr<EngineInterfaceClass> KLPInterfaceClass::EngineInterface2;
std::shared_ptr<EngineInterfaceClass> KLPInterfaceClass::EngineInterface3;


KLPInterfaceClass* KLPInterfaceClass::KLPInterface = 0;

std::mutex KLPInterfaceClass::interruptions_lock;
std::queue<InterruptData> KLPInterfaceClass::available_interruptions;
	
stateblocksenum KLPInterfaceClass::StateBlock = stateblocksenum::BlockDisable;

mppd_wrap* KLPInterfaceClass::CardModule = 0;
std::mutex StateReadMutex;

void KLPInterfaceClass::CardSoftReset()
{
	qDebug() << TAG << "CARD SOFT RESET";
}



KLPInterfaceClass::KLPInterfaceClass() 
{      
	this->StateBlock = BlockAtWork;

	this->InitialaizeInterface();

	std::thread interruptThread(this->RecieveInterruptionFunction,this->CardModule);
	std::thread performInterruptThread(this->PerformInterruptionFunction);
	interruptThread.detach();
	performInterruptThread.detach();

	KLPInterface = this;
	
	CameraInterface = std::shared_ptr<CameraInterfaceClass>(new CameraInterfaceClass(this));
	EngineInterface1 = std::shared_ptr<EngineInterfaceClass>(new EngineInterfaceClass(this,0xB0,0x0A));
        EngineInterface2 = std::shared_ptr<EngineInterfaceClass>(new EngineInterfaceClass(this,0xB0,0x100000A));
        EngineInterface3 = std::shared_ptr<EngineInterfaceClass>(new EngineInterfaceClass(this,0xB0,0x200000A));
}


void operator<<(QDataStream& out, Regim_CommutatorCommand& SendPocket)
{
	out << SendPocket.FC_HEADER;
	out << quint64(0);// Метка времени, не используется
	out << SendPocket.Regim << SendPocket.TTLSignal << SendPocket.ChannelsSupply << SendPocket.Reserv;
}

KLPInterfaceClass::~KLPInterfaceClass() 
{
    this->StateBlock = BlockDisable;
}
void KLPInterfaceClass::DeinitializeInterface()
{
    this->StateBlock = BlockDisable;
    qDebug() << TAG << "======================================";
                                  qDebug() << TAG << "DEINITALIZE KLP INTERFACE";
    CardModule->AbortGetResult(); qDebug() << TAG << "ABORT GET RESULT"; std::this_thread::sleep_for(std::chrono::milliseconds(50));
    CardModule->ResetCard();      qDebug() << TAG << "RESET CARD"; std::this_thread::sleep_for(std::chrono::milliseconds(50));
    CardModule->CloseDevice();    qDebug() << TAG << "CLOSE DEVICE"; std::this_thread::sleep_for(std::chrono::milliseconds(50));
    qDebug() << TAG << "======================================";
}

uint8_t KLPInterfaceClass::WriteCommandDataEx(QByteArray CommandData,OutFcChannelFlags FCChannel)
{
    if (WriteDataBuffer1 == 0 || WriteDataBuffer2 == 0) return 0;


    if(current_write_buffer)
        memcpy(WriteDataBuffer2, CommandData.data(), CommandData.size());
    else
        memcpy(WriteDataBuffer1, CommandData.data(), CommandData.size());

    uint16_t bufferSize = CommandData.size();

    dma_next_write_buffer_params2 out_channel_params;
    out_channel_params.channels = FCChannel;
    out_channel_params.buf_number = current_write_buffer;
    out_channel_params.length = bufferSize;
    out_channel_params.is_set_frame_header = 1;
    out_channel_params.frame_header.destinationId = 0x04;
    out_channel_params.frame_header.cs_Ctl = 0;
    out_channel_params.frame_header.r_Ctl = 0;
    out_channel_params.frame_header.sourceId = 0;

    uint8_t errorCode;
    errorCode = CardModule->DmaNextWriteBufferExt(out_channel_params);

    current_write_buffer = !current_write_buffer;

    if(errorCode)
        qDebug() << TAG << "WRITE COMMAND RESULT EX - " << Qt::hex << errorCode << " write buffer - " << current_write_buffer;


    return errorCode;
}


uint8_t KLPInterfaceClass::WriteCommandData(QByteArray CommandData, OutFcChannelFlags FCCHannel)
{

if (WriteDataBuffer1 == 0 || WriteDataBuffer2 == 0) return 0;


if(current_write_buffer) 
memcpy(WriteDataBuffer1, CommandData.data(), CommandData.size());
else
memcpy(WriteDataBuffer2, CommandData.data(), CommandData.size());

uint16_t bufferSize = CommandData.size();
uint8_t errorCode;
errorCode = CardModule->DmaNextWriteBuffer(current_write_buffer, bufferSize, FCCHannel);

current_write_buffer = !current_write_buffer;

if(errorCode)
qDebug() << TAG << "WRITE COMMAND RESULT - " << Qt::hex << errorCode << " write buffer - " << current_write_buffer;


return errorCode;
}

void KLPInterfaceClass::SetSateCommutator(Regim_CommutatorCommand State)
{
	QByteArray Command;
	QDataStream out(&Command, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::LittleEndian);
	out << State;

	this->WriteCommandData(Command,ChannelNone);
}


void operator<<(QDataStream &out, AsmHeader &HEADER)
{
	out << HEADER.MessageId << HEADER.DeviceID << HEADER.Reserv1 << HEADER.Reserv2;
}


void KLPInterfaceClass::InitialaizeInterface()
{
uint8_t error;
CardModule = new mppd_wrap();
CardModule->OpenDevice("/dev/mppd0");
CardModule->ResetCard();

error = CardModule->DMAOpenReadBuffers(&ReadDataBuffer1, &ReadDataBuffer2); qDebug() << TAG << "OPEN READ BUFFER - "<< Qt::hex << error;
error = CardModule->DMAOpenWriteBuffers(&WriteDataBuffer1, &WriteDataBuffer2); qDebug() << TAG << "OPEN WRITE BUFFER - "<< Qt::hex << error;

CardModule->DmaBufferFree(0);
CardModule->DmaBufferFree(1);

CreateVirtualChannel();
sPortStatus portStatus;

qDebug() << TAG << "=====================================================";
qDebug() << TAG << "KLP INTERFACE ";
qDebug() << TAG << "DEVICE OPEN - " << CardModule->IsOpen();
error = CardModule->GetPortState(Fc1,portStatus); qDebug() << TAG << "Port 1 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
error = CardModule->GetPortState(Fc2,portStatus); qDebug() << TAG << "Port 2 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
error = CardModule->GetPortState(Fc3,portStatus); qDebug() << TAG << "Port 3 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
error = CardModule->GetPortState(Fc4,portStatus); qDebug() << TAG << "Port 4 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
error = CardModule->GetPortState(Fc5,portStatus); qDebug() << TAG << "Port 5 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
error = CardModule->GetPortState(Fc6,portStatus); qDebug() << TAG << "Port 6 status - "<< portStatus.IsFcErrorDetected<< portStatus.IsFreqLocked << portStatus.ErrorCount << "ERROR - " << Qt::hex << error;
qDebug() << TAG << "=====================================================";
}
        //MOI_SUCCESS = 0x00,
        //MOI_NO_CARDS_FOUND = 0x01,
        //MOI_NO_CARDS_INIT = 0x02,
        //MOI_WINDRIVER_CLOSE_ERROR = 0x03,
        //MOI_MEMORY_WRITE_ERROR = 0x04,
        //MOI_CARD_IN_USE = 0x05,
        //MOI_TOO_BIG_BUFFER = 0x06,
        //MOI_TOO_SMALL_BUFFER = 0x07,
        //MOI_ERROR_SLOT_BUS_NUMBER = 0x08,
        //MOI_GET_INFO_ERROR = 0x09,
        //MOI_ERROR_CHANNEL = 0x0A,
        //MOI_DMA_NOT_ENOUGH_MEMORY = 0x0B,
        //MOI_MEMORY_READ_ERROR = 0x0C,
        //MOI_CAN_NOT_DISABLE_INTS = 0x0D,
        //MOI_CAN_NOT_OPEN_MEMORY_INTS = 0x0E,
        //MOI_INVALID_WRITE_SPACE = 0x0F,
        //MOI_WRONG_CALLBACK_ADDR = 0x10,
        //MOI_DMA_CAN_NOT_CLOSE = 0x11,
        //MOI_DIDNT_USE_DATA_TRANS = 0x12,
        //MOI_NOT_USE_FOR_READ_DATA = 0x13,
        //MOI_NOT_USE_FOR_WRITE_DATA = 0x14,
        //MOI_BUFFER_BIGGER = 0x15,
        //NO_INTERRUPT_FUNCTION = 0x16,
        //MOI_CAN_NOT_ENABLE_INTS = 0x17,
        //MOI_CAN_NOT_CLOSE_DEVICE = 0x18,
        //MOI_CAN_NOT_INIT_LIBRARY = 0x19,
        //MOI_NO_ACTIVE_SPACES = 0x1A,
        //MOI_PCIE_SCAN_ERROR = 0x1B,
        //MOI_CAN_NOT_OPEN_HANDLE = 0x1C,
        //MOI_NO_DEVS_VEND_ID = 0x1D,
        //MOI_TOO_MANY_DEVICES = 0x1E,
        //MOI_INVALID_INTERRUPT = 0x1F,
        //MOI_BUFFER_ALREADY_USED = 0x20,
        //MOI_ERROR_TWIN_READ = 0x21,
        //MOI_ERROR_TWIN_WRITE = 0x22,
        //MOI_ERROR_BUFFER_NUMBER = 0x23,
        //MOI_ERROR_DEPRECATED = 0x24,
        //MOI_DMA_INVALID_HANDLE = 0x25,
        //MOI_NOT_ALIGNED_BUFFER = 0x26,
        //MOI_SGDMA_NOT_INIT = 0x27,
        //MOI_SGDMA_NOT_END_PREV_TRANSACTION = 0x28,
        //MOI_DMA_INVALID_BUFFER_NUMBER = 0x29,
        //MOI_VIRTUAL_READ_CHANNELS_EMPTY = 0x2A,
        //MOI_VIRTUAL_READ_CHANNEL_DATA_SIZE_ERROR = 0x2B,
        //MOI_VIRTUAL_READ_CHANNEL_NOT_INIT = 0x2C,
        //MOI_OUTPUT_CHANNEL_NOT_INIT = 0x2D,




void KLPInterfaceClass::CreateVirtualChannel()
{
sVirtChannelsParamsInfo ImageChannel;
sVirtChannelsParamsInfo ImageChannelWindow;
sVirtChannelsParamsInfo StateCamera;
sVirtChannelsParamsInfo StateChannel;
sVirtChannelsParamsInfo StateChannelEngine;
sVirtChannelsParamsInfo StateChannelEngine2;
sVirtChannelsParamsInfo StateChannelEngine3;

ImageChannel.DeviceId = 0x04;
ImageChannel.MessageId = 0x51;
ImageChannel.StartAddress = 0x11000000;
ImageChannel.Length = 16777216;


ImageChannelWindow.DeviceId = 0x04;
ImageChannelWindow.MessageId = 0x52;
ImageChannelWindow.StartAddress = 0x13000000;
ImageChannelWindow.Length = 16777216;

StateChannel.DeviceId = 0x78;
StateChannel.MessageId = 0x05;
StateChannel.StartAddress = 0x14000000;
StateChannel.Length = 4096;

StateChannelEngine.DeviceId = 0x0A;
StateChannelEngine.MessageId = 0x05;
StateChannelEngine.StartAddress = 0x14001000;
StateChannelEngine.Length = 4096;

StateChannelEngine2.DeviceId = 0x100000A;
StateChannelEngine2.MessageId = 0x05;
StateChannelEngine2.StartAddress = 0x14002000;
StateChannelEngine2.Length = 4096;

StateChannelEngine3.DeviceId = 0x200000A;
StateChannelEngine3.MessageId = 0x05;
StateChannelEngine3.StartAddress = 0x14003000;
StateChannelEngine3.Length = 4096;

StateCamera.DeviceId = 0x04;
StateCamera.MessageId = 0x05;
StateCamera.StartAddress = 0x14004000;
StateCamera.Length = 4096;

sVirtChannelsParamsInfo channelsParams[7];
channelsParams[0] = ImageChannel;
channelsParams[1] = ImageChannelWindow;
channelsParams[2] = StateChannel;
channelsParams[3] = StateChannelEngine;
channelsParams[4] = StateChannelEngine2;
channelsParams[5] = StateChannelEngine3;
channelsParams[6] = StateCamera;


qDebug() << TAG << "=====================================================";
uint8_t error = 0;
error = CardModule->SetVirtualChannelsParams(channelsParams,7);
qDebug() << TAG << "SET VIRTUAL CHANNELS PARAM - " << error;
//error = CardModule->EnableReadVirtChannels(0b111111100000000000000000111111); qDebug() << TAG << "ENABLE READ VIRTCHANNELS" << error;
error = CardModule->EnableReadVirtChannels(0xFFFFFFFF);
qDebug() << TAG << "ENABLE READ VIRTCHANNELS" << error;
qDebug() << TAG << "=====================================================";
}



void operator>>(QDataStream &in, StatusCommutatorStruct &RecievePocket)
{

	in.setFloatingPointPrecision(QDataStream::SinglePrecision);
	in >> RecievePocket.StateController
		>> RecievePocket.TempSensorState
		>> RecievePocket.Temeperature1
		>> RecievePocket.Temeperature2
		>> RecievePocket.Temeperature3
		>> RecievePocket.Temeperature4
		>> RecievePocket.Temeperature5
		>> RecievePocket.Temeperature7
		>> RecievePocket.Temeperature8
		>> RecievePocket.Temeperature9

		>> RecievePocket.SignalTTLIn
		>> RecievePocket.SignalTTLOut

		>> RecievePocket.PowerSupplyChannels
		>> RecievePocket.Reserv

		>> RecievePocket.WeTemp1
		>> RecievePocket.WePresure1
		>> RecievePocket.WeHumidity1

		>> RecievePocket.WeTemp2
		>> RecievePocket.WePresure2
		>> RecievePocket.WeHumidity2

		>> RecievePocket.FC1Params
		>> RecievePocket.FC2Params

		>> RecievePocket.ABCDVersion;

	bool ErrorFC1 = (RecievePocket.FC1Params >> 2) & 1;
	bool ErrorFC2 = (RecievePocket.FC2Params >> 2) & 1;

	bool CRCError = (RecievePocket.FC1Params >> 3) & 1;
	quint8 CRCCountError = (RecievePocket.FC1Params >> 12) & 7;

	bool CRCError2 = (RecievePocket.FC2Params >> 3) & 1;
	quint8 CRCCountError2 = (RecievePocket.FC2Params >> 12) & 7;

//	qDebug() << TAG << "=========================================================================";

   // qDebug() << TAG << "CONTROLLER STATUS - ";
   // qDebug() << TAG     << "PowerSupplyChannels - " << bin << RecievePocket.PowerSupplyChannels;
   // qDebug() << TAG     << "FC1 Param - " << bin << RecievePocket.FC1Params;
   // qDebug() << TAG     << "FC2 Param - " << bin << RecievePocket.FC2Params;

//  qDebug() << TAG << "---------WEATHER DATA ------- ";
//  qDebug() << TAG << "TEMPERATURE1 - " << RecievePocket.WeTemp1;
//  qDebug() << TAG << "PRESURE    1 - " << RecievePocket.WePresure1;
//  qDebug() << TAG << "HUMIDITY   1 - " << RecievePocket.WeHumidity1;
//  qDebug() << TAG << "---------------------------------------------";

//  qDebug() << TAG << "---------WEATHER DATA ------- ";
//  qDebug() << TAG << "TEMPERATURE2 - " << RecievePocket.WeTemp2;
//  qDebug() << TAG << "PRESURE    2 - " << RecievePocket.WePresure2;
//  qDebug() << TAG << "HUMIDITY   2 - " << RecievePocket.WeHumidity2;
//  qDebug() << TAG << "---------------------------------------------";

	if (ErrorFC1 || ErrorFC2)
		//qDebug() << TAG << "ERROR FC CHANNELS";

	if (CRCError || CRCError2)
	{
		//qDebug() << "CRC Error FC1 - " << CRCError << endl
			//<< "          FC2 - " << CRCError2 << endl
			//<< "count FC1     -" << CRCCountError << endl
			//<< "count FC2     - " << CRCCountError2;

	}

}

void operator<<(QDataStream &out, ResetCommandCommutator &SendPocket)
{
     //out.setByteOrder(QDataStream::BigEndian);
     out << SendPocket.FC_HEADER;
     //out.setByteOrder(QDataStream::LittleEndian);
     out << quint64(0);// Метка времени, не используется
     out << SendPocket.ResetRegim;
}

void operator<<(QDataStream &out, StatusRequestCommutator &SendPocket)
{
     //out.setByteOrder(QDataStream::BigEndian);
     out << SendPocket.FC_HEADER;
     //out.setByteOrder(QDataStream::LittleEndian);
     out << quint64(0);// Метка времени, не используется
     out << SendPocket.ReqFrequency;
     out << SendPocket.Param;
}


void KLPInterfaceClass::StatusRequest()
{
	StatusRequestCommutator SendCommand;
	QByteArray WriteCommand;

	QDataStream out(&WriteCommand,QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::LittleEndian);

	out << SendCommand;

	qDebug() << TAG << "Status request freq - " << SendCommand.ReqFrequency;

	OutFcChannelFlags fcChannels = ChannelNone;
	this->WriteCommandData(WriteCommand, fcChannels);
}
void KLPInterfaceClass::ResetCommutator()
{
	ResetCommandCommutator SendCommand;
	QByteArray WriteCommand;

	QDataStream out(&WriteCommand,QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::LittleEndian);

	out << SendCommand;

	OutFcChannelFlags fcChannels = ChannelNone;
	this->WriteCommandData(WriteCommand, fcChannels);
}


void KLPInterfaceClass::append_new_interruption(InterruptData interrupt)
{
   interruptions_lock.lock();
   available_interruptions.push(interrupt);
   interruptions_lock.unlock();
}

InterruptData KLPInterfaceClass::get_new_interruption()
{
   InterruptData new_interruption; new_interruption.ReadDataSize = 0;

   interruptions_lock.lock();
   if(available_interruptions.size() > 0)
   {
       new_interruption = available_interruptions.front(); available_interruptions.pop();
   };

   interruptions_lock.unlock();

   return new_interruption;
}


using namespace std;
void KLPInterfaceClass::RecieveInterruptionFunction(mppd_wrap* KLPCardHandler)
{
  qDebug() << TAG << "RECIEVE INTERRUPTION FUNCTION THREAD START ";
  InterruptData NewInterrupt;
  while(KLPInterfaceClass::StateBlock == BlockAtWork)
  {
     KLPCardHandler->GetInterruptData(NewInterrupt);

     if(NewInterrupt.DmaReadEnd)
     	append_new_interruption(NewInterrupt);

     if(NewInterrupt.Error)
	 qDebug() << TAG << "Error interruption from KLP" << Qt::hex << NewInterrupt.Error;
  }
  qDebug() << TAG << "REC INTERRUPT THREAD END";
  return;
}

void   KLPInterfaceClass::PerformInterruptionFunction()
{
    qDebug() << TAG << "PERF INTERRUPTION FUNCTION THREAD START ";
    while(KLPInterfaceClass::StateBlock == BlockAtWork)
    {
        // Обработка поступивших данных с модуля
        InterruptData interrupt = get_new_interruption();

        //std::this_thread::sleep_for(chrono::milliseconds(500)); qDebug() << "INT COUNT"<< KLPInterfaceClass::available_interruptions.size()
        //                                                                           << "ID -     " << interrupt.DeviceId;
        if (interrupt.ReadDataSize == 0) continue;
        if (ReadDataBuffer1 == 0) continue;

        void* DataBuffer = 0;
        // Выбор следующего буфера
        if (interrupt.ReadBufferNumber == 0){ DataBuffer = ReadDataBuffer1;};
        if (interrupt.ReadBufferNumber == 1){ DataBuffer = ReadDataBuffer2;};

        HEADER_ASM_STRUCT HEADER_ASM; FRAME_STRUCT FRAME;

        QByteArray data((const char*)DataBuffer, 16);
        QDataStream in_stream(data);

        in_stream >> HEADER_ASM;

        if (HEADER_ASM.Message_ID == 0x52000000)
        {

            ImageStruct newImage = KLPInterface->CameraInterface->GetNewImage();
            //==============================================================
            auto NewTimePoint = std::chrono::high_resolution_clock::now();
            CameraInterface->PeriodROI = std::chrono::duration<double>((NewTimePoint - CameraInterface->LastTimePointROI)).count()*1000;
            CameraInterface->LastTimePointROI = NewTimePoint;
            //==============================================================
            QByteArray info_data((const char*)DataBuffer, 2024);
            info_data.remove(0, 16);
            QDataStream in_stream2(info_data);
            in_stream2.setByteOrder(QDataStream::LittleEndian);


            in_stream2 >> FRAME.TIME_STAMP;
            in_stream2 >> FRAME.FILE_HEADER;
            in_stream2 >> FRAME.INFO_HEADER;
            in_stream2 >> FRAME.CAMERA_PARAM;
            uchar* ROIImage = (uchar*)DataBuffer + FRAME.FILE_HEADER.ByteImageOffset + 24;

            CameraInterface->RecieveNewImage(ROIImage, FRAME);
        }


        if (HEADER_ASM.Message_ID == 0x51000000)
        {
            QByteArray info_data((const char*)DataBuffer, 2024);
            info_data.remove(0, 16);
            QDataStream in_stream2(info_data);
            in_stream2.setByteOrder(QDataStream::LittleEndian);

            in_stream2 >> FRAME.TIME_STAMP;
            in_stream2 >> FRAME.FILE_HEADER;
            in_stream2 >> FRAME.INFO_HEADER;
            in_stream2 >> FRAME.CAMERA_PARAM;

            uchar* FullROIImage = (uchar*)DataBuffer + FRAME.FILE_HEADER.ByteImageOffset + 24;

            CameraInterface->RecieveNewImage(FullROIImage, FRAME);

            //==============================================================
            auto NewTimePoint = std::chrono::high_resolution_clock::now();
            CameraInterface->PeriodFULL = std::chrono::duration<double>((NewTimePoint - CameraInterface->LastTimePointFULL)).count()*1000;
            CameraInterface->LastTimePointFULL = NewTimePoint;
            //==============================================================
        }
        if (HEADER_ASM.Message_ID == 0x5000000)
        {
            //qDebug() << TAG << "STATUS TO DEVICE REC - "<< Qt::hex << HEADER_ASM.Device_ID;
            QByteArray info_data((const char*)DataBuffer, 56 + 8);
            info_data.remove(0, 16);

            QDataStream in_stream2(info_data);
            in_stream2.setByteOrder(QDataStream::LittleEndian);

            in_stream2 >> FRAME.TIME_STAMP;

            if (HEADER_ASM.Device_ID == 0x78000000)
            {
                const std::lock_guard<std::mutex> lock(StateReadMutex);
                in_stream2 >> KLPInterface->DevicesState;
            }

            if (HEADER_ASM.Device_ID == 0x0A000000)
                in_stream2>>EngineInterface1->Status_Engine;

            if (HEADER_ASM.Device_ID == 0x0A000001)
                in_stream2>>EngineInterface2->Status_Engine;

            if (HEADER_ASM.Device_ID == 0x0A000002)
                in_stream2>>EngineInterface3->Status_Engine;

            if (HEADER_ASM.Device_ID == 0x04000000)
            {
                //CameraInterface->RecieveStatusCamera(in_stream);
            }

        }

        KLPInterfaceClass::CardModule->DmaBufferFree(interrupt.ReadBufferNumber);

    }
    qDebug() << TAG << "PERF INTERRUPT THREAD END DEINITIALIZE KLP INTERFACE";
    return;
}

DataWeatherStructure KLPInterfaceClass::GetWheatherState()
{
    const std::lock_guard<std::mutex> lock(StateReadMutex);
    DataWeatherStructure Data;
    Data.Humidity1 = DevicesState.WeHumidity1; Data.Humidity2 = DevicesState.WeHumidity2;
    Data.Presure1  = DevicesState.WePresure1;  Data.Presure2  = DevicesState.WePresure2;
    Data.Temp1     = DevicesState.WeTemp1;     Data.Temp2     = DevicesState.WeTemp2;
    return Data;
   
}
