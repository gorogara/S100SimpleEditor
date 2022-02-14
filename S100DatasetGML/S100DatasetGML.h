// S100DatasetGML.h : S100DatasetGML DLL의 기본 헤더 파일입니다. 

#pragma once

#ifdef S100GMLDLL_EXPORTS
#define S100GMLDLL_API __declspec(dllexport) 
#else
#define S100GMLDLL_API __declspec(dllimport) 
#endif

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h" 


class S100GMLDLL_API CS100DatasetGMLApp : public CWinApp
{
public:
	CS100DatasetGMLApp(); 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};