#include "CommonHeaders.h"
#include "TransformCoordClass.h"  


QPair<double, double> TransformCoordClass::GetCoord()
{
	return TransformedCoord;
}

void TransformCoordClass::SetCoord(QPair<double, double> Coord)
{
	TransformCoord(Coord);
}

