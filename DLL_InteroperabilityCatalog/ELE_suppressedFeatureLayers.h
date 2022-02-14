#pragma once
#include <list>
#include "S100_IC_SuppressedFeatureLayer.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class ELE_suppressedFeatureLayers
{
public:
	ELE_suppressedFeatureLayers();
	virtual ~ELE_suppressedFeatureLayers();
	
	std::list<S100_IC_SuppressedFeatureLayer> S100_IC_SuppressedFeatureLayers;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

