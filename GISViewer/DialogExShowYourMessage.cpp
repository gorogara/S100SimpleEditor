// DialogExShowYourMessage.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExShowYourMessage.h"
#include "afxdialogex.h"
#include "FileLoad.h"

#include <iostream>
#include <locale.h>

using namespace std; 

IMPLEMENT_DYNAMIC(DialogExShowYourMessage, CDialogEx)


DialogExShowYourMessage::DialogExShowYourMessage(CWnd* pParent )
	: CDialogEx(DialogExShowYourMessage::IDD, pParent)
	, m_radioAgreement1(0)
{


}

DialogExShowYourMessage::~DialogExShowYourMessage()
{
}

void DialogExShowYourMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_comboCategory);
	DDX_Control(pDX, IDC_CHECK_OPTION1, m_checkboxOption1);

	DDX_Radio(pDX, IDC_RADIO_AGREEMENT1, m_radioAgreement1);
	DDX_Control(pDX, IDC_CHECKLIST1, m_checkList);
	DDX_Control(pDX, IDC_EDIT_FILELOAD, m_editFileLoad);
}


BEGIN_MESSAGE_MAP(DialogExShowYourMessage, CDialogEx)
	ON_COMMAND(IDD_DIALOG_SHOW_YOUR_MESSAGE, &DialogExShowYourMessage::OnIddDialogShowYourMessage)
	ON_BN_CLICKED(IDOK, &DialogExShowYourMessage::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DialogExShowYourMessage::OnBnClickedCancel)
	ON_CLBN_CHKCHANGE(IDC_CHECKLIST1, &DialogExShowYourMessage::OnBnClickedBtnRead)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_AGREEMENT1, IDC_RADIO_AGREEMENT3, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_BUTTON_FILELOAD, &DialogExShowYourMessage::OnBnClickedFileLoad)
END_MESSAGE_MAP() 
void DialogExShowYourMessage::OnIddDialogShowYourMessage()
{
}

#pragma warning(disable:4129)
void DialogExShowYourMessage::OnBnClickedOk()
{ 
	CString strMessage;
	CString strCategory;
	
	GetDlgItemText(IDC_YOUR_MESSAGE, strMessage);
	GetDlgItemText(IDC_COMBO_CATEGORY, strCategory);

	m_message = strMessage;
	m_category = strCategory;
	m_option = DialogExShowYourMessage::OnBnClickedCheckOption();

	CDialogEx::OnOK();
}


void DialogExShowYourMessage::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL DialogExShowYourMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboCategory.AddString(_T("category 1"));
	m_comboCategory.AddString(_T("category 2"));
	m_comboCategory.AddString(_T("category 3"));
	m_comboCategory.SetCurSel(0); 
	m_checkboxOption1.SetCheck(BST_CHECKED); 
	m_checkList.InsertString(-1, _T("ITEM1"));
	m_checkList.InsertString(-1, _T("ITEM2"));
	m_checkList.InsertString(-1, _T("ITEM3"));
	m_checkList.InsertString(-1, _T("ITEM4"));
	m_checkList.InsertString(-1, _T("ITEM5"));
	m_checkVList = 0;
	UpdateData(FALSE);

	return true;
	
} 
void DialogExShowYourMessage::OnBnClickedRadio(UINT value)
{
	UpdateData(TRUE);
}


CString DialogExShowYourMessage::OnBnClickedCheckOption()
{
	CString strOption = L"";
	
	strOption += IsDlgButtonChecked(IDC_CHECK_OPTION1) ? "Option1 \n" : "";
	strOption += IsDlgButtonChecked(IDC_CHECK_OPTION2) ? "Option2 \n" : "";
	strOption += IsDlgButtonChecked(IDC_CHECK_OPTION3) ? "Option3 \n" : "";

	return strOption;

} 





void DialogExShowYourMessage::OnBnClickedBtnRead()
{
	
	UpdateData(TRUE);
	CString str = NULL;

	m_checkListStr = L""; 
	
	for (int i = 0; i < m_checkList.GetCount(); i++){
		
		if (m_checkList.GetCheck(i) == BST_CHECKED){
			m_checkList.GetText(i, str);
			m_checkListStr += str;
		}
		
	}

} 
void DialogExShowYourMessage::OnBnClickedFileLoad()
{

	CString str;
	CString path = _T("C:\\devEnv\\a.txt");
	str = FileLoad(path).FileLoadFromPath();
		
	m_editFileLoad.SetWindowTextW(str);
	

}



