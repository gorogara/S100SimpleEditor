#pragma once
#include "Item.h"
#include <pugixml.hpp>

class Role :
	public Item
{
public:
	Role();
	virtual ~Role();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

