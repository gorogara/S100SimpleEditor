// CDialogExChangeAll.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExChangeAll.h"
#include "afxdialogex.h"
#include "FileLoad.h"
#include "GISViewer.h"

#include "..\\FeatureCatalog\\SimpleAttribute.h"

#include <iostream>
#include <locale.h>
#include <unordered_map>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExChangeAll, CDialogEx)


CDialogExChangeAll::CDialogExChangeAll(CWnd* pParent )
	: CDialogEx(CDialogExChangeAll::IDD, pParent)
{
}

CDialogExChangeAll::~CDialogExChangeAll() 
{
}

void CDialogExChangeAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANGE_ALL_ATTRIBUTE, m_ComboAttribute);
	DDX_Control(pDX, IDC_COMBO_CHANGE_ALL_VALUE_ENUM, m_ComboValue);
}


BEGIN_MESSAGE_MAP(CDialogExChangeAll, CDialogEx)
	ON_COMMAND(IDD_DIALOG_CHANGEALL, &CDialogExChangeAll::OnIddDialogChangeAll)
	ON_BN_CLICKED(IDOK, &CDialogExChangeAll::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExChangeAll::OnBnClickedCancel)

	ON_CBN_SELCHANGE(IDC_COMBO_CHANGE_ALL_ATTRIBUTE, &CDialogExChangeAll::OnCbnSelchangeComboChangeAllAttribute)
END_MESSAGE_MAP() 
void CDialogExChangeAll::OnIddDialogChangeAll()
{
}

#pragma warning(disable:4129)
void CDialogExChangeAll::OnBnClickedOk()
{ 
	m_ComboAttribute.GetWindowText(m_attribteName);
	m_ComboValue.GetWindowText(m_attribteValue);

	CDialogEx::OnOK();
}


void CDialogExChangeAll::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL CDialogExChangeAll::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] Dialog initializing"));

	CComboBox* cb = (CComboBox*)GetDlgItem(IDC_COMBO_CHANGE_ALL_ATTRIBUTE);

	for (auto it = m_attr_hash.begin(); it != m_attr_hash.end(); it++)
	{
		SimpleAttribute* sa = it->second;
		cb->AddString(sa->name.c_str());
	}
	cb->SetCurSel(0);

	OnCbnSelchangeComboChangeAllAttribute();
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] Dialog initializing completed"));

	return true;
	
}





void CDialogExChangeAll::SetAttribute(FeatureCatalogue* fc, std::unordered_map<wstring, SimpleAttribute*> attr_hash)
{
	m_fc = fc;

	m_attr_hash.clear();
	for (auto it = attr_hash.begin(); it != attr_hash.end(); it++)
	{
		m_attr_hash.insert(std::unordered_map<wstring, SimpleAttribute*>::value_type(it->first, it->second));
	}
}

void CDialogExChangeAll::OnCbnSelchangeComboChangeAllAttribute()
{ 
	m_ComboValue.ResetContent();

	CString str;
	m_ComboAttribute.GetLBText(m_ComboAttribute.GetCurSel(), str);

	auto it = m_attr_hash.find(str.GetBuffer());

	SimpleAttribute *sa = it->second; 
	if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
	{
		for (auto itor = sa->listedValues.begin(); itor != sa->listedValues.end(); itor++)
		{
			ListedValues* lvs = &(*itor);

			for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++){
				ListedValue* lv = &(lvitor->second);
				m_ComboValue.AddString(lv->label.c_str());
			}
		}
	}
}
