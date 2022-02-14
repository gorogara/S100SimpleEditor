#pragma once
#include <vector>
#include "S100_Catalogue.h"
#include "S100_IC_SaturationOffset.h"
#include "ELE_displayPlanes.h"
#include "S100_IC_PredefinedCombination.h"
#include "S100_IC_SuppressedFeatureLayer.h"
#include "S100_IC_HybridFeature.h"
#include "S100_IC_SuppressedFeatureInstance.h"
#include "ELE_predefinedProductCombinations.h"
#include "ELE_hybridizationRules.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp" 
struct FEATURE_VALUE
{
	FEATURE_VALUE::FEATURE_VALUE()
	{
		geometry = 255;
		drawOrder = 0;
		viewingGroup = 0;
		significant = false;
	}
	std::wstring featureCode;
	std::wstring featureID; 
	int geometry;
	int drawOrder;
	int viewingGroup;
	bool significant;

	int displayPriority;
};

struct LV1_PRODUCT_VALUE
{
	std::wstring PRODUCT;  
	std::unordered_map<std::wstring, FEATURE_VALUE> lv1_features;
}; 
struct FEATURE_REF_VALUE
{
	std::wstring featureCode;
	std::wstring product;
	std::wstring featureRef;
};
struct LV2_PRODUCT_VALUE
{ 
	std::list<std::wstring> PRODUCTs; 
	std::unordered_map<std::wstring, std::list<FEATURE_REF_VALUE>> featuresInProduct;
};


class S100_IC_InteroperabilityCatalogue : public S100_Catalogue
{
public:
	S100_IC_InteroperabilityCatalogue();
	virtual ~S100_IC_InteroperabilityCatalogue(); 
	std::wstring ELEMENTID;     
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureLayer*> SFL_FCODEREF;    
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureLayer*> SFL_FID;    
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureLayer*> SFI_FID;    
	std::unordered_map<std::wstring, S100_IC_HybridFeature*> HYF_FID;     
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureInstance*> SFI_FCODEREF_O;     
	std::unordered_map<std::wstring, S100_IC_HybridFeature*> HYF_FCODEREF_O;     
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureInstance*> SFI_FCODEREF_P;     
	std::unordered_map<std::wstring, S100_IC_HybridFeature*> HYF_FCODEREF_P;     
	std::unordered_map<std::wstring, S100_IC_SuppressedFeatureInstance*> SFI_FCODEREF_S;     
	std::unordered_map<std::wstring, S100_IC_HybridFeature*> HYF_FCODEREF_S;    
	std::unordered_map<std::wstring, S100_IC_HybridFeature*> HYF_RULEIDENTIFIER;

	std::wstring description;
	std::wstring comment;
	std::wstring digitalSignatureReference;
	std::wstring digitalSignatureValue; 
	S100_requirementType requirementType; 
	std::wstring requirementDescription;
	std::list<S100_dataProduct> productCovered; 
	S100_IC_SaturationOffset S100_IC_SaturationOffset;

	ELE_displayPlanes displayPlanes;
	ELE_predefinedProductCombinations predefinedProductCombinations;
	ELE_hybridizationRules hybridizationRules;  

	std::unordered_map<std::wstring, LV1_PRODUCT_VALUE> IC_LEVEL_1_VALUES;     
	std::unordered_map<std::wstring, LV2_PRODUCT_VALUE> IC_LEVEL_2_VALUES;

	int GET_S100_IC_LV1_FEATURE_LIST();
	int GET_S100_IC_LV2_FEATURE_LIST(); 
	FEATURE_VALUE GET_S100_IC_FEATURE_VALUE(FEATURE_REF_VALUE frv);


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
	void BuildHashMap();
};

