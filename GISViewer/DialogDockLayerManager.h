#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include <vector>

class LayerManager;
class CGISViewerView;
class R_FeatureRecord;
class S101Cell;
class S413Cell;

class CDialogDockLayerManager : public CDialog
{
	DECLARE_DYNAMIC(CDialogDockLayerManager)

public:
	CDialogDockLayerManager(CWnd* pParent = NULL); 
	virtual ~CDialogDockLayerManager(); 
	enum { IDD = IDD_DIALOG_DOCK_LAYERMANEGER };

	CMFCPropertyGridCtrl m_wndPropList;
	CFont m_fntPropList;

	int nSelectedItem = -1;
	CDWordArray m_anDragIndexes; 
	std::vector<CString> SelectdItem;

	CListCtrl m_ListLayer;
	SpatialObject* curCell = nullptr;
	bool isclickLayerManager = false; 

public:
	void SetVSDotNetLook(BOOL bSet);
	void AdjustLayout();
	void InitPropList();
	void RemoveAllPropList();
	void FillPropList(S101Cell*);
	void FillPropList(S413Cell*);
	void SetPropListFont();
	void SetSelectedInformation();
	void AdjustToolbarMenu();
	void ShowSuBItemDialog();
	void OnButtonDeleteAllLayer();
	void UpdateList();
	void SaveLayerTextPlacement(CString filename, CString extend);
	void SaveLayer(CString filename, CString extend);
	
	int GetSelectedIndexNum(); 
	int GetSafeSelectedIndex();

	int GetLayerCount();
	
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnNMClickListLm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonOn();
	afx_msg void OnButtonOff();
	afx_msg void OnNMDblclkListLm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnButtonLayerinfoON();
	afx_msg void OnButtonLayerinfoOff();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnNMRClickListLm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* , CPoint );
	afx_msg void OnLvnKeydownListLm(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);
};
