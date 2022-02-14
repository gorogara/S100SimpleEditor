// DialogProgressBar.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogProgressBar.h"
#include "afxdialogex.h" 

IMPLEMENT_DYNAMIC(DialogProgressBar, CDialogEx)

DialogProgressBar::DialogProgressBar(CWnd* pParent )
	: CDialogEx(DialogProgressBar::IDD, pParent)
{

}

DialogProgressBar::~DialogProgressBar()
{
}

void DialogProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogProgressBar, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogProgressBar::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DialogProgressBar::OnBnClickedCancel)
END_MESSAGE_MAP() 


BOOL DialogProgressBar::PreTranslateMessage(MSG* pMsg)
{ 
	return CDialogEx::PreTranslateMessage(pMsg);
}

void DialogProgressBar::OnBnClickedOk()
{  
}


void DialogProgressBar::OnBnClickedCancel()
{  
}
