// DialogExRoutePlan.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExRoutePlan.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

#include "LatLonUtility\\LatLonUtility.h"  
BEGIN_MESSAGE_MAP(CRoutePlanListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CRoutePlanListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()


void CRoutePlanListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	CString text;
	if (pNMLV->uNewState == 3)
	{
		int  iRow = pNMLV->iItem;
		int  iCol = pNMLV->iSubItem;

	}

	*pResult = 0;
} 

IMPLEMENT_DYNAMIC(CDialogExRoutePlan, CDialogEx)

CDialogExRoutePlan::CDialogExRoutePlan(CWnd* pParent )
: CDialogEx(CDialogExRoutePlan::IDD, pParent),
indexCurrentRClickedWP(0)
{
	m_dataProcessType = 0;
}

CDialogExRoutePlan::~CDialogExRoutePlan()
{
}

void CDialogExRoutePlan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROUTE_LIST, routeList);
	DDX_Control(pDX, IDC_LIST_WAYPOINT, m_CListCtrlWaypoint);
	DDX_Control(pDX, IDC_STATIC_DEPARTURE_TIME, m_departureTime);
}


BEGIN_MESSAGE_MAP(CDialogExRoutePlan, CDialogEx)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_COMBO_ROUTE_LIST, &CDialogExRoutePlan::OnCbnSelchangeComboRouteList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_WAYPOINT, &CDialogExRoutePlan::OnNMClickListWaypoint)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WAYPOINT, &CDialogExRoutePlan::OnNMDblclkListWaypoint)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_WAYPOINT, &CDialogExRoutePlan::OnNMRClickListWaypoint)
	ON_COMMAND(ID_MENU_WP_INSERT_PREV, &CDialogExRoutePlan::OnMenuWpInsertPrev)
	ON_COMMAND(ID_MENU_WP_INSERT_AFTER, &CDialogExRoutePlan::OnMenuWpInsertAfter)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_WAYPOINT, &CDialogExRoutePlan::OnNMCustomdrawListWaypoint)
END_MESSAGE_MAP()


