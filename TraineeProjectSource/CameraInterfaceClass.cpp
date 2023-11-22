//��������� ������, ���������� ����������� � ������ 
#include "CommonHeaders.h"
#include "KLPInterfaceClass.h"
#include "CameraInterfaceClass.h"
#include <QThread>
#include <QTime>

#define FULL_IMAGE_HEIGHT_ROI 512
#define FULL_IMAGE_WIDTH_ROI 2048

#define FULL_IMAGE_HEIGHT 2048
#define FULL_IMAGE_WIDTH 2048

#define ROI_HEIGHT 256
#define ROI_WIDTH  1024
//********************************************************************************************************************

uchar* CameraInterfaceClass::ImageBufferFull = 0;
uchar* CameraInterfaceClass::ImageBufferROI  = 0;   
uchar* CameraInterfaceClass::ImageBufferROI2  = 0;   
uchar* CameraInterfaceClass::ImageBufferFullROI = 0;
uchar* CameraInterfaceClass::ImageBufferFullROI2 = 0;

void ROI_Channels_Command::SetSizeROI(int width, int height)
{
	this->W1 = width;
	this->W2 = width;
	this->W3 = width;
	this->W4 = width;
	
	this->H1 = height;
	this->H2 = height;
	this->H3 = height;
	this->H4 = height;
}

CameraInterfaceClass::CameraInterfaceClass(KLPInterfaceClass* KLPPointer,QObject* parent)
{
	
 std::chrono::time_point<std::chrono::high_resolution_clock> LastTimePoint;
 ImageBufferFull       = new uchar[int(FULL_IMAGE_HEIGHT*FULL_IMAGE_WIDTH*1.25)];
 ImageBufferFullROI       = new uchar[int(FULL_IMAGE_HEIGHT_ROI*FULL_IMAGE_HEIGHT*1.25)];
 ImageBufferFullROI2       = new uchar[int(FULL_IMAGE_HEIGHT_ROI*FULL_IMAGE_HEIGHT*1.25)];
 FULL_ROI_Buffers.push_back(ImageBufferFullROI);
 FULL_ROI_Buffers.push_back(ImageBufferFullROI2);


 ImageBufferROI       = new uchar[int(ROI_HEIGHT*ROI_WIDTH*1.25)];
 ImageBufferROI2       = new uchar[int(ROI_HEIGHT*ROI_WIDTH*1.25)];
 ROI_Buffers.push_back(ImageBufferROI);
 ROI_Buffers.push_back(ImageBufferROI2);


	this->StateBlock = BlockAtWork;

 this->KLPInterface = KLPPointer;
}
//********************************************************************************************************************

//********************************************************************************************************************
CameraInterfaceClass::~CameraInterfaceClass(void)
{
	//qDebug() << "DESTRUCT CAMERA INTERFACE CLASS";

	delete ImageBufferFull;
	delete ImageBufferROI;
	delete ImageBufferFullROI;

	delete ImageBufferROI2;
	delete ImageBufferFullROI2;

	//qDebug() << "IMAGE BUFFER DELETED";

}




ImageStruct CameraInterfaceClass::GetNewImage()
{
	return NewImageData;
}

