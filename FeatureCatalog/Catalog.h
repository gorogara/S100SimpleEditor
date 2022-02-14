#pragma once

#include <string>
#include <unordered_map>

class FeatureCatalogue;
class Catalog
{
public:
	Catalog(void);
	Catalog(std::wstring path);
	virtual ~Catalog(void);

public:
	std::wstring m_filepath;
	std::unordered_map<std::wstring, FeatureCatalogue*> m_pCatalogueList;

public:
	bool ReadXMLFile(std::wstring path);
	bool ReadXMLFileByPugiXML(std::wstring path);

	void AddFeatureCatalogue(std::wstring name, FeatureCatalogue* fc);
	std::wstring GetFeatureCatalogueName();

	void SetFilePath(std::wstring& value);
	std::wstring GetFilePath();
};