#pragma once

#include "CATD.h"

#include <Windows.h>
#include <list>
#include <unordered_map>


class DRDirectoryInfo;
class Layer;
class ENC_Catalogue
{
public:
	ENC_Catalogue();
	virtual ~ENC_Catalogue();
	
public:
	CATD m_catd;
	int m_index;
	CString m_filePath;
	MBR m_mbr;
	bool m_bLoaded;
	bool m_bShow;
	ENCLayer *m_layer;

public:
	bool ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
};
typedef list<ENC_Catalogue*> CatalogueList;
typedef unordered_map<int, ENC_Catalogue*> CatalogueMap;
