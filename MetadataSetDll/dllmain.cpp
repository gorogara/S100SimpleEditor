// dllmain.cpp : DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

static AFX_EXTENSION_MODULE MetadataSetDllDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{ 
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MetadataSetDll.DLL을 초기화하고 있습니다.\n"); 
		if (!AfxInitExtensionModule(MetadataSetDllDLL, hInstance))
			return 0;           

		new CDynLinkLibrary(MetadataSetDllDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MetadataSetDll.DLL을 종료하고 있습니다.\n"); 
		AfxTermExtensionModule(MetadataSetDllDLL);
	}
	return 1; 
}
