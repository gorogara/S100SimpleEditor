#pragma once
class CMFCPropertySelectColorGridProperty : public CMFCPropertyGridProperty
{
	friend CMFCPropertyGridProperty;
	DECLARE_DYNAMIC(CMFCPropertySelectColorGridProperty)
public:

	CMFCPropertySelectColorGridProperty(const CString& strGroupName,
		DWORD_PTR dwData = 0,
		BOOL bIsValueList = FALSE);
	CMFCPropertySelectColorGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	~CMFCPropertySelectColorGridProperty();

	bool selected = false;
	UINT selectedColor = 0xFF0000;
	
	HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor);
};