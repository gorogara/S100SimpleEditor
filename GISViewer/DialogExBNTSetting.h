

#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

class CGISViewerView;
// CDialogExBNTSetting 대화 상자입니다.

class CDialogExBNTSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExBNTSetting)

public:
	CDialogExBNTSetting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogExBNTSetting();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BNT_SETTING };
	CGISViewerView* m_pView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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

