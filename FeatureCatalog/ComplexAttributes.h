#pragma once
#include "ComplexAttribute.h"

#include <unordered_map>
#include <pugixml.hpp>

class ComplexAttributes :
	public XML_Item
{
public:
	ComplexAttributes(void);
	virtual ~ComplexAttributes(void);

public:
	std::unordered_map<std::wstring, ComplexAttribute> complexAttribute;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};