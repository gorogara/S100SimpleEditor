// DLL_InteroperabilityCatalog.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "DLL_InteroperabilityCatalog.h"
#include "S100_IC_InteroperabilityCatalogue.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(CDLL_InteroperabilityCatalogApp, CWinApp)
END_MESSAGE_MAP() 

CDLL_InteroperabilityCatalogApp::CDLL_InteroperabilityCatalogApp()
{  
} 

CDLL_InteroperabilityCatalogApp theApp; 

BOOL CDLL_InteroperabilityCatalogApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

int CDLL_InteroperabilityCatalogApp::ExitInstance()
{ 
	for (auto itor = map_ICs.begin(); itor != map_ICs.end(); itor++)
	{
		delete itor->second;
	}
	return CWinApp::ExitInstance();
}

std::wstring S100_IC_OPEN(std::wstring path)
{
	MSXML2::IXMLDOMDocument2Ptr g_pXMLDoc; 
	MSXML2::IXMLDOMNodeListPtr pNodeList; 

	std::wstring retName;

	for (auto itor = theApp.map_ICs.begin(); itor != theApp.map_ICs.end(); itor++)
	{
		S100_IC_InteroperabilityCatalogue *ic = itor->second;

		delete ic;
	}
	theApp.map_ICs.clear();

	if (path.size() > 0)
	{
		g_pXMLDoc.CreateInstance(__uuidof(DOMDocument));
		g_pXMLDoc->async = VARIANT_FALSE;

		g_pXMLDoc->validateOnParse = VARIANT_TRUE;
		g_pXMLDoc->resolveExternals = VARIANT_TRUE; 
		if (g_pXMLDoc->load((_variant_t)path.c_str()))
		{
			pNodeList = g_pXMLDoc->GetchildNodes();

			for (int k = 0; k < pNodeList->Getlength(); k++)
			{
				MSXML2::IXMLDOMNodePtr pNodePtr = pNodeList->Getitem(k);
				std::wstring nodeName = (LPCTSTR)pNodePtr->GetnodeName();
				if (nodeName.find(L"S100_IC_InteroperabilityCatalogue") == std::wstring::npos)
				{
					continue;
				}
				S100_IC_InteroperabilityCatalogue *ic = new S100_IC_InteroperabilityCatalogue();
				ic->GetContents(pNodePtr);
				theApp.map_ICs.insert(std::unordered_map<std::wstring, S100_IC_InteroperabilityCatalogue*>::value_type(ic->name, ic));

				retName = ic->name;
			}
		}
	}

	return retName;
}

std::wstring S100_IC_OPENByPugi(std::wstring path)
{
	pugi::xml_document xmldoc;
	pugi::xml_parse_result result = xmldoc.load_file(path.c_str());

	std::wstring retName;

	for (auto itor = theApp.map_ICs.begin(); itor != theApp.map_ICs.end(); itor++)
	{
		S100_IC_InteroperabilityCatalogue *ic = itor->second;

		delete ic;
	}

	theApp.map_ICs.clear();
	pugi::xml_node first_child = xmldoc.first_child();
	auto dsfsf = first_child.name();

	if (strcmp(first_child.name(),"S100IC:S100_IC_InteroperabilityCatalogue")==0)
	{
		S100_IC_InteroperabilityCatalogue *ic = new S100_IC_InteroperabilityCatalogue();
		ic->GetContents(first_child);
		theApp.map_ICs.insert(std::unordered_map<std::wstring, S100_IC_InteroperabilityCatalogue*>::value_type(ic->name, ic));
		retName = ic->name;
	}
	return retName;
}

enum ATTRIBUTE_COMBINATION_OPERATOR
{
	_EQUAL = 0,
	_NOT,
	_IN,
	_NOT_IN,
	_GT,
	_GE,
	_LT,
	_LE,
	_NULL
};


ATTRIBUTE_COMBINATION_OPERATOR StringToEnum_CombinationOperator(std::wstring name)
{
	if (name.compare(L"=") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_EQUAL; }
	else if (name.compare(L"=!") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_NOT; }
	else if (name.compare(L"in") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_IN; }
	else if (name.compare(L"notIn") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_NOT_IN; }
	else if (name.compare(L"gt") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_GT; }
	else if (name.compare(L"ge") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_GE; }
	else if (name.compare(L"lt") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_LT; }
	else if (name.compare(L"le") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_LE; }
	else if (name.compare(L"null") == 0) { return ATTRIBUTE_COMBINATION_OPERATOR::_NULL; }
	else return ATTRIBUTE_COMBINATION_OPERATOR::_NULL;
}  
int GET_S100_IC_LIST(std::vector<std::wstring> &path)
{
	for (auto itor = theApp.map_ICs.begin(); itor != theApp.map_ICs.end(); itor++)
	{
		path.push_back(itor->second->name);
	}

	return theApp.map_ICs.size();
}

int GET_S100_IC_PRODUCT_LIST(std::wstring icName, std::vector<std::wstring> &products)
{
	auto it = theApp.map_ICs.find(icName);
	if (it == theApp.map_ICs.end())
		return -1;

	S100_IC_InteroperabilityCatalogue *ic = it->second;

	for (auto itor = ic->productCovered.begin(); itor != ic->productCovered.end(); itor++)
	{
		S100_dataProduct dp = *itor;

		products.push_back(EnumToString_DataProduct(dp));
	}

	return 0;
}

