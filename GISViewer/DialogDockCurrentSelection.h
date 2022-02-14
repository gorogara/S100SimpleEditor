#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "DialogExPickReport.h"

#include <map> 
#include <string>

class CurrentSelection;
class CGISViewerView;
class R_FeatureRecord;
class S101Cell;
class FeatureType;
class CGISLibraryApp; 
class CDialogDockCurrentSelection : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDockCurrentSelection)

public:
	CDialogDockCurrentSelection(CWnd* pParent = NULL); 
	virtual ~CDialogDockCurrentSelection();

	virtual BOOL OnInitDialog();

	void UpdateList();
	void SaveLayer(CString filename);
	void DeleteItem(CString id); 
	enum { IDD = IDD_DIALOG_DOCK_CURRENT_SELECTION };

	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	};

	BOOL m_bAscending;
	CGISViewerView* pView; 
	FeatureType* m_selectedFeatureType;
	InformationType* m_selectedInformationType = nullptr;
	CMenu m_ContextMenu; 
	int nSelectedItem = -1;
	CListCtrl m_ListCurrentSelection;
	int m_SelectedListCount;
	S101Cell* m_Cell;
	CGISLibraryApp* m_pGisLib; 
public: 
	void AdjustLayout(); 

	void OnMenuChangeAll();

	unsigned GetATIX(R_FeatureRecord* feature, unsigned natc, unsigned parentIndex);

	void OnMenuCopyFeature();
	void OnMenuRelation();
	void OnMenuRelationInformation(); 
	void OnMenuRemove();
	void OnMenuRemoveOthers();
	void OnMenuRemoveAll();
	void OnMenuCreateTextPlacement();
	void OnMenuDeleteFeature();

	void GetSelectionList(CStringArray* str);
	void UpdateListTest(CStringArray *csa, S101Cell *cell, CString isCtrlClicked);

	std::string* StringSplit(std::string strTarget, std::string strTok);
	void GetFeatureCatalogue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel(); 
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);  
	afx_msg void OnContextMenu(CWnd* , CPoint );
	afx_msg void OnHdnItemclickListCurrentSelection(NMHDR *pNMHDR, LRESULT *pResult);

	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};