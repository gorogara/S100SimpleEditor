// DockablePaneLogger.cpp : implementation file 
#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneLogger.h"
#include "DialogDockLogger.h"

IMPLEMENT_DYNAMIC(CDockablePaneLogger, CDockablePane)

CDockablePaneLogger::CDockablePaneLogger()
{
	EnableAutomation();
}


CDockablePaneLogger::~CDockablePaneLogger()
{
	delete pDlg;
}


BEGIN_MESSAGE_MAP(CDockablePaneLogger, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()  
END_MESSAGE_MAP()

void CDockablePaneLogger::OnPaint()
{
	CPaintDC dc(this);   

	CRect rect;
	this->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	dc.FillRect(rect, &CBrush(RGB(230, 230, 230))); 
}



int CDockablePaneLogger::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;  
	CRect rect;
	this->GetWindowRect(&rect);  ;                   

	pDlg = new CDialogDockLogger();
	pDlg->Create(IDD_DIALOG_DOCK_LOGGER, this);
	pDlg->InvalidateRect(NULL, TRUE);
	pDlg->ShowWindow(SW_SHOW); 
	return 0;
}





void CDockablePaneLogger::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);  
	CRect rect;
	this->GetWindowRect(rect);
	pDlg->MoveWindow(0, 0, cx, cy);
	adjustLayout();
}


void CDockablePaneLogger::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);  
	pDlg->SetFocus();
}

void CDockablePaneLogger::OnDestroy()
{
	CDockablePane::OnDestroy(); 
}


BOOL CDockablePaneLogger::CanBeClosed() const
{
	return FALSE;
}


BOOL CDockablePaneLogger::CanBeResized() const
{
	return TRUE;
}


BOOL CDockablePaneLogger::CanFloat() const
{
	return TRUE;
}


BOOL CDockablePaneLogger::CanAutoHide() const
{
	return TRUE;
}

void CDockablePaneLogger::OnFinalRelease()
{ 

	CDockablePane::OnFinalRelease(); 
}


BOOL CDockablePaneLogger::PreCreateWindow(CREATESTRUCT& cs)
{ 

	return CDockablePane::PreCreateWindow(cs);
}


void CDockablePaneLogger::OnContextMenu(CWnd* , CPoint )
{ 
	return;
}


void CDockablePaneLogger::UpdateList()
{
	pDlg->UpdateList();
}
 

void CDockablePaneLogger::UpdateListTest()
{
	pDlg->UpdateListTest();
}


void CDockablePaneLogger::AppendList(CString str)
{
	pDlg->AppendList(str);
}
CListCtrl* CDockablePaneLogger::GetLogListView()
{
	return &pDlg->m_ListLogger;
}            
void CDockablePaneLogger::adjustLayout()
{
	if (GetSafeHwnd() == NULL) return;     
}