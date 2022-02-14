#pragma once
#include "XML_Item.h"
#include <list>
#include <pugixml.hpp>
class Telephone :
	public XML_Item
{
public:
	Telephone();
	virtual ~Telephone();

public:
	std::list<std::wstring> voice;
	std::wstring facsimile;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

