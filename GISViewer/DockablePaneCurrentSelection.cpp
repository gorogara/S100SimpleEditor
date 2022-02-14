// DockablePaneRelation.cpp : implementation file 
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneCurrentSelection.h"
#include "DialogDockCurrentSelection.h"

#include <map>


IMPLEMENT_DYNAMIC(CDockablePaneCurrentSelection, CDockablePane)

CDockablePaneCurrentSelection::CDockablePaneCurrentSelection()
{
	EnableAutomation();
}


CDockablePaneCurrentSelection::~CDockablePaneCurrentSelection()
{
	delete pDlg;
}


BEGIN_MESSAGE_MAP(CDockablePaneCurrentSelection, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU() 
END_MESSAGE_MAP()

void CDockablePaneCurrentSelection::OnPaint()
{
	CPaintDC dc(this);   

	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(230, 230, 230))); 
}



int CDockablePaneCurrentSelection::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;  
	CRect rect;
	this->GetWindowRect(&rect);

	pDlg = new CDialogDockCurrentSelection();
	pDlg->Create(IDD_DIALOG_DOCK_CURRENT_SELECTION, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->pView = pView;

	return 0;
}





void CDockablePaneCurrentSelection::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);  
	CRect rect;
	this->GetWindowRect(rect);
	pDlg->MoveWindow(0, 0, cx, cy);
}


void CDockablePaneCurrentSelection::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);  
	pDlg->SetFocus();
}

void CDockablePaneCurrentSelection::OnDestroy()
{
	CDockablePane::OnDestroy(); 
}


BOOL CDockablePaneCurrentSelection::CanBeClosed() const
{
	return FALSE;
}


BOOL CDockablePaneCurrentSelection::CanBeResized() const
{
	return TRUE;
}


BOOL CDockablePaneCurrentSelection::CanFloat() const
{
	return TRUE;
}


BOOL CDockablePaneCurrentSelection::CanAutoHide() const
{
	return TRUE;
}

void CDockablePaneCurrentSelection::OnFinalRelease()
{ 

	CDockablePane::OnFinalRelease();
}


BOOL CDockablePaneCurrentSelection::PreCreateWindow(CREATESTRUCT& cs)
{ 

	return CDockablePane::PreCreateWindow(cs);
}


void CDockablePaneCurrentSelection::OnContextMenu(CWnd* , CPoint )
{ 
	return;
}


void CDockablePaneCurrentSelection::UpdateList()
{
	pDlg->UpdateList();
}

void CDockablePaneCurrentSelection::RemoveAll()
{
	pDlg->OnMenuRemoveAll();
}

void CDockablePaneCurrentSelection::DeleteItem(CString id) 
{
	pDlg->DeleteItem(id);
}

void CDockablePaneCurrentSelection::UpdateListTest(CStringArray *csa, S101Cell *cell, CString isCtrlClicked)
{
	pDlg->UpdateListTest(csa, cell, isCtrlClicked);
}

void CDockablePaneCurrentSelection::SetView(CGISViewerView* v)
{
	pView = v; 
	pDlg->pView = v;
}