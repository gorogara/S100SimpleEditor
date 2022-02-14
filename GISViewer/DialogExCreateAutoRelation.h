#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"
#include "DialogExCreateInformationFeature.h"

#include "GISLibrary\\GISLibrary.h"

#include <string>
#include <list>
#include <unordered_map>
#include <map>
class CGISViewerView;
class S101Cell;
class R_FeatureRecord;
class FeatureType; 

class CFeatureCodeStringAuto
{
public:
	int _id;
	std::wstring _name;

	R_FeatureRecord* _fr;
};

class CDialogExCreateAutoRelation : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCreateAutoRelation)

public:
	CDialogExCreateAutoRelation(CWnd* pParent = NULL); 
	virtual ~CDialogExCreateAutoRelation();
	enum { IDD = IDD_DIALOG_CREATE_AUTO_RELATION};

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
	std::list<CFeatureCodeStringAuto> ngflist;
	std::list<CInformationCodeString> infoflist;

	void InitNonGeometryList();
	void InitInformationFeatureList();
	
	void OnMenuAutoRelation(CStringArray *featureArr);
	void SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist);

	void OnMenuAutoRelationInformation(CStringArray *featureArr);
	void SetInformationList(S101Cell* cell, std::list<R_FeatureRecord*> flist);


	CString SelectedFeatureName;

	S101Cell* m_cell;

	CGISViewerView *pView;
	CGISLibraryApp *pGisLib;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogCreateAutoRelation();
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboRelationCreateList();
	
	CComboBox m_ComboName;
	CListCtrl m_ListNoGeometry;
	CListCtrl m_ListInformationFeature;
	string *StringSplitInformation(string strTarget, string strTok);
	
	afx_msg void OnBnClickedButtonAddNoGeometryList();
	afx_msg void OnLvnItemchangedListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg void OnLvnItemchangedListCreateAutoRelationList(NMHDR *pNMHDR, LRESULT *pResult);
};


