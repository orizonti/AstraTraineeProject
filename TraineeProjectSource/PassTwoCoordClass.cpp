#include "stdafx.h"
#include "PassTwoCoordClass.h"
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

QPair<double, double> PassTwoCoordClass::GetCoord()
{
	return QPair<double, double>(0, 0);
}


PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever)
{
	Reciever.SetCoord(Sender.GetCoord());
	return Reciever;
}

PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, QPair<double,double>& Coord)
{
	Coord = Sender.GetCoord();
	return Sender;
}

PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever)
{

	Reciever.SetCoord(Coord);
	return Reciever;
}

PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, Eigen::Matrix< float, 2, 1 >& Reciever)
{
		Reciever[0, 0] = Sender.GetCoord().first;
		Reciever[1, 0] = Sender.GetCoord().second;
		return Sender;
}

void PassTwoCoordClass::SetLink(PassTwoCoordClass* NewLink)
{
	qDebug() << "PASS TWO COORD SET LINK"; 
	Link = NewLink;
}
