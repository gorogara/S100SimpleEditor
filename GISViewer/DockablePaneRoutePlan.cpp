#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneRoutePlan.h"
#include "DialogExRoutePlan.h"


IMPLEMENT_DYNAMIC(CDockablePaneRoutePlan, CDockablePane)

CDockablePaneRoutePlan::CDockablePaneRoutePlan()
{
}

CDockablePaneRoutePlan::~CDockablePaneRoutePlan()
{
	delete pDlg;
}


BEGIN_MESSAGE_MAP(CDockablePaneRoutePlan, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


BOOL CDockablePaneRoutePlan::CanBeClosed() const
{
	return FALSE;
}


BOOL CDockablePaneRoutePlan::CanBeResized() const
{
	return TRUE;
}


BOOL CDockablePaneRoutePlan::CanFloat() const
{
	return TRUE;
}


BOOL CDockablePaneRoutePlan::CanAutoHide() const
{
	return TRUE;
}


int CDockablePaneRoutePlan::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1; 
	CRect rect;
	this->GetWindowRect(&rect);
	pDlg = new CDialogExRoutePlan();
	pDlg->Create(IDD_DIALOGEXROUTEPLAN, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW);

	return 0;
}


void CDockablePaneRoutePlan::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy); 
	pDlg->MoveWindow(0, 0, cx, cy);
}


void CDockablePaneRoutePlan::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	pDlg->SetFocus();
}


void CDockablePaneRoutePlan::OnPaint()
{
	CPaintDC dc(this);   
	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(200, 200, 200))); 
}

void CDockablePaneRoutePlan::SetProcessType(int type)
{
	pDlg->m_dataProcessType = type;
}

void CDockablePaneRoutePlan::OnContextMenu(CWnd* , CPoint )
{ 
}
