#pragma once
#include "XML_Item.h"
#include "ListedValue.h"
#include <pugixml.hpp>

class ListedValues :
	public XML_Item
{
public:
	ListedValues();
	virtual ~ListedValues();

public:
	std::unordered_map<int, ListedValue> listedValue;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};