#pragma once
#include "S100_Enumeration.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <list> 
class S100_IC_SuppressedFeatureLayer
{
public:
	S100_IC_SuppressedFeatureLayer();
	virtual ~S100_IC_SuppressedFeatureLayer(); 
public:
	std::wstring id; 
public:
	std::wstring featureCode;
	S100_dataProduct product; 
	std::list<std::wstring> featureRef;


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

