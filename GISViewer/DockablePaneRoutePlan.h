#pragma once

class CDialogExRoutePlan;

class CDockablePaneRoutePlan : public CDockablePane
{
	DECLARE_DYNAMIC(CDockablePaneRoutePlan)

public:
	CDockablePaneRoutePlan();
	virtual ~CDockablePaneRoutePlan();

public:

protected:
public:
	CDialogExRoutePlan* pDlg;

public:
	void SetProcessType(int type);

public:
	BOOL CanBeClosed() const;
	BOOL CanBeResized() const;
	BOOL CanFloat() const;
	BOOL CanAutoHide() const;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* , CPoint );
};