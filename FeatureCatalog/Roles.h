#pragma once
#include "XML_Item.h"
#include "Role.h"

#include <pugixml.hpp>
class Roles : public XML_Item
{
public:
	Roles(void);
	virtual ~Roles(void);

public:
	std::unordered_map<std::wstring, Role> role;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);


};