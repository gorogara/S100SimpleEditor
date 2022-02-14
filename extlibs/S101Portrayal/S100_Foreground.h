#pragma once
#include <string>
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_Foreground 
{
public:
	S100_Foreground();
	virtual ~S100_Foreground();
public:
	std::wstring token;
	std::wstring transparency;
public:
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node node);
};

