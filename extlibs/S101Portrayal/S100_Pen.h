#pragma once

#include "S100_Color.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"
#include <string>

class S100_Pen
{
public:
	S100_Pen();
	virtual ~S100_Pen();

public:
	std::wstring width;
	S100_Color *color = nullptr;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};