// DialogExAddWaypoint.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExAddWaypoint.h"
#include "afxdialogex.h" 

IMPLEMENT_DYNAMIC(CDialogExAddWaypoint, CDialogEx)

CDialogExAddWaypoint::CDialogExAddWaypoint(CWnd* pParent )
: CDialogEx(CDialogExAddWaypoint::IDD, pParent)
{
	m_fLat = 0.0;
	m_fLon = 0.0;
	m_dSpeed = 0.0;
	isAdd = true;
}

CDialogExAddWaypoint::~CDialogExAddWaypoint()
{
}

void CDialogExAddWaypoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WP_LAT, m_fLat);
	DDX_Text(pDX, IDC_EDIT_WP_LON, m_fLon);

	DDX_Text(pDX, IDC_EDIT_SPEED, m_dSpeed);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_editSpeed);
}


BEGIN_MESSAGE_MAP(CDialogExAddWaypoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExAddWaypoint::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDialogExAddWaypoint::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	if (isAdd == false)
	{
		SetWindowTextW(_T("Change Waypoint"));
	}

	return TRUE;  
}


void CDialogExAddWaypoint::OnBnClickedOk()
{ 
	CDialogEx::OnOK();
}
