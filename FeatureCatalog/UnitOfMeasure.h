#pragma once
#include "XML_Item.h"

#include <string>
#include <pugixml.hpp>

class UnitOfMeasure : public XML_Item
{
public:
	UnitOfMeasure();
	virtual ~UnitOfMeasure();

public:
	std::wstring name;
	std::wstring definition;
	std::wstring symbol;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetName(std::wstring value);
	std::wstring GetName();

	void SetDefinition(std::wstring value);
	std::wstring GetDefinition();

	void SetSymbol(std::wstring value);
	std::wstring GetSymbol();
};

