//	����� ��� ��������� ����������� � ��������� ��������� ����� ���������
#include "stdafx.h"
#include "ImageProcessingClass.h"

void CopyDataToImage(PIXEL_WORD* Data)
{

}

void OptimizationThreshold::Reset()
{
	for (auto StatObj : Statistics)
		StatObj.Reset();

	CoordDispersionResults.clear();
	LuminosityResults.clear();

	pixel_sum_minimum_dispersion = 0;
}

OptimizationThreshold::OptimizationThreshold()
					{

					Statistics = std::vector<Statistic>(ThresholdVector.size(), Statistic(20));
					
					CoordDispersionResults = std::vector<double>(ThresholdVector.size());
					LuminosityResults = std::vector<double>(ThresholdVector.size());

						this->CalcSumLoadStat = [=](int Number, int Threshold, cv::Mat& Image)
						{
							double sum_x = 0.0, sum_y = 0.0, sum = 0.0;
							sum_x = 0.0, sum_y = 0.0, sum = 0.0;
							QPair<double, double> Coord;

							for (short row = 0; row < Image.rows; row++)
							{
								const unsigned short* RowData = Image.ptr<unsigned short>(row);
								for (short col = 0; col < Image.cols; col++)
								{
										if (RowData[col] > Threshold)
										{
											sum += 1;
											sum_x += col;
											sum_y += row;
										}
								}
							}

								Coord.first = sum_x / sum;
								Coord.second = sum_y / sum;

								sum >> this->Statistics[Number];
								Coord >> this->Statistics[Number];
						};


					
}
//double Statistic::AvarageBackground = 0;
ImageProcessingClass::ImageProcessingClass(QObject* parent) : QObject(parent)
{  

	this->StateBlock = BlockAtWork;
    
	Proc1 = new Processor(0);
	Proc2 = new Processor(320);
	Proc3 = new Processor(320 * 2);
	ProcToPointer = new Processor(0);

	Proc1->NumberChannel = 1; 
	Proc2->NumberChannel = 2; 
	Proc3->NumberChannel = 3; 
	ProcToPointer->NumberChannel = 4; 
	Processors.append(Proc1);
	Processors.append(Proc2);
	Processors.append(Proc3);
	Processors.append(ProcToPointer);

	Proc1->Threshold = 50;
	Proc2->Threshold = 100;
	Proc3->Threshold = 100;
	ProcToPointer->Threshold = 100;

	Proc1->strob_coord = QPair<double, double>(128, 64);
	Proc2->strob_coord = QPair<double, double>(640, 64);
	Proc3->strob_coord = QPair<double, double>(1152, 64);



} 

//*******************************************************************************************************************
ImageProcessingClass::~ImageProcessingClass()
{

}  
//************************************************************************************************

void ImageProcessingClass::operator>>(CameraInterfaceClass& Camera)
{
	 bool FLAG_ROI_MOVE = Camera.SetROI(this->GetROI());
	
}

