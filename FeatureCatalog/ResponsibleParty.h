#pragma once

#include "XML_Item.h"
#include "Contact.h"
#include "RoleCode.h"
#include "Party.h"

#include <pugixml.hpp>
#include <string>

class ResponsibleParty :
	public XML_Item
{
public:
	ResponsibleParty();
	virtual ~ResponsibleParty();
public:
	std::wstring individualName; 
	std::wstring organisationName; 
	std::wstring positionName;//없습니다.
	Contact contactInfo; 
	RoleCode role;
	Party party;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

