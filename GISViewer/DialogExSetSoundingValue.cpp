// DialogExSetSoundingValue.cpp: 구현 파일 

#include "stdafx.h"
#include "DialogExSetSoundingValue.h"
#include "afxdialogex.h"
#include "Resource.h" 

IMPLEMENT_DYNAMIC(DialogExSetSoundingValue, CDialogEx)

DialogExSetSoundingValue::DialogExSetSoundingValue(CWnd* pParent )
	: CDialogEx(IDD_DIALOG_SOUNDING_VALUE, pParent)
	, m_soundingValue(0)
{

}

DialogExSetSoundingValue::~DialogExSetSoundingValue()
{
}

void DialogExSetSoundingValue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SOUNDING_VALUE, m_soundingValue);
}


BEGIN_MESSAGE_MAP(DialogExSetSoundingValue, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogExSetSoundingValue::OnBnClickedOk)
END_MESSAGE_MAP() 


void DialogExSetSoundingValue::OnBnClickedOk()
{ 
	UpdateData();
	CDialogEx::OnOK();
}


float DialogExSetSoundingValue::GetSoundingValue()
{
	return m_soundingValue;
}