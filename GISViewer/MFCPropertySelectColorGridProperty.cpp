#include "stdafx.h"
#include "MFCPropertySelectColorGridProperty.h"
#include "MainFrm.h"
#include "GISViewerView.h"

CMFCPropertySelectColorGridProperty::CMFCPropertySelectColorGridProperty(const CString& strGroupName,
	DWORD_PTR dwData,
	BOOL bIsValueList )
	: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}
CMFCPropertySelectColorGridProperty::CMFCPropertySelectColorGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr , DWORD_PTR dwData ,
	LPCTSTR lpszEditMask , LPCTSTR lpszEditTemplate , LPCTSTR lpszValidChars )
	: CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData,
	lpszEditMask, lpszEditTemplate, lpszValidChars)
{
	selectedColor = 0xFF0000;
}

CMFCPropertySelectColorGridProperty::~CMFCPropertySelectColorGridProperty()
{
}
IMPLEMENT_DYNAMIC(CMFCPropertySelectColorGridProperty, CMFCPropertyGridProperty)

HBRUSH CMFCPropertySelectColorGridProperty::OnCtlColor(CDC* pDC, UINT nCtlColor)
{


	pDC->SetBkColor(nCtlColor);

	return CMFCPropertyGridProperty::OnCtlColor(pDC, 0xFF0000);
};                      
