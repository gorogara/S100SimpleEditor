#pragma once
#include "..\\extlibs\pugixml\include\pugixml.hpp"
#include <string>

class S100_AreaPlacement
{
public:
	S100_AreaPlacement();
	virtual ~S100_AreaPlacement();

public:
	std::wstring placementMode;

public:
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node& node);
};

