#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h"
#include "stdafx.h"

#include <string>
class CGISViewerView; 

class CDialogExRelationInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRelationInfo)

public:
	CDialogExRelationInfo(CWnd* pParent = NULL); 
	virtual ~CDialogExRelationInfo(); 
	enum { IDD = IDD_DIALOG_RELATION_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogRelationInfo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

	
	

};


