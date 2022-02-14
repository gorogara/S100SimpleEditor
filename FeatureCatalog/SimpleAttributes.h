#pragma once
#include "XML_Item.h"
#include "SimpleAttribute.h"

#include <pugixml.hpp>

class SimpleAttributes : public XML_Item
{
public:
	SimpleAttributes(void);
	virtual ~SimpleAttributes(void);

public:
	std::unordered_map<std::wstring, SimpleAttribute> simpleAttribute;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};