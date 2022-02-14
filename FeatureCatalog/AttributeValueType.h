#pragma once

#include "Restriction_Item.h"
#include <pugixml.hpp>

class AttributeValueType : public Restriction_Item
{
public:
	AttributeValueType();
	virtual~AttributeValueType();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};