//	enum MoiErrorCodes
//	{
//		MOI_SUCCESS = 0x00,
//		MOI_NO_CARDS_FOUND = 0x01,
//		MOI_NO_CARDS_INIT = 0x02,
//		MOI_WINDRIVER_CLOSE_ERROR = 0x03,
//		MOI_MEMORY_WRITE_ERROR = 0x04,
//		MOI_CARD_IN_USE = 0x05,
//		MOI_TOO_BIG_BUFFER = 0x06,
//		MOI_TOO_SMALL_BUFFER = 0x07,
//		MOI_ERROR_SLOT_BUS_NUMBER = 0x08,
//		MOI_GET_INFO_ERROR = 0x09,
//		MOI_ERROR_CHANNEL = 0x0A,
//		MOI_DMA_NOT_ENOUGH_MEMORY = 0x0B,
//		MOI_MEMORY_READ_ERROR = 0x0C,
//		MOI_CAN_NOT_DISABLE_INTS = 0x0D,
//		MOI_CAN_NOT_OPEN_MEMORY_INTS = 0x0E,
//		MOI_INVALID_WRITE_SPACE = 0x0F,
//		MOI_WRONG_CALLBACK_ADDR = 0x10,
//		MOI_DMA_CAN_NOT_CLOSE = 0x11,
//		MOI_DIDNT_USE_DATA_TRANS = 0x12,
//		MOI_NOT_USE_FOR_READ_DATA = 0x13,
//		MOI_NOT_USE_FOR_WRITE_DATA = 0x14,
//		MOI_BUFFER_BIGGER = 0x15,
//		NO_INTERRUPT_FUNCTION = 0x16,
//		MOI_CAN_NOT_ENABLE_INTS = 0x17,
//		MOI_CAN_NOT_CLOSE_DEVICE = 0x18,
//		MOI_CAN_NOT_INIT_LIBRARY = 0x19,
//		MOI_NO_ACTIVE_SPACES = 0x1A,
//		MOI_PCIE_SCAN_ERROR = 0x1B,
//		MOI_CAN_NOT_OPEN_HANDLE = 0x1C,
//		MOI_NO_DEVS_VEND_ID = 0x1D,
//		MOI_TOO_MANY_DEVICES = 0x1E,
//		MOI_INVALID_INTERRUPT = 0x1F,
//		MOI_BUFFER_ALREADY_USED = 0x20,
//		MOI_ERROR_TWIN_READ = 0x21,
//		MOI_ERROR_TWIN_WRITE = 0x22,
//		MOI_ERROR_BUFFER_NUMBER = 0x23,
//		MOI_ERROR_DEPRECATED = 0x24,
//		MOI_DMA_INVALID_HANDLE = 0x25,
//		MOI_NOT_ALIGNED_BUFFER = 0x26,	
//		MOI_SGDMA_NOT_INIT = 0x27,
//		MOI_SGDMA_NOT_END_PREV_TRANSACTION = 0x28,
//		MOI_DMA_INVALID_BUFFER_NUMBER = 0x29,
//		MOI_VIRTUAL_READ_CHANNELS_EMPTY = 0x2A,
//		MOI_VIRTUAL_READ_CHANNEL_DATA_SIZE_ERROR = 0x2B,
//		MOI_VIRTUAL_READ_CHANNEL_NOT_INIT = 0x2C,
//		MOI_OUTPUT_CHANNEL_NOT_INIT = 0x2D,
//	};	
bool CameraInterfaceClass::SetROI(ROI_Channels_Command ROI)
{

		qDebug() << "TRY to SET ROI 1 - " << POS_ROI.X1 << POS_ROI.Y1;
		qDebug() << "TRY to SET ROI 2 - " << POS_ROI.X2 << POS_ROI.Y1;
		qDebug() << "TRY to SET ROI 3 - " << POS_ROI.X3 << POS_ROI.Y1;
		qDebug() << "TRY to SET ROI 4 - " << POS_ROI.X4 << POS_ROI.Y1;

	if (this->POS_ROI.X1 > 2048 - 256 || this->POS_ROI.Y1 > 512 - 256)
		return false;
	if (this->POS_ROI.X2 > 2048 - 256 || this->POS_ROI.Y1 > 512 - 256)
		return false;
	if (this->POS_ROI.X3 > 2048 - 256 || this->POS_ROI.Y1 > 512 - 256)
		return false;
	if (this->POS_ROI.X4 > 2048 - 256 || this->POS_ROI.Y1 > 512 - 256)
		return false;


	if (abs(this->POS_ROI.Y1 != ROI.Y1)||
		abs(this->POS_ROI.X1 != ROI.X1)||
		abs(this->POS_ROI.X2 != ROI.X2)||
		abs(this->POS_ROI.X3 != ROI.X3))
	{
	this->POS_ROI = ROI;

	qDebug() << " ROI SET SUCCESS";
	QByteArray Command;
	QDataStream out(&Command, QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::LittleEndian);


	out << POS_ROI;

    KLPInterface->WriteCommandDataEx(Command, ChannelFc1);
	return true;
	}

	return false;
}


void CameraInterfaceClass::SendCommand(Control_Camera_Command SettingsCamera)
{

	QByteArray Command;
    QDataStream out1(&Command, QIODevice::WriteOnly);
    out1.setByteOrder(QDataStream::LittleEndian);

    out1 << SettingsCamera;

    KLPInterface->WriteCommandDataEx(Command, ChannelFc1);
}


