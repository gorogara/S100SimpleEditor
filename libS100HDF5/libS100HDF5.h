  

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"    
#ifdef LIBS100HDF5_EXPORTS
#define LIBS100HDF5_API __declspec(dllexport)
#define LIBS100HDF5_TEMPLATE
#else
#define LIBS100HDF5_API __declspec(dllimport)
#define LIBS100HDF5_TEMPLATE extern
#endif

class ClibS100HDF5App : public CWinApp
{
public:
	ClibS100HDF5App(); 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
