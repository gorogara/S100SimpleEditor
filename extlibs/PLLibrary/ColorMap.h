#pragma once

#include "stdafx.h"
#include "PLCommon.h"           

class CColorMap
{
public:
	CColorMap();
	virtual ~CColorMap();

public:
	CMap<CString, LPCTSTR, COLOUR*, COLOUR*&> aGetName;

public:
	void Add(COLOUR* tempCColor);
	BOOL ReadFileCheck(CString path);
	BOOL ReadFile(CString path);
	COLOUR* GetAt(CString name);
	void ChangeColorTable(CString _filePath);
};