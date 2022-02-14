#pragma once

#include "RoutePlanner.h"
#include "UserObject.h"
#include "UserPoint.h"
#include "UserPolyLine.h"
#include "UserPolygon.h"
#include "UserText.h"

namespace RT
{
#define TYPE_POINT 1
#define TYPE_POLYLINE 2
#define TYPE_POLYGON 3
#define TYPE_TEXT 4

	class UserObject;

	class UserDefinedLayer
	{
	public:
		UserDefinedLayer();
		virtual ~UserDefinedLayer();
	
	public:
		std::vector<UserObject*> vObj;
	
	public:
		void AddPoint(double _x, double _y);
		void AddPolyline(double _px[], double _py[], int _cnt);
		void AddPolygon(double _px[], double _py[], int _cnt);
		void AddText(double _x, double _y, std::wstring _name);

		void AddPoint(UserPoint* _point);
		void AddLine(UserPolyLine* _line);
		void AddArea(UserPolygon* _area);
		void AddText(UserText* _text);

		UserObject* Get(int _index);

		void Up(int _index);
		void Down(int _index);
		void Delete(int _index);
		void On(int _index);
		void Off(int _index);
	};
}