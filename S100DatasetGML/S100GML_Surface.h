#pragma once
#include "S100GML_Geometry.h"
#include "GMLPoint.h"
#include <string>
#include <list>

namespace S100DatasetGML
{
	class S100GML_Surface : public S100GML_Geometry
	{
	public:
		S100GML_Surface();
		virtual ~S100GML_Surface();

		std::list<std::list<GMLPoint>> GetCoordinatesInSurface();
		std::wstring posListOfExterior;
		std::list<std::wstring> posListOfInteriorList;

	public:
		int GetType();
	};

}