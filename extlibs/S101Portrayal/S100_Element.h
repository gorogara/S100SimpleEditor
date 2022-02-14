#pragma once
#include "S100_Text.h"
#include "S100_Foreground.h"
#include "S100_Font.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_Element
{
public:
	S100_Element();
	virtual ~S100_Element();

public:
	S100_Text *text;
	std::wstring bodySize;
	std::wstring verticalOffset;
	S100_Foreground* foreground;
	S100_Font* font;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

