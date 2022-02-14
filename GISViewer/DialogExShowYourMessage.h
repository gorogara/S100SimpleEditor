#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <string>
class CGISViewerView; 

class DialogExShowYourMessage : public CDialogEx
{
	DECLARE_DYNAMIC(DialogExShowYourMessage)

public:
	DialogExShowYourMessage(CWnd* pParent = NULL); 
	virtual ~DialogExShowYourMessage(); 
	enum { IDD = IDD_DIALOG_SHOW_YOUR_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogShowYourMessage();
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio(UINT msg);
	afx_msg CString OnBnClickedCheckOption();
	afx_msg void OnBnClickedBtnRead();
	virtual BOOL OnInitDialog();

	CString m_message;
	CString m_category;
	CString m_option;


	CEdit m_editMessage; 
	CComboBox m_comboCategory;

	CButton m_checkboxOption1;

	int m_radioAgreement1;
	

	int m_checkVList;
	CString m_checkListStr;
	CCheckListBox m_checkList;
	afx_msg void OnBnClickedFileLoad();
	CEdit m_editFileLoad;
	CEdit m_editXML;

	

};


