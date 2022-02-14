#pragma once

#include <map>

class CatalogWithEditionNumber;
class CatalogSortByProduct
{
public:
	CatalogSortByProduct();
	virtual ~CatalogSortByProduct();

public:
	std::wstring productName;
	std::map<std::wstring, CatalogWithEditionNumber*> catalogs;
};