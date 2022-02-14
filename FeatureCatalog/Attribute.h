#pragma once
#include "Item.h"
#include <pugixml.hpp>

class Attribute : public Item
{
public:
	Attribute();
	virtual ~Attribute();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

