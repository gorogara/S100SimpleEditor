#pragma once

#include "S100GML_Point.h"
#include "GMLPoint.h"
#include "S100GML_Geometry.h"

#include <list>
#include <string>

namespace S100DatasetGML
{
	class S100GML_Point : public S100GML_Geometry
	{
	public:
		S100GML_Point();
		~S100GML_Point();

	public:
		std::wstring pos;

	public:
		int GetType();
		std::list<GMLPoint> GetCoordinates();
	};
}