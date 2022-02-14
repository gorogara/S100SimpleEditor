// stdafx.h : include file for standard system include files,  

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

#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1")

#include <vector>
#include <map>
#include <gdiplus.h>
using namespace Gdiplus;

#define S102_STEP_COUNT 7

#define S111_STEP_COUNT 9

struct PointXY {
	double x;
	double y;
};

struct DataPerPoint {
	float dir;
	float spd;
};

struct Data {
	std::vector<DataPerPoint> dataPerPoint;
};

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