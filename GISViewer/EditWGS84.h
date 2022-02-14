#pragma once
#include "afxwin.h"
class CEditWGS84 :
	public CEdit
{
public:
	CEditWGS84();
	virtual ~CEditWGS84();

	double GetLon();
	double GetLat();
	bool CheckForm();
	bool CheckValue();

	CString cstr;
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
};