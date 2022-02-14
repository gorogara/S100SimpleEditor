#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "stdafx.h"

#include <string> 
class FileLoad
{

public:
	FileLoad(CString path); 
	FileLoad(FileLoad &pStd);
	virtual ~FileLoad();
	
public:
	CString FileLoadFromPath();
	CString m_LoadStr;
	const CString m_Path;
};