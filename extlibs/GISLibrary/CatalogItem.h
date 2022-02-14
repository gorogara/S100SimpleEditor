#pragma once
#include <atlstr.h>

class Catalog;
class CatalogItem
{
public:
	CatalogItem()
	{
		m_catalog = nullptr;
	}
	Catalog* m_catalog;
	CString m_name;
	CString m_version;
};
