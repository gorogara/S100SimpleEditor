#pragma once

#include "..\\extlibs\pugixml\include\pugixml.hpp"
#include <string>
class S100_LinePlacement
{
public:
	S100_LinePlacement();
	virtual ~S100_LinePlacement();

public:
	std::wstring offset;
	std::wstring placementMode;

public:
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node& node);
};

