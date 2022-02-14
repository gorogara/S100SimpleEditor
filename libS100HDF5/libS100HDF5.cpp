// libS100HDF5.cpp : DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "libS100HDF5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(ClibS100HDF5App, CWinApp)
END_MESSAGE_MAP() 

ClibS100HDF5App::ClibS100HDF5App()
{  
} 

ClibS100HDF5App theApp;

const GUID CDECL _tlid = {0xa180f301,0x7048,0x43fe,{0xbe,0xe9,0x69,0x85,0x4f,0xd9,0x82,0xe0}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0; 

BOOL ClibS100HDF5App::InitInstance()
{
	CWinApp::InitInstance();  
	COleObjectFactory::RegisterAll();

	return TRUE;
} 

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
} 

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
} 

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
} 

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}
