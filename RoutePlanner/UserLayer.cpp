#include "stdafx.h"
#include "UserLayer.h"
#include "UserPoint.h"
#include "UserPolyLine.h"
#include "UserPolygon.h"

namespace RT
{

	UserDefinedLayer::UserDefinedLayer()
	{

	}

	UserDefinedLayer::~UserDefinedLayer()
	{
		for (unsigned i = 0; i < vObj.size(); i++)
		{
			delete vObj.at(i);
		}

		vObj.clear();
	}

	void UserDefinedLayer::AddPoint(double _x, double _y)
	{
		UserObject* obj = new UserPoint(_x, _y);
		vObj.push_back(obj);
	}

	void UserDefinedLayer::AddPolyline(double _px[], double _py[], int _cnt)
	{
		UserObject* obj = new UserPolyLine(_px, _py, _cnt);
		vObj.push_back(obj);
	}

	void UserDefinedLayer::AddPolygon(double _px[], double _py[], int _cnt)
	{
		UserObject* obj = new UserPolygon(_px, _py, _cnt);
		vObj.push_back(obj);
	}                                    

	UserObject* UserDefinedLayer::Get(int _index)
	{
		try
		{
			return vObj.at(_index);
		}
		catch (std::out_of_range)
		{
			return nullptr;
		}
	}

	void UserDefinedLayer::AddPoint(UserPoint* _point)
	{
		vObj.push_back(_point);
	}

	void UserDefinedLayer::AddLine(UserPolyLine* _line)
	{
		vObj.push_back(_line);
	}

	void UserDefinedLayer::AddArea(UserPolygon* _area)
	{
		vObj.push_back(_area);
	}

	void UserDefinedLayer::AddText(UserText* _text)
	{
		vObj.push_back(_text);
	}

	void UserDefinedLayer::Up(int _index)
	{
		try
		{
			UserObject* tmp = vObj.at(_index);
			vObj.at(_index) = vObj.at(_index - 1);
			vObj.at(_index - 1) = tmp;
		}
		catch (std::out_of_range)
		{
			return;
		}
	}

	void UserDefinedLayer::Down(int _index)
	{
		try
		{
			UserObject* tmp = vObj.at(_index);
			vObj.at(_index) = vObj.at(_index + 1);
			vObj.at(_index + 1) = tmp;
		}
		catch (std::out_of_range)
		{
			return;
		}
	}

	void UserDefinedLayer::Delete(int _index)
	{
		try
		{
			delete vObj.at(_index);
			vObj.erase(vObj.begin() + _index);
		}
		catch (std::out_of_range)
		{
			return;
		}
	}

	void UserDefinedLayer::On(int _index)
	{
		try
		{
			vObj.at(_index)->on = true;
		}
		catch (std::out_of_range)
		{
			return;
		}
	}

	void UserDefinedLayer::Off(int _index)
	{
		try
		{
			vObj.at(_index)->on = false;
		}
		catch (std::out_of_range)
		{
			return;
		}
	}
}