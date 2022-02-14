#pragma once
#include "XML_Item.h"
#include "Citation.h"
#include <pugixml.hpp>
class DefinitionSource :
	public XML_Item
{
public:
	DefinitionSource();
	virtual	~DefinitionSource();
	
public:
	Citation source;
	
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

