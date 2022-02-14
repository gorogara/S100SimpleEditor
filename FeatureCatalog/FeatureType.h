#pragma once
#include "S100ObjectType.h"
#include "FeatureUseType.h"
#include "FeatureBinding.h"
#include "InformationBinding.h"
#include "SpatialPrimitiveType.h"

#include <pugixml.hpp>
class FeatureType :
	public S100ObjectType
{
public:
	FeatureType();
	virtual ~FeatureType();

public:
	std::wstring superType; 
	std::list<std::wstring> subType; 
	FeatureUseType featureUseType;
	std::unordered_map<std::wstring, FeatureBinding> featureBinding; 
	std::list<SpatialPrimitiveType> permittedPrimitives;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

