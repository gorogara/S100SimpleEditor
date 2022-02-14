#pragma once
#include "Restriction_Item.h"

#include <pugixml.hpp>
class RoleType :
	public Restriction_Item
{
public:
	RoleType();
	virtual ~RoleType();

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};