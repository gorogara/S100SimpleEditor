#pragma once
#include "S100GML_Curve.h"
#include "GMLPoint.h"
#include "S100GML_Geometry.h"

#include <list>
#include <string>

namespace S100DatasetGML
{
	class S100GML_Curve : public S100GML_Geometry
	{
	public:
		S100GML_Curve();
		virtual ~S100GML_Curve();

		std::list<GMLPoint> GetCoordinates();

		std::wstring GetPosList();
		void SetPosList(std::wstring value);


	public:
		std::wstring posList;

	public:
		int GetType();
	};
}