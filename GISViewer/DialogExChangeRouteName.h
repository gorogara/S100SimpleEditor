#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

class CGISViewerView; 

class CDialogExChangeRouteName : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExChangeRouteName)

public:
	CDialogExChangeRouteName(CWnd* pParent = NULL); 
	virtual ~CDialogExChangeRouteName(); 
	enum { IDD = IDD_DIALOG_CHANGE_ROUTE_NAME };

	CGISViewerView* pView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewName;
	CDateTimeCtrl m_dateTimeCtrlNewDate;
	CDateTimeCtrl m_dateTimeCtrlNewTime;
	afx_msg void OnBnClickedOk();
	CEdit m_editName;
};
