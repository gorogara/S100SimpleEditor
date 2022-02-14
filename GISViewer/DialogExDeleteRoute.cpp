// DialogExDeleteRoute.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExDeleteRoute.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDialogExDeleteRoute, CDialogEx)

CDialogExDeleteRoute::CDialogExDeleteRoute(CWnd* pParent )
: CDialogEx(CDialogExDeleteRoute::IDD, pParent)
, m_strRouteName(_T(""))
{

}

CDialogExDeleteRoute::~CDialogExDeleteRoute()
{
}

void CDialogExDeleteRoute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_ROUTENAME, m_strRouteName);
}


BEGIN_MESSAGE_MAP(CDialogExDeleteRoute, CDialogEx)
END_MESSAGE_MAP() 
