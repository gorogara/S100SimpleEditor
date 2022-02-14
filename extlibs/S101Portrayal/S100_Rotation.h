#pragma once
#include <string>
#include "..\\extlibs\pugixml\include\pugixml.hpp"

class S100_Rotation
{
public:
	S100_Rotation();
	virtual ~S100_Rotation();
	std::wstring useValueOf;
	std::wstring value;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

