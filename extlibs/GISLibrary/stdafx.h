// stdafx.h : ���� ��������� ���� ��������� �ʴ�  

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN 
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 

#include <afxwin.h> 
#include <afxext.h> 

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h> 
#include <afxodlgs.h> 
#include <afxdisp.h> 
#endif 

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h> 
#endif 

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h> 
#endif 

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h> 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> 
#endif 

#include "resource.h"

#include "Common.h"
#include <afxcontrolbars.h>           

#ifndef _TEXTCLUTTER
	#define _TEXTCLUTTER
#endif


#ifndef _GETOBJECT 
#endif

#ifndef _CREATE_MPA_GML 
#endif

#ifndef _LOAD_MPA_GML 
#endif

#ifndef _DRAW_WRECKS_CS
	#define _DRAW_WRECKS_CS
#endif

#ifndef _TEST_PERFORMANCE 
#endif

#ifndef _GET_LANDREGION 
#endif

#ifndef _GET_ATTRIBUTES 
#endif
#ifndef _DEBUG_POINTS 
#endif

#ifndef _USE_SENC
	#define _USE_SENC
#endif

#ifndef _S101_VIEWER 
#endif

#ifndef ROUTE_CHECK 
	#define ROUTE_CHECK
#endif

#ifndef PORTRAYAL_RULE_TEST  
#endif



#import <msxml4.dll>

#include <d2d1.h>
#include <d2d1_1.h>
#pragma comment(lib, "d2d1.lib")

#include "..\extlibs\hdf5\include\hdf5.h"
#include "../LatLonUtility/LatLonUtility.h"

#ifndef D2_SAFE_RELEASE
#define D2_SAFE_RELEASE

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#endif