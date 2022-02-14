#pragma once
#include "..\\extlibs\pugixml\include\pugixml.hpp"

#include <string>

class S100_VectorPoint
{
public:
	S100_VectorPoint();
	virtual ~S100_VectorPoint();

public:
	std::wstring x;
	std::wstring y;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

