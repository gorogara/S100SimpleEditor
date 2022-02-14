#pragma once
#include "InformationAssociation.h"

#include <pugixml.hpp>
class InformationAssociations :
	public XML_Item
{
public:
	InformationAssociations();
	virtual ~InformationAssociations();

public:
	std::unordered_map<std::wstring, InformationAssociation> informationAssociation;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};