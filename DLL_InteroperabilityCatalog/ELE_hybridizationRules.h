#pragma once
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class ELE_hybridizationRules
{
public:
	ELE_hybridizationRules();
	virtual ~ELE_hybridizationRules();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

