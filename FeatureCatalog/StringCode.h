#pragma once
#include "Restriction_Item.h"
#include <pugixml.hpp>
class StringCode :
	public Restriction_Item
{
public:
	StringCode();
	virtual ~StringCode();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};