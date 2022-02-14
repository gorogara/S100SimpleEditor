#pragma once
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"

class S100_LineSymbol
{
public:
	S100_LineSymbol();
	virtual ~S100_LineSymbol();

public: 
	std::wstring reference;
	std::wstring rotation;
	std::wstring scaleFactor;
	std::wstring crsType; 
	std::wstring position;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

