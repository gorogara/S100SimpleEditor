// DockablePaneRelation.cpp : implementation file 
#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneRelation.h"
#include "DialogDockRelation.h"

IMPLEMENT_DYNAMIC(CDockablePaneRelation, CDockablePane)

CDockablePaneRelation::CDockablePaneRelation()
{
	EnableAutomation();
}


CDockablePaneRelation::~CDockablePaneRelation()
{
	delete pDlg;
}


BEGIN_MESSAGE_MAP(CDockablePaneRelation, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU() 
END_MESSAGE_MAP()

void CDockablePaneRelation::OnPaint()
{
	CPaintDC dc(this);   

	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(230, 230, 230))); 
}



int CDockablePaneRelation::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;  
	CRect rect;
	this->GetWindowRect(&rect);

	pDlg = new CDialogDockRelation();
	pDlg->Create(IDD_DIALOG_DOCK_RELATION, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW);

	return 0;
}





void CDockablePaneRelation::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);  
	CRect rect;
	this->GetWindowRect(rect);
	pDlg->MoveWindow(0, 0, cx, cy);
}


void CDockablePaneRelation::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);  
	pDlg->SetFocus();
}

void CDockablePaneRelation::OnDestroy()
{
	CDockablePane::OnDestroy(); 
}


BOOL CDockablePaneRelation::CanBeClosed() const
{
	return FALSE;
}


BOOL CDockablePaneRelation::CanBeResized() const
{
	return TRUE;
}


BOOL CDockablePaneRelation::CanFloat() const
{
	return TRUE;
}


BOOL CDockablePaneRelation::CanAutoHide() const
{
	return TRUE;
}

void CDockablePaneRelation::OnFinalRelease()
{ 

	CDockablePane::OnFinalRelease();
}


BOOL CDockablePaneRelation::PreCreateWindow(CREATESTRUCT& cs)
{ 

	return CDockablePane::PreCreateWindow(cs);
}


void CDockablePaneRelation::OnContextMenu(CWnd* , CPoint )
{ 
	return;
}


void CDockablePaneRelation::UpdateList()
{
	pDlg->UpdateList();
}
 
