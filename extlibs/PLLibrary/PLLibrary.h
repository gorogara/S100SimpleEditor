// PLLibrary.h : PLLibrary DLL�� �⺻ ��� �����Դϴ�. 

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif   

class CPLLibraryApp : public CWinApp
{
public:
	CPLLibraryApp(); 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
