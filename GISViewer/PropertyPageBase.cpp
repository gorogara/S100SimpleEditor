#include "stdafx.h"

#include "Resource.h"
#include "MainFrm.h"
#include "PropertyPageBase.h"

#include <string>

BEGIN_MESSAGE_MAP(PropertyPageBase, CMFCPropertyPage)
	ON_WM_CREATE()
END_MESSAGE_MAP()

PropertyPageBase::PropertyPageBase()
{
}
PropertyPageBase::~PropertyPageBase()
{
}

bool PropertyPageBase::addProperty_Boolean(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	return addProperty_Boolean((wchar_t*)std::wstring(strTitleW).c_str(), strDescW.GetBuffer(), dwID, pParent, bVal);
}
bool PropertyPageBase::addProperty_Boolean(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false; 
	CMFCPropertyGridProperty* pBooleanProp1 = new CMFCPropertyGridProperty(strTitle, (_variant_t)bVal, strDesc);
	PropertyPage_Assert(pBooleanProp1);
	if(pBooleanProp1 == 0) return false; 
	pBooleanProp1->SetData(dwID); 
	if(pParent)	{pParent->AddSubItem(pBooleanProp1);}
	else		{m_wndPropList.AddProperty(pBooleanProp1);}

	return true;
}
bool PropertyPageBase::setProperty_Boolean(DWORD dwID, bool bVal)
{ 
	CMFCPropertyGridProperty* pBooleanProp1 = m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pBooleanProp1); 
	if(pBooleanProp1)
	{
		pBooleanProp1->SetValue((_variant_t)bVal);
		return true;
	}

	return false;
}
bool PropertyPageBase::getProperty_Boolean(DWORD dwID, CMFCPropertyGridProperty* pProperty, bool* pBoolOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pBoolOut);
	if(pProperty == 0 || pBoolOut == 0) return false; 
	DWORD id = pProperty->GetData();
	if(id != dwID)
	{
		PropertyPage_Assert(0);
		return false;
	} 
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;
	PropertyPage_Assert(vt == VT_BOOL);
	if(vt != VT_BOOL) return false;

#pragma warning(disable:4800)
	*pBoolOut = (bool)v.boolVal;
#pragma warning(default:4800)

	return true;
}

bool PropertyPageBase::addProperty_DropdownCombo(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, int nCount, int nDefault, ...)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CMFCPropertyGridProperty* pDropdownCombo1 = 0;
	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	CStringW strDefaultW;
	char* pstr;

	va_list ptr; va_start(ptr, nDefault);
	for(int i = 0; i<nCount; i++)
	{
		pstr = va_arg(ptr, char*);
		CStringW strCurrent(pstr);
		if(i == 0)
		{
			pDropdownCombo1 = new CMFCPropertyGridProperty(strTitleW, strCurrent, strDescW);
			PropertyPage_Assert(pDropdownCombo1);
			if(pDropdownCombo1 == 0)
			{
				va_end(ptr);
				return false;
			}			
		}
		if(i == nDefault)
		{
			strDefaultW = pstr;
		}
		pDropdownCombo1->AddOption(strCurrent);
	}
	va_end(ptr);

	pDropdownCombo1->AllowEdit(FALSE);
	pDropdownCombo1->SetData(dwID);
	if(strDefaultW.GetLength() > 0) pDropdownCombo1->SetValue(strDefaultW);

	if(pParent)	{pParent->AddSubItem(pDropdownCombo1);}
	else		{m_wndPropList.AddProperty(pDropdownCombo1);}

	return true;
}
bool PropertyPageBase::addProperty_DropdownCombo(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, int nCount, int nDefault, ...)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CMFCPropertyGridProperty* pDropdownCombo1 = 0;
	wchar_t* pstr;
	wchar_t* pDefault = 0;

	va_list ptr; va_start(ptr, nDefault);
	for(int i = 0; i<nCount; i++)
	{
		pstr = va_arg(ptr, wchar_t*);
		if(i == 0)
		{
			pDropdownCombo1 = new CMFCPropertyGridProperty(strTitle, pstr, strDesc);
			PropertyPage_Assert(pDropdownCombo1);
			if(pDropdownCombo1 == 0)
			{
				va_end(ptr);
				return false;
			}			
		}
		if(i == nDefault)
		{
			pDefault = pstr;
		}
		pDropdownCombo1->AddOption(pstr);
	}
	va_end(ptr);

	pDropdownCombo1->AllowEdit(FALSE);
	pDropdownCombo1->SetData(dwID);
	if(pDefault) pDropdownCombo1->SetValue(pDefault);

	if(pParent)	{pParent->AddSubItem(pDropdownCombo1);}
	else		{m_wndPropList.AddProperty(pDropdownCombo1);}

	return true;
}

