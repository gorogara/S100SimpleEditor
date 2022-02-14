#pragma once
#include "S100_IC_FeatureDerivation.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_IC_SuppressedFeatureInstance : public S100_IC_FeatureDerivation
{
public:
	S100_IC_SuppressedFeatureInstance();
	virtual ~S100_IC_SuppressedFeatureInstance();


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

