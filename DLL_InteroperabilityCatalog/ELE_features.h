#pragma once

#include <vector>
#include "S100_IC_Feature.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class ELE_features
{
public:
	ELE_features();
	virtual ~ELE_features();

	std::vector<S100_IC_Feature> S100_IC_Features;
	
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

