#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <string>
class CDialogDockRelation;
class CGISViewerView;
class R_FeatureRecord;
class S101Cell; 

class CDialogExRelationListAll : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRelationListAll)

public:
	CDialogExRelationListAll(CWnd* pParent = NULL); 
	virtual ~CDialogExRelationListAll();
	virtual BOOL OnInitDialog(); 
	enum { IDD = IDD_DIALOG_RELATIONALL_LIST };


	CGISViewerView *pView;
	CGISLibraryApp *pGisLib;
	CMenu m_ContextMenu; 

	int nSelectedItem;
	S101Cell* m_cell;

	void AdjustLayout();

	void SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist);

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogRelationListAll();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_ListRelation;


	afx_msg void OnLvnItemchangedListRelation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickListRelationAll(NMHDR *pNMHDR, LRESULT *pResult);


};