DataCamerasStructure CameraInterfaceClass::GetState()
{

	DataCamerasStructure CamStateToDisplay;

	CamStateToDisplay.TypeBlock = this->TypeBlock;
	CamStateToDisplay.State = this->StateBlock;

	CamStateToDisplay.X1 = POS_ROI.X1;
    CamStateToDisplay.Y1 = POS_ROI.Y1;

	CamStateToDisplay.X2 = POS_ROI.X2;
    CamStateToDisplay.Y2 = POS_ROI.Y2;

	CamStateToDisplay.X3 = POS_ROI.X3;
    CamStateToDisplay.Y3 = POS_ROI.Y3;

	CamStateToDisplay.X4 = POS_ROI.X4;
    CamStateToDisplay.Y4 = POS_ROI.Y4;

	CamStateToDisplay.FramePeriodFULL = this->PeriodFULL;
	CamStateToDisplay.FramePeriodROI = this->PeriodROI;

	return CamStateToDisplay;
}





Control_Camera_Command::Control_Camera_Command()
{

	HEADER.DeviceID = 0x04;
	HEADER.MessageId = 0x06;
	HEADER.Length = sizeof(Control_Camera_Command)+sizeof(quint64);
}

void Control_Camera_Command::SetCommand(quint8 Command)
{
	this->CommandAndSizeImage |= Command;
	//qDebug() << "COMMAND - " << bin << this->CommandAndSizeImage;
}

void Control_Camera_Command::SetReadControl(quint32 Command)
{
	this->ReadParamControl = Command;


}

void Control_Camera_Command::SetSizeImage(quint32 Width, quint32 Height)
{
	Width <<= 8;
	Height <<= 20;
	this->CommandAndSizeImage |= Width;
	this->CommandAndSizeImage |= Height;

	//qDebug() << "COMMAND AND IMAGE SIZE - " << bin << this->CommandAndSizeImage;


}

void operator<<(QDataStream &out, Control_Camera_Command &CamParam)
{
	out << CamParam.HEADER;


	out << quint64(0);// ����� �������, �� ������������

	out << CamParam.CommandAndSizeImage
		<< CamParam.TimeExposure
		<< CamParam.AvarageBackground
		<< CamParam.reserve1
		<< CamParam.GainCTCControl
		<< CamParam.Gain
		<< CamParam.HeatControl
		<< CamParam.TimeExposure
		<< CamParam.IrisEnginePos
		<< CamParam.reserve2
		<< CamParam.reserve3
		<< CamParam.reserve4
		<< CamParam.reserve5
		<< CamParam.reserve6
		<< CamParam.reserve7
		<< CamParam.ReadParamControl
		<< CamParam.ImagePositionLeftTop
		<< CamParam.reserve8;

}

void operator<<(QDataStream &out, ROI_Channels_Command &ROIWindows)
{
	out << ROIWindows.HEADER;

	out << quint64(0);


	out << ROIWindows.X1 << ROIWindows.Y1 << ROIWindows.W1 << ROIWindows.H1;
	out << ROIWindows.X2 << ROIWindows.Y2 << ROIWindows.W2 << ROIWindows.H2;
	out << ROIWindows.X3 << ROIWindows.Y3 << ROIWindows.W3 << ROIWindows.H3;
	out << ROIWindows.X4 << ROIWindows.Y4 << ROIWindows.W4 << ROIWindows.H4;

}

void CameraInterfaceClass::SetState(stateblocksenum State)
{
	this->StateBlock = State;
}

void CameraInterfaceClass::RecieveNewImage(uchar *Image, FRAME_STRUCT FRAME)
{

	if (this->StateBlock == BlockDisable)
		return;



	if (FRAME.INFO_HEADER.Height == 512 && FRAME.INFO_HEADER.Width == 2048)
	{

		std::memcpy(FULL_ROI_Buffers[CurrentBufferROI_Full], Image, 2048 * 512 * 1.25);
		NewImageData.p_image = ImageBufferFullROI;
		NewImageData.x_size = 2048;
		NewImageData.y_size = 512;
		CurrentBufferROI_Full++; if (CurrentBufferROI_Full == 2) { CurrentBufferROI_Full = 0; };

	}

	if (FRAME.INFO_HEADER.Height == POS_ROI.H1 && FRAME.INFO_HEADER.Width == POS_ROI.W1*4)
	{
		std::memcpy(ROI_Buffers[CurrentBufferROI], Image, 1024 * 256 * 1.25);
		NewImageData.p_image = ImageBufferROI;
		NewImageData.x_size = 1024;
		NewImageData.y_size = 256;

		NewImageData.X1 = POS_ROI.X1;
		NewImageData.Y1 = POS_ROI.Y1;

		NewImageData.X2 = POS_ROI.X1;
		NewImageData.Y2 = POS_ROI.Y1;

		NewImageData.X3 = POS_ROI.X1;
		NewImageData.Y3 = POS_ROI.Y1;

		NewImageData.X4 = POS_ROI.X1;
		NewImageData.Y4 = POS_ROI.Y1;

		CurrentBufferROI++; if (CurrentBufferROI == 2) { CurrentBufferROI = 0; };
	}


	emit SignalRecieveNewFrame();
}



