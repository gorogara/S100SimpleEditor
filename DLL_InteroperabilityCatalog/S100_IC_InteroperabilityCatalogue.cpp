#include "stdafx.h"
#include "S100_IC_InteroperabilityCatalogue.h"


S100_IC_InteroperabilityCatalogue::S100_IC_InteroperabilityCatalogue()
{
}


S100_IC_InteroperabilityCatalogue::~S100_IC_InteroperabilityCatalogue()
{
}

void S100_IC_InteroperabilityCatalogue::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	((S100_Catalogue*)this)->S100_Catalogue::GetContents(pNode);
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::wstring baseName = std::wstring(pChildNode->baseName);

		if (baseName.compare(L"description") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				description = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"comment") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				comment = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"digitalSignatureReference") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				digitalSignatureReference = std::wstring(variant.bstrVal).c_str();;
		}

		else if (baseName.compare(L"digitalSignatureValue") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				digitalSignatureValue = std::wstring(variant.bstrVal).c_str();;
		}

		else if (baseName.compare(L"requirementType") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				requirementType = StringToEnum_RequirementType(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"requirementDescription") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				requirementDescription = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"productCovered") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				productCovered.push_back(StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str()));
		}
		else if (baseName.compare(L"S100_IC_SaturationOffset") == 0)
		{
			S100_IC_SaturationOffset.GetContents(pChildNode);
		}
		else if (baseName.compare(L"displayPlanes") == 0)
		{
			displayPlanes.GetContents(pChildNode);
		}
		else if (baseName.compare(L"predefinedProductCombinations") == 0)
		{
			predefinedProductCombinations.GetContents(pChildNode);
		}
		else if (baseName.compare(L"hybridizationRules") == 0)
		{
			hybridizationRules.GetContents(pChildNode);
		}
		else
		{

		}
	}
	BuildHashMap();

	GET_S100_IC_LV1_FEATURE_LIST();
	GET_S100_IC_LV2_FEATURE_LIST(); 
}

