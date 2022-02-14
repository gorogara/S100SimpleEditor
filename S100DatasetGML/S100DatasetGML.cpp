// S100DatasetGML.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "S100DatasetGML.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(CS100DatasetGMLApp, CWinApp)
END_MESSAGE_MAP() 

CS100DatasetGMLApp::CS100DatasetGMLApp()
{  
} 

CS100DatasetGMLApp theApp; 

BOOL CS100DatasetGMLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}