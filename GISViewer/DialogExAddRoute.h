#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"

class CGISViewerView; 

class CDialogExAddRoute : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExAddRoute)

public:
	CDialogExAddRoute(CWnd* pParent = NULL); 
	virtual ~CDialogExAddRoute();

	void UpdateRouteList(); 
	enum { IDD = IDD_DIALOG_ADD_ROUTE };

	CGISViewerView* pView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CEdit routeName;
	CDateTimeCtrl date;
	CDateTimeCtrl time;
	afx_msg void OnBnClickedOk();
	CString m_routeName;
	COleDateTime m_date;
	COleDateTime m_time;
};
