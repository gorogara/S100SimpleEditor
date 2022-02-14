#pragma once 

class CFCPCSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFCPCSettingDlg)

public:
	CFCPCSettingDlg(CWnd* pParent = nullptr); 
	virtual ~CFCPCSettingDlg(); 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PC_FC_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_fclist;
	CListCtrl m_pclist;
	void SettingPCFC();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFcChangeButton();
	afx_msg void OnBnClickedPcChangeButton();

	afx_msg void OnNMClickListFc(NMHDR *pNMHDR, LRESULT *pResult);
};
