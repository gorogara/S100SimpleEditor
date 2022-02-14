#pragma once
#include "XML_Item.h"
#include "Reference.h"
#include <pugixml.hpp>

class DefinitionReference :
	public XML_Item
{
public:
	DefinitionReference();
	virtual ~DefinitionReference();

public:
	std::wstring sourceIdentifier;
	Reference definitionSource;
	
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

