// CDialogExRelationInfo.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExRelationInfo.h"
#include "afxdialogex.h"

#include <iostream>
#include <locale.h>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExRelationInfo, CDialogEx)


CDialogExRelationInfo::CDialogExRelationInfo(CWnd* pParent )
	: CDialogEx(CDialogExRelationInfo::IDD, pParent)
{


}

CDialogExRelationInfo::~CDialogExRelationInfo()
{
}

void CDialogExRelationInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDialogExRelationInfo, CDialogEx)
	ON_COMMAND(IDD_DIALOG_RELATION_INFO, &CDialogExRelationInfo::OnIddDialogRelationInfo)
	ON_BN_CLICKED(IDOK, &CDialogExRelationInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExRelationInfo::OnBnClickedCancel)
END_MESSAGE_MAP() 
void CDialogExRelationInfo::OnIddDialogRelationInfo()
{
}

#pragma warning(disable:4129)
void CDialogExRelationInfo::OnBnClickedOk()
{ 

	CDialogEx::OnOK();
}


void CDialogExRelationInfo::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL CDialogExRelationInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return true;
	
}
