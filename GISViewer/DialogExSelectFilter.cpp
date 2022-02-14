// CDialogExSelectFilter.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExSelectFilter.h"
#include "afxdialogex.h"
#include "FileLoad.h"
#include "GISViewer.h"
#include "GISViewerView.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include <iostream>
#include <locale.h>
#include <unordered_map>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExSelectFilter, CDialogEx)


CDialogExSelectFilter::CDialogExSelectFilter(CWnd* pParent )
: CDialogEx(CDialogExSelectFilter::IDD, pParent)
{
}

CDialogExSelectFilter::~CDialogExSelectFilter()
{
}

void CDialogExSelectFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_FILTER_ATTRIBUTE, m_ComboAttribute);
	DDX_Control(pDX, IDC_COMBO_SELECT_FILTER_VALUE_ENUM, m_ComboValue);
	DDX_Control(pDX, IDC_COMBO_SELECT_FILTER_FEATURE, m_ComboFeature);
	DDX_Control(pDX, IDC_COMBO_SELECT_FILTER_OPERATOR, m_ComboOperator);
	DDX_Control(pDX, IDC_STATIC_SELECT_FILTER_ATTRIBUTE, m_StaticAttributeCamelCase);
}


BEGIN_MESSAGE_MAP(CDialogExSelectFilter, CDialogEx)
	ON_COMMAND(IDD_DIALOG_SELECT_FILTER, &CDialogExSelectFilter::OnIddDialogSelectFilter)
	ON_BN_CLICKED(IDOK, &CDialogExSelectFilter::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExSelectFilter::OnBnClickedCancel)

	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_FILTER_ATTRIBUTE, &CDialogExSelectFilter::OnCbnSelchangeComboSelectFilterAttribute)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_FILTER_FEATURE, &CDialogExSelectFilter::OnCbnSelchangeComboSelectFilterFeature)
END_MESSAGE_MAP() 
void CDialogExSelectFilter::OnIddDialogSelectFilter()
{
}

#pragma warning(disable:4129)
void CDialogExSelectFilter::OnBnClickedOk()
{ 
	m_ComboFeature.GetWindowText(m_feature);
	m_ComboAttribute.GetWindowText(m_attribute);
	m_ComboValue.GetWindowText(m_value);
	m_ComboOperator.GetWindowText(m_operator);
	m_StaticAttributeCamelCase.GetWindowText(m_attributeCamelCase);

	CDialogEx::OnOK();
}


void CDialogExSelectFilter::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
}  
BOOL CDialogExSelectFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pView = theApp.pView;

	theApp.m_DockablePaneLogger.AppendList(_T("[Select filter] Dialog initializing"));
	SetFeatureData();
	SetOperator();

	theApp.m_DockablePaneLogger.AppendList(_T("[Select filter] Dialog initializing completed"));

	return true;

}

void CDialogExSelectFilter::SetOperator(){
	m_ComboOperator.AddString(L">");
	m_ComboOperator.AddString(L">=");
	m_ComboOperator.AddString(L"=");
	m_ComboOperator.AddString(L"<");
	m_ComboOperator.AddString(L"<=");
}

void CDialogExSelectFilter::SetFeatureData(){

	CStringArray featureArr; 


	NewFeatureManager *nfm = pView->m_pNewFeatureManager;
	S101Layer *l = (S101Layer *)m_cell->m_pLayer;

	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second;

	CString tmpFeatureType;
	vector<CString> vale; 
	for (auto ftfcit = fc->featureTypes.featureType.begin(); ftfcit != fc->featureTypes.featureType.end(); ftfcit++)
	{
		vale.push_back(ftfcit->first.c_str());
	}   
	SetFeatureList(&vale);
	

}


