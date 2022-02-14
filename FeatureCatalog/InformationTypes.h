#pragma once
#include "XML_Item.h"
#include "InformationType.h"
#include <pugixml.hpp>

class InformationTypes : public XML_Item
{
public:
	InformationTypes(void);
	virtual ~InformationTypes(void);

public:
	std::unordered_map<std::wstring, InformationType> informationType;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
	bool SetAssociationFromSuperType(InformationType* it);
};

