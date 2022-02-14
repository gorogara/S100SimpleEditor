#pragma once
#include "XML_Item.h"
#include "CI_Organisation.h"

#include <pugixml.hpp>

class Party :
	public XML_Item
{
public:
	Party();
	virtual ~Party();

public:
	CI_Organisation ci_Organisation;

public:
	void GetContents(pugi::xml_node& node);
};

