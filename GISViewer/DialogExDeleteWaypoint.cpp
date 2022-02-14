// DialogExDeleteWaypoint.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExDeleteWaypoint.h"
#include "afxdialogex.h" 

IMPLEMENT_DYNAMIC(CDialogExDeleteWaypoint, CDialogEx)

CDialogExDeleteWaypoint::CDialogExDeleteWaypoint(CWnd* pParent )
: CDialogEx(CDialogExDeleteWaypoint::IDD, pParent)
, m_strWaypointNumber(_T(""))
{

}

CDialogExDeleteWaypoint::~CDialogExDeleteWaypoint()
{
}

void CDialogExDeleteWaypoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_WPNAME, m_strWaypointNumber);
}


BEGIN_MESSAGE_MAP(CDialogExDeleteWaypoint, CDialogEx)
END_MESSAGE_MAP() 
