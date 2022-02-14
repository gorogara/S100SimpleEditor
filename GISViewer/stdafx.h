// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface            

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN 
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  
#define _AFX_ALL_WARNINGS

#include <afxwin.h> 
#include <afxext.h> 

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h> 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> 
#endif 

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

#include <afxcontrolbars.h> 

#include "Common.h"

#include <afxsock.h> 
#include <gdiPlus.h>
#include <afxcview.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

#ifndef _TEXTCLUTTER
#define _TEXTCLUTTER
#endif

#ifndef _USEINIT_WORLDMAP_OPEN
#define _USEINIT_WORLDMAP_OPEN
#endif

#ifndef _USEINIT_EXCHANGE_SET_OPEN 
#endif

#ifndef _SQLITE_OBJECT
#define _SQLITE_OBJECT
#endif

#ifndef ROUTE_CHECK 
#define ROUTE_CHECK
#endif

#ifndef EXECUTE_FILE_WITH_ARGUMENT_OF_DATASET 
#define EXECUTE_FILE_WITH_ARGUMENT_OF_DATASET 
#endif

#ifndef TILE_MAP 
#endif      
#define TID_ROUTE_SIMULATION 1126
#define TID_S111_SIMULATION 1127

#import <msxml4.dll>

#define DEFAULT_USER_POINT_SIZE 13

#define ZOOM_FACTOR 30

#define WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_ATTRIBUTE	80001

#define WM_TRANSLATION_MESSAGE_TO_PARENT_ADD_VECTOR			80101
#define WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_VECTOR		80102
#define WM_TRANSLATION_MESSAGE_TO_PARENT_SELECTED_VECTOR	80103

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