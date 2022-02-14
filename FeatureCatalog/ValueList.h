#pragma once
#include "XML_Item.h"
#include <pugixml.hpp>

class ValueList :
	public XML_Item
{
public:
	ValueList();
	virtual ~ValueList();

public:
	std::list<int> value;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};