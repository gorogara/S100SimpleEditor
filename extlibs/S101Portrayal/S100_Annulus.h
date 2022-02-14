#pragma once
#include "S100_VectorPoint.h"
#include "S100_Sector.h"
class S100_Annulus
{
public:
	S100_Annulus();
	virtual ~S100_Annulus();

public:
	S100_VectorPoint point;
	std::wstring *innerRadius;
	std::wstring outerRadius;
	S100_Sector *sector;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};