bool PropertyPageBase::setProperty_DropdownCombo(DWORD dwID, char* strA)
{
	PropertyPage_Assert(strA);
	if(strA == 0) return false;

	CStringW strW(strA);
	return setProperty_DropdownCombo(dwID, strW.GetBuffer());
}
bool PropertyPageBase::setProperty_DropdownCombo(DWORD dwID, wchar_t* strW)
{
	PropertyPage_Assert(strW);
	if(strW == 0) return false;

	CMFCPropertyGridProperty* pDropdownCombo1 = m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pDropdownCombo1);
	if(pDropdownCombo1)
	{
		pDropdownCombo1->SetValue(strW);
		return true;
	}
	return false;
}

bool PropertyPageBase::getProperty_DropdownCombo(DWORD dwID, CMFCPropertyGridProperty* pProperty, char* strOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(strOut);
	if(pProperty == 0 || strOut == 0) return false;

	wchar_t strBuf[1024];
	if(getProperty_DropdownCombo(dwID, pProperty, strBuf) == true)
	{
		CStringA strA(strBuf);		
		memcpy(strOut, strA.GetBuffer(), sizeof(char)*strA.GetLength());
		strOut[strA.GetLength()] = 0;
		return true;
	}
	return false;
}
bool PropertyPageBase::getProperty_DropdownCombo(DWORD dwID, CMFCPropertyGridProperty* pProperty, wchar_t* strOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(strOut);
	if(pProperty == 0 || strOut == 0) return false; 
	DWORD id = pProperty->GetData();
	if(id != dwID)
	{
		PropertyPage_Assert(0);
		return false;
	}

	USES_CONVERSION;
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	PropertyPage_Assert(vt == VT_BSTR);
	if(vt != VT_BSTR) return false;

	CString strW = OLE2W(v.bstrVal);
	memcpy(strOut, strW.GetBuffer(), sizeof(wchar_t)*strW.GetLength());
	strOut[strW.GetLength()] = 0;

	return true;
}

bool PropertyPageBase::addProperty_Integer(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, int nMin, int nMax, int nVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	return addProperty_Integer(strTitleW.GetBuffer(), strDescW.GetBuffer(), dwID, pParent, bAllowEdit, nMin, nMax, nVal);
}
bool PropertyPageBase::addProperty_Integer(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, int nMin, int nMax, int nVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false; 
	CMFCPropertyGridProperty* pIntegerProp1 = new CMFCPropertyGridProperty(strTitle, (_variant_t)(long int)nVal, strDesc);
	PropertyPage_Assert(pIntegerProp1);
	if(pIntegerProp1 == 0) return false; 
	if(bAllowEdit == true) pIntegerProp1->AllowEdit(TRUE);
	else pIntegerProp1->AllowEdit(FALSE); 
	if(nMin != nMax)
	{
		if(nMin < nMax) pIntegerProp1->EnableSpinControl(TRUE, nMin, nMax);
		else {PropertyPage_Assert(0);}
	} 
	pIntegerProp1->SetData(dwID); 
	if(pParent)	{pParent->AddSubItem(pIntegerProp1);}
	else		{m_wndPropList.AddProperty(pIntegerProp1);}

	return true;
}
bool PropertyPageBase::setProperty_Integer(DWORD dwID, int nVal)
{ 
	CMFCPropertyGridProperty* pIntegerProp1 = m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pIntegerProp1); 
	if(pIntegerProp1)
	{
		pIntegerProp1->SetValue((_variant_t)(long int)nVal);
		return true;
	}

	return false;
}
bool PropertyPageBase::getProperty_Integer(DWORD dwID, CMFCPropertyGridProperty* pProperty, int* pIntOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pIntOut);
	if(pProperty == 0 || pIntOut == 0) return false; 
	DWORD id = pProperty->GetData();
	if(id != dwID)
	{
		PropertyPage_Assert(0);
		return false;
	} 
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;
	PropertyPage_Assert(vt == VT_I4);
	if(vt != VT_I4) return false;

#pragma warning(disable:4800)
	*pIntOut = (int)v.intVal;
#pragma warning(default:4800)

	return true;
}

