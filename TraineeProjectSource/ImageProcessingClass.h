//	����� ��� ��������� ����������� � ��������� ��������� ����� ���������
#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "ImageStruct.h"
#include "DataImageProcStructure.h"
#include "CameraInterfaceClass.h"


#include <math.h>
#include <functional>
#include <opencv2/opencv.hpp>
#include <QQueue>


struct ROI_Coord
{
	QPair<int, int> Position;
	int Width;
	int Height;
};

struct PIXEL_WORD_BIT
{
	quint16 pixel1 : 10;
	quint16 pixel2 : 10;
	quint16 pixel3 : 10;
	quint16 pixel4 : 10;
};

class PIXEL_WORD
{
public:

	PIXEL_WORD(uchar *ImageMass);
	PIXEL_WORD(PIXEL_WORD& Pixels);



	quint8 x1;
	quint8 x2;
	quint8 x3;
	quint8 x4;
	quint8 x5;


	quint8 MassByte[5];
	quint8 MassPixels[8];


	PIXEL_WORD_BIT* PIXELS_10BIT;

	quint16 pixel1;
	quint16 pixel2;
	quint16 pixel3;
	quint16 pixel4;

	uchar* Image;

	void NewLine();
	void NewLine_on_N_shift(int on_N_pixel);   //MVZ

	PIXEL_WORD &operator++();
	void friend operator>>(QDataStream& in_stream, PIXEL_WORD& FourPixels);

};
class Statistic
{
public:
	Statistic(const Statistic& Stat) { this->Size = Stat.Size;};
	Statistic() { Size = 10;};
	Statistic(int WindowSize) { Size = WindowSize;};



	QQueue<QPair<double, double>> CoordMassive;
	QQueue<double> ValueMassive;

	double MinValue = 0;
	double MaxValue = 0;
	double AvarageValue = 0;
	double DispersionValue = 0;

	int Size = 10;
	QPair<double, double> AvarageCoord;
	QPair<double, double> SKOCoord;
	QPair<double, double> DispersionCoord;
	int Counter = 0;

	void CalcDispersion();

	void Reset();
	bool IsValueLoaded() { if (ValueMassive.size() == Size) { return true; } else { return false; } };
	bool IsCoordLoaded() { if (CoordMassive.size() == Size) { return true; } else { return false; } };



	friend void operator>>(double NewValue, Statistic& StatObj)
	{
		if (StatObj.MinValue > NewValue)
			StatObj.MinValue = NewValue;
		if (StatObj.MaxValue < NewValue)
			StatObj.MaxValue = NewValue;

		if (StatObj.MinValue == 0)
			StatObj.MinValue = NewValue;


			StatObj.AvarageValue = StatObj.AvarageValue + NewValue / StatObj.Size;

		if (StatObj.IsValueLoaded())
			StatObj.AvarageValue = StatObj.AvarageValue - StatObj.ValueMassive.dequeue() / StatObj.Size;


		StatObj.ValueMassive.enqueue(NewValue);
	};


	friend void operator>>(QPair<double, double> NewValue, Statistic& StatObj)
	{

		if (StatObj.IsCoordLoaded())
		{
		QPair<double,double> FirstValue =  StatObj.CoordMassive.dequeue();

		StatObj.AvarageCoord.first -= FirstValue.first/StatObj.Size;
		StatObj.AvarageCoord.second -= FirstValue.second/StatObj.Size;

		}

		// accumulate coord measure, calc Avarage and Dispersion, accumulate coord that more then 10% of MinValue, Value - Sum of pixels, or luminosity
		StatObj.CoordMassive.enqueue(NewValue);

		StatObj.AvarageCoord.first += NewValue.first/StatObj.Size;
		StatObj.AvarageCoord.second += NewValue.second/StatObj.Size;

		StatObj.Counter++; // Dispersion calcs every size values
		if (StatObj.IsCoordLoaded())
		{
			if (StatObj.Counter >= StatObj.Size)
			{
		     StatObj.CalcDispersion();
			 StatObj.Counter = 0;
			}
		}
	};



	//QPair<double, double> GetAvarageCoord();
	//QPair<double, double> GetDispersionCoord();

	void SetSize(int SizeStat){ this->Size = SizeStat;};

};

class OptimizationThreshold
{
public:
	OptimizationThreshold(); 
	std::vector<Statistic> Statistics;
	std::vector<int> ThresholdVector = {150,200,250,300,350,400,450,500,550,600,650,700,750};
	std::vector<double> CoordDispersionResults;
	std::vector<double> LuminosityResults;

	double pixel_sum_minimum_dispersion;
	int BestThreshold = 150;