void operator>>(QDataStream &in_data_stream, HEADER_ASM_STRUCT &HEADER)
{
	in_data_stream >> HEADER.Message_ID >> HEADER.Device_ID >> HEADER.Reserve >> HEADER.Lenght;



	//if (HEADER.Message_ID != 0)
	//{
	//	//    qDebug() << "=====================================================================================";
	//	//    qDebug() << "FRAME MESSAGE - "<< hex << HEADER.Message_ID << HEADER.Device_ID << endl
	//	//             << "LENGHT DATA   - " <<bin<< HEADER.Lenght << dec << HEADER.Lenght;

	//	//    qDebug() << "=====================================================================================";
	//}
	HEADER.Lenght = HEADER.Lenght&HEADER.MaskForLenght;

}

void operator>>(QDataStream &in_data_stream, TIME_STAMP_STRUCT &TIME_STRUCT)
{
	in_data_stream >> TIME_STRUCT.TIME_SENDING_LITTLE >> TIME_STRUCT.TIME_SENDING_BIG;
}


void CameraInterfaceClass::RecieveStatusCamera(QDataStream& DataStatus)
{
	DataStatus >> StatusCamera;
}

QImage CameraInterfaceClass::GetFullImageToDisplay()
{
	return QImage();
}

void operator>>(QDataStream &in_data_stream, BITMAP_INFO_HEADER &HEADER)
{
	in_data_stream >> HEADER.Size >> HEADER.Width >> HEADER.Height >> HEADER.Planes >> HEADER.BitCount
		>> HEADER.Compression >> HEADER.SizeCompressImage
		>> HEADER.Reserve1 >> HEADER.Reserve2 >> HEADER.Reserve3 >> HEADER.Reserve4
		>> HEADER.FrameFrequency >> HEADER.CT >> HEADER.OppDetectorData >> HEADER.BitCountPix >> HEADER.BitSigPos >> HEADER.BytePerScrmb
		>> HEADER.PixPerScrmb >> HEADER.CI >> HEADER.PTN >> HEADER.PTN >> HEADER.PA
		>> HEADER.Reserv5
		>> HEADER.Reserv6
		>> HEADER.Reserv7
		>> HEADER.Reserv8;
	//qDebug() << "period - " << Widget::time.restart();

//	qDebug() << "=====================================================================================";
//	qDebug() << "WIDTH - "              << HEADER.Width << "HEIGHT - " << HEADER.Height << endl
//	         << "FREQ       - "   << HEADER.FrameFrequency << endl
//	         << "COMPRESSION    - " << HEADER.Compression;

//	qDebug() << "=====================================================================================";
}


void operator>>(QDataStream &in_data_stream, BITMAP_FILE_HEADER &HEADER)
{

	in_data_stream >> HEADER.TYPE_FRAME
		>> HEADER.Size
		>> HEADER.TimeStamp
		>> HEADER.TimeExposure
		>> HEADER.preFormat
		>> HEADER.ByteImageOffset;



}

void operator>>(QDataStream &in_data_stream, CAMERA_PARAM_STRUCT &CAMERA_PARAM)
{

	in_data_stream >> CAMERA_PARAM.Ang_PixSize_W
		>> CAMERA_PARAM.Ang_PixSize_H
		>> CAMERA_PARAM.OpticCenter_X
		>> CAMERA_PARAM.OpticCenter_Y


		>> CAMERA_PARAM.TransFieldOpPos
		>> CAMERA_PARAM.TransFocusPos


		>> CAMERA_PARAM.Distorsion_A
		>> CAMERA_PARAM.Distorsion_B
		>> CAMERA_PARAM.Distorsion_C
		>> CAMERA_PARAM.Distorsion_D

		>> CAMERA_PARAM.Distorsion_E
		>> CAMERA_PARAM.Distorsion_F
		>> CAMERA_PARAM.Distorsion_G
		>> CAMERA_PARAM.Distorsion_H


		>> CAMERA_PARAM.Revers_Distorsion_A
		>> CAMERA_PARAM.Revers_Distorsion_B
		>> CAMERA_PARAM.Revers_Distorsion_C
		>> CAMERA_PARAM.Revers_Distorsion_D

		>> CAMERA_PARAM.Revers_Distorsion_E
		>> CAMERA_PARAM.Revers_Distorsion_F
		>> CAMERA_PARAM.Revers_Distorsion_G
		>> CAMERA_PARAM.Revers_Distorsion_H


		>> CAMERA_PARAM.ResolutionW
		>> CAMERA_PARAM.ResolutionH
		>> CAMERA_PARAM.Temperature;
	//qDebug() << "CAMERA PARAM RESOLUTION - " << CAMERA_PARAM.ResolutionW << CAMERA_PARAM.ResolutionH <<"TEMPERATURE - " << CAMERA_PARAM.Temperature;
}


