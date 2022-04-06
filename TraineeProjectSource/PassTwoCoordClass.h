#pragma once
#include <QPair>


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
