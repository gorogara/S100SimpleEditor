#include "StdAfx.h"
#include "Catalog.h"
#include "FeatureCatalogue.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

Catalog::Catalog(void)
{
}

Catalog::Catalog(std::wstring path)
{
	ReadXMLFileByPugiXML(path);
}

Catalog::~Catalog(void)
{
	for (auto itor = m_pCatalogueList.begin();
		itor != m_pCatalogueList.end();
		itor++)
	{
		delete itor->second;
	}
}

bool Catalog::ReadXMLFile(std::wstring path)
{
	CoInitialize(NULL);

	SetFilePath(path); 
	MSXML2::IXMLDOMDocument2Ptr g_pXMLDoc; 
	MSXML2::IXMLDOMNodeListPtr pNodeList; 

	if (path.size() > 0)
	{
		g_pXMLDoc.CreateInstance(__uuidof(DOMDocument));
		g_pXMLDoc->async = VARIANT_FALSE;

		g_pXMLDoc->validateOnParse = VARIANT_TRUE;
		g_pXMLDoc->resolveExternals = VARIANT_TRUE; 
		g_pXMLDoc->load((_variant_t)path.c_str());
		pNodeList = g_pXMLDoc->selectNodes(L"S100FC:S100_FC_FeatureCatalogue");
		for (int i = 0; i < pNodeList->Getlength(); i++) 
		{
			MSXML2::IXMLDOMNodePtr pNodePtr = pNodeList->Getitem(i);
			FeatureCatalogue* fc = new FeatureCatalogue();
			fc->GetContents(pNodePtr);
			AddFeatureCatalogue(fc->name, fc);
		}
		pNodeList.Release();
	}
	return true;
}

bool Catalog::ReadXMLFileByPugiXML(std::wstring path)
{ 
	SetFilePath(path);

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(m_filepath.c_str()); 
	pugi::xml_node displayList = doc.child("S100FC:S100_FC_FeatureCatalogue");

 	if (displayList!= nullptr) 
	{
		FeatureCatalogue *fc = new FeatureCatalogue();
		fc->GetContents(displayList);
		AddFeatureCatalogue(fc->name, fc); 
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_FeatureCatalogue loading",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		return true;
	}
	else
	{ 
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"S100FC:S100_FC_FeatureCatalogue is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		return false;
	}
}

void Catalog::AddFeatureCatalogue(std::wstring name, FeatureCatalogue* fc)
{
	if (name.empty() == true || fc == nullptr)
	{
		return;
	}

	m_pCatalogueList.insert({ name, fc });
	int ti = 0;
}

std::wstring Catalog::GetFeatureCatalogueName()
{
	if (m_pCatalogueList.size() > 0)
	{
		return m_pCatalogueList.begin()->first;
	}

	return L"";
}

void Catalog::SetFilePath(std::wstring& value)
{
	m_filepath = value;
}

std::wstring Catalog::GetFilePath()
{
	return m_filepath;
}