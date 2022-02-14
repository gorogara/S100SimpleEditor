// LibMFCUtil.cpp : Defines the initialization routines for the DLL. 

#include "stdafx.h"
#include "LibMFCUtil.h"

#include <algorithm>
#include <regex>
#include <gdiplus.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "MD5ChecksumDefines.h"
#include "MD5Checksum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEG2RAD (M_PI / 180.0); 
#define RAD2DEG (180.0 / M_PI);                         

BEGIN_MESSAGE_MAP(CLibMFCUtilApp, CWinApp)
END_MESSAGE_MAP() 

CLibMFCUtilApp::CLibMFCUtilApp()
{  
	QueryPerformanceFrequency(&freq);
} 

CLibMFCUtilApp theApp; 

BOOL CLibMFCUtilApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


bool LibMFCUtil::ResizeCImage(CString _pathSrc, CString _pathDst, int _newWidth, int _newHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CImage srcImage;
	HRESULT res = srcImage.Load(_pathSrc);

	if (SUCCEEDED(res))
	{ 
		CImage dstImage;
		dstImage.CreateEx(_newWidth, _newHeight, 32, BI_RGB, NULL, dstImage.createAlphaChannel); 
		SetStretchBltMode(dstImage.GetDC(), COLORONCOLOR);
		dstImage.ReleaseDC(); 
		srcImage.SetTransparentColor(RGB(255, 255, 255));
		srcImage.StretchBlt(dstImage.GetDC(), 0, 0, _newWidth, _newHeight, SRCCOPY);
		dstImage.ReleaseDC();

		dstImage.Save(_pathDst);

		return true;
	}
	else
	{
		
	}

	return false;
}


bool LibMFCUtil::ResizeCImage(CImage& _src, CImage& _dst, int _newWidth, int _newHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	_dst.CreateEx(_newWidth, _newHeight, 32, BI_RGB, NULL, _dst.createAlphaChannel); 
	SetStretchBltMode(_dst.GetDC(), COLORONCOLOR);
	_dst.ReleaseDC(); 
	_src.SetTransparentColor(RGB(255, 255, 255));
	_src.StretchBlt(_dst.GetDC(), 0, 0, _newWidth, _newHeight, SRCCOPY);
	_dst.ReleaseDC();

	return true;
}


