#pragma once
#include "XML_Item.h"
#include "UnlimitedInteger.h"

#include <pugixml.hpp>

class Multiplicity :
	public XML_Item
{
public:
	Multiplicity();
	virtual ~Multiplicity();

public:
	int lower = 0;
	UnlimitedInteger upper;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetLower(int value);
	int GetLower();

	void SetUpper(UnlimitedInteger& value);
	UnlimitedInteger& GetUpper();
};

