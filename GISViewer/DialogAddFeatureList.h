#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CGISViewerView;
class Catalog; 

class CDialogAddFeatureList : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAddFeatureList)

public:
	CDialogAddFeatureList(CWnd* pParent = NULL); 
	virtual ~CDialogAddFeatureList(); 
	enum { IDD = IDD_DIALOG_SELECT_ADD_FEATURE };      
	int m_mode; 
	std::wstring m_strFilter;
public:   
private:
	CGISViewerView *m_pView;

	CButton m_btOK;
	CButton m_btCancel;
	CEdit m_eFilter;
	CListCtrl m_ListAddFeature;
public:
	void SetView(CGISViewerView *pView);
	void SetCatalogueList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditFilter();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLvnItemchangedListNewFeature(NMHDR *pNMHDR, LRESULT *pResult);
};
