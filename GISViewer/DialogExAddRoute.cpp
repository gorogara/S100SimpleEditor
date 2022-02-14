// DialogExAddRoute.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExAddRoute.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

#include <ctime> 

IMPLEMENT_DYNAMIC(CDialogExAddRoute, CDialogEx)

CDialogExAddRoute::CDialogExAddRoute(CWnd* pParent )
: CDialogEx(CDialogExAddRoute::IDD, pParent)
, m_routeName(_T(""))
, m_date(COleDateTime::GetCurrentTime())
, m_time(COleDateTime::GetCurrentTime())
{
	pView = NULL;
}

CDialogExAddRoute::~CDialogExAddRoute()
{
}

void CDialogExAddRoute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, routeName);
	DDX_Control(pDX, ID_DAY, date);
	DDX_Control(pDX, ID_TIME, time);
	DDX_DateTimeCtrl(pDX, ID_DAY, m_date);
	DDX_DateTimeCtrl(pDX, ID_TIME, m_time);
}


BEGIN_MESSAGE_MAP(CDialogExAddRoute, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExAddRoute::OnBnClickedOk)
END_MESSAGE_MAP() 


void CDialogExAddRoute::OnBnClickedOk()
{
	if (routeName.GetSafeHwnd())
	{ 
		CString strRouteName;
		routeName.GetWindowText(strRouteName); 
		SYSTEMTIME sysDate;
		SYSTEMTIME sysTime;

		date.GetTime(&sysDate); 
		time.GetTime(&sysTime); 

		SYSTEMTIME sysDateTime; 

		sysDateTime.wYear = sysDate.wYear;
		sysDateTime.wMonth = sysDate.wMonth;
		sysDateTime.wDay = sysDate.wDay;
		sysDateTime.wDayOfWeek = sysDate.wDayOfWeek;

		sysDateTime.wHour = sysTime.wHour;
		sysDateTime.wMinute = sysTime.wMinute;
		sysDateTime.wSecond = sysTime.wSecond;
		sysDateTime.wMilliseconds = sysTime.wMilliseconds; 
		CTime cTime(sysDateTime);
		std::time_t routeTime = cTime.GetTime(); 
		pView->pRoutePlanner->AddRoute(strRouteName.GetBuffer(), routeTime);
	}

	CDialogEx::OnOK();
}


void CDialogExAddRoute::UpdateRouteList()
{

}