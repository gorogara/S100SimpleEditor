#pragma once

#include <vector>
#include "afxwin.h"

class CGISViewerView;
class ENC_Feature;
class R_FeatureRecord;
class ENCCell;
class S101Cell;
class Catalog;
class FeatureCatalogue; 
class ENCItem
{
public:
	ENCItem()
	{
		type = 0;
	}
	int type;
};

class ObjectItem : public ENCItem
{
public:
	ObjectItem()
	{
		type = 0;
		_cell = NULL;
	}
	CString _description;
	CString _acronym;
	CString _cellName;
	ENC_Feature* _feature;
	ENCCell* _cell;
};

class FeatureItem : public ENCItem
{
public:
	FeatureItem()
	{
		type = 1;
		_cell = NULL;
	}
	CString _description;
	CString _acronym;
	CString _cellName;
	R_FeatureRecord* _feature;
	S101Cell* _cell;
};              

class CDialogExPickReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExPickReport)

public:
	CDialogExPickReport(CWnd* pParent = NULL); 
	virtual ~CDialogExPickReport();

	void SetView(CGISViewerView* v);

	void InitObjectList(); 
	void AddObject(CString _description, CString _acronym, CString _cellName, ENC_Feature* _feature, ENCCell* cell);
	void AddObject(CString _description, CString _acronym, CString _cellName, R_FeatureRecord* _feature, S101Cell* cell);
	void SetObjectListCtrl(Catalog *catalog);
	void SortObjectList();

	void ChangeObject(CString _description, CString _acronym, CString _cellName, R_FeatureRecord* _feature, S101Cell* cell, int index = -1);  
	enum { IDD = IDD_DIALOG_PICK_REPORT };

private:
	CGISViewerView*           m_pView;
public:
	std::vector<ENCItem*> m_allFeatureItems;
	std::vector<ENCItem*> m_activeFeatureItems; 

	Catalog *m_catalog;
	std::wstring m_searchCode;

	CButton m_pointSelect;
	CButton m_curveSelect;
	CButton m_surfaceSelect;

	CEdit m_searchFeatureName;
	CButton m_searchButton;
	CButton m_btnFilter;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckPicPoint();
	afx_msg void OnBnClickedCheckPicCurve();
	afx_msg void OnBnClickedCheckPicSurface();
	afx_msg void OnBnClickedBtnPicSearch();
	afx_msg void OnBnClickedBtnPicFilter();
};