bool LibMFCUtil::CheckFileKhoaDmsFormat(CString _path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CStdioFile file;

	bool bCheck = true;

	if (file.Open(_path, CFile::modeRead))
	{
		CString line;

		while (file.ReadString(line)) {
			bCheck = LibMFCUtil::CheckKhoaDmsFormat(line);
			if (!bCheck)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

#pragma warning(disable:4129)
bool LibMFCUtil::CheckKhoaDmsFormat(CString _str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	std::wregex rx(L"^\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[NSns]{1}\\s*\,?\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[EWew]{1}\\s*$");
	std::wstring wstr(_str);

	if (!std::regex_match(wstr, rx))
	{
		return false;
	}

	return true;
}


int LibMFCUtil::CheckKhoaDMSForm(std::wstring str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	std::wregex rx1(L"^\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}[NSns]{1}\\,?\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}[EWew]{1}$");
	std::wregex rx2(L"^\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}\\,{1}\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}$");

	if (std::regex_match(str, rx1))
	{
		return 1;
	}
	else if (std::regex_match(str, rx2))
	{
		return 2;
	}

	return 0;
}


CString LibMFCUtil::GetClipboardText(HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!OpenClipboard(hWnd))
	{
		OutputDebugString(_T("Can't open clipboard!\n"));
		return _T("");
	}

	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	WCHAR* buffer = (WCHAR*)GlobalLock(hData);
	CString text;
	text.Format(_T("%s"), buffer);
	GlobalUnlock(hData);
	CloseClipboard();

	return text;
}


std::wstring LibMFCUtil::EraseAllSpace(std::wstring str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}


char* LibMFCUtil::ConvertWCtoC(wchar_t* str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	char* pStr = nullptr; 
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	if (strSize <= 0)
	{
		OutputDebugString(_T("Failed to WideCharToMultiByte()\n"));
		return nullptr;
	} 
	pStr = new char[strSize]; 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}


wchar_t* LibMFCUtil::ConvertCtoWC(char* str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	wchar_t* pStr = nullptr; 
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	if (strSize <= 0)
	{
		OutputDebugString(_T("Failed to MultiByteToWideChar()\n"));
		return nullptr;
	} 
	pStr = new WCHAR[strSize]; 
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;

}


HTREEITEM LibMFCUtil::FindTreeItem(CTreeCtrl* pTree, HTREEITEM hItem, DWORD data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HTREEITEM hItemFind, hItemChild, hItemSibling;
	hItemFind = hItemChild = hItemSibling = NULL;

	if (pTree->GetItemData(hItem) == data)
	{
		hItemFind = hItem;
	}
	else
	{
		hItemChild = pTree->GetChildItem(hItem);
		if (hItemChild)
		{
			hItemFind = FindTreeItem(pTree, hItemChild, data);
		}
	
		hItemSibling = pTree->GetNextSiblingItem(hItem);
		if (!hItemFind && hItemSibling)
		{
			hItemFind = FindTreeItem(pTree, hItemSibling, data);	
		}
	}

	return hItemFind;
}


CString LibMFCUtil::ReplaceExtension(CString path, CString newExtention)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int indexLastDot = path.ReverseFind(_T('.'));

	int lengthExtension = path.GetLength() - indexLastDot;

	path.Delete(indexLastDot + 1, lengthExtension);

	path.Append(newExtention);

	return path;
} 
CString LibMFCUtil::GetExtension(CString path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString ext = _T("");

	int length = path.GetLength();

	if (length <= 0) 
		return ext;

	int indexOfLastReverseSlash = path.ReverseFind('\\'); 
	if (indexOfLastReverseSlash >= 0)//전체 경로를 불러온경우
	{
		int indexOfLastDot = path.ReverseFind('.');
		if (indexOfLastDot >= 0)
		{
			int lengthOfExtension = path.GetLength() - indexOfLastDot - 1;
			ext = path.Right(lengthOfExtension);
			return ext;
		}
	}
	else 
	{
		int indexOfLastDot = path.ReverseFind('.');
		if (indexOfLastDot >= 0)
		{
			int lengthOfExtension = path.GetLength() - indexOfLastDot - 1;
			ext = path.Right(lengthOfExtension);
			return ext;
		}
	}

	
	return ext;
}


CString LibMFCUtil::GetFileName(CString path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString name = path;

	int length = path.GetLength();

	if (length <= 0)
		return name;

	int indexOfLastReverseSlash = path.ReverseFind('\\');
	if (indexOfLastReverseSlash >= 0)
	{
		int indexOfLastDot = path.ReverseFind('.');
		if (indexOfLastDot >= 0)
		{
			return path.Mid(indexOfLastReverseSlash + 1, indexOfLastDot - indexOfLastReverseSlash - 1);
		}
	}
	else
	{ 
		int indexOfLastDot = path.ReverseFind('.');
		int nameLength = path.GetLength();
		if (indexOfLastDot >= 0)
		{
			return path.Mid(0, indexOfLastDot);
		}
	}

	return name;
}


CString LibMFCUtil::GetFolderPathFromFilePath(CString path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CFile file;
	if (file.Open(path, CFile::modeRead ))
	{
		CT2CA pszConvertedAnsiString(file.GetFilePath());
		std::string s(pszConvertedAnsiString);
		int itor = s.find_last_of('\\');
		std::string result = s.substr(0,itor)+"\\";

		CString resultC(result.c_str());
		return resultC;
		return file.GetFilePath();
	}
	return _T("");
}


int LibMFCUtil::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT  num = 0; 
	UINT  size = 0; 

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1; 

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1; 

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; 
		}
	}

	free(pImageCodecInfo);
	return -1; 
}


std::vector<CString> LibMFCUtil::GetFilePathFromFolder(CString folderPath, CString extension)
{
	CFileFind finder;

	BOOL bWorking = finder.FindFile(folderPath + _T("\\*.") + extension);

	std::vector<CString> vecFilePath;
	CString filePath;

	while (bWorking)
	{
		bWorking = finder.FindNextFileW(); 
		{
			vecFilePath.push_back(finder.GetFilePath());
		}
	}

	return vecFilePath;
}


CString LibMFCUtil::GetMD5(BYTE* pBuf, UINT nLength)
{
	return CMD5Checksum::GetMD5(pBuf, nLength);
}


