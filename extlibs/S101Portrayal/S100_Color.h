#pragma once

#include "..\\extlibs\pugixml\include\pugixml.hpp"

#include <string>

class S100_Color
{
public:
	S100_Color();
	virtual ~S100_Color();

public:
	std::wstring token;
	std::wstring name;
	std::wstring transparency; 
	std::wstring description;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};