void S100_IC_InteroperabilityCatalogue::GetContents(pugi::xml_node node)
{
	((S100_Catalogue*)this)->S100_Catalogue::GetContents(node);
	USES_CONVERSION;

	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();

		if (!strcmp(instructionName, "description"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			description = value;
		}
		else if (!strcmp(instructionName, "comment"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			comment = value;
		}
		else if (!strcmp(instructionName, "digitalSignatureReference"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			digitalSignatureReference = value;
		}
		else if (!strcmp(instructionName, "digitalSignatureValue"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			digitalSignatureValue = value;
		}
		else if (!strcmp(instructionName, "requirementType"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			requirementType = StringToEnum_RequirementType(value);
		}
		else if (!strcmp(instructionName, "requirementDescription"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			requirementDescription = value;
		}
		else if (!strcmp(instructionName, "productCovered"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			productCovered.push_back(StringToEnum_DataProduct(value));
		}
		else if (!strcmp(instructionName, "S100_IC_SaturationOffset"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			S100_IC_SaturationOffset.GetContents(instruction); 
		}
		else if (!strcmp(instructionName, "displayPlanes"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			displayPlanes.GetContents(instruction); 
		}
		else if (!strcmp(instructionName, "predefinedProductCombinations"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			predefinedProductCombinations.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "hybridizationRules"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			hybridizationRules.GetContents(instruction);
		}
	}

	BuildHashMap();

	GET_S100_IC_LV1_FEATURE_LIST();
	GET_S100_IC_LV2_FEATURE_LIST();
}                    
void S100_IC_InteroperabilityCatalogue::BuildHashMap()
{       

	for (auto itor = predefinedProductCombinations.S100_IC_PredefinedCombinations.begin();
		itor != predefinedProductCombinations.S100_IC_PredefinedCombinations.end();
		itor++)
	{
		S100_IC_PredefinedCombination *pc = &(*itor);

		for (auto itor2 = pc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.begin();
			itor2 != pc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.end();
			itor2++)
		{
			S100_IC_SuppressedFeatureLayer *sf = &(*itor2);

			std::vector<std::wstring> in;
			in.push_back(EnumToString_DataProduct(sf->product));
			in.push_back(sf->featureCode);
			std::wstring key = CreateHashMapKey(in);

			SFL_FCODEREF.insert(std::unordered_map<std::wstring, S100_IC_SuppressedFeatureLayer*>::value_type(key, sf));
		}
	}     

	for (auto itor = predefinedProductCombinations.S100_IC_PredefinedCombinations.begin();
		itor != predefinedProductCombinations.S100_IC_PredefinedCombinations.end();
		itor++)
	{
		S100_IC_PredefinedCombination *pc = &(*itor);

		for (auto itor2 = pc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.begin();
			itor2 != pc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.end();
			itor2++)
		{
			S100_IC_SuppressedFeatureLayer *sf = &(*itor2);

			std::vector<std::wstring> in;

			for (auto itor3 = sf->featureRef.begin(); itor3 != sf->featureRef.end(); itor3++)
			{
				in.push_back(*itor3);
			}
			std::wstring key = CreateHashMapKey(in);

			SFL_FID.insert(std::unordered_map<std::wstring, S100_IC_SuppressedFeatureLayer*>::value_type(key, sf));
		}
	}                                                   

}            
int S100_IC_InteroperabilityCatalogue::GET_S100_IC_LV1_FEATURE_LIST()
{
	for (auto itor = displayPlanes.S100_IC_DisplayPlanes.begin(); itor != displayPlanes.S100_IC_DisplayPlanes.end(); itor++)
	{
		S100_IC_DisplayPlane *dp = *itor;

		for (auto itor2 = dp->features.S100_IC_Features.begin(); itor2 != dp->features.S100_IC_Features.end(); itor2++)
		{
			S100_IC_Feature *f = &(*itor2);
			FEATURE_VALUE fv;
			fv.featureID = f->id;
			fv.displayPriority = dp->displayPriority;
			fv.featureCode = f->featureCode;
			fv.geometry = f->geometry;
			fv.drawOrder = f->drawOrder;
			fv.viewingGroup = f->viewingGroup;
			fv.significant = f->significant; 
			std::wstring strProduct = EnumToString_DataProduct(f->product);
			auto pi = IC_LEVEL_1_VALUES.find(strProduct);

			if (pi == IC_LEVEL_1_VALUES.end())
			{
				LV1_PRODUCT_VALUE lv1p;
				lv1p.PRODUCT = strProduct;
				lv1p.lv1_features.insert(std::unordered_map<std::wstring, FEATURE_VALUE>::value_type(fv.featureID, fv));

				IC_LEVEL_1_VALUES.insert(std::unordered_map<std::wstring, LV1_PRODUCT_VALUE>::value_type(strProduct, lv1p));
			}
			else
			{
				LV1_PRODUCT_VALUE *lv1p = &pi->second;
				lv1p->lv1_features.insert(std::unordered_map<std::wstring, FEATURE_VALUE>::value_type(fv.featureID, fv));
			}
		}
	}



	return 0;
}               

int S100_IC_InteroperabilityCatalogue::GET_S100_IC_LV2_FEATURE_LIST()
{
	for (auto itor = predefinedProductCombinations.S100_IC_PredefinedCombinations.begin();
		itor != predefinedProductCombinations.S100_IC_PredefinedCombinations.end();
		itor++)
	{
		S100_IC_PredefinedCombination *pdc = &(*itor);

		LV2_PRODUCT_VALUE lv2p;
		for (auto ipi = pdc->includedProduct.begin(); ipi != pdc->includedProduct.end(); ipi++)
		{
			lv2p.PRODUCTs.push_back(EnumToString_DataProduct(*ipi));
		}

		for (auto itor2 = pdc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.begin();
			itor2 != pdc->suppressedFeatureLayers.S100_IC_SuppressedFeatureLayers.end();
			itor2++)
		{
			S100_IC_SuppressedFeatureLayer *sfl = &(*itor2);

			FEATURE_REF_VALUE frv;

			frv.product = EnumToString_DataProduct(sfl->product);
			frv.featureCode = sfl->featureCode;

			for (auto itor3 = sfl->featureRef.begin(); itor3 != sfl->featureRef.end(); itor3++)
			{
				frv.featureRef = *itor3; 
				auto pi = lv2p.featuresInProduct.find(frv.product);

				if (pi == lv2p.featuresInProduct.end())
				{
					std::list<FEATURE_REF_VALUE> fl;
					fl.push_back(frv);
					lv2p.featuresInProduct.insert(std::unordered_map<std::wstring, std::list<FEATURE_REF_VALUE>>::value_type(frv.product, fl));

				}
				else
				{
					std::list<FEATURE_REF_VALUE> *fl = &pi->second;
					fl->push_back(frv);
				}
			}

			std::vector<std::wstring> in;
			in.push_back(frv.product);
			in.push_back(frv.featureCode);
			std::wstring key = CreateHashMapKey(in);

			IC_LEVEL_2_VALUES.insert(std::unordered_map<std::wstring, LV2_PRODUCT_VALUE>::value_type(key, lv2p));
		}
	}
	return 0;
}                                                        