CString LibMFCUtil::GetMD5(CFile& File)
{
	return CMD5Checksum::GetMD5(File);
}


CString LibMFCUtil::GetMD5(const CString& strFilePath)
{
	return CMD5Checksum::GetMD5(strFilePath);
}


void LibMFCUtil::MercatorProjectionForward(double lon, double lat, double* x, double* y)
{
	*x = MercatorProjectionForwardX(lon);
	*y = MercatorProjectionForwardY(lat);
}


void LibMFCUtil::MercatorProjectionReverse(double x, double y, double* lon, double* lat)
{
	*lon = MercatorProjectionReverseX(x);
	*lat = MercatorProjectionReverseY(y);
}


double LibMFCUtil::MercatorProjectionForwardX(double lon)
{
	return lon * DEG2RAD;
}


double LibMFCUtil::MercatorProjectionForwardY(double lat)
{
	if (lat <= -85.0f) {
		lat = -85.0f;
	}
	else if (lat >= 85.0f)
	{
		lat = 85.0f;
	}

	lat *= DEG2RAD;
	lat = log(tan((lat / 2.0) + M_PI_4));

	return lat;
}


double LibMFCUtil::MercatorProjectionReverseX(double x)
{
	return x * RAD2DEG;
}


double LibMFCUtil::MercatorProjectionReverseY(double y)
{
	y = 2 * (atan(exp(y)) - M_PI_4);
	return y * RAD2DEG;
}


std::string LibMFCUtil::CStringToString(CString str)
{
	CT2CA convertedString(str);
	return std::string(convertedString);
}

std::string LibMFCUtil::WStringToString(std::wstring str) 
{
	std::string Value;
	Value.assign(str.begin(), str.end());

	return Value;
}


void LibMFCUtil::StartPerformanceTimer()
{
	QueryPerformanceCounter(&theApp.sPos);
}


void LibMFCUtil::EndPerformanceTimer()
{
	QueryPerformanceCounter(&theApp.ePos);
}


__int64 LibMFCUtil::GetPerformanceTimeByMS()
{
	return (theApp.ePos.QuadPart - theApp.sPos.QuadPart) / (theApp.freq.QuadPart / 1000);
}


__int64 LibMFCUtil::GetPerformanceTimeByMicrosecond()
{
	return (theApp.ePos.QuadPart - theApp.sPos.QuadPart) / (theApp.freq.QuadPart / 1000000);
}


void LibMFCUtil::OutputPerformanceTimeByMS()
{
	CString str;
	str.Format(_T("Performance Time (ms) : %d\n"), GetPerformanceTimeByMS());
	OutputDebugString(str);
}


void LibMFCUtil::OutputPerformanceTimeByMicrosecond()
{
	CString str;
	str.Format(_T("Performance Time (microsecond) : %d\n"), GetPerformanceTimeByMicrosecond());
	OutputDebugString(str);
}


CString LibMFCUtil::INIReadString(CString strAppName, CString strKeyName, CString strFilePath)
{
	wchar_t szReturnString[1024] = { 0, };

	memset(szReturnString, NULL, sizeof(wchar_t) * 1024);

	GetPrivateProfileString(strAppName, strKeyName, _T(""), szReturnString, 1024, strFilePath);

	CString str;

	str.Format(_T("%s"), szReturnString);

	return str;
}

void LibMFCUtil::INIWriteString(CString strAppName, CString strKeyName, CString strValue, CString strFilePath)
{
	WritePrivateProfileString(strAppName, strKeyName, strValue, strFilePath);

}


CString LibMFCUtil::GetDesktopPath()
{
	TCHAR Path[MAX_PATH];

	SHGetSpecialFolderPath(NULL, Path, CSIDL_DESKTOP, FALSE);

	CString str(Path);

	return str;
}


bool LibMFCUtil::CheckDirExistAndCreate(CString path)
{
	CFileFind file;
	CString strFile = _T("*.*");
	BOOL bResult = file.FindFile(path + strFile);

	if (!bResult)
	{
		bResult = CreateDirectory(path + _T("\\"), NULL);
		if (!bResult)
		{ 
			return false;
		}
		return true;
	}
	return true;
}


