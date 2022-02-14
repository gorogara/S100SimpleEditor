// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface           

#include "stdafx.h"
#include "MainFrm.h"
#include "GISViewerDoc.h"
#include "GISViewerView.h"
#include "GISViewer.h"
#include "DialogDockLayerManager.h"
#include "DialogExPickReport.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#ifdef _DEBUG

#define new DEBUG_NEW
#endif

#ifdef _KHOA_ENC_VIEWER
#include "DialogExCloseProgram.h"
#endif 

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_BUTTON_LAYERMANAGER, &CMainFrame::OnButtonLayermanager)
	ON_COMMAND(ID_BUTTON_ON, &CMainFrame::OnButtonOn)
	ON_COMMAND(ID_BUTTON_OFF, &CMainFrame::OnButtonOff)
	ON_COMMAND(ID_BUTTON_LAYERDELETE, &CMainFrame::OnButtonLayerdelete)
	ON_COMMAND(ID_BUTTON_WINDOW_LAYERMANAGER, &CMainFrame::OnButtonWindowLayermanager)
	ON_COMMAND(ID_BUTTON_WINDOW_PICK_REPORT, &CMainFrame::OnButtonWindowPickReport)
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONUP()
	ON_WM_SYSCOMMAND()

	ON_COMMAND(ID_BUTTON_LAYERINFO_OFF, &CMainFrame::OnButtonLayerinfoOff) 
	ON_COMMAND(ID_BUTTON_INFO, &CMainFrame::OnButtonInfo) 

	ON_COMMAND(ID_BUTTON_UP, &CMainFrame::OnButtonUp)
	ON_COMMAND(ID_BUTTON_DOWN, &CMainFrame::OnButtonDown)
END_MESSAGE_MAP() 

CMainFrame::CMainFrame()
{ 
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_AQUA); 
	m_pView = NULL;
	_putenv("BAG_HOME=..\\configdata");
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;  
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);

	if (theApp.IsEditingMode())
	{
		m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	}
	else
	{
		m_wndRibbonBar.LoadFromResource(IDR_RIBBON_VIEWER);
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1; 
	}

	EnableDocking(CBRS_ALIGN_ANY); 
	if (theApp.IsEditingMode())
	{
		if (!m_tbrFeatureEdit.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			!m_tbrFeatureEdit.LoadToolBar(IDR_TOOLBAR_FEATURE_EDIT))
		{
			TRACE0("도구 모음을 만들지 못했습니다.\n");
			return -1; 
		}

		m_tbrFeatureEdit.EnableDocking(CBRS_RIGHT);
		DockPane(&m_tbrFeatureEdit);
	}

#ifdef _S101_VIEWER
	m_tbrFeatureEdit.ShowPane(FALSE, FALSE, FALSE);
#endif    
	CDockingManager::SetDockingMode(DT_SMART); 
	EnableAutoHidePanes(CBRS_ALIGN_ANY);


	CreateDockablePane();
	EnableDockablePane();
	DockDockablePane();
	CloseAllDock();
	ResizeDockablePane();
	LayoutDockablePane(); 
	SeperateDockablePane();

	CDockablePane* pTabbedBar = NULL; 

	if (pTabbedBar)
	{
		pTabbedBar->SetControlBarStyle(0);
		pTabbedBar->SetControlBarStyle(AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE);
		pTabbedBar->ShowPane(TRUE, FALSE, TRUE);
	} 
	if (theApp.IsEditingMode())
	{
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)GetRibbonBar();
		ribbon->ShowCategory(3, FALSE);


		int cntCategory = ribbon->GetCategoryCount();


		CMFCRibbonCategory* category = (CMFCRibbonCategory*)ribbon->GetCategory(cntCategory - 1);
		CMFCRibbonLabel* label = (CMFCRibbonLabel*)category->GetPanel(0)->GetElement(0);
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;  

	cs.style &= ~(LONG)FWS_ADDTOTITLE;

	cs.lpszName = _T("KHOA S-100 Viewer");

	return TRUE;
} 

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif  

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnButtonLayermanager()
{     
	BOOL isVisible = theApp.m_pDockablePaneLayerManager.IsVisible();
	theApp.m_pDockablePaneLayerManager.ShowPane(!isVisible, FALSE, TRUE);

	if (!isVisible) {
		theApp.m_pDockablePaneLayerManager.ShowPane(!isVisible, FALSE, TRUE);
		theApp.m_pDockablePaneLayerManager.pDlg->UpdateList();
	}
}

void CMainFrame::OnButtonOn()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonOn();
}

void CMainFrame::OnButtonOff()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonOff();
}

void CMainFrame::OnButtonLayerdelete()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonDelete();
}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			m_pView->fePickGML = nullptr;
			m_pView->fePick = nullptr;
			m_pView->frPick = nullptr;
			m_pView->onPickArrow = false;
			m_pView->m_pSelectedLayer = nullptr;
			m_pView->Invalidate();
		}
		break;
	}
	return CFrameWndEx::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnButtonWindowLayermanager()
{
	theApp.m_DockablePanePickReport.ShowPane(FALSE, FALSE, TRUE);

	theApp.m_pDockablePaneLayerManager.ShowPane(!theApp.m_pDockablePaneLayerManager.IsVisible(), FALSE, TRUE);
}