bool PropertyPageBase::addProperty_Float(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, float fVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	return addProperty_Float(strTitleW.GetBuffer(), strDescW.GetBuffer(), dwID, pParent, bAllowEdit, fVal);
}
bool PropertyPageBase::addProperty_Float(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, float fVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false; 
	CMFCPropertyGridProperty* pFloatProp1 = new CMFCPropertyGridProperty(strTitle, (_variant_t)fVal, strDesc);
	PropertyPage_Assert(pFloatProp1);
	if(pFloatProp1 == 0) return false; 
	if(bAllowEdit == true) pFloatProp1->AllowEdit(TRUE);
	else pFloatProp1->AllowEdit(FALSE); 
	pFloatProp1->SetData(dwID); 
	if(pParent)	{pParent->AddSubItem(pFloatProp1);}
	else		{m_wndPropList.AddProperty(pFloatProp1);}

	return true;
}
bool PropertyPageBase::setProperty_Float(DWORD dwID, float fVal)
{ 
	CMFCPropertyGridProperty* pFloatProp1 = m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pFloatProp1); 
	if(pFloatProp1)
	{
		pFloatProp1->SetValue((_variant_t)fVal);
		return true;
	}

	return false;
}
bool PropertyPageBase::getProperty_Float(DWORD dwID, CMFCPropertyGridProperty* pProperty, float* pFloatOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pFloatOut);
	if(pProperty == 0 || pFloatOut == 0) return false; 
	DWORD id = pProperty->GetData();
	if(id != dwID)
	{
		PropertyPage_Assert(0);
		return false;
	} 
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;
	PropertyPage_Assert(vt == VT_R4);
	if(vt != VT_R4) return false;

#pragma warning(disable:4800)
	*pFloatOut = (float)v.fltVal;
#pragma warning(default:4800)

	return true;
}

bool PropertyPageBase::addProperty_String(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, char* strVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	CStringW strValW(strVal);	
	return addProperty_String(strTitleW.GetBuffer(), strDescW.GetBuffer(), dwID, pParent, bAllowEdit, strValW.GetBuffer());
}
bool PropertyPageBase::addProperty_String(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, wchar_t* strVal)
{
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false; 
	CMFCPropertyGridProperty* pStringProp1 = new CMFCPropertyGridProperty(strTitle, (_variant_t)strVal, strDesc);
	PropertyPage_Assert(pStringProp1);
	if(pStringProp1 == 0) return false; 
	if(bAllowEdit == true) pStringProp1->AllowEdit(TRUE);
	else pStringProp1->AllowEdit(FALSE); 
	pStringProp1->SetData(dwID); 
	if(pParent)	{pParent->AddSubItem(pStringProp1);}
	else		{m_wndPropList.AddProperty(pStringProp1);}

	return true;
}
bool PropertyPageBase::setProperty_String(DWORD dwID, char* strA)
{
	PropertyPage_Assert(strA);
	if(strA == 0) return false;

	CStringW strW(strA);
	return setProperty_String(dwID, strW.GetBuffer());
}
bool PropertyPageBase::setProperty_String(DWORD dwID, wchar_t* strW)
{
	PropertyPage_Assert(strW);
	if(strW == 0) return false; 
	CMFCPropertyGridProperty* pStringProp1 = m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pStringProp1); 
	if(pStringProp1)
	{
		pStringProp1->SetValue((_variant_t)strW);
		return true;
	}

	return false;
}
bool PropertyPageBase::getProperty_String(DWORD dwID, CMFCPropertyGridProperty* pProperty, char* strOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(strOut);
	if(pProperty == 0 || strOut == 0) return false;

	wchar_t wbuf[1024];
	if(getProperty_String(dwID, pProperty, wbuf) == true)
	{
		CStringA strA(wbuf);
		memcpy(strOut, strA.GetBuffer(), sizeof(char)*strA.GetLength());
		strOut[strA.GetLength()] = 0;
		return true;
	}
	return false;
}
bool PropertyPageBase::getProperty_String(DWORD dwID, CMFCPropertyGridProperty* pProperty, wchar_t* strOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(strOut);
	if(pProperty == 0 || strOut == 0) return false; 
	DWORD id = pProperty->GetData();
	if(id != dwID)
	{
		PropertyPage_Assert(0);
		return false;
	}

	USES_CONVERSION;
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	PropertyPage_Assert(vt == VT_BSTR);
	if(vt != VT_BSTR) return false;

	CString strW = OLE2W(v.bstrVal);
	memcpy(strOut, strW.GetBuffer(), sizeof(wchar_t)*strW.GetLength());
	strOut[strW.GetLength()] = 0;

	return true;
}

