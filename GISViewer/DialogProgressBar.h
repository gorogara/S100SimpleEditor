#pragma once 

class DialogProgressBar : public CDialogEx
{
	DECLARE_DYNAMIC(DialogProgressBar)

public:
	DialogProgressBar(CWnd* pParent = NULL); 
	virtual ~DialogProgressBar(); 
	enum { IDD = IDD_DLG_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
#pragma once
