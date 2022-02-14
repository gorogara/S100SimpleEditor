// PLLibrary.h : PLLibrary DLL의 기본 헤더 파일입니다. 

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif   

class CPLLibraryApp : public CWinApp
{
public:
	CPLLibraryApp(); 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
