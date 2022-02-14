// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface           

#pragma once   

class CGISViewerView;

class CMainFrame : public CFrameWndEx
{
	
protected: 
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame) 
public:
	CGISViewerView* m_pView;

	void CloseAllDock(); 
	BOOL CreateDockablePane(); 
	void EnableDockablePane(); 
	void DockDockablePane();  
	void ResizeDockablePane(); 
	void LayoutDockablePane(); 
	void SeperateDockablePane();

	void CreateEditingToolbar(); 
public: 
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); 
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CMFCRibbonBar* GetRibbonBar(){ return &m_wndRibbonBar; };
public: 
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

	CMFCToolBar m_tbrFeatureEdit; 
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonLayermanager();
	afx_msg void OnButtonOn();
	afx_msg void OnButtonOff();
	afx_msg void OnButtonLayerdelete();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonWindowLayermanager();
	afx_msg void OnButtonWindowPickReport();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	afx_msg void OnButtonLayerinfoOff();
	afx_msg void OnButtonInfo();

	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
};