bool PropertyPageBase::addProperty_Font(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, LOGFONT* pFontInOut, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(pFontInOut);
	PropertyPage_Assert(pColorOut);
	if(strTitle == 0 || pFontInOut == 0 || pColorOut == 0) return false;

	CStringW strTitleA(strTitle);
	CStringW strDescA(strDesc);
	return addProperty_Font(strTitleA.GetBuffer(), strDescA.GetBuffer(), dwID, pParent, pFontInOut, pColorOut);
}
bool PropertyPageBase::addProperty_Font(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, LOGFONT* pFontInOut, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(pFontInOut);
	PropertyPage_Assert(pColorOut);
	if(strTitle == 0 || pFontInOut == 0 || pColorOut == 0) return false;

	CMFCPropertyGridFontProperty* pFont1 = new CMFCPropertyGridFontProperty(strTitle, *pFontInOut, CF_EFFECTS | CF_SCREENFONTS, strDesc);
	pFont1->SetData(dwID);	
	LOGFONT* pFont = pFont1->GetLogFont();
	*pColorOut = pFont1->GetColor();
	memcpy(pFontInOut, pFont, sizeof(LOGFONT));
	if(pParent)	{pParent->AddSubItem(pFont1);}
	else		{m_wndPropList.AddProperty(pFont1);}

	return true;
}
bool PropertyPageBase::setProperty_Font(DWORD dwID, char* strA, LOGFONT* pFontOut, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(strA);
	PropertyPage_Assert(pFontOut);
	PropertyPage_Assert(pColorOut);
	if(strA == 0 || pFontOut == 0 || pColorOut == 0) return false;

	CStringW strW(strA);
	return setProperty_Font(dwID, strW.GetBuffer(), pFontOut, pColorOut);
}
bool PropertyPageBase::setProperty_Font(DWORD dwID, wchar_t* strW, LOGFONT* pFontOut, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(strW);
	PropertyPage_Assert(pFontOut);
	PropertyPage_Assert(pColorOut);
	if(strW == 0 || pFontOut == 0 || pColorOut == 0) return false;

	CMFCPropertyGridFontProperty* pFontProp1 = (CMFCPropertyGridFontProperty*)m_wndPropList.FindItemByData(dwID);
	if(pFontProp1)
	{
		LOGFONT* pFont = pFontProp1->GetLogFont();
		lstrcpy(pFont->lfFaceName, strW);
		m_wndPropList.UpdateData(FALSE);
		*pColorOut = pFontProp1->GetColor();
		memcpy(pFontOut, pFont, sizeof(LOGFONT));
		return true;
	}
	return false;
}
bool PropertyPageBase::setProperty_Font(DWORD dwID, LOGFONT* pFontInOut, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(pFontInOut);
	PropertyPage_Assert(pColorOut);
	if(pFontInOut == 0 || pColorOut == 0) return false;

	CMFCPropertyGridFontProperty* pFontProp1 = (CMFCPropertyGridFontProperty*)m_wndPropList.FindItemByData(dwID);
	if(pFontProp1)
	{
		LOGFONT* pFont = pFontProp1->GetLogFont();
		memcpy(pFont, pFontInOut, sizeof(LOGFONT));
		m_wndPropList.UpdateData(FALSE);
		*pColorOut = pFontProp1->GetColor();
		memcpy(pFontInOut, pFont, sizeof(LOGFONT));
		return true;
	}
	return false;
}

bool PropertyPageBase::getProperty_Font(DWORD dwID, CMFCPropertyGridProperty* pProperty, LOGFONT* pFontInOut, COLORREF* pColorInOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pFontInOut);
	PropertyPage_Assert(pColorInOut);
	if(pProperty == 0 || pFontInOut == 0 || pColorInOut == 0) return false;

	USES_CONVERSION;
	LPLOGFONT pFont1;
	COLORREF FontColor1;
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_BSTR);
	CMFCPropertyGridFontProperty* pFontProperty = (CMFCPropertyGridFontProperty*)pProperty;
	pFont1 = pFontProperty->GetLogFont();
	FontColor1 = pFontProperty->GetColor();

	if(FontColor1 != *pColorInOut || (memcmp(pFontInOut, pFont1, sizeof(LOGFONT)) != 0))
	{
		*pColorInOut = FontColor1;
		memcpy(pFontInOut, pFont1, sizeof(LOGFONT));
		return true;
	}
	return false;
}

