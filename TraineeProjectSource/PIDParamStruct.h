#pragma once


class PIDParamStruct
{
public:
	double RateParam;
	double DiffParam;
	double IntParam;
	double Common;

	void operator=(PIDParamStruct Param)
	{
		this->Common = Param.Common;
		this->DiffParam = Param.DiffParam;
		this->IntParam = Param.IntParam;
		this->RateParam = Param.RateParam;
	}
};