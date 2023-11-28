//��������� ������ , ���������� ���������� � ������ 
#ifndef CAMERAINTERFACECLASS_H
#define CAMERAINTERFACECLASS_H

#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageStruct.h"
#include "DataCamerasStructure.h"

#include "FC_STRUCTS.h"

#define READ_AUTOEXPOSE_ONOFF   0x1
#define READ_BAD_PIXEL_REPLACE  0x2
#define READ_FRAME_MODE         0x4
#define READ_IMAGE_FORMAT       0x8
#define READ_EXPOSE_PARAM       0x10
#define READ_AVARAGE_BACKGROUD  0x20
#define READ_NOISE_CORRETION    0x20000
#define READ_NIGHT_MODE         0x80000
#define READ_FRAME_OFFSET       0x400000

#define COMM_TEXT_INFO_ON           0x1
#define COMM_START_CALIBRATION      0x2
#define COMM_NOISE_CORRETION_ON     0x4
#define COMM_CURTAIN_ON             0x8
#define COMM_GET_SINGLE_FRAME       0x10
#define COMM_SINGLE_FRAME_ON        0x20
#define COMM_BAD_PIXEL_REPLACE_ON   0x40
#define COMM_AUTOEXPOSE_ON          0x80

class KLPInterfaceClass;
class Status_CameraStruct
{
public:
	quint8 Status;
	quint8 RegimDevice;
	quint16 AvarageBackGround;
	quint8 Reserve;
	quint8 ParamCompensation;
	quint8 CameraParam;
	quint8 HeadStatus;
	quint32 TimeExposure;
	quint16 CamIdentificator;
	quint16 ImageFormatX;
	quint16 ImageFormatY;
	quint8  Settings;
	quint8  GainControl;
	quint32 FrameRate;
	quint16 ImageSensorTemperature;
	quint16 PLICSensorTemperature;
	quint32 FC1Param;
	quint32 FC2Param;


	void CheckStatus(quint8 Status);
	void CheckCamearaParam(quint8 Param);
	void CheckChannelState(quint32 FC1, quint32 FC2);




	friend void operator>>(QDataStream& in_data_stream, Status_CameraStruct& StatusPocket);

};


class HEADER_ASM_STRUCT
{
public:
	quint32 Message_ID;
	quint32 Device_ID;



	quint32 Reserve;
	quint32 Lenght;

private:
	quint32 MaskForLenght = 0xFFFFFFFE;

	void friend operator>>(QDataStream& in_data_stream, HEADER_ASM_STRUCT& HEADER);

};


class TIME_STAMP_STRUCT
{
public:
	quint32 TIME_SENDING_LITTLE;
	quint32 TIME_SENDING_BIG;

	void friend operator>>(QDataStream& in_data_stream, TIME_STAMP_STRUCT& TIME_STRUCT);
};

class BITMAP_FILE_HEADER
{
public:
	quint16 TYPE_FRAME;
	quint32 Size;
	quint64 TimeStamp;
	quint32 TimeExposure;
	quint16 preFormat;
	quint32 ByteImageOffset;
	void friend operator>>(QDataStream& in_data_stream, BITMAP_FILE_HEADER& HEADER);
};


class BITMAP_INFO_HEADER
{
public:
	quint32 Size;
	quint32 Width;
	quint32 Height;
	quint16 Planes;
	quint16 BitCount;


	quint32 Compression;
	quint32 SizeCompressImage;

	quint32 Reserve1;
	quint32 Reserve2;
	quint32 Reserve3;
	quint32 Reserve4;

	quint32 FrameFrequency;
	quint32 CT;
	quint64 OppDetectorData;

	quint8 BitCountPix;
	quint8 BitSigPos;
	quint8 BytePerScrmb;
	quint8 PixPerScrmb;
	quint8 CI;
	quint8 PTN;
	quint8 PA;


	quint8  Reserv5;
	quint32 Reserv6;

	quint32 Reserv7;
	quint32 Reserv8;

	void friend operator>>(QDataStream& in_data_stream, BITMAP_INFO_HEADER& HEADER);
};

class CAMERA_PARAM_STRUCT
{
public:

	quint32 Ang_PixSize_W;
	quint32 Ang_PixSize_H;
	quint32 OpticCenter_X;
	quint32 OpticCenter_Y;


	quint16 TransFieldOpPos;
	quint16 TransFocusPos;


	quint32 Distorsion_A;
	quint32 Distorsion_B;
	quint32 Distorsion_C;
	quint32 Distorsion_D;

	quint32 Distorsion_E;
	quint32 Distorsion_F;
	quint32 Distorsion_G;
	quint32 Distorsion_H;


	quint32 Revers_Distorsion_A;
	quint32 Revers_Distorsion_B;
	quint32 Revers_Distorsion_C;
	quint32 Revers_Distorsion_D;

