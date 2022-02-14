#pragma once
#include "Item.h"
#include "AttributeBinding.h"

#include <pugixml.hpp>

class ComplexAttribute :
	public Item
{
public:
	ComplexAttribute();
	virtual ~ComplexAttribute();

public:
	std::list<AttributeBinding> subAttributeBinding;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

