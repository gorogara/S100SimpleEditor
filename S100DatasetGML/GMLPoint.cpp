#include "stdafx.h"
#include "GMLPoint.h"

namespace S100DatasetGML
{
	GMLPoint::GMLPoint(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
	GMLPoint::~GMLPoint()
	{

	}

	double GMLPoint::GetX()
	{
		return x;
	}

	void GMLPoint::SetX(double value)
	{
		x = value;
	}

	double GMLPoint::GetY()
	{
		return y;
	}

	void GMLPoint::SetY(double value)
	{
		y = value;
	}
}
