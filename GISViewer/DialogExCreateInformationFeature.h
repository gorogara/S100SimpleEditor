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
class R_InformationRecord;
class InformationType; 


class CInformationCodeString
{
public:
	int _id;
	std::wstring _name;

	R_InformationRecord* _ir;
};

class CDialogExCreateInformationFeature : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCreateInformationFeature)

public:
	CDialogExCreateInformationFeature(CWnd* pParent = NULL); 
	virtual ~CDialogExCreateInformationFeature(); 
	enum { IDD = IDD_DIALOG_CREATE_INFORMATION_TYPE_FEATURE};

	BOOL m_bAscending;

	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	};



public:

	std::unordered_map<std::wstring, InformationType*> fnhash; 
	std::vector<CInformationCodeString> ngflist; 
	CString SelectedFeatureName;
	S101Cell* m_cell;
	int Item = 0;
	

	void InitInformationFeatureList();
	void AddInformationFeatureItem(CInformationCodeString* cs);
	void SetInformationFeatureList(S101Cell* cell);
	int GetItemsId();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnCbnSelchangeComboCreateInformationFeatureList();

	CComboBox m_ComboName;
	CListCtrl m_ListInformationFeature;
	afx_msg void OnBnClickedButtonCreateInformationFeatureList();
	afx_msg void OnLvnItemchangedListInformationFeatureList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListInformationFeatureList(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	

};


