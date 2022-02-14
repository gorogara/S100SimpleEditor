#pragma once
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class S100_Sector
{
public:
	S100_Sector();
	virtual ~S100_Sector();

public:
	std::wstring startAngle;
	std::wstring angularDistance;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);

};

