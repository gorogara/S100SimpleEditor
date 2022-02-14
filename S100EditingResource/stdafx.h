// stdafx.h : 자주 사용하지만 자주 변경되지는 않는  

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
#include <gdiPlus.h>
#include <afxcview.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;