void CDialogExSelectFilter::SetAttributeList()
{ 
	m_ComboAttribute.ResetContent();

	CString tmpFeatureType;
	m_ComboFeature.GetLBText(m_ComboFeature.GetCurSel(), tmpFeatureType);
	
	NewFeatureManager *nfm = pView->m_pNewFeatureManager;
	S101Layer *l = (S101Layer *)m_cell->m_pLayer;

	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second; 
	auto ftfcit = fc->featureTypes.featureType.find(std::wstring(tmpFeatureType));
	FeatureType* ft = &ftfcit->second;

	for (auto itor = ft->attributeBinding.begin(); itor != ft->attributeBinding.end(); itor++)
	{
		AttributeBinding* ab = &(*itor);

		std::wstring name;

		std::list<XML_Attribute> attri= ab->attribute.Getattributes();
		for (auto i = attri.begin(); i != attri.end(); i++)
		{
			if (i->Getname().compare(L"ref") == 0)
			{
				name = i->Getvalue();
			}
		}

		auto atitor = fc->simpleAttributes.simpleAttribute.find(name.c_str());
		if (atitor != fc->simpleAttributes.simpleAttribute.end())
		{
			SimpleAttribute* sa = &atitor->second; 
			attr_map.insert({ sa->name, sa });
		}
	}
	SetAttribute(fc, attr_map);
}


void CDialogExSelectFilter::SetFeatureList(CStringArray *csa)
{
	int acount = csa->GetCount();
	int sfsf = csa->GetSize();


	for (int i = 0; i < csa->GetSize(); i++)
	{
		if (csa->GetAt(i) != L"")
		{
			m_ComboFeature.AddString(csa->GetAt(i));
		}
	}
	m_ComboFeature.SetCurSel(0);  
	SetAttributeList();
}

void CDialogExSelectFilter::SetFeatureList(vector<CString>* csa)
{
	int Count = csa->size();
	for (int i=0; i < Count; i++)
	{
		CString text = csa->at(i);
		m_ComboFeature.AddString(text);
	}
	m_ComboFeature.SetCurSel(0);

	SetAttributeList();
} 
void CDialogExSelectFilter::SetAttribute(FeatureCatalogue* fc, std::unordered_map<wstring, SimpleAttribute*> attr_hash)
{
	m_ComboAttribute.ResetContent(); 
	m_fc = fc;

	m_attr_hash.clear();
	for (auto it = attr_hash.begin(); it != attr_hash.end(); it++)
	{
		m_attr_hash.insert({ it->first, it->second });
	}


	for (auto it = m_attr_hash.begin(); it != m_attr_hash.end(); it++)
	{
		SimpleAttribute* sa = it->second;
		CString name = sa->name.c_str();
		m_ComboAttribute.AddString(name);
	}
	m_ComboAttribute.SetCurSel(0);

	OnCbnSelchangeComboSelectFilterAttribute();
}



void CDialogExSelectFilter::OnCbnSelchangeComboSelectFilterAttribute()
{ 
	m_ComboValue.ResetContent();

	CString str;
	m_ComboAttribute.GetLBText(m_ComboAttribute.GetCurSel(), str);

	auto it = m_attr_hash.find(str.GetBuffer());

	SimpleAttribute *sa = it->second;

	CString selAttribute;
	selAttribute = sa->code.GetValueString().c_str(); 
	auto itor = m_cell->m_dsgir.m_atcs->m_arrFindForCode.find(sa->code.GetValueString());
	
	if (itor != m_cell->m_dsgir.m_atcs->m_arrFindForCode.end())
	{
		CodeWithNumericCode* nc = itor->second;
		CString attrCode;
		attrCode.Format(_T("%d"), nc->m_nmcd);
		m_attributeCode = attrCode;
		SetDlgItemText(IDC_STATIC_SELECT_FILTER_ATTRIBUTE, L"Attribute code : " + selAttribute + L"(" + attrCode + L")");

	} 
	if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
	{
		m_ComboOperator.SetCurSel(2);
		m_ComboOperator.EnableWindow(FALSE);
		m_enumValueYn = true;
		for (auto itor = sa->listedValues.begin(); itor != sa->listedValues.end(); itor++)
		{
			ListedValues* lvs = &(*itor);

			for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++){
				ListedValue* lv = &(lvitor->second);
				CString valueCode;
				valueCode.Format(_T("%s___%d"), lv->label.c_str(), lvitor->first);
				m_ComboValue.AddString(valueCode);
			}
		}
	}
	else {
		m_ComboOperator.EnableWindow(TRUE);
		m_enumValueYn = false;
	}
}


void CDialogExSelectFilter::OnCbnSelchangeComboSelectFilterFeature()
{  
	SetAttributeList();
}


