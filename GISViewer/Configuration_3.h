#pragma once
#include "afxwin.h"

class CConfigrationDlg;
class CConfiguration_3 : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration_3)

public:
	CConfiguration_3(CWnd* pParent = nullptr); 
	virtual ~CConfiguration_3(); 
	enum { IDD = IDD_DIALOG_CONFIG_3 };

	CConfigrationDlg* m_pParent;

private:
	void InitComboBoxUnitDistance();
	void AddString_ComboBox_UnitDistance();
	void SetCurSel_ComboBox_UnitDistance();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CComboBox m_ComboBoxUnitDistance;
};
