#pragma once

#define PropertyPage_Assert(x)	if(!(x)) {__asm{int 3}}

class PropertyPageBase : public CMFCPropertyPage
{
	DECLARE_MESSAGE_MAP()
public:
	PropertyPageBase();
	virtual ~PropertyPageBase();

	void adjustLayout(CRect& rRect);

protected:
	CMFCPropertyGridCtrl m_wndPropList;

protected:

	bool			addProperty_Boolean(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bVal);
	bool			addProperty_Boolean(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bVal);
	bool			setProperty_Boolean(DWORD dwID, bool bVal);
	bool			getProperty_Boolean(DWORD dwID, CMFCPropertyGridProperty* pProperty, bool* pBoolOut);

	bool			addProperty_DropdownCombo(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, int nCount, int nDefault, ...);
	bool			addProperty_DropdownCombo(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, int nCount, int nDefault, ...);
	bool			setProperty_DropdownCombo(DWORD dwID, char* strA);
	bool			setProperty_DropdownCombo(DWORD dwID, wchar_t* strW);
	bool			getProperty_DropdownCombo(DWORD dwID, CMFCPropertyGridProperty* pProperty, char* strOut);
	bool			getProperty_DropdownCombo(DWORD dwID, CMFCPropertyGridProperty* pProperty, wchar_t* strOut);

	bool			addProperty_Integer(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, int nMin, int nMax, int nVal);
	bool			addProperty_Integer(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, int nMin, int nMax, int nVal);
	bool			setProperty_Integer(DWORD dwID, int nVal);
	bool			getProperty_Integer(DWORD dwID, CMFCPropertyGridProperty* pProperty, int* pIntOut);

	bool			addProperty_Float(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, float fVal);
	bool			addProperty_Float(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, float fVal);
	bool			setProperty_Float(DWORD dwID, float fVal);
	bool			getProperty_Float(DWORD dwID, CMFCPropertyGridProperty* pProperty, float* pFloatOut);

	bool			addProperty_String(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, char* strVal);
	bool			addProperty_String(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, wchar_t* strVal);
	bool			setProperty_String(DWORD dwID, char* strA);
	bool			setProperty_String(DWORD dwID, wchar_t* strW);
	bool			getProperty_String(DWORD dwID, CMFCPropertyGridProperty* pProperty, char* strOut);
	bool			getProperty_String(DWORD dwID, CMFCPropertyGridProperty* pProperty, wchar_t* strOut);

	bool			addProperty_Font(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, LOGFONT* pFontInOut, COLORREF* pColorOut);
	bool			addProperty_Font(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, LOGFONT* pFontInOut, COLORREF* pColorOut);
	bool			setProperty_Font(DWORD dwID, char* strA, LOGFONT* pFontOut, COLORREF* pColorOut);
	bool			setProperty_Font(DWORD dwID, wchar_t* strW, LOGFONT* pFontOut, COLORREF* pColorOut);
	bool			setProperty_Font(DWORD dwID, LOGFONT* pFontInOut, COLORREF* pColorInOut);
	bool			getProperty_Font(DWORD dwID, CMFCPropertyGridProperty* pProperty, LOGFONT* pFontInOut, COLORREF* pColorInOut);

	bool			addProperty_Color(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, COLORREF hColor);
	bool			addProperty_Color(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, COLORREF hColor);
	bool			setProperty_Color(DWORD dwID, COLORREF hColor);
	bool			getProperty_Color(DWORD dwID, CMFCPropertyGridProperty* pProperty, COLORREF* pColorOut);

	bool			addProperty_File(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, char* strFilter, CString* strOut);
	bool			addProperty_File(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, wchar_t* strFilter, CString* strOut);
	bool			setProperty_File(DWORD dwID, char* strFile, CString* pFileOut);
	bool			setProperty_File(DWORD dwID, wchar_t* strFile, CString* pFileOut);
	bool			getProperty_File(DWORD dwID, CMFCPropertyGridProperty* pProperty, CString* pFileOut);

	bool			addProperty_Folder(char* strTitle, DWORD dwID, CMFCPropertyGridProperty* pParent, char* strInitialFolder, CString* pFolderOut);
	bool			addProperty_Folder(wchar_t* strTitle, DWORD dwID, CMFCPropertyGridProperty* pParent, wchar_t* strInitialFolder, CString* pFolderOut);
	bool			setProperty_Folder(DWORD dwID, char* strFolder, CString* pFolderOut);
	bool			setProperty_Folder(DWORD dwID, wchar_t* strFolder, CString* pFolderOut);
	bool			getProperty_Folder(DWORD dwID, CMFCPropertyGridProperty* pProperty, CString* pFolderOut);

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
}; 
