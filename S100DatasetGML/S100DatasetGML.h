// S100DatasetGML.h : S100DatasetGML DLL�� �⺻ ��� �����Դϴ�. 

#pragma once

#ifdef S100GMLDLL_EXPORTS
#define S100GMLDLL_API __declspec(dllexport) 
#else
#define S100GMLDLL_API __declspec(dllimport) 
#endif

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
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