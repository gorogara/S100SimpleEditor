#pragma once
#include "XML_Item.h"
#include <pugixml.hpp>

class Series : public XML_Item
{
public:
	Series();
	virtual ~Series();

public:
	std::wstring name;
	std::wstring issueIdentification;
	std::wstring page; 

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