//************************************************************************************************
void ImageProcessingClass::PerformImage(ImageStruct in_imageStruct)
{
	QFutureSynchronizer<void> synchronizer;
	if (in_imageStruct.x_size == 1024 && in_imageStruct.y_size == 256)
	{
			auto TimePointStart = std::chrono::high_resolution_clock::now();


		synchronizer.addFuture(QtConcurrent::run(this->Proc1, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		synchronizer.addFuture(QtConcurrent::run(this->Proc2, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		synchronizer.addFuture(QtConcurrent::run(this->Proc3, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));


			auto TimePointEnd = std::chrono::high_resolution_clock::now();
			PeriodImagePerform = std::chrono::duration<double>((TimePointStart - TimePointEnd)).count()*1000;
			PeriodImageReceive = std::chrono::duration<double>((TimePointEnd - LastTimePoint)).count()*1000;

			LastTimePoint = TimePointEnd;

			return;
	} 

	if (in_imageStruct.x_size == 2048 && in_imageStruct.y_size == 512)
	{
		if (this->Proc1->AimingState == AimingInFullImage && this->Proc2->AimingState == AimingInFullImage && this->Proc3->AimingState == AimingInFullImage)
		{
		synchronizer.addFuture(QtConcurrent::run(this->Proc1, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		synchronizer.addFuture(QtConcurrent::run(this->Proc2, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		synchronizer.addFuture(QtConcurrent::run(this->Proc3, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		synchronizer.addFuture(QtConcurrent::run(this->ProcToPointer, &Processor::ProcessImage, in_imageStruct.p_image,in_imageStruct.x_size,in_imageStruct.y_size));
		}
		else
		ProcToPointer->ProcessImage(in_imageStruct.p_image, in_imageStruct.x_size, in_imageStruct.y_size);
	}

}

ROI_Channels_Command ImageProcessingClass::GetROI()
{
	ROI_Channels_Command newROI_ToCamera;

	newROI_ToCamera.X1= this->Proc1->strob_coord.first;
	newROI_ToCamera.Y1= this->Proc1->strob_coord.second;

	newROI_ToCamera.X2= this->Proc2->strob_coord.first;
	newROI_ToCamera.Y2= this->Proc2->strob_coord.second;

	newROI_ToCamera.X3= this->Proc3->strob_coord.first;
	newROI_ToCamera.Y3= this->Proc3->strob_coord.second;



	newROI_ToCamera.SetSizeROI(256, 256);
	return newROI_ToCamera;

}

//************************************************************************************************

//************************************************************************************************

void operator>>(ImageStruct& Image, Processor& Proc)
{
	Proc.ProcessImage(Image.p_image,Image.x_size,Image.y_size);
}

//************************************************************************************************
ImageProcessingClass& operator>>(ImageStruct& Image, ImageProcessingClass& ImageProcessor)
{

	if (ImageProcessor.StateBlock == BlockAtWork)
	ImageProcessor.PerformImage(Image);



	return ImageProcessor;
}
//************************************************************************************************




QVector<QPair<double, double>> ImageProcessingClass::GetCoordsToDisplay(int Channel)
{

	QVector<QPair<double, double>> Coords;

		if (Channel == 1)
		{
			Coords.append(Proc1->spot_coord_abs);
			Coords.append(Proc1->strob_coord);
			Coords.append(QPair<double,double>(Proc1->x_pos_spot_in_strob,Proc1->y_pos_spot_in_strob));
		}


		if (Channel == 2)
		{
			Coords.append(Proc2->spot_coord_abs);
			Coords.append(Proc2->strob_coord);
			Coords.append(QPair<double,double>(Proc2->x_pos_spot_in_strob,Proc2->y_pos_spot_in_strob));
		}


		if (Channel == 3)
		{
			Coords.append(Proc3->spot_coord_abs);
			Coords.append(Proc3->strob_coord);
			Coords.append(QPair<double,double>(Proc3->x_pos_spot_in_strob,Proc3->y_pos_spot_in_strob));
		}

		if (Channel == 4)
		{
			Coords.append(ProcToPointer->spot_coord_abs);
			Coords.append(ProcToPointer->strob_coord);
			Coords.append(QPair<double,double>(ProcToPointer->x_pos_spot_in_strob,ProcToPointer->y_pos_spot_in_strob));
		}


	return Coords;
}

DataImageProcAllChannels ImageProcessingClass::GetDataAllChannels()
{
	DataImageProcAllChannels Data;
	Data.ProcessPeriod = this->PeriodImagePerform;
	Data.ReceivePeriod = this->PeriodImageReceive;
	
	Data.TypeBlock = this->TypeBlock;
	Data.Channel1 = Proc1->GetImageToDisplay();
	Data.Channel2 = Proc2->GetImageToDisplay();
	Data.Channel3 = Proc3->GetImageToDisplay();
	Data.Channel4 = ProcToPointer->GetImageToDisplay();


	Data.AllChannelsCoord.Coords.append(Proc1->spot_coord_abs);
	Data.AllChannelsCoord.Coords.append(Proc2->spot_coord_abs);
	Data.AllChannelsCoord.Coords.append(Proc3->spot_coord_abs);
	Data.AllChannelsCoord.Coords.append(ProcToPointer->spot_coord_abs);

//	Data.AllChannelsCoord.Coords.append(Proc1->StatProcessor.Avarage);
//	Data.AllChannelsCoord.Coords.append(Proc2->StatProcessor.Avarage);
//	Data.AllChannelsCoord.Coords.append(Proc3->StatProcessor.Avarage);
//	Data.AllChannelsCoord.Coords.append(ProcToPointer->StatProcessor.Avarage);

	Data.AllChannelsCoord.CoordsROI.append(Proc1->strob_coord);
	Data.AllChannelsCoord.CoordsROI.append(Proc2->strob_coord);
	Data.AllChannelsCoord.CoordsROI.append(Proc3->strob_coord);
	Data.AllChannelsCoord.CoordsROI.append(ProcToPointer->strob_coord);
	return Data;
}

Processor* ImageProcessingClass::GetProcessor(int Channel)
{

    	if (Channel == 1)
		return Proc1;
		if (Channel == 2)
		return Proc2;
		if (Channel == 3)
		return Proc3;
		if (Channel == 4)
		return ProcToPointer;

}

QPair<double,double>  ImageProcessingClass::GetLastCoordChannel(int Channel)
{
	QPair<double, double> Coord;

		if (Channel == 1)
			Coord = Proc1->spot_coord_abs;
		if (Channel == 2)
			Coord = Proc2->spot_coord_abs;
		if (Channel == 3)
			Coord = Proc3->spot_coord_abs;
		if (Channel == 4)
			Coord = ProcToPointer->spot_coord_abs;

	return Coord;
}


Processor::Processor(int OffsetImage)
{
	StateBlock = BlockAtWork;

	this->Offset = OffsetImage; // offset in 1024x256 image contatated from 256x256 strobs
	ResetAiming();
	StrobImage = cv::Mat(cv::Size(256, 256), CV_16U, cv::Scalar(0));
	StrobImageCopy = cv::Mat(cv::Size(256, 256), CV_16U, cv::Scalar(0));
	StrobImageFiltered = cv::Mat(cv::Size(256, 256), CV_16U, cv::Scalar(0));

	ROIImage = cv::Mat(cv::Size(roi_rect_in_strob.width,roi_rect_in_strob.height), CV_16U, cv::Scalar(0));
	ROIImageFiltered = cv::Mat(cv::Size(roi_rect_in_strob.width, roi_rect_in_strob.height), CV_16U, cv::Scalar(0));

}

Processor::~Processor()
{
	qDebug() << "Destructor Processor do nothing";

}






void Processor::ResetAiming()
{
	StatProcessor.SetSize(60);
	StatProcessor.Reset();

	strob_coord = QPair<double, double>(0, 0);
	spot_coord_abs = QPair<double, double>(0, 0);
	SwitchToFindSpotInFullImage();
}


cv::Mat Processor::GetStrobFromRowImage(PIXEL_WORD NEW_PIXELS,int Width,int Height,int Offset)
{
		unsigned short* StrobImageData = this->StrobImage.ptr<unsigned short>();

		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x = x + 4)
			{
				++NEW_PIXELS;
				*(StrobImageData) = (NEW_PIXELS.pixel1 > Threshold) ? ((NEW_PIXELS.pixel1)) : 0;
				*(StrobImageData + 1) = (NEW_PIXELS.pixel2 > Threshold) ? ((NEW_PIXELS.pixel2)) : 0;
				*(StrobImageData + 2) = (NEW_PIXELS.pixel3 > Threshold) ? ((NEW_PIXELS.pixel3)) : 0;
				*(StrobImageData + 3) = (NEW_PIXELS.pixel4 > Threshold) ? ((NEW_PIXELS.pixel4)) : 0;

				//*(StrobImageData) = NEW_PIXELS.pixel1;
				//*(StrobImageData + 1) = NEW_PIXELS.pixel2;
				//*(StrobImageData + 2) = NEW_PIXELS.pixel3;
				//*(StrobImageData + 3) = NEW_PIXELS.pixel4;

				StrobImageData += 4;
			}
			NEW_PIXELS.NewLine_on_N_shift(Offset);
		}
		return StrobImage;
}

void Statistic::CalcDispersion()
{
		DispersionCoord = QPair<double, double>(0, 0);
		DispersionValue = 0;

			for (auto Coord : CoordMassive)
			{

				DispersionCoord.first += std::pow(Coord.first - AvarageCoord.first, 2) / CoordMassive.size();
				DispersionCoord.second += std::pow(Coord.second - AvarageCoord.second, 2) / CoordMassive.size();
			}


			for(auto Value: ValueMassive)
			DispersionValue += std::pow(Value - AvarageValue, 2) / ValueMassive.size();
}

void OptimizationThreshold::CalcSumLD(int Number, int Threshold, cv::Mat& Image)
{
	double sum_x = 0.0, sum_y = 0.0, sum = 0.0;
	sum_x = 0.0, sum_y = 0.0, sum = 0.0;
	QPair<double, double> Coord;

	for (short row = 0; row < Image.rows; row++)
	{
		const unsigned short* RowData = Image.ptr<unsigned short>(row);
		for (short col = 0; col < Image.cols; col++)
		{
				if (RowData[col] > Threshold)
				{
					sum += RowData[col];
					sum_x += RowData[col] * col;
					sum_y += RowData[col] * row;
				}
		}
	}

	Coord.first = sum_x / sum;
	Coord.second = sum_y / sum;

	sum >> this->Statistics[Number - 1];
	Coord >> this->Statistics[Number - 1];
}

void OptimizationThreshold::CalcSumForAllThreshold(cv::Mat& Image)
{

		QFutureSynchronizer<void> synchronizer;

		for (int n = 0; n < ThresholdVector.size(); n++)
		synchronizer.addFuture(QtConcurrent::run(this->CalcSumLoadStat, n,ThresholdVector[n],Image));

		return;
}

void OptimizationThreshold::AccumulateImageStatistics(cv::Mat& Image)
{


		CalcSumForAllThreshold(Image);

		if(this->IsStatisticLoaded())
		{

			int n = -1;
			auto CalcAbsoluteDispersionCoord = [n,this]() mutable -> double
			{
				n++;
				return std::hypot(Statistics[n].DispersionCoord.first, Statistics[n].DispersionCoord.second);
			};

			auto GetAvarageSumPixels = [n,this]() mutable -> double
			{
				n++;
				return Statistics[n].AvarageValue;
			};
			
			
			std::generate(CoordDispersionResults.begin(), CoordDispersionResults.end(), CalcAbsoluteDispersionCoord);
			std::generate(LuminosityResults.begin(), LuminosityResults.end(), GetAvarageSumPixels);

			auto min_element_it = std::min_element(CoordDispersionResults.begin(), CoordDispersionResults.end());
			auto max_element_it = std::max_element(CoordDispersionResults.begin(), CoordDispersionResults.end());
			int index_min_element_dispersion = std::distance(CoordDispersionResults.begin(), min_element_it);

			this->pixel_sum_minimum_dispersion = LuminosityResults[index_min_element_dispersion];
			this->BestThreshold = ThresholdVector[index_min_element_dispersion];

			qDebug() << "THRESHOLD PARAMETERS";
			qDebug() << "Min dispersion - " << *min_element_it << "Max dispersion - " << *max_element_it;
			qDebug() << "Pixel sum minimum disperions - " << pixel_sum_minimum_dispersion;
			qDebug() << "Best threshold - " << BestThreshold;
			qDebug() << "====================================";
			qDebug() << "THRESHOLDS";
			qDebug() << ThresholdVector;
			qDebug() << "COORD DISPERSION RESULTS";
			qDebug() << CoordDispersionResults;
			qDebug() << "====================================";
			qDebug() << "LUMINOSITY RESULTS";
			qDebug() << LuminosityResults;
			qDebug() << "====================================";
		}

}
OptimizationThreshold& operator>>(cv::Mat& Image,OptimizationThreshold& Optimizator)
{
	if(!Optimizator.IsStatisticLoaded())
	Optimizator.AccumulateImageStatistics(Image);

	if(Optimizator.IsStatisticLoaded())
		Optimizator.FindThreshold(Image);
		
	
	return Optimizator;
}
int OptimizationThreshold::CheckLuminosityOffset(double pixel_sum)
{
     int offset = std::floor(pixel_sum_minimum_dispersion - pixel_sum);	

	 if(std::abs(offset) < pixel_sum_minimum_dispersion*0.1) // if offset < 10% then pixel_sum is good
		 return 0;

	 return offset;
}

void OptimizationThreshold::FindThreshold(cv::Mat& Image)
{
	
		int Threshold = BestThreshold;
        double sum = FindPixelsSum(Image, BestThreshold);
	    int sum_offset = CheckLuminosityOffset(sum); // if sum_offset < 10% then sum_offset set to 0
        
	    if(sum_offset == 0)	return;

		int counter = 0;
	    //================================================ 
		int Direction = -1*sum_offset/abs(sum_offset);
		int ThresholdStep = 15*Direction;
	
		qDebug() << "--------------------------------------";

		int sum_offset_last = std::abs(sum_offset);
		int last_sum = sum;
	    while(true)
	    {
			int new_threshold = Threshold + ThresholdStep;
	     sum = FindPixelsSum(Image,new_threshold);
	     sum_offset = std::abs(CheckLuminosityOffset(sum));	    

		

		qDebug() << "CHECK - " << new_threshold << "sum % " << 100*sum/pixel_sum_minimum_dispersion;
		     if(counter > 10) break;

			 if (sum_offset_last < sum_offset) { BestThreshold = Threshold; break; };

			 if (sum_offset == 0) { BestThreshold = Threshold + ThresholdStep; break; };


	         sum_offset_last = sum_offset; last_sum = sum; counter++;
		     Threshold += ThresholdStep;
	    }
         


		qDebug() << "NEW - " << BestThreshold << "sum % " << 100*sum/pixel_sum_minimum_dispersion;
		

}

double OptimizationThreshold::FindPixelsSum(cv::Mat& Image, int Threshold)
{
	
	    double sum = 0;
		for (short row = 0; row < Image.rows; row++)
		{
			const unsigned short* RowData = Image.ptr<unsigned short>(row);
			for (short col = 0; col < Image.cols; col++)
			{
					if (RowData[col] > Threshold)
						sum += 1;
			}
		}
		return sum;
}

void Processor::SwitchToAimingInStrob()
{

	//qDebug() << "Switch to aiming in strob";
	this->AimingState = AimingInStrob;
	auto CheckROIPos = [=](cv::Rect& Roi)
	{
		//qDebug() << "CHECK ROI POS X START - " << X_START << "Y START - " << Y_START;
		const int X_RIGHT_EDGE = Roi.x + Roi.width;
		const int Y_BOTTOM_EDGE = Roi.y + Roi.height;

		const int OFFSET_X = X_RIGHT_EDGE - 256;
		const int OFFSET_Y = Y_BOTTOM_EDGE - 256;

		if (OFFSET_X > 0)
			Roi.x -= OFFSET_X;

		if (OFFSET_Y > 0)
			Roi.y -= OFFSET_Y;

		if (Roi.x < 0)
			Roi.x = 1;
		if (Roi.y < 0)
			Roi.y = 1;

	};

	auto CalcThresholdlByLuminosity = [=](cv::Mat& Image) -> int
	{
		double max_pixel = 0;
		double avg_pixel = 0;
		double sum_all = 0;

		for (short row = 0; row < Image.rows; row++)
		{
			const unsigned short* RowData = Image.ptr<unsigned short>(row);
			for (short col = 0; col < Image.cols; col++)
			{
				sum_all += RowData[col];
				if (max_pixel < RowData[col])
					max_pixel = RowData[col];

			}
		}

		avg_pixel = sum_all / (Image.rows * Image.cols);
		return (avg_pixel + (max_pixel - avg_pixel) / 4); // return threshold
	};


	this->StatProcessor.Reset();
	this->StatProcessor.Size = 400;

	ProcessImagePoly = [this, CalcThresholdlByLuminosity, CheckROIPos](uchar* ImageToProcess, int Width, int Height)
	{
		double sum_x = 0.0, sum_y = 0.0, sum = 0.0;

		PIXEL_WORD NEW_PIXELS(ImageToProcess + Offset);
		this->StrobImage = this->GetStrobFromRowImage(NEW_PIXELS, 256, 256, Width - 256);
		cv::Mat ROIImage = StrobImage(this->roi_rect_in_strob);

		if (this->FlagThresholdAutoControl)
		{
			//ROIImage >> this->ThresholdOptimizator;
			//Threshold = ThresholdOptimizator.BestThreshold;
			Threshold = CalcThresholdlByLuminosity(ROIImage);
		}

		//ROIImageFiltered = ROIImage;
		cv::medianBlur(ROIImage, this->ROIImageFiltered, 5);

		for (short row = 0; row < this->ROIImageFiltered.rows; row++)
		{
			const unsigned short* RowData = this->ROIImageFiltered.ptr<unsigned short>(row);
			for (short col = 0; col < this->ROIImageFiltered.cols; col++)
			{
				if (RowData[col] > Threshold)
				{
					sum += RowData[col];
					sum_x += RowData[col] * col;
					sum_y += RowData[col] * row;
				}
			}
		}

		if (sum != 0.0)
		{
			sum >> StatProcessor;

				this->FlagDisplayNewImage = true;
				this->spot_coord_abs >> StatProcessor;

				this->y_pos_spot_in_roi = sum_y / sum; // get spot center coord 
				this->x_pos_spot_in_roi = sum_x / sum;
				this->x_pos_spot_in_strob = x_pos_spot_in_roi + roi_rect_in_strob.x;
				this->y_pos_spot_in_strob = y_pos_spot_in_roi + roi_rect_in_strob.y;


				this->spot_coord_abs.first = x_pos_spot_in_strob + strob_coord.first;
				this->spot_coord_abs.second = y_pos_spot_in_strob + strob_coord.second;

				this->roi_rect_in_strob.x = x_pos_spot_in_strob - roi_rect_in_strob.width / 2;
				this->roi_rect_in_strob.y = y_pos_spot_in_strob - roi_rect_in_strob.height / 2;
				CheckROIPos(roi_rect_in_strob);
				//====================================================================

				if (StatProcessor.DispersionCoord.first < 24 && StatProcessor.DispersionCoord.second < 24 && StatProcessor.IsCoordLoaded() && roi_rect_in_strob.width != 96)
				{
					this->roi_rect_in_strob.width = 96;    // correct roi 
					this->roi_rect_in_strob.height = 96;
					this->roi_rect_in_strob.x = x_pos_spot_in_strob - roi_rect_in_strob.width / 2;
					this->roi_rect_in_strob.y = y_pos_spot_in_strob - roi_rect_in_strob.height / 2;
					CheckROIPos(roi_rect_in_strob);
					//ThresholdOptimizator.Reset();
					this->ROI_MODE = 2;

					this->FlagDisplayNewImage = false;
				}
		}

	};
}

void Processor::Binarization(cv::Mat& Image, int Threshold)
{
	for (short row = 0; row < ProcessingImage.rows; row++)
	{
		 unsigned short* RowData = ProcessingImage.ptr<unsigned short>(row);
		for (short col = 0; col < ProcessingImage.cols; col++)
		{

			if (RowData[col] > Threshold)
				RowData[col] = 1;
			else
				RowData[col] = 0;
		}
	}
}
			
void Processor::SwitchToAimingInFullImage()
{
	auto CheckROIPos = [=](cv::Rect& Roi)
	{
		//qDebug() << "CHECK ROI POS X START - " << X_START << "Y START - " << Y_START;
		const int X_RIGHT_EDGE = Roi.x + Roi.width;
		const int Y_BOTTOM_EDGE = Roi.y + Roi.height;

		const int OFFSET_X = X_RIGHT_EDGE - 256;
		const int OFFSET_Y = Y_BOTTOM_EDGE - 256;

		if (OFFSET_X > 0)
			Roi.x -= OFFSET_X;

		if (OFFSET_Y > 0)
			Roi.y -= OFFSET_Y;

		if (Roi.x < 0)
			Roi.x = 1;
		if (Roi.y < 0)
			Roi.y = 1;

	};

	auto CheckStrobPos = [=](int& X_START, int& Y_START, int X_ROI, int Y_ROI)
	{
		//qDebug() << "CHECK ROI POS X START - " << X_START << "Y START - " << Y_START;
		const int X_RIGHT_EDGE = X_START + X_ROI;
		const int Y_BOTTOM_EDGE = Y_START + Y_ROI;

		const int OFFSET_X = X_RIGHT_EDGE - 2048;
		const int OFFSET_Y = Y_BOTTOM_EDGE - 512;


		if (OFFSET_X > 0)
			X_START -= OFFSET_X;

		if (OFFSET_Y > 0)
			Y_START -= OFFSET_Y;

		if (X_START < 1)
			X_START = 2;
		if (Y_START < 1)
			Y_START = 2;

	};

	auto CalcThresholdlByLuminosity = [=](cv::Mat& Image) -> int
	{
		double max_pixel = 0;
		double min_pixel = 0;
		double avg_pixel = 0;
		double sum_all = 0;

		for (short row = 0; row < Image.rows; row++)
		{
			const unsigned short* RowData = Image.ptr<unsigned short>(row);
			for (short col = 0; col < Image.cols; col++)
			{
				sum_all += RowData[col];
				if (max_pixel < RowData[col])
					max_pixel = RowData[col];

				//if (min_pixel > RowData[col])
				//	min_pixel = RowData[col];

			}
		}

		avg_pixel = sum_all / (Image.rows * Image.cols);
		return (avg_pixel + (max_pixel - avg_pixel) * 0.5); // return threshold
	};

	//qDebug() << "Switch to aiming in FULL Image";
	this->StatProcessor.Reset();
	this->StatProcessor.Size = 400;
	ProcessImagePoly = [this, CheckROIPos, CheckStrobPos, CalcThresholdlByLuminosity](uchar* ImageToProcess, int Width, int Height) -> void  //FUNCTION THAT FIND SPOT IN WHOLE IMAGE
	{


		double temp_val, sum_x = 0.0, sum_y = 0.0, sum = 0.0;

		int	ROI_offset_start = 1.25 * 2048 * this->strob_coord.second + 1.25 * this->strob_coord.first;

		PIXEL_WORD NEW_PIXELS(ImageToProcess + ROI_offset_start); // iterator to convert 10 bit compressed pixels to 16 bit 

		this->StrobImage = this->GetStrobFromRowImage(NEW_PIXELS, strob_width, strob_height, Width - strob_width); // get images to process and 8 bit images to display

		ROIImage = StrobImage(this->roi_rect_in_strob);


		if (this->FlagThresholdAutoControl)
		{
			//ROIImage >> this->ThresholdOptimizator;
			//Threshold = ThresholdOptimizator.BestThreshold;
			Threshold = CalcThresholdlByLuminosity(ROIImage);
		}
		cv::medianBlur(ROIImage, ROIImageFiltered, 5);
		cv::medianBlur(ROIImageFiltered, ROIImageFiltered, 5);
		Binarization(ROIImageFiltered, Threshold);


		for (short row = 0; row < ROIImageFiltered.rows; row++)
		{
			const unsigned short* RowData = ROIImageFiltered.ptr<unsigned short>(row);
			for (short col = 0; col < ROIImageFiltered.cols; col++)
			{
				sum += RowData[col];
				sum_x += RowData[col] * col;
				sum_y += RowData[col] * row;
			}
		}




		if (sum != 0.0)
		{
			sum >> StatProcessor;
			this->FlagDisplayNewImage = false;
			if (StatProcessor.IsValueLoaded() && sum <= (StatProcessor.MinValue + (StatProcessor.MaxValue - StatProcessor.MinValue) * FrameFilterProcentage))  // filter overexposed images if stat data available
			{

				this->spot_coord_abs >> StatProcessor;

				this->y_pos_spot_in_roi = sum_y / sum; // get spot center coord 
				this->x_pos_spot_in_roi = sum_x / sum;
				this->x_pos_spot_in_strob = x_pos_spot_in_roi + roi_rect_in_strob.x;
				this->y_pos_spot_in_strob = y_pos_spot_in_roi + roi_rect_in_strob.y;


				this->spot_coord_abs.first = x_pos_spot_in_strob + strob_coord.first;
				this->spot_coord_abs.second = y_pos_spot_in_strob + strob_coord.second;


				//====================================================================
				this->FlagDisplayNewImage = true;

				int roi_size = 96;
				if (StatProcessor.DispersionCoord.first < roi_size && StatProcessor.DispersionCoord.second < roi_size && StatProcessor.IsCoordLoaded() && roi_rect_in_strob.width != roi_size)
				{
					//qDebug() << "SET ROI SIZE 96X96";
					ThresholdOptimizator.Reset();

					this->roi_rect_in_strob.width = roi_size;    // correct roi 
					this->roi_rect_in_strob.height = roi_size;

					this->ROI_MODE = 2;

					this->FlagDisplayNewImage = false;
				}

				this->roi_rect_in_strob.x = x_pos_spot_in_strob - roi_rect_in_strob.width / 2;
				this->roi_rect_in_strob.y = y_pos_spot_in_strob - roi_rect_in_strob.height / 2;
				CheckROIPos(roi_rect_in_strob);

				/// ==============================================
				int offset = std::sqrt(std::pow(x_pos_spot_in_strob - 128, 2) + std::pow(y_pos_spot_in_strob - 128, 2));
				int strob_coord_x_new, strob_coord_y_new;
				int step_strob_x, step_strob_y;

				//if (this->NumberChannel == 4)
				//	return;

				//if (ROI_MODE == 2 && offset > 80)
				//{
				//	strob_coord_x_new = spot_coord_abs.first - strob_width / 2;
				//	strob_coord_y_new = spot_coord_abs.second - strob_height / 2;
				//	CheckStrobPos(strob_coord_x_new, strob_coord_y_new, 256, 256);
				//	qDebug() << "JUMP STROB";
				//	step_strob_x = strob_coord_x_new - strob_coord.first;
				//	step_strob_y = strob_coord_y_new - strob_coord.second;
				//	strob_coord.first += step_strob_x; roi_rect_in_strob.x -= step_strob_x;
				//	strob_coord.second += step_strob_y; roi_rect_in_strob.y -= step_strob_y;
				//}
				// ==============================================
			}

		}
	};
}

void Processor::SwitchToFindSpotInFullImage()
{
	
	qDebug() << "Switch to Find spoit in FULL Image";
	this->StatProcessor.Reset();
	this->StatProcessor.Size = 30;
	auto CheckROIPos = [=](int& X_START, int& Y_START, int X_ROI, int Y_ROI)
	{
		//qDebug() << "CHECK ROI POS X START - " << X_START << "Y START - " << Y_START;
		const int X_RIGHT_EDGE = X_START + X_ROI;
		const int Y_BOTTOM_EDGE = Y_START + Y_ROI;

		const int OFFSET_X = X_RIGHT_EDGE - 2048;
		const int OFFSET_Y = Y_BOTTOM_EDGE - 512;


		if (OFFSET_X > 0)
			X_START -= OFFSET_X;

		if (OFFSET_Y > 0)
			Y_START -= OFFSET_Y;

		if (X_START < 0)
			X_START = 1;
		if (Y_START < 0)
			Y_START = 1;

	};


	auto GetMinPixelInWord = [](PIXEL_WORD& Pixels) -> quint16&
	{
		if (Pixels.pixel1 < Pixels.pixel2 && Pixels.pixel1 < Pixels.pixel3 && Pixels.pixel1 < Pixels.pixel4)
			return Pixels.pixel1;

		if (Pixels.pixel2 < Pixels.pixel3 && Pixels.pixel2 < Pixels.pixel4)
			return Pixels.pixel2;

		if (Pixels.pixel3 < Pixels.pixel4)
			return Pixels.pixel3;

		return Pixels.pixel4;

	};
	auto GetMaxPixelInWord = [](PIXEL_WORD& Pixels) -> quint16&
	{
		if (Pixels.pixel1 > Pixels.pixel2 && Pixels.pixel1 > Pixels.pixel3 && Pixels.pixel1 > Pixels.pixel4)
			return Pixels.pixel1;

		if (Pixels.pixel2 > Pixels.pixel3 && Pixels.pixel2 > Pixels.pixel4)
			return Pixels.pixel2;

		if (Pixels.pixel3 > Pixels.pixel4)
			return Pixels.pixel3;

		return Pixels.pixel4;

	};

	auto GetAvaragePixelInWord = [](PIXEL_WORD& Pixels) -> quint16
	{
		return (Pixels.pixel4 + Pixels.pixel3 + Pixels.pixel2 + Pixels.pixel1)/4;
	};

	auto GetMedianPixelInWord = [GetMinPixelInWord](PIXEL_WORD& Pixels) -> quint16
	{
		int Avarage = (Pixels.pixel4 + Pixels.pixel3 + Pixels.pixel2 + Pixels.pixel1) / 4;

		if (Pixels.pixel4 < Avarage && Pixels.pixel4 > GetMinPixelInWord(Pixels))
			return Pixels.pixel4;
		if (Pixels.pixel3 < Avarage && Pixels.pixel3 > GetMinPixelInWord(Pixels))
			return Pixels.pixel3;
		if (Pixels.pixel2 < Avarage && Pixels.pixel2 > GetMinPixelInWord(Pixels))
			return Pixels.pixel2;

			return Pixels.pixel1;

	};



	ProcessImagePoly = [this,CheckROIPos,GetMinPixelInWord,GetMedianPixelInWord,GetMaxPixelInWord](uchar* ImageToProcess, int Width, int Height) mutable  //FUNCTION THAT FIND SPOT IN WHOLE IMAGE
	{
	double temp_val, sum_x = 0.0, sum_y = 0.0, sum = 0.0;
	quint16 median_pixel = 0;
	quint16 min_pixel = 0;
	quint16 max_pixel = 0;
	quint32 sum_pixels = 0;

	int	ROI_offset_start = 0;
	int Process_Width = Width;
	int Process_Height = Height;

	PIXEL_WORD NEW_PIXELS(ImageToProcess + ROI_offset_start);  

	for (int y = 0; y<Process_Height; y++)
	{
		for (int x = 0; x < Process_Width; x = x + 4)
		{
			++NEW_PIXELS;
            
			if (y < 30) 
			{ 
			   max_pixel = GetMaxPixelInWord(NEW_PIXELS);
			   if (Threshold < max_pixel) { Threshold = max_pixel;};

               //sum_pixels += GetAvaragePixelInWord(NEW_PIXELS);
               //pixel_count++;
               //Threshold = sum_pixels/pixel_count;
			}

			if (y > 30)
			{
			   if (NEW_PIXELS.pixel1 > Threshold)  {sum += NEW_PIXELS.pixel1; sum_x += NEW_PIXELS.pixel1 * x;   sum_y += NEW_PIXELS.pixel1 * y;}
			   if (NEW_PIXELS.pixel2 > Threshold)  {sum += NEW_PIXELS.pixel2; sum_x += NEW_PIXELS.pixel2 * x+1; sum_y += NEW_PIXELS.pixel2 * y;}
			   if (NEW_PIXELS.pixel3 > Threshold)  {sum += NEW_PIXELS.pixel3; sum_x += NEW_PIXELS.pixel3 * x+2; sum_y += NEW_PIXELS.pixel3 * y;}
			   if (NEW_PIXELS.pixel4 > Threshold)  {sum += NEW_PIXELS.pixel4; sum_x += NEW_PIXELS.pixel4 * x+3; sum_y += NEW_PIXELS.pixel4 * y;}
			}

		}

			NEW_PIXELS.NewLine_on_N_shift(Width - Process_Width);//2048 - this->strob_width
	}
	

		if (sum != 0.0)
		{
			sum >> StatProcessor;

			if (StatProcessor.IsValueLoaded() && sum <= StatProcessor.AvarageValue) //if sum pixels > 10% from min sum pixels then image overexposed
			{
			this->spot_coord_abs.first = sum_x / sum;
			this->spot_coord_abs.second = sum_y / sum;
			this->strob_coord.first = spot_coord_abs.first - strob_width/2;
			this->strob_coord.second = spot_coord_abs.second - strob_height/2;
			this->spot_coord_abs >> StatProcessor;                                      //to find spot and calc center
			}

			if (StatProcessor.IsCoordLoaded() && StatProcessor.DispersionCoord.first < 32 && StatProcessor.DispersionCoord.second < 32)
			{
			    //qDebug() << "SPOT FOUND !!!" << this->NumberChannel << "Coord - " << spot_coord_abs.first << spot_coord_abs.second;
				this->FlagSpotFound = true;
				this->AimingState = AimingInFullImage;
			    CheckROIPos(strob_coord.first, strob_coord.second, 256, 256);
			}

		}
	};
}
void Processor::ResizeProcessStrob(int X_SIZE, int Y_SIZE)
{
	this->strob_width = X_SIZE;
	this->strob_height = Y_SIZE;
	qDebug() << "Resize display image";

}

void Statistic::Reset()
{
	this->CoordMassive.clear();
	this->ValueMassive.clear();
	this->AvarageCoord = QPair<double, double>(0, 0);
	this->DispersionCoord = QPair<double,double>(0,0);
	this->MinValue = 0; this->MaxValue = 0; this->AvarageValue = 0;
}


void Processor::ProcessImage(uchar* ImageToProcess, int Width, int Height)
{
	if (this->StateBlock == BlockAtWork)
	{
	this->ProcessImagePoly(ImageToProcess,Width,Height); 
	}
}


PIXEL_WORD::PIXEL_WORD(uchar *ImageMass)
{
	Image = ImageMass;
}

PIXEL_WORD::PIXEL_WORD(PIXEL_WORD& Pixels)
{
	this->Image = Pixels.Image;
	this->pixel1 = Pixels.pixel1;
	this->pixel2 = Pixels.pixel2;
	this->pixel3 = Pixels.pixel3;
	this->pixel4 = Pixels.pixel4;
}

void PIXEL_WORD::NewLine()
{
	int strob_offset = 256 * 1.25 * 3;

	Image = Image + strob_offset; //Jamp over three other image ROI
}

void PIXEL_WORD::NewLine_on_N_shift(int on_N_pixel)   //MVZ
{
	int strob_offset = on_N_pixel*1.25;
	Image = Image + strob_offset; 
}

PIXEL_WORD &PIXEL_WORD::operator++()
{

	pixel1 = *((quint16*)Image) & 0x3FF;
	pixel2 = (*((quint16*)(Image + 1)) >> 2) & 0x3FF;
	pixel3 = (*((quint16*)(Image + 2)) >> 4) & 0x3FF;
	pixel4 = (*((quint16*)(Image + 3)) >> 6) & 0x3FF;

	Image = Image + 5;
	return *this;
}

void operator>>(QDataStream &in_stream, PIXEL_WORD& FourPixels)
{

	//in_stream >> FourPixels.x5 >> FourPixels.x4 >> FourPixels.x3 >> FourPixels.x2 >> FourPixels.x1;
	in_stream >> FourPixels.MassByte[4] >> FourPixels.MassByte[3] >> FourPixels.MassByte[2] >> FourPixels.MassByte[1] >> FourPixels.MassByte[0];


	FourPixels.MassPixels[0] = FourPixels.MassByte[4];
	FourPixels.MassPixels[1] = FourPixels.MassByte[3];

	FourPixels.MassPixels[2] = FourPixels.MassByte[3];
	FourPixels.MassPixels[3] = FourPixels.MassByte[2];


	FourPixels.MassPixels[4] = FourPixels.MassByte[2];
	FourPixels.MassPixels[5] = FourPixels.MassByte[1];

	FourPixels.MassPixels[6] = FourPixels.MassByte[1];
	FourPixels.MassPixels[7] = FourPixels.MassByte[0];

	quint16* DataPixels = (quint16*)FourPixels.MassPixels;

	FourPixels.pixel1 = *DataPixels;  DataPixels++;
	FourPixels.pixel2 = *DataPixels;  DataPixels++;
	FourPixels.pixel3 = *DataPixels;  DataPixels++;
	FourPixels.pixel4 = *DataPixels;

	FourPixels.pixel2 >>= 2;
	FourPixels.pixel3 >>= 4;
	FourPixels.pixel4 >>= 6;

	FourPixels.pixel1 &= 0x3FF;
	FourPixels.pixel2 &= 0x3FF;
	FourPixels.pixel3 &= 0x3FF;
	FourPixels.pixel4 &= 0x3FF;

	//if(FourPixels.pixel1 > 255)
	//    FourPixels.pixel1 = 255;
	//if(FourPixels.pixel2 > 255)
	//    FourPixels.pixel2 = 255;
	//if(FourPixels.pixel3 > 255)
	//    FourPixels.pixel3 = 255;
	//if(FourPixels.pixel4 > 255)
	//    FourPixels.pixel4 = 255;


}



DataImageProcStructure Processor::GetImageToDisplay()
{
	DataImageProcStructure Data;

	if (FlagDisplayNewImage)
	{
	StrobImageCopy = cv::Scalar(0);
	ROIImageFiltered.copyTo(StrobImageCopy(roi_rect_in_strob));
	StrobImageCopy = StrobImageCopy*200 * 256;
	}

    Data.Image = QImage(StrobImageCopy.data, StrobImageCopy.cols, StrobImageCopy.rows, StrobImageCopy.step, QImage::Format_RGB16);
	Data.LastCoord = this->spot_coord_abs;
	Data.LastCoordInROI = QPair<double, double>(x_pos_spot_in_strob, y_pos_spot_in_strob);
	Data.strob_coord = this->strob_coord;


	Data.TypeBlock = this->TypeBlock;
	Data.NumberBlock = this->NumberChannel;
    Data.State = this->StateBlock;
	Data.Threshold = this->Threshold;

	Data.ROIInStrob = QRect(this->roi_rect_in_strob.x, this->roi_rect_in_strob.y, this->roi_rect_in_strob.width, this->roi_rect_in_strob.height);
	return Data;
}




