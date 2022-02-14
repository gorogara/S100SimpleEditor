#pragma once
#include "XML_Item.h"
#include "Multiplicity.h"
#include "ValueList.h"
#include "Reference.h"

#include <pugixml.hpp>

class InformationBinding :
	public XML_Item
{
public:
	InformationBinding();
	virtual ~InformationBinding();

public:
	Multiplicity multiplicity;
	Reference association;
	Reference role;
	Reference informationType;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);


};

