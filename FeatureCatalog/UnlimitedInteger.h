#pragma once
#include "XML_Item.h"
#include <pugixml.hpp>

class UnlimitedInteger :
	public XML_Item
{
public:
	UnlimitedInteger();
	virtual ~UnlimitedInteger();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

