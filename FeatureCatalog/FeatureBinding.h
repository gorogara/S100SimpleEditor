#pragma once
#include "XML_Item.h"
#include "Multiplicity.h"
#include "Reference.h"
class FeatureBinding :
	public XML_Item
{
public:
	FeatureBinding();
	virtual ~FeatureBinding();

public:
	Multiplicity multiplicity;
	Reference association;
	Reference role;
	Reference featureType;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);


};

