#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"

#include "GISLibrary\\GISLibrary.h"

class CDialogDockLogger;
class CGISViewerView;
class R_FeatureRecord;
class S101Cell;  
class CDialogDockLogger : public CDialog
{ 
	DECLARE_DYNAMIC(CDialogDockLogger)

public:
	CDialogDockLogger(CWnd* pParent = NULL); 
	virtual ~CDialogDockLogger();
	virtual BOOL OnInitDialog();

	void UpdateList();
	void UpdateListTest();
	void AppendList(CString str); 
	enum { IDD = IDD_DIALOG_DOCK_LOGGER };
	CGISViewerView *pView;
	CGISLibraryApp *pGisLib;

	

	int nSelectedItem; 
public:

	void AdjustLayout();
	void AdjustToolbarMenu();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnNMClickListLm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListLm(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonListclear(); 
	static CListCtrl m_ListLogger;
	static CComboBox m_ComboLogType; 

	CButton b_ListClearButton;  
	afx_msg void OnCbnSelchangeComboLogType();
};
