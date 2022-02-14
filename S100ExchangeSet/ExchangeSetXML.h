#pragma once
#include "msxml.h"
#include "Tag.h"

#include "S100_SupportFileDiscoveryMetadata.h"
#include "S100_CatalogueMetadata.h"
#include "ScaleSearchFormat.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"


#include <list>
#include <unordered_map>
#import <msxml4.dll>
using namespace std;
class ExchangeSetXML
{
public:
	ExchangeSetXML();
	virtual ~ExchangeSetXML();

private:
	Tag m_root;
	list<Dataset::S100_DatasetDiscoveryMetadata> m_searchData;
	list<Dataset::S100_CatalogueMetadata> m_catalogues;

public:
	void SetRoot(Tag value);
	Tag GetRoot();

	void SetSearchData(list<Dataset::S100_DatasetDiscoveryMetadata> value);
	list<Dataset::S100_DatasetDiscoveryMetadata> GetSearchData();
	
	void SetCatalogues(list<Dataset::S100_CatalogueMetadata> value);
	list<Dataset::S100_CatalogueMetadata> GetCatalogues();
	  
	void XmlOpen(std::wstring path);
	void XmlOpenByPugi(std::wstring path);

	list<Dataset::S100_DatasetDiscoveryMetadata> GetAllDataset();
	list<Dataset::S100_DatasetDiscoveryMetadata> SearchForFilename(std::wstring filename);
	list<Dataset::S100_DatasetDiscoveryMetadata> SearchForSpecificUsage(std::wstring specificUsage);
	list<Dataset::ScaleSearchFormat> SearchForScale(int Scale); 

	void ChileNodeArrange(MSXML2::IXMLDOMNodeListPtr nodes, Tag* parent, Tag &root);
	void ChileNodeArrange(pugi::xml_node nodes, Tag* parent, Tag &root);

	list<Dataset::S100_DatasetDiscoveryMetadata> SearchDataExtract(const Tag root);
	void SearchDiscoveryMetadata(const Tag root, list<Dataset::S100_DatasetDiscoveryMetadata> &list);
	std::wstring GetFeatureCatalog();
	std::wstring GetPortrayalCatalog();
};