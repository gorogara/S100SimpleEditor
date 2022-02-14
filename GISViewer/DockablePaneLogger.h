#pragma once
#define MYCOMBO1_ID 1000
class CGISViewerView;
class CDialogDockLogger;

class CDockablePaneLogger : public CDockablePane
{
	DECLARE_DYNAMIC(CDockablePaneLogger)
	 
public:

	void UpdateList();
	void UpdateListTest();
	void AppendList(CString str);

	CGISViewerView			*pView;
	CDialogDockLogger		*pDlg;

	BOOL CanBeClosed() const;
	BOOL CanBeResized() const;
	BOOL CanFloat() const;
	BOOL CanAutoHide() const;

	CDockablePaneLogger();
	virtual ~CDockablePaneLogger(); 

	void SaveLayer(CString filename);
	CListCtrl* GetLogListView();

protected:
	DECLARE_MESSAGE_MAP()
    void adjustLayout();  

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	virtual void OnFinalRelease();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnContextMenu(CWnd* , CPoint ); 

};
