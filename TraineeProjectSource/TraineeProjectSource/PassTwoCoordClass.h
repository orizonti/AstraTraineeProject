#pragma once
#include <QPair>

std::pair<double, double> operator+(const std::pair<double, double>& x, const std::pair<double, double>& y);
std::pair<double, double> operator-(const std::pair<double, double>& x, const std::pair<double, double>& y);
QPair<double, double> operator+(const QPair<double, double>& x, const QPair<double, double>& y);
QPair<double, double> operator-(const QPair<double, double>& x, const QPair<double, double>& y);
QPair<double, double> operator*(const QPair<double, double>& x, double Scale);
void operator+=(QPair<double, double>& x, const QPair<double, double>& y);
void operator-=(QPair<double, double>& x, const QPair<double, double>& y);


class PassTwoCoordClass
{
public:
	PassTwoCoordClass* Link = 0;

	virtual QPair<double, double> GetCoord() = 0;
	virtual void SetCoord(QPair<double, double> Coord) = 0;
	void SetLink(PassTwoCoordClass* NewLink);
	
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, QPair<double, double>& Coord);
    friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(QPair<double,double> Coord, PassTwoCoordClass& Reciever);
};
