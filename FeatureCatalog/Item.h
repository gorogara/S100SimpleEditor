#pragma once
#include "XML_Item.h"
#include "StringCode.h"
#include "DefinitionReference.h"

#include <pugixml.hpp>
#include <string>

class Item :
	public XML_Item
{
public:
	Item();
	virtual ~Item();

public:
	std::wstring name;
	std::wstring definition;
	StringCode code;
	std::wstring remarks;
	std::list<std::wstring> alias;
	DefinitionReference definitionReference; 

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

