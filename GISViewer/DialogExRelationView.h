#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <list>
#include <string>
class CGISViewerView;
class S101Cell;
class R_FeatureRecord;
class R_InformationRecord; 

class CDialogExRelationView : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRelationView)

public:
	CDialogExRelationView(CWnd* pParent = NULL); 
	virtual ~CDialogExRelationView();


public:
	S101Cell *m_cell;
	R_FeatureRecord* m_fr;
	R_FeatureRecord* m_tfr;

	R_InformationRecord* m_ifr;
	R_FeatureRecord* m_tifr;
	
	R_FeatureRecord* m_ifr1;
	R_InformationRecord* m_tifr1;

	CString m_viewMode; 
	enum { IDD = IDD_DIALOG_RELATION_VIEW };

	void AdjustLayout();
	void SetDataOrg();
	void SetDataObj();
	void SetDataOrgInformation1();
	void SetDataObjInformation1();
	void SetDataOrgInformation2();
	void SetDataObjInformation2();

	CString m_assoName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();

public :
	void SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist);
public: 
	afx_msg void OnIddDialogRelationView();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnHdnItemdblclickListRelationView(NMHDR *pNMHDR, LRESULT *pResult);

	CListCtrl m_ListFeatureRelation;
	afx_msg void OnBnClickedButtonRelationDelete();
};


