#include "stdafx.h"
#include "UserObject.h"

namespace RT
{

	UserObject::UserObject(void)
	{
		on = true;
	}

	UserObject::~UserObject(void)
	{
	}

	double UserObject::AdjustLon(double _lon)
	{
		while ((_lon > 180.0) || (_lon < -180.0))
		{
			if (_lon > 180.0)
			{
				_lon -= 360.0;
			}
			else if (_lon < -180.0)
			{
				_lon += 360.0;
			}
		}

		return _lon;
	}

	double UserObject::AdjustLat(double _lat)
	{
		if (_lat > 90.0)
		{
			_lat = 90.0;
		}
		else if (_lat < -90.0)
		{
			_lat = -90.0;
		}

		return _lat;
	}

	int UserObject::AdjustRGB(int _rgb)
	{
		if (_rgb > 255)
		{
			_rgb = 255;
		}
		else if (_rgb < 0)
		{
			_rgb = 0;
		}

		return _rgb;
	}

	void UserObject::SetColor(int _R, int _G, int _B)
	{
		R = AdjustRGB(_R);
		G = AdjustRGB(_G);
		B = AdjustRGB(_B);
	}

	void UserObject::GetColor(int& _R, int& _G, int& _B)
	{
		_R = R;
		_G = G;
		_B = B;
	}

	void UserObject::SetFont(std::wstring _font)
	{
		font = _font;
	}

	std::wstring UserObject::GetFont()
	{
		return font;
	}
}