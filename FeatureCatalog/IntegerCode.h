#pragma once
#include "Restriction_Item.h"

#include <pugixml.hpp>
class IntegerCode :
	public Restriction_Item
{
public:
	IntegerCode();
	virtual ~IntegerCode();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