	quint32 Revers_Distorsion_E;
	quint32 Revers_Distorsion_F;
	quint32 Revers_Distorsion_G;
	quint32 Revers_Distorsion_H;


	quint32 ResolutionW;
	quint32 ResolutionH;
	quint32 Temperature;

	quint32 LenghtReserv = 804;

	void friend operator>>(QDataStream& in_data_stream, CAMERA_PARAM_STRUCT& CAMERA_PARAM);
};


class FRAME_STRUCT
{
public:
	BITMAP_FILE_HEADER FILE_HEADER;
	BITMAP_INFO_HEADER INFO_HEADER;
	CAMERA_PARAM_STRUCT CAMERA_PARAM;
	TIME_STAMP_STRUCT TIME_STAMP;

	quint32 NavDataPassLenght = 1024;
};




class Control_Camera_Command
{
public:
	Control_Camera_Command();




	void SetCommand(quint8 Command);
	void SetReadControl(quint32 Command);
	void SetSizeImage(quint32 Width, quint32 Height);

	AsmHeader HEADER;


	quint32 CommandAndSizeImage = 0;

	quint16 TimeExposure = 0;
	quint16 AvarageBackground = 0;

	//not use
	quint8 reserve1 = 0;
	quint8 GainCTCControl = 0;
	quint8 Gain = 0;
	quint8 HeatControl = 0;
	quint16 TimeExposureLaser = 0;
	quint16 IrisEnginePos = 0;

	quint8 reserve2 = 0;
	quint8 reserve3 = 0;
	quint8 reserve4 = 0;
	quint8 reserve5 = 0;

	quint32 reserve6 = 0;
	quint32 reserve7 = 0;
	////////////////////////////

	quint32 ReadParamControl = 0;

	quint32 ImagePositionLeftTop = 0;
	quint8 reserve8;



	void friend operator<<(QDataStream& out, Control_Camera_Command& CamParam);
};

class ROI_Channels_Command
{
public:

	ROI_Channels_Command()
	{
		HEADER.DeviceID = 0x04;
		HEADER.MessageId = 0x22;
		HEADER.Length = sizeof(ROI_Channels_Command)+sizeof(quint64)-16;

		//qDebug() << TAG << "HEADER LENGHT ROI PARAM - " << sizeof(ROI_Channels_Command)-16;
	}

	AsmHeader HEADER;


	quint16 X1 = 128;
	quint16 Y1 = 128;
	quint16 W1 = 256;
	quint16 H1 = 256;

	quint16 X2 = 512;
	quint16 Y2 = 128;
	quint16 W2 = 256;
	quint16 H2 = 256;

	quint16 X3 = 1024;
	quint16 Y3 = 128;
	quint16 W3 = 256;
	quint16 H3 = 256;

	quint16 X4 = 1536;
	quint16 Y4 = 128;
	quint16 W4 = 256;
	quint16 H4 = 256;

	//quint16 reserve = 0;

	void SetSizeROI(int width, int height);
	friend void operator<<(QDataStream& out, ROI_Channels_Command& ROIWindows);
};

class CameraInterfaceClass : public QObject
{
	Q_OBJECT

    public:
	typeblocksenum TypeBlock = typeblocksenum::CamerasControlBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;

		CameraInterfaceClass(KLPInterfaceClass* KLPPointer,QObject* parent = 0);
		~CameraInterfaceClass(void);
		void SetState(stateblocksenum State);

		bool SetROI(ROI_Channels_Command ROI_Channels); 
		void SendCommand(Control_Camera_Command SettingsCamera);


		DataCamerasStructure GetState();

		ImageStruct GetNewImage();
	
		ROI_Channels_Command POS_ROI;
		Control_Camera_Command CameraControlState;
		Status_CameraStruct StatusCamera;
		ImageStruct NewImageData;

		int CurrentBufferROI = 0;
		int CurrentBufferROI_Full = 0;
		std::vector<uchar*> ROI_Buffers;
		std::vector<uchar*> FULL_ROI_Buffers;
        std::chrono::time_point<std::chrono::high_resolution_clock> LastTimePointROI;
        std::chrono::time_point<std::chrono::high_resolution_clock> LastTimePointFULL;
		double PeriodFULL = 1.222;
		double PeriodROI = 1.222; 
		
static	uchar *ImageBufferFull;
static	uchar *ImageBufferROI;
static	uchar *ImageBufferROI2;

static	uchar *ImageBufferFullROI;
static	uchar *ImageBufferFullROI2;

    private:
		KLPInterfaceClass* KLPInterface = 0;

public:
	void RecieveNewImage(uchar *Image, FRAME_STRUCT FRAME);
	void RecieveStatusCamera(QDataStream& DataStatus);
	QImage GetFullImageToDisplay();

	signals:
		//������ ��������� ������ ����������� 
		void SignalRecieveNewFrame();		
};

#endif CAMERAINTERFACECLASS_H