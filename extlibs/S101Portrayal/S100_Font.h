#pragma once
#include <string>
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class S100_Font
{
public:
	S100_Font();
	virtual ~S100_Font();

public:
	std::wstring serifs;
	std::wstring weight;
	std::wstring slant;
	std::wstring proportion;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);

};

