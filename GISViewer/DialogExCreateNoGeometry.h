#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <string>
#include <list>
#include <unordered_map>

class CGISViewerView;
class S101Cell;
class R_FeatureRecord;
class FeatureType; 

class CFeatureCodeString
{
public:
	int _id;
	std::wstring _name;

	R_FeatureRecord* _fr;
};

class CDialogExCreateNoGeometry : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCreateNoGeometry)

public:
	CDialogExCreateNoGeometry(CWnd* pParent = NULL); 
	virtual ~CDialogExCreateNoGeometry(); 
	enum { IDD = IDD_DIALOG_CREATE_NO_GEOMETRY};

	BOOL m_bAscending;

	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	};



public:
	void SetNoGeometryFeatureList(S101Cell* cell);

	std::unordered_map<std::wstring, FeatureType*> fnhash;
	std::vector<CFeatureCodeString> ngflist;
	CString SelectedFeatureName;
	S101Cell* m_cell;
	int Item = 0;


	void InitNonGeometryList();
	void AddNoGeometryFeatureItem(CFeatureCodeString* cf);
	int GetItemsId();
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogCreateNoGeometry();
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboRelationCreateList();

	CComboBox m_ComboName;
	CListCtrl m_ListNoGeometry;
	afx_msg void OnBnClickedButtonAddNoGeometryList();
	afx_msg void OnLvnItemchangedListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg void OnBnClickedDelete();
};


