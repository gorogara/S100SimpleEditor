#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"

#include <string>
#include <list>
#include <unordered_map>

class CGISViewerView;
class FeatureCatalogue;
class SimpleAttribute;
class ComplexAttribute; 

class CDialogExChangeAll : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExChangeAll)

public:
	CDialogExChangeAll(CWnd* pParent = NULL); 
	virtual ~CDialogExChangeAll(); 
	enum { IDD = IDD_DIALOG_CHANGEALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP();
public: 
	afx_msg void OnIddDialogChangeAll();
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

	FeatureCatalogue* m_fc;
	std::unordered_map<std::wstring, SimpleAttribute*> m_attr_hash;
	afx_msg void OnCbnSelchangeComboChangeAllAttribute();
};


