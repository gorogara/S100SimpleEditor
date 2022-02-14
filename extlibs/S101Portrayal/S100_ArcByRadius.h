#pragma once
#include "S100_VectorPoint.h"
#include "S100_Sector.h"
class S100_ArcByRadius
{
public:
	S100_ArcByRadius();
	virtual ~S100_ArcByRadius();
	
public:
	S100_VectorPoint center;
	S100_Sector *sector;
	std::wstring radius;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

