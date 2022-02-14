#include "stdafx.h"
#include "UserPoint.h"
#include "UserLayer.h"

using namespace RT;

UserPoint::UserPoint(double _x, double _y, std::wstring _name, std::wstring _description)
{
	x = AdjustLon(_x);
	y = AdjustLat(_y);
	type = TYPE_POINT;
	name = _name;
	description = _description;
}

UserPoint::~UserPoint(void)
{
}

void UserPoint::Set(double _x, double _y)
{
	x = AdjustLon(_x);
	y = AdjustLat(_y);
}

void UserPoint::Get(double& _x, double& _y)
{
	_x = x;
	_y = y;
}

void UserPoint::SetSize(int _size)
{
	if (_size < 1)
	{
		size = 1;
	}
	else
	{
		size = _size;
	}
}

int UserPoint::GetSize()
{
	return size;
}

void UserPoint::GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax)
{
	_xmin = x;
	_ymin = y;
	_xmax = x;
	_ymax = y;
}