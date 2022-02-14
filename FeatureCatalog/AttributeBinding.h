#pragma once
#include "XML_Item.h"
#include "ValueList.h"
#include "Multiplicity.h"
#include "Reference.h"

#include <pugixml.hpp>

class AttributeBinding :
	public XML_Item
{
public:
	AttributeBinding();
	virtual ~AttributeBinding();
	
public:
	Multiplicity multiplicity;
	ValueList permittedValues;
	Reference attribute;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

