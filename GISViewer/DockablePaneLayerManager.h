#pragma once 

class CGISViewerView;
class CDialogDockLayerManager; 

class CDockablePaneLayerManager : public CDockablePane
{
	DECLARE_DYNAMIC(CDockablePaneLayerManager)

public:
	CDockablePaneLayerManager();
	virtual ~CDockablePaneLayerManager();

	void UpdateList();

	CGISViewerView			*pView;
	CDialogDockLayerManager *pDlg;

	BOOL CanBeClosed() const;
	BOOL CanBeResized() const;
	BOOL CanFloat() const;
	BOOL CanAutoHide() const;

	void SaveLayer(CString filename, CString extend);
	void SaveLayerTextPlacement(CString filename, CString extend);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	virtual void OnFinalRelease();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnContextMenu(CWnd* , CPoint );
	afx_msg void OnEdit32913();
};