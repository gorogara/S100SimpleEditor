

#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

class CGISViewerView;
// CDialogExBNTSetting ��ȭ �����Դϴ�.

class CDialogExBNTSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExBNTSetting)

public:
	CDialogExBNTSetting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogExBNTSetting();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BNT_SETTING };
	CGISViewerView* m_pView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CDateTimeCtrl m_DataTimeCtrlStartDate;
	CDateTimeCtrl m_DateTimeCtrlStartTime;
	CDateTimeCtrl m_DateTimeCtrlEndDate;
	CDateTimeCtrl m_DateTimeCtrlEndTime;
	CComboBox m_ComboBoxInterval;
	virtual BOOL OnInitDialog();
};

