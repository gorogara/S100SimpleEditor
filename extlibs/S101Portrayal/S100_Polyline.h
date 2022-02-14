#pragma once
#include "S100_VectorPoint.h"

#include <list>
class S100_Polyline
{
public:
	S100_Polyline();
	virtual ~S100_Polyline();

public:
	std::list<S100_VectorPoint> points;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

