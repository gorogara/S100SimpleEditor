// DockablePanePickReport.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePanePickReport.h"
#include "DialogExPickReport.h" 

IMPLEMENT_DYNAMIC(CDockablePanePickReport, CDockablePane)

CDockablePanePickReport::CDockablePanePickReport()
{
	EnableAutomation();
}

CDockablePanePickReport::~CDockablePanePickReport()
{
	delete pDlg;
}


BEGIN_MESSAGE_MAP(CDockablePanePickReport, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


int CDockablePanePickReport::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1; 
	CRect rect;
	this->GetWindowRect(rect);

	pDlg = new CDialogExPickReport();
	pDlg->Create(IDD_DIALOG_PICK_REPORT, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW);

	return 0;
}


void CDockablePanePickReport::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rect;
	this->GetWindowRect(rect);
	pDlg->MoveWindow(0, 0, cx, cy);
}


void CDockablePanePickReport::OnPaint()
{
	CPaintDC dc(this);  

	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(200, 200, 200)));
}


void CDockablePanePickReport::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd); 
	pDlg->SetFocus();
}


BOOL CDockablePanePickReport::CanBeClosed() const
{
	return FALSE;
}


BOOL CDockablePanePickReport::CanBeResized() const
{
	return TRUE;
}


BOOL CDockablePanePickReport::CanFloat() const
{
	return TRUE;
}


BOOL CDockablePanePickReport::CanAutoHide() const
{
	return TRUE;
}

void CDockablePanePickReport::OnContextMenu(CWnd* , CPoint )
{
	return;
}