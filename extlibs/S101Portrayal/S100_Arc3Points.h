#pragma once
#include "S100_VectorPoint.h"

class S100_Arc3Points
{
public:
	S100_Arc3Points();
	virtual ~S100_Arc3Points();

public:
	S100_VectorPoint point;
	S100_VectorPoint medianPoint;
	S100_VectorPoint endPoint;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};