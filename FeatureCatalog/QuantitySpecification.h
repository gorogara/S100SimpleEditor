#pragma once

#include "Restriction_Item.h"

#include <pugixml.hpp>

class QuantitySpecification :
	public Restriction_Item
{
public:
	QuantitySpecification();
	virtual ~QuantitySpecification();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};