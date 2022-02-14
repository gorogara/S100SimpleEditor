// LibMFCUtil.h : main header file for the LibMFCUtil DLL 

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" 

#include <vector>
#include <atlimage.h>
#define DELETE_NULL(x) { delete[] x; x = nullptr; }   

#ifdef LIBMFC_API_EXPORT
	#define LIBMFC_API __declspec(dllexport)
#else
	#define LIBMFC_API __declspec(dllimport)
#endif

class CTreeCtrl;

class CLibMFCUtilApp : public CWinApp
{
public:
	CLibMFCUtilApp();
	LARGE_INTEGER sPos;
	LARGE_INTEGER ePos;
	LARGE_INTEGER freq; 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

namespace LibMFCUtil
{
	extern LIBMFC_API bool ResizeCImage(CString _pathSrc, CString _pathDst, int _newWidth, int _newHeight);
	extern LIBMFC_API bool ResizeCImage(CImage& _src, CImage& _dst, int _newWidth, int _newHeight);
	extern LIBMFC_API bool CheckFileKhoaDmsFormat(CString _path); 
	extern LIBMFC_API bool CheckKhoaDmsFormat(CString _str); 
	extern LIBMFC_API int CheckKhoaDMSForm(std::wstring str);
	extern LIBMFC_API CString GetClipboardText(HWND hWnd);
	extern LIBMFC_API std::wstring EraseAllSpace(std::wstring str);
	extern LIBMFC_API char* ConvertWCtoC(wchar_t* str); 
	extern LIBMFC_API wchar_t* ConvertCtoWC(char* str); 
	extern LIBMFC_API HTREEITEM FindTreeItem(CTreeCtrl* pTree, HTREEITEM hItem, DWORD data);
	extern LIBMFC_API int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	extern LIBMFC_API CString GetMD5(BYTE* pBuf, UINT nLength);
	extern LIBMFC_API CString GetMD5(CFile& File);
	extern LIBMFC_API CString GetMD5(const CString& strFilePath);
	extern LIBMFC_API void StartPerformanceTimer();
	extern LIBMFC_API void EndPerformanceTimer();
	extern LIBMFC_API __int64 GetPerformanceTimeByMS();
	extern LIBMFC_API __int64 GetPerformanceTimeByMicrosecond();
	extern LIBMFC_API void OutputPerformanceTimeByMS();
	extern LIBMFC_API void OutputPerformanceTimeByMicrosecond();
	extern LIBMFC_API POINT RotatePoint(POINT& pt, double radian, int centerX, int centerY);
	extern LIBMFC_API RECT RotateRect(RECT& rect, double radian, int centerX, int centerY);
	extern LIBMFC_API std::string GetHDF5SplittedFilePath(std::string path); 
	extern LIBMFC_API CString GetDesktopPath();

	extern LIBMFC_API std::string CStringToString(CString str);
	extern LIBMFC_API std::string WStringToString(std::wstring str); 
	extern LIBMFC_API CString ReplaceExtension(CString path, CString newExtention); 
	extern LIBMFC_API CString GetExtension(CString path); 
	extern LIBMFC_API CString GetFileName(CString path);

	extern LIBMFC_API CString GetFolderPathFromFilePath(CString path);   
	extern LIBMFC_API std::vector<CString> GetFilePathFromFolder(CString folderPath, CString extension = _T(""));
	
	extern LIBMFC_API void MercatorProjectionForward(double lon, double lat, double* x, double* y);
	extern LIBMFC_API void MercatorProjectionReverse(double x, double y, double* lon, double* lat);
	extern LIBMFC_API double MercatorProjectionForwardX(double lon);
	extern LIBMFC_API double MercatorProjectionForwardY(double lat);
	extern LIBMFC_API double MercatorProjectionReverseX(double x);
	extern LIBMFC_API double MercatorProjectionReverseY(double y);

	extern LIBMFC_API CString INIReadString(CString strAppName, CString strKeyName, CString strFilePath);
	extern LIBMFC_API void INIWriteString(CString strAppName, CString strKeyName, CString strValue, CString strFilePath);

	extern LIBMFC_API bool CheckDirExistAndCreate(CString path);

	extern LIBMFC_API bool CopyTextToClipboard(CString str);

	extern LIBMFC_API bool SaveImage(CString path, HDC& hdc, int width, int height);

	extern LIBMFC_API bool SaveImage2(CString path, CImage& image, HDC& hdc, int width, int height);

	extern LIBMFC_API CString FullPathToPath(CString fullPath);

	extern LIBMFC_API void createDirectoryRecursively(const std::wstring &directory);
}