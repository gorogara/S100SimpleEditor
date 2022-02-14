#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"
#include"GISViewerView.h"

#include <string>

class CGISViewerView; 

class CDialogExRelationCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRelationCreate)

public:
	CDialogExRelationCreate(CWnd* pParent = NULL); 
	virtual ~CDialogExRelationCreate();

	CGISViewerView *pView; 
	enum { IDD = IDD_DIALOG_RELATION_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogRelationCreate();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};


