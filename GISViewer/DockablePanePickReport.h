#pragma once

class CGISViewerView;
class CDialogExPickReport; 

class CDockablePanePickReport : public CDockablePane
{
	DECLARE_DYNAMIC(CDockablePanePickReport)

public:
	CDockablePanePickReport();
	virtual ~CDockablePanePickReport();

	CGISViewerView*      pView;
	CDialogExPickReport* pDlg;

	BOOL CanBeClosed() const;
	BOOL CanBeResized() const;
	BOOL CanFloat() const;
	BOOL CanAutoHide() const;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* , CPoint );
};


