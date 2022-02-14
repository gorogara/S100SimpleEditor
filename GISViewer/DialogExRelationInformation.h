#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <list>
#include <unordered_map>
#include <string>
class CGISViewerView;
class FeatureCatalogue;
class SimpleAttribute;
class ComplexAttribute;
class R_FeatureRecord;

class S101Cell; 

class CDialogExRelationInformation : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExRelationInformation)

public:
	CDialogExRelationInformation(CWnd* pParent = NULL); 
	virtual ~CDialogExRelationInformation(); 
	enum { IDD = IDD_DIALOG_RELATION_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogRelationInformation();
	afx_msg void OnEnChangeEditPos();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();


	CString text;
	
	
public:
	void SetAttribute(FeatureCatalogue* fc, std::unordered_map<std::wstring, SimpleAttribute*> attr_hash);
	CComboBox m_ComboAttribute;
	CComboBox m_ComboValue;

	CString m_attribteName;
	CString m_attribteValue;

	S101Cell *m_cell;
	std::list<R_FeatureRecord*> m_selectedFeatureList;
	FeatureCatalogue* m_fc;
	std::unordered_map<std::wstring, SimpleAttribute*> m_attr_hash;
	afx_msg void OnCbnSelchangeComboRelationInformationAttribute();
};