void CDialogExRoutePlan::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy); 
	CComboBox* pComboBoxRouteList = (CComboBox*)GetDlgItem(IDC_COMBO_ROUTE_LIST);
	CListCtrl* pListCtrlWaypoint = (CListCtrl*)GetDlgItem(IDC_LIST_WAYPOINT); 
	if (pListCtrlWaypoint->GetSafeHwnd())
	{ 
		pListCtrlWaypoint->MoveWindow(1, 50, cx - 1, cy - 51); 
		CRect rectListCtrlWaypoint;
		pListCtrlWaypoint->GetWindowRect(rectListCtrlWaypoint);  

		for (int i = 0; i < pListCtrlWaypoint->GetHeaderCtrl()->GetItemCount(); ++i)
			pListCtrlWaypoint->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

BOOL CDialogExRoutePlan::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	CListCtrl* pListCtrlWaypoint = (CListCtrl*)GetDlgItem(IDC_LIST_WAYPOINT);   
	CImageList ilWaypoint;
	ilWaypoint.Create(1, 35, ILC_COLOR32, 1, 1); 
	pListCtrlWaypoint->SetImageList(&ilWaypoint, LVSIL_SMALL);
	pListCtrlWaypoint->ModifyStyle(0, LVS_SINGLESEL);
	ilWaypoint.Detach();

	pListCtrlWaypoint->InsertColumn(0, _T("No"), LVCFMT_LEFT, 30, 1);
	pListCtrlWaypoint->InsertColumn(1, _T("위치"), LVCFMT_LEFT, 70);
	pListCtrlWaypoint->InsertColumn(2, _T("속력"), LVCFMT_LEFT, 100);
	pListCtrlWaypoint->InsertColumn(3, _T("도착시간"), LVCFMT_LEFT, 100); 
	pListCtrlWaypoint->SetExtendedStyle(pListCtrlWaypoint->GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	return TRUE;  
}


void CDialogExRoutePlan::UpdateRouteList()
{
	routeList.ResetContent();

	for (unsigned int i = 0; i < pRoutePlanner->GetRouteCount(); i++)
	{
		CString str(pRoutePlanner->GetRouteName(i).c_str());
		routeList.AddString(str);
	}
}


void CDialogExRoutePlan::UpdateWaypointList()
{
	m_CListCtrlWaypoint.DeleteAllItems();

	if (routeList.GetCurSel() < 0)
	{
		return;
	}

	int routeIndex = routeList.GetCurSel();
	int waypointIndex;
	int cntWP = pRoutePlanner->GetWaypointCount(routeList.GetCurSel());

	for (unsigned int i = 0; i < pRoutePlanner->GetWaypointCount(routeList.GetCurSel()); i++)
	{
		waypointIndex = i;

		CString strNo;
		CString strPosition;
		CString strSpeed;
		CString strPartDistance;
		CString strAccumulatedDistance;
		CString strTime; 
		strNo.Format(_T("%d"), i + 1);
		double lon = pRoutePlanner->GetY(routeIndex, waypointIndex);
		double lat = pRoutePlanner->GetX(routeIndex, waypointIndex);
		((CGISViewerView*)pView)->m_pGisLib->InverseProjection(&lat, &lon);
		strPosition.Format(_T("LAT:%0.3f\nLON:%0.3f\n"), lat, lon);   
		double speed = pRoutePlanner->GetSpeed(routeIndex, waypointIndex); 
		strSpeed.Format(_T("%0.2f"), speed);
		strPartDistance.Format(_T("%0.2f"), pRoutePlanner->GetDistance(routeIndex, waypointIndex - 1));
		strAccumulatedDistance.Format(_T("%0.2f"), pRoutePlanner->GetDistanceAccumulated(routeIndex, waypointIndex - 1));

		std::time_t arrivalTime = pRoutePlanner->GetArrivalTime(routeIndex, waypointIndex);
		struct tm t;
		localtime_s(&t, &arrivalTime);
		int year = t.tm_year + 1900;
		int month = t.tm_mon + 1;
		int day = t.tm_mday;
		int hour = t.tm_hour;
		int min = t.tm_min;
		int sec = t.tm_sec;

		strTime.Format(_T("%d년 %d월 %d일 %d시 %d분 %d초"), year, month, day, hour, min, sec);


		m_CListCtrlWaypoint.InsertItem(i, strNo, 0);
		m_CListCtrlWaypoint.SetItemText(i, 1, strPosition);
		m_CListCtrlWaypoint.SetItemText(i, 2, strSpeed);
		m_CListCtrlWaypoint.SetItemText(i, 3, strTime);
	}
}


int CDialogExRoutePlan::GetCurrentRouteIndex()
{
	return routeList.GetCurSel();
}


int CDialogExRoutePlan::GetCurrentWaypointIndex()
{
	return m_CListCtrlWaypoint.GetNextItem(-1, LVNI_SELECTED);
}


void CDialogExRoutePlan::SelectRouteIndex(int _index)
{
	routeList.SetCurSel(_index);
}

void CDialogExRoutePlan::OnOK()
{
	return;
}


void CDialogExRoutePlan::OnCancel()
{
	return;
}


void CDialogExRoutePlan::OnCbnSelchangeComboRouteList()
{
	if (routeList.GetCurSel() >= 0)
	{
		time_t time;
		pRoutePlanner->GetDepartureTime(routeList.GetCurSel(), &time); 
		struct tm t;
		localtime_s(&t, &time);
		int year = t.tm_year + 1900;
		int month = t.tm_mon + 1;
		int day = t.tm_mday;
		int hour = t.tm_hour;
		int min = t.tm_min;

		CString strDepartureTime;
		strDepartureTime.Format(_T("%d-%02d-%02d, %02d:%02d"), year, month, day, hour, min);
		SetDepartureTime(strDepartureTime);
	}
	UpdateWaypointList();

	pView->Invalidate();
}



void CDialogExRoutePlan::SetDepartureTime(CString str)
{
	m_departureTime.SetWindowTextW(str);
}

void CDialogExRoutePlan::SetRouteListActive(bool bActive)
{
	routeList.EnableWindow(bActive);
}

void CDialogExRoutePlan::OnNMClickListWaypoint(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	pView->Invalidate();


#ifdef _SHIP_REPORT_MSG
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_DockablePaneShipReport.SetSpatialInformation();
#endif

	*pResult = 0;
}


void CDialogExRoutePlan::OnNMDblclkListWaypoint(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	*pResult = 0;

	int nClickedWP = pNMItemActivate->iItem;

	if (nClickedWP < 0) return;

	int nRouteIndex = GetCurrentRouteIndex();

	double mx = pView->pRoutePlanner->GetX(nRouteIndex, nClickedWP);
	double my = pView->pRoutePlanner->GetY(nRouteIndex, nClickedWP);

	CRect rectView;
	pView->GetClientRect(rectView);
	pView->m_pGisLib->MoveMap(rectView.Width() / 2, rectView.Height() / 2, mx, my);
	pView->MapRefresh();
}


void CDialogExRoutePlan::OnNMRClickListWaypoint(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	*pResult = 0;

	int indexRoute = GetCurrentRouteIndex();
	int indexWP = pNMItemActivate->iItem;
	int cntWP = pView->pRoutePlanner->GetWaypointCount(indexRoute);
	indexCurrentRClickedWP = indexWP;

	CMenu menu;
	menu.LoadMenuW(IDR_MENU_ADD_WP);
	CMenu* pMenu = menu.GetSubMenu(0);

	if (indexWP == -1) {
		pMenu->EnableMenuItem(ID_MENU_WP_INSERT_PREV, MF_DISABLED);
		pMenu->EnableMenuItem(ID_MENU_WP_INSERT_AFTER, MF_DISABLED);
	}
	else if (indexWP == 0) {
		pMenu->EnableMenuItem(ID_MENU_WP_INSERT_PREV, MF_DISABLED);
	}
	else if (indexWP == (cntWP - 1)) {
		pMenu->EnableMenuItem(ID_MENU_WP_INSERT_AFTER, MF_DISABLED);
	}

	CPoint point;
	GetCursorPos(&point);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);
}


