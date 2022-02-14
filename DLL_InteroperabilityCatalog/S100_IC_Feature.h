#pragma once

#include <string>
#include <list>
#include "S100_Enumeration.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class S100_IC_Feature
{
public:
	S100_IC_Feature();
	virtual ~S100_IC_Feature();  
	std::wstring id; 

	std::wstring featureCode;
	S100_dataProduct product;
	S100_geometry geometry; 
	int drawOrder; 
	std::list<std::wstring> attributeCombination;
	int viewingGroup;   
	bool significant;


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

