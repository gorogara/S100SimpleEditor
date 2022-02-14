// S100ExchangeSet.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "S100ExchangeSet.h"
#include <algorithm>
#include "ExchangeSetXML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(CS100ExchangeSetApp, CWinApp)
END_MESSAGE_MAP() 

CS100ExchangeSetApp::CS100ExchangeSetApp()
{  
} 

CS100ExchangeSetApp theApp; 

BOOL CS100ExchangeSetApp::InitInstance()
{
	CWinApp::InitInstance();
	COleObjectFactory::RegisterAll();

	return TRUE;
}

int CS100ExchangeSetApp::ExitInstance()
{     

	return CWinApp::ExitInstance();
}



bool ExchangeSet::AddExchangeSet(std::wstring _filePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (StrCmp(L"", _filePath.c_str()))
	{
		ExchangeSetXML *exchangeSet = new ExchangeSetXML();
		exchangeSet->XmlOpenByPugi(_filePath); 
		
		
		theApp.m_exchangeSets[_filePath] = exchangeSet;
	}

	return true;
}

std::list<std::wstring> ExchangeSet::SearchForScale(int scale)
{
	std::list<std::wstring> result;

	for (auto itor = theApp.m_exchangeSets.begin(); itor != theApp.m_exchangeSets.end(); itor++)
	{
		ExchangeSetXML* e = itor->second;

		list<Dataset::ScaleSearchFormat> l = e->SearchForScale(scale);

		for (auto litor = l.begin(); litor != l.end(); litor++)
		{
			Dataset::ScaleSearchFormat* s = &(*litor); 
			{
				result.push_back(s->GetData().GetFilePath());
			}
		}
	}

	return result;
}


std::list<DatasetStructureInExchangeSet> ExchangeSet::GetDatasetInExchangeSet(std::wstring _filePath)
{

	std::list<DatasetStructureInExchangeSet> result;
	auto itor = theApp.m_exchangeSets.find(_filePath);
	if (itor == theApp.m_exchangeSets.end())
		return result;
	ExchangeSetXML* e = itor->second;

	list<Dataset::S100_DatasetDiscoveryMetadata> l = e->GetAllDataset();

	for (auto litor = l.begin(); litor != l.end(); litor++)
	{
		Dataset::S100_DatasetDiscoveryMetadata* s = &(*litor);

		int product = 100;
		DatasetStructureInExchangeSet dses;  
		wstring strProduct = s->GetProductSpecification().GetName();
		std::transform(strProduct.begin(), strProduct.end(), strProduct.begin(), tolower);

		int floi = strProduct.find(L"s-");
		if (floi != -1)
		{
			wstring subStr = strProduct.substr(floi + 2, 3);
			product = _wtoi(subStr.c_str());
		}
		else
		{
			floi = strProduct.find(L"s");
			if (floi != -1)
			{
				wstring subStr = strProduct.substr(floi + 1, 3);
				product = _wtoi(subStr.c_str());
			}
		}
		dses.product = product;

		if (s->GetFilePath().length() > 0)
		{
			std::wstring path = s->GetFilePath() + L"\\" + s->GetFileName();
			dses.datasetPath = path;
		}
		else
		{
			dses.datasetPath = s->GetFileName();
		}
		result.push_back(dses);
	}
	return result;
}

std::list<std::wstring> ExchangeSet::GetAllDataset()
{
	std::list<std::wstring> result;

	for (auto itor = theApp.m_exchangeSets.begin(); itor != theApp.m_exchangeSets.end(); itor++)
	{
		ExchangeSetXML* e = itor->second;

		list<Dataset::S100_DatasetDiscoveryMetadata> l = e->GetAllDataset();

		for (auto litor = l.begin(); litor != l.end(); litor++)
		{
			Dataset::S100_DatasetDiscoveryMetadata* s = &(*litor); 
			{
				CString fp;
				if (s->GetFilePath().size() > 0)
				{
					fp.Format(L"%s\\%s", s->GetFilePath().c_str(), s->GetFileName().c_str());
				}
				else
				{
					fp.Format(L"%s", s->GetFileName().c_str());
				}
				result.push_back(std::wstring(fp));
				fp.ReleaseBuffer();
			}
		}
	}
	return result;
}


std::wstring ExchangeSet::GetFeatureCatalogName(std::wstring _exchangeFilePath)
{
	auto itor = theApp.m_exchangeSets.find(_exchangeFilePath);
	if (itor == theApp.m_exchangeSets.end())
		return L"";

	ExchangeSetXML* e = itor->second;

	return e->GetFeatureCatalog();
}

std::wstring ExchangeSet::GetPortrayalCatalogName(std::wstring _exchangeFilePath)
{
	auto itor = theApp.m_exchangeSets.find(_exchangeFilePath);
	if (itor == theApp.m_exchangeSets.end())
		return L"";

	ExchangeSetXML* e = itor->second;

	return e->GetPortrayalCatalog();
}