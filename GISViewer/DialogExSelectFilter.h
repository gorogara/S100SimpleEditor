#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <string>
#include <list>
#include <unordered_map>
#include <vector>

class CGISViewerView;
class FeatureCatalogue;
class SimpleAttribute;
class ComplexAttribute;
class S101Cell; 

class CDialogExSelectFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExSelectFilter)

public:
	CDialogExSelectFilter(CWnd* pParent = NULL); 
	virtual ~CDialogExSelectFilter(); 
	enum { IDD = IDD_DIALOG_SELECT_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnIddDialogSelectFilter();
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	void SetOperator();
	void SetFeatureData();
	void SetAttributeList();
	void SetFeatureList(CStringArray *csa);
	void SetFeatureList(std::vector<CString>* csa);
	virtual BOOL OnInitDialog();


	CString text;
	CGISViewerView *pView;


public:
	void SetAttribute(FeatureCatalogue* fc, std::unordered_map<std::wstring, SimpleAttribute*> attr_hash);
	CComboBox m_ComboAttribute;
	CComboBox m_ComboValue;
	CComboBox m_ComboFeature;
	CComboBox m_ComboOperator;

	CString m_attribute;
	CString m_value;
	CString m_feature;
	CString m_operator;
	CString m_attributeCamelCase;
	CString m_attributeCode;
	BOOL m_enumValueYn;
	S101Cell* m_cell;

	FeatureCatalogue* m_fc;
	std::unordered_map<std::wstring, SimpleAttribute*> m_attr_hash;
	afx_msg void OnCbnSelchangeComboSelectFilterAttribute();
	afx_msg void OnCbnSelchangeComboSelectFilterFeature();
	CStatic m_StaticAttributeCamelCase;
};


