#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "..\\RoutePlanner\\RoutePlanner.h"

class CGISViewerView;

class CRoutePlanListCtrl : public CListCtrl
{
public:
	CRoutePlanListCtrl() {};
	~CRoutePlanListCtrl() {};
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

class CDialogExRoutePlan : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRoutePlan)

public:
	CDialogExRoutePlan(CWnd* pParent = NULL); 
	virtual ~CDialogExRoutePlan();

	void UpdateRouteList();
	void UpdateWaypointList();   
	int  GetCurrentRouteIndex();
	int  GetCurrentWaypointIndex();
	void SelectRouteIndex(int _index);

	void SetDepartureTime(CString str);

	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	enum { IDD = IDD_DIALOGEXROUTEPLAN };

	std::vector<int> wpWarning;

public:
	int m_dataProcessType;
	CComboBox routeList;
	CRoutePlanListCtrl m_CListCtrlWaypoint;
	CGISViewerView* pView;
	RT::RoutePlanner* pRoutePlanner;
	int indexCurrentRClickedWP;

public:
	void SetRouteListActive(bool bActive);

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnCbnSelchangeComboRouteList();
	CStatic m_departureTime;
	afx_msg void OnNMClickListWaypoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListWaypoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListWaypoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuWpInsertPrev();
	afx_msg void OnMenuWpInsertAfter();
	afx_msg void OnNMCustomdrawListWaypoint(NMHDR *pNMHDR, LRESULT *pResult);
};