bool LibMFCUtil::CopyTextToClipboard(CString str)
{ 
	int string_length = str.GetLength() + 1;
	int memSize = string_length * sizeof(TCHAR);  
	HANDLE h_data = GlobalAlloc(GHND | GMEM_MOVEABLE, memSize); 
	char *p_data = (char *)GlobalLock(h_data);

	if (NULL != p_data) 
	{
		std::wstring wstr(str);
		char* cstr = ConvertWCtoC((wchar_t *)wstr.c_str()); 
		memcpy(p_data, cstr, memSize); 
		GlobalUnlock(h_data);
		if (OpenClipboard(NULL)) 
		{ 
			EmptyClipboard(); 
			SetClipboardData(CF_TEXT, h_data); 
			CloseClipboard(); 

			delete[] cstr;

			return true;
		}

		delete[] cstr;
	}

	return false;
}

POINT LibMFCUtil::RotatePoint(POINT& pt, double radian, int centerX, int centerY)
{
	POINT newPt;  
	newPt.x = (LONG)(centerX + (pt.x - centerX) * cos(radian) - (pt.y - centerY) * sin(radian));
	newPt.y = (LONG)(centerY + (pt.x - centerX) * sin(radian) - (pt.y - centerY) * cos(radian));
	return newPt;
}


RECT LibMFCUtil::RotateRect(RECT& rect, double radian, int centerX, int centerY)
{
	RECT newRect;

	POINT pt;
	pt.x = rect.left;
	pt.y = rect.top;

	pt = RotatePoint(pt, radian, centerX, centerY);
	newRect.left = pt.x;
	newRect.top = pt.y;

	pt.x = rect.right;
	pt.y = rect.bottom;

	pt = RotatePoint(pt, radian, centerX, centerY);
	newRect.right= pt.x;
	newRect.bottom = pt.y;

	return newRect;
} 
std::string LibMFCUtil::GetHDF5SplittedFilePath(std::string path)
{ 
	auto Extensionsindex = path.find_last_of(".");
	auto Extensions = path.substr(Extensionsindex, path.size()); 

	auto underbarIndex = path.find_last_of("_"); 
	auto OutputValue = path.substr(0, underbarIndex);

	OutputValue += "_%d"+ Extensions;

	return OutputValue;
}

bool LibMFCUtil::SaveImage(CString path, HDC& hdc, int width, int height)
{
	auto folderPath = FullPathToPath(path);
	LibMFCUtil::createDirectoryRecursively(std::wstring(folderPath));

	CImage capImage; 

	CRect rect(0, 0, width, height);

	if (!capImage.Create(rect.Width(), rect.Height(), 32))
	{
		return false;
	}

	HDC hDC = capImage.GetDC();

	BitBlt(hDC, 0, 0, rect.Width(), rect.Height(), hdc, 0, 0, SRCCOPY);
	capImage.Save(path);
	ReleaseDC(0, hDC);
	capImage.ReleaseDC();
	capImage.Destroy();

	return true;
}

bool LibMFCUtil::SaveImage2(CString path, CImage& image, HDC& hdc, int width, int height)
{
	auto folderPath = FullPathToPath(path);
	LibMFCUtil::createDirectoryRecursively(std::wstring(folderPath));

	HDC hDC = image.GetDC();

	BitBlt(hDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
	image.Save(path);

	return true;
}

CString LibMFCUtil::FullPathToPath(CString fullPath)
{
	return fullPath.Left(fullPath.ReverseFind('\\'));
}

void LibMFCUtil::createDirectoryRecursively(const std::wstring &directory) {
	static const std::wstring separators(L"\\/"); 
	DWORD fileAttributes = ::GetFileAttributesW(directory.c_str());
	if (fileAttributes == INVALID_FILE_ATTRIBUTES) { 
		std::size_t slashIndex = directory.find_last_of(separators);
		if (slashIndex != std::wstring::npos) {
			LibMFCUtil::createDirectoryRecursively(directory.substr(0, slashIndex));
		}  
		BOOL result = ::CreateDirectoryW(directory.c_str(), nullptr);
		if (result == FALSE) {
			throw std::runtime_error("Could not create directory");
		}

	}
	else { 

		bool isDirectoryOrJunction =
			((fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
			((fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0);

		if (!isDirectoryOrJunction) {
			throw std::runtime_error(
				"Could not create directory because a file with the same name exists"
			);
		}

	}
}