// DLL_InteroperabilityCatalog.h : DLL_InteroperabilityCatalog DLL의 기본 헤더 파일입니다. 
#pragma once


#ifdef S100_DLL_EXPORTS
	#define S100_DLL_IC_EXPORTS __declspec(dllexport) 
#else
#define S100_DLL_IC_EXPORTS __declspec(dllimport) 
#endif

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include <string>
#include <vector>
#include <unordered_map> 
struct OUT_FEATURE_VALUE
{
	int drawOrder;
	int viewingGroup;
	bool significant;
	int displayPriority;
	bool suppressedFeature;
};

struct OUT_PDC_VALUE
{
	bool suppressed = false;
};

struct FEATRUE_ATTR_COMBINATION
{
	std::wstring attributeName;
	std::wstring attributeValue;
};

S100_DLL_IC_EXPORTS std::wstring S100_IC_OPEN(std::wstring path);
S100_DLL_IC_EXPORTS std::wstring S100_IC_OPENByPugi(std::wstring path);  
S100_DLL_IC_EXPORTS int GET_S100_IC_LIST(std::vector<std::wstring> &path);
S100_DLL_IC_EXPORTS int GET_S100_IC_PRODUCT_LIST(std::wstring icName, std::vector<std::wstring> &products);
S100_DLL_IC_EXPORTS bool GET_S100_IC_FEATURE_IC_VALUE(std::wstring icName, std::wstring productName, std::wstring featureCode, std::list<FEATRUE_ATTR_COMBINATION> attributeCombination, std::wstring geometryType, OUT_FEATURE_VALUE &ofv);
S100_DLL_IC_EXPORTS bool GET_S100_IC_FEATURE_PDC_VALUE(std::wstring icName, std::wstring productName, std::wstring featureCode, OUT_PDC_VALUE &opv);  


class S100_IC_InteroperabilityCatalogue;   

class CDLL_InteroperabilityCatalogApp : public CWinApp
{
public:
	CDLL_InteroperabilityCatalogApp();

public:
	std::unordered_map<std::wstring, S100_IC_InteroperabilityCatalogue*> map_ICs; 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
