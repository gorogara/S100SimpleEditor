#pragma once
#include "afxwin.h" 

class CDialogExAddWaypoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExAddWaypoint)

public:
	CDialogExAddWaypoint(CWnd* pParent = NULL); 
	virtual ~CDialogExAddWaypoint(); 
	enum { IDD = IDD_DIALOG_ADD_WP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CEditNo;
	CEdit m_CEditLat;
	CEdit m_CEditLon;
	double m_fLat;
	double m_fLon;
	int m_nNo;
	double m_dSpeed;
	CEdit m_editSpeed;
	virtual BOOL OnInitDialog();
	bool isAdd;
	afx_msg void OnBnClickedOk();
};