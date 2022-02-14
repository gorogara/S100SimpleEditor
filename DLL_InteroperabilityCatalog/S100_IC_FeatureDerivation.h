#pragma once
#include "S100_Enumeration.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_IC_FeatureDerivation
{
public:
	S100_IC_FeatureDerivation();
	virtual ~S100_IC_FeatureDerivation();


	S100_dataProduct primaryProduct;
	std::wstring primaryFeatureCode; 
	std::wstring primarySelector;
	S100_dataProduct secondaryProduct;
	std::wstring secondaryFeatureCode;  
	std::wstring secondarySelector; 
	S100_dataProduct outputProduct;
	std::wstring outputFeatureCode;  
	std::wstring featureRef;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

