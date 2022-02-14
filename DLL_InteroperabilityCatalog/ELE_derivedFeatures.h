#pragma once
#include "S100_IC_SuppressedFeatureInstance.h"
#include "ELE_colorModeOffsets.h"
#include "S100_IC_HybridFeature.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <list>
class ELE_derivedFeatures
{
public:
	ELE_derivedFeatures();
	virtual ~ELE_derivedFeatures();

	std::list<S100_IC_SuppressedFeatureInstance> S100_IC_SuppressedFeatureInstances;
	std::list<S100_IC_HybridFeature> S100_IC_HybridFeatures;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};