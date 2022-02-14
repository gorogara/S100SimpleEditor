#include "stdafx.h"
#include "UserText.h"
#include "UserLayer.h"

using namespace RT;

UserText::UserText(double _x, double _y, std::wstring _name, std::wstring _description)
{
	x = _x;
	y = _y;
	type = TYPE_TEXT;
	name = _name;
	description = _description;
}


UserText::~UserText()
{
}

void UserText::Set(double _x, double _y)
{
	x = _x;
	y = _y;
}

void UserText::Get(double& _x, double& _y)
{
	_x = x;
	_y = y;
}

void UserText::GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax)
{
	_xmin = x;
	_ymin = y;
	_xmax = x;
	_ymax = y;
}


int UserText::GetSize()
{
	return size;
}


void UserText::SetSize(int _size)
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