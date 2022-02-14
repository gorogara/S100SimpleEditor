#pragma once
#include "XML_Item.h"
#include "DefinitionSource.h"

#include <string>
#include <pugixml.hpp>

class DefinitionSources : public XML_Item
{
public:
	DefinitionSources();
	virtual ~DefinitionSources();

public:
	std::wstring sourceIdentifier;
	std::unordered_map<std::wstring, DefinitionSource> definitionSource;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

