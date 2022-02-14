#pragma once
#include "XML_Item.h"
#include "OnlineFunctionCode.h"

#include <pugixml.hpp>
#include <string>

class OnlineResource :
	public XML_Item
{
public:
	OnlineResource();
	virtual ~OnlineResource();

public:
	std::wstring url; 
	std::wstring protocol; 
	std::wstring applicationProfile; 
	std::wstring name; 
	std::wstring description; 
	OnlineFunctionCode function; 
	std::string linkage;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);  
};