#pragma once
#include "PassTwoCoordClass.h"


template <class Type>

class Substract : public PassTwoCoordClass
{
public:
	QPair<Type, Type> CoordFirst;
	QPair<Type, Type> CoordSecond;
	QPair<Type, Type> CoordOutput;

	int InputCount = 0;

	 QPair<double, double> GetCoord()
	 {
		 return CoordOutput;
	 }
	 void SetCoord(QPair<double, double> Coord)
	 {
		 
			if (InputCount == 0)
			{
				CoordFirst = Coord;
				InputCount++;
			}
			else
			{
				CoordSecond = Coord;
				InputCount = 0;
			CoordOutput.first = CoordFirst.first - CoordSecond.first;
			CoordOutput.second = CoordFirst.second - CoordSecond.second;
			}
	 }

};



template <class Type>
class SummVec : public PassTwoCoordClass
{
public:
	QPair<Type, Type> CoordOutput;

	 QPair<double, double> GetCoord()
	 {
		 QPair<Type, Type> Return = CoordOutput;
		CoordOutput.first = 0;
		CoordOutput.second = 0;
		return Return;
	 }
	 void SetCoord(QPair<double, double> Coord)
	 {
		 
		CoordOutput.first += Coord.first;
		CoordOutput.second += Coord.second;
	 }

	friend SummVec<Type>& operator<<(SummVec<Type>& SubObj,QPair<Type, Type> Coord)
    {

		SubObj.SetCoord(Coord);
			return SubObj;

    }
	friend SummVec<Type>& operator<<( SummVec<Type>& SubObj,PassTwoCoordClass& Sender)
    {

		SubObj.SetCoord(Sender.GetCoord());
			return SubObj;

    }
};
