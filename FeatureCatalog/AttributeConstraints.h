#pragma once

#include "XML_Item.h"
#include "NumericRange.h"

#include <pugixml.hpp>

class AttributeConstraints :
	public XML_Item
{
public:
	AttributeConstraints();
	virtual ~AttributeConstraints();

public:
	int stringLength;
	std::wstring textPattern;
	NumericRange range;
	int precision;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};