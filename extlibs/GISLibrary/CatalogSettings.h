#pragma once
class CatalogSettings
{
public:
	CatalogSettings();
	virtual ~CatalogSettings();

public:
	std::wstring featureCatalogPath;
	std::wstring portrayalCatalogPath;
};

