// DockablePaneLayerManager.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneLayerManager.h"
#include "DialogDockLayerManager.h" 

IMPLEMENT_DYNAMIC(CDockablePaneLayerManager, CDockablePane)

CDockablePaneLayerManager::CDockablePaneLayerManager()
{
	EnableAutomation();
}

CDockablePaneLayerManager::~CDockablePaneLayerManager()
{
	delete pDlg; 
}


BEGIN_MESSAGE_MAP(CDockablePaneLayerManager, CDockablePane)
	ON_WM_CREATE() 
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_32913, &CDockablePaneLayerManager::OnEdit32913)
END_MESSAGE_MAP() 

int CDockablePaneLayerManager::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}  
	CRect rect;
	this->GetWindowRect(&rect);
	
	pDlg = new CDialogDockLayerManager();
	pDlg->Create(IDD_DIALOG_DOCK_LAYERMANEGER, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW);
	
	return 0;
}


void CDockablePaneLayerManager::OnPaint()
{
	CPaintDC dc(this);   

	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(230, 230, 230))); 
}


void CDockablePaneLayerManager::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);  
	CRect rect;
	this->GetWindowRect(rect);
	pDlg->MoveWindow(0, 0, cx, cy);
}


void CDockablePaneLayerManager::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);  
	pDlg->SetFocus();
}

void CDockablePaneLayerManager::OnDestroy()
{
	CDockablePane::OnDestroy(); 
}


BOOL CDockablePaneLayerManager::CanBeClosed() const
{
	return false;
}


BOOL CDockablePaneLayerManager::CanBeResized() const
{
	return true;
}


BOOL CDockablePaneLayerManager::CanFloat() const
{
	return true;
}


BOOL CDockablePaneLayerManager::CanAutoHide() const
{
	return true;
}

void CDockablePaneLayerManager::OnFinalRelease()
{ 

	CDockablePane::OnFinalRelease();
}


BOOL CDockablePaneLayerManager::PreCreateWindow(CREATESTRUCT& cs)
{ 

	return CDockablePane::PreCreateWindow(cs);
}


void CDockablePaneLayerManager::OnContextMenu(CWnd* , CPoint )
{ 
	return;
}


void CDockablePaneLayerManager::UpdateList()
{
	pDlg->UpdateList();
}

void CDockablePaneLayerManager::SaveLayer(CString filename, CString extend)
{
	pDlg->SaveLayer(filename, extend);
}

void CDockablePaneLayerManager::SaveLayerTextPlacement(CString filename, CString extend)
{
	pDlg->SaveLayerTextPlacement(filename, extend);
}

void CDockablePaneLayerManager::OnEdit32913()
{ 
}
