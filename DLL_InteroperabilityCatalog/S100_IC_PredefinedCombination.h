#pragma once
#include "S100_Enumeration.h"
#include "ELE_suppressedFeatureLayers.h"
#include "ELE_derivedFeatures.h"
#include "ELE_colorModeOffsets.h"
class S100_IC_PredefinedCombination
{
public:
	S100_IC_PredefinedCombination();
	virtual ~S100_IC_PredefinedCombination();

	std::wstring identifier;
	std::wstring name;
	std::wstring description;
	std::wstring useConditions;
	int interoperabilityLevel;
	std::list<S100_dataProduct> includedProduct;
	ELE_suppressedFeatureLayers suppressedFeatureLayers;
	ELE_derivedFeatures derivedFeatures;
	ELE_colorModeOffsets colorModeOffsets;


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

