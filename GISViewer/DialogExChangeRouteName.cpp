// DialogExChangeRouteName.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExChangeRouteName.h"
#include "afxdialogex.h"
#include "GISViewerView.h"
#include "DockablePaneRoutePlan.h"
#include "DialogExRoutePlan.h" 

IMPLEMENT_DYNAMIC(CDialogExChangeRouteName, CDialogEx)

CDialogExChangeRouteName::CDialogExChangeRouteName(CWnd* pParent )
: CDialogEx(CDialogExChangeRouteName::IDD, pParent)
, m_strNewName(_T(""))
{
	pView = nullptr;
}

CDialogExChangeRouteName::~CDialogExChangeRouteName()
{
}

void CDialogExChangeRouteName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_strNewName);
	DDX_Control(pDX, ID_DAY_NEW_DAY, m_dateTimeCtrlNewDate);
	DDX_Control(pDX, ID_TIME_NEW_TIME, m_dateTimeCtrlNewTime);
	DDX_Control(pDX, IDC_EDIT_NEW_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CDialogExChangeRouteName, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExChangeRouteName::OnBnClickedOk)
END_MESSAGE_MAP() 


void CDialogExChangeRouteName::OnBnClickedOk()
{
	int curIndex = pView->m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex(); 
	SYSTEMTIME sysDate;
	SYSTEMTIME sysTime;

	m_dateTimeCtrlNewDate.GetTime(&sysDate); 
	m_dateTimeCtrlNewTime.GetTime(&sysTime); 

	struct tm t;
	t.tm_year = sysDate.wYear - 1900;
	t.tm_mon = sysDate.wMonth - 1;
	t.tm_mday = sysDate.wDay;
	t.tm_hour = sysTime.wHour;
	t.tm_min = sysTime.wMinute;
	t.tm_sec = sysTime.wSecond;

	time_t time = mktime(&t);

	CString newName;
	m_editName.GetWindowTextW(newName);
	pView->pRoutePlanner->SetRouteName(curIndex, newName.GetBuffer());
	pView->pRoutePlanner->SetDepartureTime(curIndex, time);

	CDialogEx::OnOK();
}