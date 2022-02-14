#pragma once
#include <string>
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_Text
{
public:
	S100_Text();
	virtual ~S100_Text();

public:
	std::wstring value;
	std::wstring useValueOf;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

