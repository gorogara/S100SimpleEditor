#pragma once
#include "Restriction_Item.h"

#include <pugixml.hpp>

class IntervalType :
	public Restriction_Item
{
public:
	IntervalType();
	virtual ~IntervalType();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

