#pragma once
#include <string>
#include "S100_Enumeration.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp" 
class S100_IC_SaturationOffset
{
public:
	S100_IC_SaturationOffset();
	virtual ~S100_IC_SaturationOffset(); 
	S100_dataProduct product; 
	float offsetDusk; 
	float offsetNight;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