bool S100_IC_ATTR_COMBINATION_CHECK(std::wstring attributeName,
	std::wstring oper,
	std::wstring value,
	const std::list<FEATRUE_ATTR_COMBINATION> &attributeCombination)
{
	ATTRIBUTE_COMBINATION_OPERATOR eOper = StringToEnum_CombinationOperator(oper);
	switch (eOper)
	{
	case ATTRIBUTE_COMBINATION_OPERATOR::_EQUAL:
		for (auto it = attributeCombination.begin(); it != attributeCombination.end(); it++)
		{
			FEATRUE_ATTR_COMBINATION ac = *it;

			if (ac.attributeName.compare(attributeName) == 0 && ac.attributeValue.compare(value) == 0)
			{
				return true;
			}
		}
		return false;
	default:
		return false;
	}
	return false;
}

S100_IC_Feature* S100_IC_ATTR_CHECK(std::list<S100_IC_Feature*> *features, const std::list<FEATRUE_ATTR_COMBINATION> &attributeCombination)
{
	std::map<int, std::list<S100_IC_Feature*>> featuresSortByLevel;
	for (auto fsi = features->begin(); fsi != features->end(); fsi++)
	{
		S100_IC_Feature* feature = *fsi;
		int cnt = feature->attributeCombination.size();

		auto ffi = featuresSortByLevel.find(cnt + 1);
		if (ffi == featuresSortByLevel.end())
		{
			std::list<S100_IC_Feature*> features;
			features.push_back(feature);
			featuresSortByLevel.insert(std::map<int, std::list<S100_IC_Feature*>>::value_type(cnt + 1, features));
		}
		else
		{
			std::list<S100_IC_Feature*> features;
			features.push_back(feature);
		}
	}

	for (auto fsi = featuresSortByLevel.rbegin(); fsi != featuresSortByLevel.rend(); fsi++)
	{
		std::list<S100_IC_Feature*> *sfs = &fsi->second;
		for (auto fsi = sfs->begin(); fsi != sfs->end(); fsi++)
		{
			S100_IC_Feature* feature = *fsi;
			for (auto itor = feature->attributeCombination.begin();
				itor != feature->attributeCombination.end();
				itor++)
			{
				std::wstring com = *itor;

				std::wstring _delimiter = L" ";
				std::wstring::size_type lastPos = com.find_first_not_of(_delimiter, 0); 
				std::wstring::size_type Pos = com.find_first_of(_delimiter, lastPos); 

				std::vector<std::wstring> token;
				while (std::wstring::npos != Pos || std::wstring::npos != lastPos)
				{
					token.push_back(com.substr(lastPos, Pos - lastPos));
					lastPos = com.find_first_not_of(_delimiter, Pos); 
					Pos = com.find_first_of(_delimiter, lastPos); 
				}

				if (token.size() >= 3)
				{
					std::wstring fn = token[0];
					std::wstring oper = token[1];
					std::wstring value = token[2];

					if (S100_IC_ATTR_COMBINATION_CHECK(fn, oper, value, attributeCombination))
					{
						continue;
					}

				}

				return NULL;
			}
			return feature;
		}
	}
	return NULL;

}

bool GET_S100_IC_FEATURE_IC_VALUE(std::wstring icName,
	std::wstring productName,
	std::wstring featureCode,
	std::list<FEATRUE_ATTR_COMBINATION> attributeCombination,
	std::wstring geometryType,
	OUT_FEATURE_VALUE &ofv)
{
	ofv.drawOrder = 0;
	ofv.viewingGroup = 0;
	ofv.significant = false;
	ofv.displayPriority = 0;
	ofv.suppressedFeature = false;

	auto it = theApp.map_ICs.find(icName);
	if (it == theApp.map_ICs.end())
		return false;

	S100_IC_InteroperabilityCatalogue *ic = it->second;

	auto l1vi = ic->IC_LEVEL_1_VALUES.find(productName);
	if (l1vi == ic->IC_LEVEL_1_VALUES.end())
		return false;
	LV1_PRODUCT_VALUE *pv1 = &l1vi->second;

	std::vector<std::wstring> in;
	std::wstring key;

	in.push_back(productName);
	in.push_back(featureCode);
	in.push_back(geometryType);
	key = CreateHashMapKey(in);

	auto fcode = ic->displayPlanes.map_DP_FCODE.find(key);

	if (fcode == ic->displayPlanes.map_DP_FCODE.end())
		return false;

	std::list<S100_IC_Feature*> *features = &fcode->second;

	S100_IC_Feature* feature = S100_IC_ATTR_CHECK(features, attributeCombination);

	if (!feature)
		return false;

	auto ff = pv1->lv1_features.find(feature->id);

	FEATURE_VALUE *fv = &ff->second;

	ofv.displayPriority = fv->displayPriority;
	ofv.viewingGroup = fv->viewingGroup;
	ofv.drawOrder = fv->drawOrder;
	ofv.significant = fv->significant; 

	return true;
}

bool GET_S100_IC_FEATURE_PDC_VALUE(std::wstring icName,
	std::wstring productName,
	std::wstring featureCode,
	OUT_PDC_VALUE &opv)
{
	auto it = theApp.map_ICs.find(icName);
	if (it == theApp.map_ICs.end())
		return false;

	S100_IC_InteroperabilityCatalogue *ic = it->second;

	std::vector<std::wstring> in;
	std::wstring key;

	in.push_back(productName);
	in.push_back(featureCode);
	key = CreateHashMapKey(in);

	auto l2vi = ic->IC_LEVEL_2_VALUES.find(key); 
	if (l2vi == ic->IC_LEVEL_2_VALUES.end())
		opv.suppressed = false;
	else
		opv.suppressed = true;

	return true;
}