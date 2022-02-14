#pragma once
#include "S100_IC_PredefinedCombination.h"
#include <unordered_map>
class ELE_predefinedProductCombinations
{
public:
	ELE_predefinedProductCombinations();
	virtual ~ELE_predefinedProductCombinations();       
	std::unordered_map<std::wstring, S100_IC_PredefinedCombination*> PDCID;       
	std::unordered_map<std::wstring, S100_IC_PredefinedCombination*> PDCNM;

	std::list<S100_IC_PredefinedCombination>  S100_IC_PredefinedCombinations;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