bool PropertyPageBase::addProperty_Color(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, COLORREF hColor)
{ 
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	return addProperty_Color(strTitleW.GetBuffer(), strDescW.GetBuffer(), dwID, pParent, bAllowEdit, hColor);
}
bool PropertyPageBase::addProperty_Color(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, bool bAllowEdit, COLORREF hColor)
{ 
	PropertyPage_Assert(strTitle);
	if(strTitle == 0) return false;

	CMFCPropertyGridColorProperty* pColor1 = new CMFCPropertyGridColorProperty(strTitle, hColor, NULL, strDesc);
	pColor1->SetData(dwID);
	pColor1->EnableOtherButton(_T("기타...")); 
	if(bAllowEdit == true) pColor1->AllowEdit(TRUE);
	else pColor1->AllowEdit(FALSE);

	if(pParent)	{pParent->AddSubItem(pColor1);}
	else		{m_wndPropList.AddProperty(pColor1);}

	return true;
}
bool PropertyPageBase::setProperty_Color(DWORD dwID, COLORREF hColor)
{ 
	CMFCPropertyGridColorProperty* pColorProp1 = (CMFCPropertyGridColorProperty*)m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pColorProp1); 
	if(pColorProp1)
	{
		pColorProp1->SetColor(hColor);
		return true;
	}

	return false;
}
bool PropertyPageBase::getProperty_Color(DWORD dwID, CMFCPropertyGridProperty* pProperty, COLORREF* pColorOut)
{ 
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pColorOut);
	if(pProperty == 0 || pColorOut == 0) return false;

	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_I4);
	CMFCPropertyGridColorProperty* pColorProperty = (CMFCPropertyGridColorProperty*)pProperty;
	*pColorOut = pColorProperty->GetColor();
	return true;
}

bool PropertyPageBase::addProperty_File(char* strTitle, char* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, char* strFilter, CString* strOut)
{ 
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(strOut);
	PropertyPage_Assert(strFilter);
	if(strTitle == 0 || strOut == 0 || strFilter == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strDescW(strDesc);
	CStringW strFilterW(strFilter);
	return addProperty_File(strTitleW.GetBuffer(), strDescW.GetBuffer(), dwID, pParent, strFilterW.GetBuffer(), strOut);
}
bool PropertyPageBase::addProperty_File(wchar_t* strTitle, wchar_t* strDesc, DWORD dwID, CMFCPropertyGridProperty* pParent, wchar_t* strFilter, CString* strOut)
{ 
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(strOut);
	PropertyPage_Assert(strFilter);
	if(strTitle == 0 || strOut == 0 || strFilter == 0) return false;

	CMFCPropertyGridFileProperty* pFileSelect1 = new CMFCPropertyGridFileProperty(strTitle, TRUE, _T(""), 0, 0, strFilter, strDesc);
	pFileSelect1->SetData(dwID);

	USES_CONVERSION;
	wchar_t wbuf[1024];
	COleVariant rVariant = pFileSelect1->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_BSTR);
	swprintf_s(wbuf, L"%s", OLE2W(v.bstrVal));
	*strOut = wbuf;

	if(pParent)	{pParent->AddSubItem(pFileSelect1);}
	else		{m_wndPropList.AddProperty(pFileSelect1);}

	return true;
}
bool PropertyPageBase::setProperty_File(DWORD dwID, char* strFile, CString* pFileOut)
{
	PropertyPage_Assert(strFile);
	PropertyPage_Assert(pFileOut);
	if(strFile == 0 || pFileOut == 0) return false;

	CStringW strFileW(strFile);
	return setProperty_File(dwID, strFileW.GetBuffer(), pFileOut);
}
bool PropertyPageBase::setProperty_File(DWORD dwID, wchar_t* strFile, CString* pFileOut)
{
	PropertyPage_Assert(strFile);
	PropertyPage_Assert(pFileOut);
	if(strFile == 0 || pFileOut == 0) return false; 
	CMFCPropertyGridFileProperty* pFile1 = (CMFCPropertyGridFileProperty*)m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pFile1);

	if(pFile1)
	{
		*pFileOut = strFile;
		pFile1->SetValue((_variant_t)strFile);
		return true;
	}
	return false;
}
bool PropertyPageBase::getProperty_File(DWORD dwID, CMFCPropertyGridProperty* pProperty, CString* pFileOut)
{
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pFileOut);
	if(pProperty == 0 || pFileOut == 0) return false;

	USES_CONVERSION;
	wchar_t wbuf[1024];
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_BSTR);
	swprintf_s(wbuf, L"%s", OLE2W(v.bstrVal));
	CString strFile1 = wbuf;
	if(*pFileOut != strFile1)
	{
		*pFileOut = wbuf;
		return true;
	}
	return false;
}

