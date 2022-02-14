#pragma once
#include "S100_IC_FeatureDerivation.h"

class S100_IC_HybridFeature : public S100_IC_FeatureDerivation
{
public:
	S100_IC_HybridFeature();
	virtual ~S100_IC_HybridFeature(); 
	std::wstring creationRule;


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

