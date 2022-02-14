#pragma once
#include "Item.h"
#include "AttributeBinding.h"

#include <pugixml.hpp>
class NamedType :
	public Item
{
public:
	NamedType();
	virtual ~NamedType();

public:
	std::list<AttributeBinding> attributeBinding;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