bool PropertyPageBase::addProperty_Folder(char* strTitle, DWORD dwID, CMFCPropertyGridProperty* pParent, char* strInitialFolder, CString* pFolderOut)
{
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(strInitialFolder);
	PropertyPage_Assert(pFolderOut);
	if(strTitle == 0 || strInitialFolder == 0 || pFolderOut == 0) return false;

	CStringW strTitleW(strTitle);
	CStringW strInitialFolderW(strInitialFolder);
	return addProperty_Folder(strTitleW.GetBuffer(), dwID, pParent, strInitialFolderW.GetBuffer(), pFolderOut);
}
bool PropertyPageBase::addProperty_Folder(wchar_t* strTitle, DWORD dwID, CMFCPropertyGridProperty* pParent, wchar_t* strInitialFolder, CString* pFolderOut)
{
	PropertyPage_Assert(strTitle);
	PropertyPage_Assert(strInitialFolder);
	PropertyPage_Assert(pFolderOut);
	if(strTitle == 0 || strInitialFolder == 0 || pFolderOut == 0) return false;

	CMFCPropertyGridFileProperty* pFolderSelect1 = new CMFCPropertyGridFileProperty(strTitle, strInitialFolder);
	pFolderSelect1->SetData(dwID);

	USES_CONVERSION;
	wchar_t wbuf[1024];
	COleVariant rVariant = pFolderSelect1->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_BSTR);
	swprintf_s(wbuf, L"%s", OLE2W(v.bstrVal));
	*pFolderOut = wbuf;

	if(pParent)	{pParent->AddSubItem(pFolderSelect1);}
	else		{m_wndPropList.AddProperty(pFolderSelect1);}

	return true;
}
bool PropertyPageBase::setProperty_Folder(DWORD dwID, char* strFolder, CString* pFolderOut)
{
	PropertyPage_Assert(strFolder);
	PropertyPage_Assert(pFolderOut);
	if(strFolder == 0 || pFolderOut == 0) return false;

	CStringW strFolderW(strFolder);
	return setProperty_Folder(dwID, strFolderW.GetBuffer(), pFolderOut);
}
bool PropertyPageBase::setProperty_Folder(DWORD dwID, wchar_t* strFolder, CString* pFolderOut)
{
	PropertyPage_Assert(strFolder);
	PropertyPage_Assert(pFolderOut);
	if(strFolder == 0 || pFolderOut == 0) return false; 
	CMFCPropertyGridFileProperty* pFolder1 = (CMFCPropertyGridFileProperty*)m_wndPropList.FindItemByData(dwID);
	PropertyPage_Assert(pFolder1);

	if(pFolder1)
	{
		*pFolderOut = strFolder;
		pFolder1->SetValue((_variant_t)strFolder);
		return true;
	}
	return false;
}
bool PropertyPageBase::getProperty_Folder(DWORD dwID, CMFCPropertyGridProperty* pProperty, CString* pFolderOut)
{
	PropertyPage_Assert(pProperty);
	PropertyPage_Assert(pFolderOut);
	if(pProperty == 0 || pFolderOut == 0) return false;

	USES_CONVERSION;
	wchar_t wbuf[1024];
	COleVariant rVariant = pProperty->GetValue();
	VARIANT v = rVariant.Detach();
	VARTYPE vt = v.vt;

	ASSERT(vt == VT_BSTR);
	swprintf_s(wbuf, L"%s", OLE2W(v.bstrVal));
	CString strFile1 = wbuf;
	if(*pFolderOut != strFile1)
	{
		*pFolderOut = wbuf;
		return true;
	}
	return false;
}

int PropertyPageBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, IDD_DUMMY_PROPERTYSHEET))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1; 
	}
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook(); 

	return 0;
}

void PropertyPageBase::adjustLayout(CRect& rRect)
{
	m_wndPropList.SetWindowPos(NULL, rRect.left, rRect.top, rRect.Width(), rRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}
