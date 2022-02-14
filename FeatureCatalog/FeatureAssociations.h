#pragma once
#include "FeatureAssociation.h"

#include <pugixml.hpp>

class FeatureAssociations :
	public XML_Item
{
public:
	FeatureAssociations(void);
	virtual ~FeatureAssociations(void);

public:
	std::unordered_map<std::wstring, FeatureAssociation> featureAssociation;
	
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

