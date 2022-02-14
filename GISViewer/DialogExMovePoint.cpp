// DialogExMovePoint.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExMovePoint.h"
#include "afxdialogex.h" 

IMPLEMENT_DYNAMIC(CDialogExMovePoint, CDialogEx)

CDialogExMovePoint::CDialogExMovePoint(CWnd* pParent )
	: CDialogEx(CDialogExMovePoint::IDD, pParent)
	, m_lat(0)
	, m_lon(0)
	, m_latMin(0)
	, m_lonMin(0)
	, m_latSec(0)
	, m_lonSec(0)
{

}

CDialogExMovePoint::~CDialogExMovePoint()
{
}

void CDialogExMovePoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LAT, m_lat);
	DDX_Text(pDX, IDC_EDIT_LON, m_lon);
	DDX_Text(pDX, IDC_EDIT_LAT_MIN, m_latMin);
	DDX_Text(pDX, IDC_EDIT_LON_MIN, m_lonMin);
	DDX_Text(pDX, IDC_EDIT_LAT_SEC, m_latSec);
	DDX_Text(pDX, IDC_EDIT_LON_SEC, m_lonSec);
}


BEGIN_MESSAGE_MAP(CDialogExMovePoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExMovePoint::OnBnClickedOk)
END_MESSAGE_MAP() 


void CDialogExMovePoint::OnBnClickedOk()
{ 
	UpdateData(TRUE);

	if ((m_lat < -85) || (m_lat > 85)) 
	{
		AfxMessageBox(_T("Invalid Value"));
		return;		
	}

	if ((m_lon < -180) || (m_lon > 180)) 
	{
		AfxMessageBox(_T("Invalid Value"));
		return; 
	}

	if ((0 > m_latMin) || (m_latMin >= 60))
	{
		AfxMessageBox(_T("Invalid Value"));
		return;
	}

	if ((0 > m_latSec) || (m_latSec >= 60))
	{
		AfxMessageBox(_T("Invalid Value"));
		return;
	}

	if ((0 > m_lonMin) || (m_lonMin >= 60))
	{
		AfxMessageBox(_T("Invalid Value"));
		return;
	}

	if ((0 > m_lonSec) || (m_lonSec >= 60))
	{
		AfxMessageBox(_T("Invalid Value"));
		return;
	}
	CDialogEx::OnOK();
}
