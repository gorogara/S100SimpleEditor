#pragma once

#include <string>
#include <map> 

class CatalogSortByProduct;
class CatalogMananger
{
public:
	CatalogMananger();
	virtual ~CatalogMananger();

public:
	std::map <std::wstring, CatalogSortByProduct*> productCatalogs;
};