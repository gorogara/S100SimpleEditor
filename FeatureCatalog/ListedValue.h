#pragma once
#include "XML_Item.h"
#include "IntegerCode.h"
#include "DefinitionReference.h"

#include <pugixml.hpp>
class ListedValue :
	public XML_Item
{
public:
	ListedValue();
	virtual ~ListedValue();

public:
	std::wstring label;
	std::wstring definition;
	IntegerCode code;
	std::wstring remarks; 
	std::list<std::wstring> alias; 
	DefinitionReference definitionReference; 

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

