#pragma once

#include "Resource.h"
#include <unordered_map>
#include "afxwin.h"
#include "afxcmn.h" 

class Layer;
class FeatureType;

class CountedFeatureType{
	
public:
	CountedFeatureType(FeatureType* ft)
	{
		m_count = 1;
		m_pFT = ft;
	};

	int m_count;
	FeatureType* m_pFT;
};

class CDialogCellFeatureList : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCellFeatureList)

public:
	CDialogCellFeatureList(CWnd* pParent = NULL); 
	virtual ~CDialogCellFeatureList(); 
	enum { IDD = IDD_DIALOG_LIST_FEATURE };


private: 
	std::unordered_map<std::wstring, CountedFeatureType> hash_cft;


	CListCtrl m_listFeatureTypes;
	CButton m_btOK;

public:
	void SetLayer(Layer* layer);
	void SetList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedListFeatureTypes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnFeatureListReport();
	CButton m_btnReport;
};
