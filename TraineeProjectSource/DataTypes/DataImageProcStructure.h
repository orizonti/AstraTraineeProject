#pragma once
#include "DataDeviceStructureCommon.h"


class DataImageProcStructure : public DataDeviceStructure
{
public:
	QPair<double, double> LastCoord;
	QPair<double, double> LastAimingCoord;
	QPair<double, double> strob_coord;
	QPair<double, double> LastCoordInROI;

	QPair<double, double> VectorCotrol;
	QImage Image;
	int Threshold;
	QRect ROIInStrob;
};

class DataCoordStructure
{
public:
		QVector < QPair<double, double> > Coords;
		QVector < QPair<double, double> > CoordsROI; 
};


class DataImageProcAllChannels : public DataDeviceStructure
{
public:

	DataCoordStructure AllChannelsCoord;
		DataImageProcStructure Channel1;
		DataImageProcStructure Channel2;
		DataImageProcStructure Channel3;
		DataImageProcStructure Channel4;

		double ProcessPeriod = 0;
		double ReceivePeriod = 0;
};