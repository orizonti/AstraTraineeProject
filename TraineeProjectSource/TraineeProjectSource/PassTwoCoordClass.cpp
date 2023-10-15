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



QPair<double, double> operator*(QPair<double, double>& x,const QPair<double, double>& y)
{
    return QPair<double,double>(x.first * y.first, x.second * y.second);
}
QPair<double, double> operator*(const QPair<double, double>& x, double Scale)
{
    return QPair<double,double>(x.first * Scale, x.second * Scale);
}

void operator+=(QPair<double, double>& x, const QPair<double, double>& y)
{
    x.first = x.first + y.first; x.second = x.second + y.second;
}

void operator-=(QPair<double, double>& x, const QPair<double, double>& y)
{
    x.first = x.first - y.first; x.second = x.second - y.second;
}


std::pair<double, double> operator+(const std::pair<double, double>& x, const std::pair<double, double>& y)
{
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::pair<double, double> operator-(const std::pair<double, double>& x, const std::pair<double, double>& y)
{
    return std::make_pair(x.first - y.first, x.second - y.second);
}

QPair<double, double> operator+(const QPair<double, double>& x, const QPair<double, double>& y)
{
    return QPair<double,double>(x.first + y.first, x.second + y.second);
}

QPair<double, double> operator-(const QPair<double, double>& x, const QPair<double, double>& y)
{
    return QPair<double,double>(x.first - y.first, x.second - y.second);
}
