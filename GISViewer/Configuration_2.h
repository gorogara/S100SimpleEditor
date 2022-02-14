#pragma once
#include "afxcmn.h"
#include "CheckListCtrl.h"
#include "afxwin.h" 
class CConfigrationDlg;
class CConfiguration_2 : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration_2)

public:
	CConfiguration_2(CWnd* pParent = NULL); 
	virtual ~CConfiguration_2(); 
	enum { IDD = IDD_DIALOG_CONFIG_2 };

	CConfigrationDlg *m_pParent;

	CButton m_sounding;
	CButton m_lights;
	CButton m_contourLabels;
	CButton m_text;
	CButton m_scaleMin;
	CButton m_textClutter;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CCheckListCtrl m_visualObjectList;
	CListCtrl m_settingsList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnShowObjectSettingsDefault();
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void OnOK();
	CButton m_abbreviationList; 
	afx_msg void OnLvnItemchangedListSettings(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_geo_wgs84_text;
	CButton m_coast_area;
	CButton m_coast_area_detail;
	CButton m_check_isd;
};