void CDialogExRoutePlan::OnMenuWpInsertPrev()
{
	int indexRoute = GetCurrentRouteIndex();
	int indexWP = indexCurrentRClickedWP;
	double prevX = pView->pRoutePlanner->GetX(indexRoute, indexWP - 1);
	double prevY = pView->pRoutePlanner->GetY(indexRoute, indexWP - 1);

	double curX = pView->pRoutePlanner->GetX(indexRoute, indexWP);
	double curY = pView->pRoutePlanner->GetY(indexRoute, indexWP);

	double newX = (prevX + curX) / 2;
	double newY = (prevY + curY) / 2;

	double speed = pView->pRoutePlanner->GetSpeed(indexRoute, indexWP - 1);

	LatLonUtility::InverseProjectionToDegree(newX, newY);

	pView->pRoutePlanner->AddWaypoint(GetCurrentRouteIndex(), indexWP - 1, newX, newY, speed, speed);
	UpdateWaypointList();
	pView->Invalidate();
}


void CDialogExRoutePlan::OnMenuWpInsertAfter()
{
	int indexRoute = GetCurrentRouteIndex();
	int indexWP = indexCurrentRClickedWP;
	double curX = pView->pRoutePlanner->GetX(indexRoute, indexWP);
	double curY = pView->pRoutePlanner->GetY(indexRoute, indexWP);

	double nextX = pView->pRoutePlanner->GetX(indexRoute, indexWP + 1);
	double nextY = pView->pRoutePlanner->GetY(indexRoute, indexWP + 1);

	double newX = (nextX + curX) / 2;
	double newY = (nextY + curY) / 2;

	double speed = pView->pRoutePlanner->GetSpeed(indexRoute, indexWP);

	LatLonUtility::InverseProjectionToDegree(newX, newY);

	pView->pRoutePlanner->AddWaypoint(GetCurrentRouteIndex(), indexWP, newX, newY, speed, speed);
	UpdateWaypointList();
	pView->Invalidate();
}


void CDialogExRoutePlan::OnNMCustomdrawListWaypoint(NMHDR *pNMHDR, LRESULT *pResult)
{  

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = 0;
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		for (unsigned i = 0; i < wpWarning.size(); i++) {
			if (pLVCD->nmcd.dwItemSpec == wpWarning.at(i)) {
				pLVCD->clrTextBk = RGB(220, 20, 60);
			}
		}

		*pResult = CDRF_DODEFAULT;
	}
}