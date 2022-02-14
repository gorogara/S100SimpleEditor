// S100ExchangeSet.h : S100ExchangeSet DLL�� �⺻ ��� �����Դϴ�. 

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h" 

#include <unordered_map>
#include <string>

class DatasetStructureInExchangeSet
{
public:
	int product=0;
	std::wstring datasetPath;
};

#ifdef S100ES_API_EXPORT
	#define S100ES_API __declspec(dllexport)
#else
	#define S100ES_API __declspec(dllimport)
#endif

namespace ExchangeSet
{
	extern S100ES_API bool AddExchangeSet(std::wstring _filePath);
	extern S100ES_API std::list<std::wstring> GetAllDataset();
	extern S100ES_API std::list<DatasetStructureInExchangeSet> GetDatasetInExchangeSet(std::wstring _filePath);
	extern S100ES_API std::list<std::wstring> SearchForScale(int scale);
	extern S100ES_API std::wstring GetFeatureCatalogName(std::wstring _exchangeFilePath);
	extern S100ES_API std::wstring GetPortrayalCatalogName(std::wstring _exchangeFilePath);
}   
class ExchangeSetXML;

class S100ES_API CS100ExchangeSetApp : public CWinApp
{
public:
	CS100ExchangeSetApp(); 
public:
	virtual BOOL InitInstance();

	std::unordered_map<std::wstring, ExchangeSetXML*> m_exchangeSets;

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