void operator>>(QDataStream &in_data_stream, Status_CameraStruct &StatusPocket)
{
	qDebug() << "STATUS CAMERA ==============================================================";
	in_data_stream >> StatusPocket.Status;
	in_data_stream >> StatusPocket.RegimDevice;
	in_data_stream >> StatusPocket.AvarageBackGround;
	in_data_stream >> StatusPocket.Reserve;
	in_data_stream >> StatusPocket.ParamCompensation;
	in_data_stream >> StatusPocket.CameraParam;
	in_data_stream >> StatusPocket.HeadStatus;
	in_data_stream >> StatusPocket.TimeExposure;
	in_data_stream >> StatusPocket.CamIdentificator;
	in_data_stream >> StatusPocket.ImageFormatX;
	in_data_stream >> StatusPocket.ImageFormatY;
	in_data_stream >> StatusPocket.Settings;
	in_data_stream >> StatusPocket.GainControl;
	in_data_stream >> StatusPocket.FrameRate;
	in_data_stream >> StatusPocket.ImageSensorTemperature;
	in_data_stream >> StatusPocket.PLICSensorTemperature;
	in_data_stream >> StatusPocket.FC1Param;
	in_data_stream >> StatusPocket.FC2Param;

	StatusPocket.CheckStatus(StatusPocket.Status);
	StatusPocket.CheckCamearaParam(StatusPocket.CameraParam);
	StatusPocket.CheckChannelState(StatusPocket.FC1Param, StatusPocket.FC2Param);

	qDebug() << "FRAME RATE    - " << StatusPocket.FrameRate << endl
		     << "TIME_EXPOSURE - " << StatusPocket.TimeExposure << endl
		     << "IMAGE FORMAT  - " << StatusPocket.ImageFormatX << StatusPocket.ImageFormatY << endl
	         << "BACKGROUD     - " << StatusPocket.AvarageBackGround << endl
	         << "REGIM         - " << StatusPocket.RegimDevice;


	qDebug() << "==============================================================";
}

void Status_CameraStruct::CheckStatus(quint8 Status)
{
	quint8 ModuleRegim = Status & 0x2;
	qDebug() << "Camera Regim - " << ModuleRegim;

	quint8 Norm = (Status >> 4) & 0x1;
	qDebug() << "Norm - " << Norm;

}

void Status_CameraStruct::CheckCamearaParam(quint8 Param)
{

	quint8 AutoExpose = (Param >> 7) & 0x1;
	qDebug() << "AutoExpose - " << AutoExpose;

}

void Status_CameraStruct::CheckChannelState(quint32 FC1, quint32 FC2)
{
	quint8 ErrorFind1 = (FC1 >> 3) & 0x1;
	quint8 ErrorFind2 = (FC2 >> 3) & 0x1;


	quint8 ErrorCRCFind1 = (FC1 >> 4) & 0x1;
	quint8 ErrorCRCFind2 = (FC2 >> 4) & 0x1;

	quint8 ErrorCounter1 = (FC1 >> 8) & 0xF;
	quint8 ErrorCounter2 = (FC2 >> 8) & 0xF;

	quint8 ErrorCounterCRC1 = (FC1 >> 12) & 0xF;
	quint8 ErrorCounterCRC2 = (FC2 >> 12) & 0xF;

	//qDebug() << "CHANNEL1 ERRORS FIND - " << ErrorFind1 << "CRC FIND - " << ErrorCRCFind1 << "COUNTER - " << ErrorCounter1 << "COUNTER CRC - " << ErrorCounterCRC1;
	//qDebug() << "CHANNEL2 ERRORS FIND - " << ErrorFind2 << "CRC FIND - " << ErrorCRCFind2 << "COUNTER - " << ErrorCounter2 << "COUNTER CRC - " << ErrorCounterCRC2;

}
