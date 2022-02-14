// CDialogExRelationInformation.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExRelationInformation.h"
#include "afxdialogex.h"
#include "FileLoad.h"
#include "GISViewer.h"

#include <iostream>
#include <locale.h>
#include <unordered_map>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExRelationInformation, CDialogEx)


CDialogExRelationInformation::CDialogExRelationInformation(CWnd* pParent )
	: CDialogEx(CDialogExRelationInformation::IDD, pParent)
{
}

CDialogExRelationInformation::~CDialogExRelationInformation() 
{
}

void CDialogExRelationInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANGE_ALL_ATTRIBUTE, m_ComboAttribute);
	DDX_Control(pDX, IDC_COMBO_CHANGE_ALL_VALUE_ENUM, m_ComboValue);
}


BEGIN_MESSAGE_MAP(CDialogExRelationInformation, CDialogEx)
	ON_COMMAND(IDD_DIALOG_RELATION_INFORMATION, &CDialogExRelationInformation::OnIddDialogRelationInformation)
	ON_BN_CLICKED(IDOK, &CDialogExRelationInformation::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExRelationInformation::OnBnClickedCancel)
END_MESSAGE_MAP() 
void CDialogExRelationInformation::OnIddDialogRelationInformation()
{
}

#pragma warning(disable:4129)
void CDialogExRelationInformation::OnBnClickedOk()
{ 
	m_ComboAttribute.GetWindowText(m_attribteName);
	m_ComboValue.GetWindowText(m_attribteValue);

	CDialogEx::OnOK();
}


void CDialogExRelationInformation::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL CDialogExRelationInformation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] Dialog initializing"));
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] Dialog initializing completed"));

	return true;
	
}