void CMainFrame::OnButtonWindowPickReport()
{
	theApp.m_pDockablePaneLayerManager.ShowPane(FALSE, FALSE, TRUE);

	theApp.m_DockablePanePickReport.ShowPane(!theApp.m_DockablePanePickReport.IsVisible(), FALSE, TRUE);
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{   

	return CFrameWndEx::PreTranslateMessage(pMsg);
}


void CMainFrame::CloseAllDock()
{
	theApp.m_DockablePanePickReport.ShowPane(FALSE, FALSE, TRUE);
	theApp.m_pDockablePaneLayerManager.ShowPane(FALSE, FALSE, TRUE);
}


BOOL CMainFrame::CreateDockablePane()
{
	if (!theApp.m_DockablePanePickReport.Create(_T("Pick Report"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		AfxMessageBox(_T("Pick Report 창을 만들지 못했습니다."));
		return FALSE;
	}

	if (!theApp.m_pDockablePaneLayerManager.Create(_T("LayerManager"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Layer Manager 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	if (!theApp.m_DockablePaneRoutePlan.Create(_T("Route Plan"), this, CRect(0, 0, 100, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		AfxMessageBox(_T("Route Plan 창을 만들지 못했습니다."));
		return FALSE;
	}

	if (theApp.IsEditingMode())
	{
		if (!theApp.m_DockablePaneAttributeList.Create(_T("Attribute List"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
		{
			TRACE0("Attribute List 창을 만들지 못했습니다.\n");
			return FALSE;
		}
	}



	if (!theApp.m_DockablePaneEditWindow.Create(_T("Feature Information List"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Feature Information 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	if (!theApp.m_DockablePaneCurrentSelection.Create(_T("Current Selection"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Current Selection 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	if (!theApp.m_DockablePaneRelation.Create(_T("Relation"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Relation 창을 만들지 못했습니다.\n");
		return FALSE;
	}

	if (!theApp.m_DockablePaneLogger.Create(_T("Logger"), this, CRect(0, 0, 300, 800), TRUE, 1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Logger 창을 만들지 못했습니다.\n");
		return FALSE;
	}
	else
	{
		KRS_MSG_PROCESS::SetTargetWindowHandle(theApp.m_DockablePaneLogger.GetLogListView());
	}

	return TRUE;
}


void CMainFrame::EnableDockablePane()
{
	theApp.m_DockablePanePickReport.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_pDockablePaneLayerManager.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneAttributeList.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneEditWindow.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneRoutePlan.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneRelation.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneCurrentSelection.EnableDocking(CBRS_ALIGN_ANY);
	theApp.m_DockablePaneLogger.EnableDocking(CBRS_ALIGN_ANY);

}

void CMainFrame::DockDockablePane()
{
	DockPane(&theApp.m_pDockablePaneLayerManager);

	if (theApp.IsEditingMode())
	{
		DockPane(&theApp.m_DockablePaneAttributeList);

	}
	DockPane(&theApp.m_DockablePaneEditWindow);
	DockPane(&theApp.m_DockablePaneRoutePlan);
	DockPane(&theApp.m_DockablePaneRelation);
	DockPane(&theApp.m_DockablePaneCurrentSelection);
	DockPane(&theApp.m_DockablePaneLogger);
}



void CMainFrame::ResizeDockablePane()
{

}


void CMainFrame::LayoutDockablePane()
{
	CDockablePane* pTabbedBar = nullptr; 
	CDockablePane* pTabbedBarRight = nullptr;   

	if (pTabbedBar)
	{

		pTabbedBar->SetControlBarStyle(0);
		pTabbedBar->SetControlBarStyle(AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE); 
		pTabbedBar->ShowPane(FALSE, FALSE, FALSE);
		pTabbedBar->UndockPane();
		pTabbedBar->FloatPane(CRect(0, 0, 300, 400), DM_UNKNOWN, false);
		pTabbedBar->ShowPane(TRUE, FALSE, TRUE);

	}

} 
void CMainFrame::SeperateDockablePane()
{ 
	theApp.m_pDockablePaneLayerManager.ShowPane(TRUE, FALSE, TRUE); 
	theApp.m_DockablePanePickReport.ShowPane(FALSE, FALSE, FALSE); 
	theApp.m_DockablePaneEditWindow.DockToWindow(&theApp.m_pDockablePaneLayerManager, CBRS_ALIGN_BOTTOM); 
	theApp.m_DockablePaneRoutePlan.ShowPane(FALSE, FALSE, FALSE);

	if (theApp.IsEditingMode())
	{ 
		theApp.m_DockablePaneAttributeList.ShowPane(TRUE, FALSE, TRUE);

	} 
	theApp.m_DockablePaneCurrentSelection.ShowPane(TRUE, FALSE, TRUE); 
	theApp.m_DockablePaneRelation.DockToWindow(&theApp.m_DockablePaneAttributeList, CBRS_ALIGN_BOTTOM); 
	theApp.m_DockablePaneLogger.DockToWindow(&theApp.m_DockablePaneRelation, CBRS_ALIGN_BOTTOM);

}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{ 
	lpMMI->ptMinTrackSize.x = 640; 
	lpMMI->ptMinTrackSize.y = 480; 
	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}


void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	CFrameWndEx::OnLButtonUp(nFlags, point);
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	CFrameWndEx::OnSysCommand(nID, lParam);
}


void CMainFrame::OnButtonLayerinfoOff()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonLayerinfoOff();
}


void CMainFrame::OnButtonInfo()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonLayerinfoON();
}


void CMainFrame::OnButtonUp()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonUp();
}


void CMainFrame::OnButtonDown()
{
	theApp.m_pDockablePaneLayerManager.pDlg->OnButtonDown(); 
}
