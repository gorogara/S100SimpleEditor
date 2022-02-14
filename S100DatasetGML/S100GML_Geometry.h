#pragma once   
#include "GMLPoint.h"
#include <list>
#import <msxml4.dll> 

namespace S100DatasetGML
{
	class S100GML_Geometry
	{
	public:
		S100GML_Geometry() {};
		virtual ~S100GML_Geometry() {};

	public: 

	public:     
		virtual int GetType() { return 0; };
		virtual void GetContents(MSXML2::IXMLDOMNodePtr pNode) {};
		virtual std::list<GMLPoint> GetCoordinates() { return std::list<GMLPoint>(); };
		virtual std::list<std::list<GMLPoint>> GetCoordinatesInSurface() { return std::list<std::list<GMLPoint>>(); };
	};
}
