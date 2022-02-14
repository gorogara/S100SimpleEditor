#pragma once
#include "afxcmn.h"
#include "Configuration_1.h"
#include "Configuration_2.h"
#include "Configuration_3.h"
#include "Configuration_4.h"

#include "GeoMetryLibrary/ENCConfiguration.h" 

class CGISViewerView;
class Catalog;
class CConfigrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigrationDlg)

public:
	CConfigrationDlg(CWnd* pParent = NULL); 
	virtual ~CConfigrationDlg(); 
	enum { IDD = IDD_DIALOG_CONFIG };

private:
	CConfiguration_1 page1;
	CConfiguration_2 page2;
	CConfiguration_3 page3;
	CConfiguration_4 page4;
	ENCConfiguration m_config;
	CGISViewerView *m_pParentView;
	bool bObjectDisplaySettingChanges;

	
public:
	void SetParentView(CGISViewerView *m_pView);
	void SettingLoadFromFile(std::wstring filename);
	void InitS101FeatureTypes(Catalog* catalog);
	void InitControlValues();
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeConfigTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingConfigTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	void OnBnClickedBtnLoadSetting();
	afx_msg void OnBnClickedApply();

public:
	CConfiguration_1* GetConfigPage1();

};
