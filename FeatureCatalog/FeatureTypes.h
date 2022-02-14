#pragma once
#include "XML_Item.h" 

#include <pugixml.hpp>
#include "FeatureType.h"

class FeatureTypes :
	public XML_Item
{
public:
	FeatureTypes(void);
	virtual ~FeatureTypes(void);
	
public:
	std::unordered_map<std::wstring, FeatureType> featureType;
	
public:
	void ApplySuperType();
	bool SetAttributeFromSuperType(FeatureType* ft);
	bool SetAssociationFromSuperType(FeatureType* ft);

	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};