	void AccumulateImageStatistics(cv::Mat& Image);
	void FindThreshold(cv::Mat& Image);
	double FindPixelsSum(cv::Mat& Image,int Threshold);
	int CheckLuminosityOffset(double pixel_sum);
	void CalcSumLD(int Number, int Threshold, cv::Mat& Image);
	void CalcSumForAllThreshold(cv::Mat& Image);
	void Reset();
	std::function<void(int,int,cv::Mat&)> CalcSumLoadStat;

	
	friend OptimizationThreshold& operator>>(cv::Mat& Image,OptimizationThreshold& Optimizator);
	void friend operator>>(OptimizationThreshold& Optimizator, int& ValueReceiver) { if (Optimizator.IsStatisticLoaded()) { ValueReceiver = Optimizator.BestThreshold;} else ValueReceiver = ValueReceiver; }

	bool IsStatisticLoaded() { return (Statistics.back().IsCoordLoaded()); };
};



class Processor : public QObject
{
	Q_OBJECT

public:
	Processor(int OffsetImage);
	~Processor();

	typeblocksenum TypeBlock = typeblocksenum::ImageProcBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
	AimingStateEnum AimingState = AimingStateEnum::SpotNoFoundState;
	int NumberChannel = 1;
	int ROI_MODE = 1;
	//==================================================
	OptimizationThreshold ThresholdOptimizator;

	void ResetAiming();
	void ResizeProcessStrob(int X_SIZE,int Y_SIZE);
	void ProcessImage(uchar* ImageToProcess,int width,int height);
	void SwitchToAimingInStrob();
	void SwitchToAimingInFullImage();
	void SwitchToFindSpotInFullImage();

	void Binarization(cv::Mat& Image, int Threshold);

	DataImageProcStructure GetImageToDisplay();
	friend void operator>>(ImageStruct& Image, Processor& Proc);

	//==================================================
	QPair<double,double> spot_coord_abs;
	QPair<int,int> strob_coord;
	double x_pos_spot_in_strob = 128; //strob in full image
	double y_pos_spot_in_strob = 128;

	cv::Rect roi_rect_in_strob = cv::Rect(1, 1, 255, 255);
	double x_pos_spot_in_roi = 0; // roi in strob
	double y_pos_spot_in_roi = 0; 

	bool FlagSpotFound = false;
	bool FlagThresholdAutoControl = true;
	bool FlagDisplayNewImage = true;

	//==================================================
	Statistic StatProcessor;
	double AvarageBackground = 150;
	int Threshold;
	double FrameFilterProcentage = 0.9;
private:
	std::function<void(uchar*,int widht,int height)> ProcessImagePoly;
	cv::Mat GetStrobFromRowImage(PIXEL_WORD NEW_PIXELS,int Width,int Height,int FullImageWidth);

	std::function<void(const uint16_t * Image, size_t width, size_t height, uint16_t * FilteredImage, int FilterWidth)> MedianFilterFunction;
	//==================================================
	cv::Mat StrobImage;        //strob image from full image
	cv::Mat StrobImageFiltered;
	cv::Mat StrobImageCopy;    //copy strob image to display

	cv::Mat ROIImage;
	cv::Mat ROIImageFiltered;  //ROI Image in strob image

	cv::Mat ProcessingImage;

	int Offset = 0;
	int strob_width = 256;
	int strob_height = 256;
	//==================================================
};

class ImageProcessingClass :public QObject
{
	Q_OBJECT
public:
	ImageProcessingClass(QObject* parent = 0);
	~ImageProcessingClass();


	typeblocksenum TypeBlock = typeblocksenum::ImageProcBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;

	QPair<double, double>  GetLastCoordChannel(int Channel);
	QVector<QPair<double, double>> GetCoordsToDisplay(int Channel);
	Processor* GetProcessor(int Channel);
	DataImageProcAllChannels GetDataAllChannels();


	int Sin_Count = 0;//to delete

    std::chrono::time_point<std::chrono::high_resolution_clock> LastTimePoint;
	double PeriodImagePerform = 0;
	double PeriodImageReceive = 0;


	friend ImageProcessingClass& operator>>(ImageStruct& Image, ImageProcessingClass &ImageProcessor);
	void operator>>(CameraInterfaceClass &Camera);
	void PerformImage(ImageStruct Image);

	ROI_Channels_Command GetROI();
	bool FLAG_ROI_MOVE = false;

	Processor* Proc1;
	Processor* Proc2;
	Processor* Proc3;
	Processor* ProcToPointer;

	QVector<Processor*> Processors;

    
};

