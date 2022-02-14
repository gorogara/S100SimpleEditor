#pragma once
#include "afxwin.h" 
class CConfigrationDlg;
class CConfiguration_1 : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration_1)

public:
	CConfiguration_1(CWnd* pParent = NULL); 
	virtual ~CConfiguration_1();
	CConfigrationDlg *m_pParent; 
	enum { IDD = IDD_DIALOG_CONFIG_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CButton m_twoShade;
	CButton m_useNationalObjectName;
	CEdit	m_safetyDepth;
	CEdit	m_safetyWaterLevel;
	CEdit	m_veryShallowWaterLevel;
	CEdit	m_veryDeepWaterLevel;
	CEdit	m_depthCorrectionInterval;

	int m_displayMode;
	int m_colorScheme; 
	int m_SymbolizedAreaBoundary;
	int m_seabed_type;

	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedBtnLoadSetting();
	int m_DrawingType;
	CButton m_useSpatailQuery;
	CEdit m_settingFontSize;

	void SetFontList(std::vector<CString> fontList);
	std::vector<CString>* GetFontList();
	CComboBox m_comboFontName;


private:
	std::vector<CString> m_fontList;
public:
	CButton m_loadSettingbutton;
};
