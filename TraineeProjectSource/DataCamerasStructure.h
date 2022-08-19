#pragma once
#include "DataToDisplayStructure.h"
#include "QSize"


class DataCamerasStructure : public DataToDisplayStructure
{
public:
	QSize SizeROI;
	int Frequency;
	int Exposure;

	int X1 = 0;
	int Y1 = 0;

	int X2 = 0;
	int Y2 = 0;
    
	int X3 = 0;
	int Y3 = 0;
    
	int Y4 = 0;
	int X4 = 0;
	
	double FramePeriodFULL = 0;
	double FramePeriodROI = 0;
};