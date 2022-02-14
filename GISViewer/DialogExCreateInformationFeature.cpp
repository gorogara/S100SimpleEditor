// CDialogExCreateInformationFeature.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExCreateInformationFeature.h"
#include "afxdialogex.h"
#include "GISViewer.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include <iostream>
#include <locale.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExCreateInformationFeature, CDialogEx)


CDialogExCreateInformationFeature::CDialogExCreateInformationFeature(CWnd* pParent )
	: CDialogEx(CDialogExCreateInformationFeature::IDD, pParent)
{


}

CDialogExCreateInformationFeature::~CDialogExCreateInformationFeature()
{
}

void CDialogExCreateInformationFeature::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CREATE_INFORMATION_FEATURE, m_ComboName);
	DDX_Control(pDX, IDC_LIST_CREATE_INFORMATION_FEATURE, m_ListInformationFeature);
}


BEGIN_MESSAGE_MAP(CDialogExCreateInformationFeature, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExCreateInformationFeature::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExCreateInformationFeature::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_CREATE_INFORMATION_FEATURE, &CDialogExCreateInformationFeature::OnCbnSelchangeComboCreateInformationFeatureList)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_INFORMATION_FEATURE, &CDialogExCreateInformationFeature::OnBnClickedButtonCreateInformationFeatureList)

	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDialogExCreateInformationFeature::OnHdnItemclickListInformationFeatureList)
	ON_BN_CLICKED(IDDELETE, &CDialogExCreateInformationFeature::OnBnClickedDelete)
END_MESSAGE_MAP()



#pragma warning(disable:4129)
void CDialogExCreateInformationFeature::OnBnClickedOk()
{ 
	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] process start")); 

	m_cell->m_infMap.RemoveAll();
	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CInformationCodeString* cs = &(*fni);
		R_InformationRecord* ifr = cs->_ir;
		__int64 keyN = ((__int64)ifr->m_irid.m_name.RCNM) << 32 | ((__int64)ifr->m_irid.m_name.RCID);
		m_cell->m_infMap.SetAt(keyN, ifr);
	}

	CString isCtrlClicked = L"1";
	CStringArray csa;
	csa.SetSize(10);

	POSITION pos = m_ListInformationFeature.GetFirstSelectedItemPosition();
	int idx = 0;

	if (pos != nullptr) 
	{
		while (pos) 
		{ 
			CString csFrid;
			CString csFeatureName;

			idx = m_ListInformationFeature.GetNextSelectedItem(pos);

			csFrid.Format(m_ListInformationFeature.GetItemText(idx, 0)); 
			csFeatureName.Format(m_ListInformationFeature.GetItemText(idx, 1)); 

			csa.Add(isCtrlClicked + _T("|||") + csFrid + _T("|||") + csFrid + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + csFeatureName + _T("|||") + L"0" + _T("|||") + L"Information");

			theApp.m_DockablePaneCurrentSelection.UpdateListTest(&csa, m_cell, isCtrlClicked);
		}
	}
	else 
	{ 
		for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
		{
			CStringArray csa;
			csa.SetSize(10);

			CString csFrid;
			CString csFeatureName;
			csFrid.Format(m_ListInformationFeature.GetItemText(idx, 0)); 
			csFeatureName.Format(m_ListInformationFeature.GetItemText(idx, 1)); 

			csa.Add(isCtrlClicked + _T("|||") + csFrid + _T("|||") + csFrid + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + csFeatureName + _T("|||") + L"0" + _T("|||") + L"Information");
			theApp.m_DockablePaneCurrentSelection.UpdateListTest(&csa, m_cell, isCtrlClicked);
			idx++;
		}

		
	}
	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	theApp.m_DockablePaneAttributeList.RemoveAll(); 

	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] process end"));
	CDialogEx::OnOK();
}

void CDialogExCreateInformationFeature::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
}

void CDialogExCreateInformationFeature::OnBnClickedDelete()
{
	POSITION pos = m_ListInformationFeature.GetFirstSelectedItemPosition();
	int idx = 0;
	while (pos)
	{                                                                          
		idx = m_ListInformationFeature.GetNextSelectedItem(pos);
	}

	CString csFrid;
	csFrid.Format(m_ListInformationFeature.GetItemText(idx, 0)); 

	m_ListInformationFeature.DeleteItem(idx);
	ngflist.erase(ngflist.begin() + idx);
	theApp.m_DockablePaneCurrentSelection.DeleteItem(csFrid);

}

void CDialogExCreateInformationFeature::InitInformationFeatureList()
{ 
	m_ListInformationFeature.DeleteAllItems();
	m_ComboName.ResetContent();

	for (auto fni = fnhash.begin(); fni != fnhash.end(); fni++)
	{
		m_ComboName.AddString(fni->first.c_str());
	}

	int iItem = 0;

	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CInformationCodeString* cs = &(*fni);
		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = iItem;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(cs->_name.c_str());
		lvi.lParam = (LPARAM)cs->_ir;
		BOOL ret = 0;

		CString id;
		id.Format(L"%d", cs->_id);
		int indexItem = m_ListInformationFeature.InsertItem(&lvi); 
		Catalog *catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
		FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;
		CString featureItemDesc;

		for (auto itor = fc->informationTypes.informationType.begin();
			itor != fc->informationTypes.informationType.end();
			itor++)
		{

			CString tmp;
			CString tmp1;

			tmp = itor->first.c_str();
			tmp1 = cs->_name.c_str();

			if (tmp == tmp1)
			{
				featureItemDesc = itor->second.definition.c_str();
			}

		}

		m_ListInformationFeature.SetItemText(indexItem, 0, id);
		m_ListInformationFeature.SetItemText(indexItem, 1, cs->_name.c_str());
		m_ListInformationFeature.SetItemText(indexItem, 2, featureItemDesc);

		iItem++;
	}
} 
BOOL CDialogExCreateInformationFeature::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	m_ListInformationFeature.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListInformationFeature.GetWindowRect(listRect);

	m_ListInformationFeature.InsertColumn(0, _T("ID"), LVCFMT_CENTER, (int)(listRect.Width()*0.10));
	m_ListInformationFeature.InsertColumn(1, _T("Feature Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.20));
	m_ListInformationFeature.InsertColumn(2, _T("Description"), LVCFMT_LEFT, (int)(listRect.Width()*0.70));

	InitInformationFeatureList();

	return true;
}

void CDialogExCreateInformationFeature::OnCbnSelchangeComboCreateInformationFeatureList()
{ 
} 
void CDialogExCreateInformationFeature::SetInformationFeatureList(S101Cell* cell)
{
	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] Create information feature list initializing"));
	ngflist.clear();
	fnhash.clear();

	Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;
	m_cell = cell;

	for (auto itor = fc->informationTypes.informationType.begin();
		itor != fc->informationTypes.informationType.end();
		itor++)
	{
		InformationType* it = &itor->second;
		fnhash.insert(std::unordered_map<std::wstring, InformationType*>::value_type(it->code.GetValueString(), it));
	} 

	POSITION pos = cell->m_infMap.GetStartPosition();

	while (pos != NULL)
	{
		__int64 key = 0;
		R_InformationRecord* ir = NULL;
		cell->m_infMap.GetNextAssoc(pos, key, ir);

		int code = ir->m_irid.m_nitc;

		auto itor = cell->m_dsgir.m_itcs->m_arr.find(code);
		CodeWithNumericCode* nc = itor->second;

		std::wstring codeStr = nc->m_code;
		InformationType *objIT = &catalog->m_pCatalogueList.begin()->second->informationTypes.informationType.find(codeStr)->second; 
		CInformationCodeString cs;
		cs._name = objIT->code.GetValueString();
		cs._id = ir->m_irid.m_name.RCID;
		cs._ir = ir;
		ngflist.push_back(cs);
	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] Create information feature list initializing complete"));

} 
void CDialogExCreateInformationFeature::OnBnClickedButtonCreateInformationFeatureList()
{
	CString str;
	m_ComboName.GetWindowText(str);

	if (str.GetLength() == 0)
	{
		return;
	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] Add information feature process start"));

	auto it = fnhash.find(wstring(str));
	InformationType* ifot = it->second;

	if(m_cell->m_dsgir.m_itcs == NULL)
		m_cell->m_dsgir.m_itcs = new F_CodeWithNumericCode();
	auto it2 = m_cell->m_dsgir.m_itcs->m_arrFindForCode.find(ifot->code.GetValueString()); 
	if (m_cell->m_dsgir.m_itcs->m_arrFindForCode.find(ifot->code.GetValueString()) == m_cell->m_dsgir.m_itcs->m_arrFindForCode.end())
	{
		for (unsigned i = 1; i < 1048575; i++)
		{
			auto fitor = m_cell->m_dsgir.m_itcs->m_arr.find(i);
			if (fitor == m_cell->m_dsgir.m_itcs->m_arr.end())
			{

				CodeWithNumericCode *cnc = new CodeWithNumericCode();
				cnc->m_nmcd = i;
				cnc->m_code = ifot->code.GetValueString().c_str();
				m_cell->m_dsgir.m_itcs->m_arrFindForCode.insert(std::unordered_map<std::wstring, CodeWithNumericCode*>::value_type(ifot->code.GetValueString(), cnc));
				m_cell->m_dsgir.m_itcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));

				it2 = m_cell->m_dsgir.m_itcs->m_arrFindForCode.find(ifot->code.GetValueString());

				break;
			}
		}
	}

	CodeWithNumericCode* nc = it2->second;

	R_InformationRecord* ifr = new R_InformationRecord();
	ifr->m_irid.m_name.RCNM = 150;
	ifr->m_irid.m_name.RCID = GetItemsId();
	ifr->m_irid.m_nitc = nc->m_nmcd;
	ifr->m_irid.m_ruin = 0;
	ifr->m_irid.m_rver = 1;

	__int64 keyN = ((__int64)ifr->m_irid.m_name.RCNM) << 32 | ((__int64)ifr->m_irid.m_name.RCID);

	std::wstring codeStr = nc->m_code;
	InformationType *objIT = &((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second->informationTypes.informationType.find(codeStr)->second; 
	CInformationCodeString cs;
	cs._name = objIT->code.GetValueString();

	cs._id = ifr->m_irid.m_name.RCID;
	cs._ir = ifr;

	AddInformationFeatureItem(&cs);
	theApp.m_DockablePaneLogger.AppendList(_T("[Create information feature] Add information process end"));
}
int CDialogExCreateInformationFeature::GetItemsId()
{
	vector<int> idlist;

	if (ngflist.size() == 0)
	{
		return 1;
	}

	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CInformationCodeString* cs = &(*fni);
		idlist.push_back(cs->_id);
	}

	sort(idlist.begin(), idlist.end());//정렬합니다. 
	for (size_t num = 0; num < idlist.size(); num++)
	{
		if (idlist[num]==(num+1))
		{
			continue;
		}
		else if (idlist[num]< (num + 1))
		{ 
			return idlist[num];
		}
		else if (idlist[num]>(num + 1))
		{
			return num + 1;
		}
	}
	return idlist.size()+1;
} 
void CDialogExCreateInformationFeature::AddInformationFeatureItem(CInformationCodeString* cs)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = Item; 
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(cs->_name.c_str());
	lvi.lParam = (LPARAM)cs->_ir;
	BOOL ret = 0;

	CString id;
	id.Format(L"%d", cs->_id);
	int indexItem = m_ListInformationFeature.InsertItem(&lvi); 
	Catalog *catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;
	CString featureItemDesc;

	for (auto itor = fc->informationTypes.informationType.begin();
		itor != fc->informationTypes.informationType.end();
		itor++)
	{

		CString tmp;
		CString tmp1;

		tmp = itor->first.c_str();
		tmp1 = cs->_name.c_str();

		if (tmp == tmp1)
		{
			featureItemDesc = itor->second.definition.c_str();
		}

	}

	m_ListInformationFeature.SetItemText(indexItem, 0, id);
	m_ListInformationFeature.SetItemText(indexItem, 1, cs->_name.c_str());
	m_ListInformationFeature.SetItemText(indexItem, 2, featureItemDesc);
	ngflist.push_back(*cs);
	Item++;
}


void CDialogExCreateInformationFeature::OnHdnItemclickListInformationFeatureList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	int nColumn = phdr->iItem;
	for (int i = 0; i < (m_ListInformationFeature.GetItemCount()); i++)
	{
		m_ListInformationFeature.SetItemData(i, i);
	} 
	m_bAscending = !m_bAscending; 
	SORTPARAM sortparams;
	sortparams.pList = &m_ListInformationFeature;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending ? true : false; 
	m_ListInformationFeature.SortItems(&CompareItem, (LPARAM)&sortparams);

	*pResult = 0;
}

int CALLBACK CDialogExCreateInformationFeature::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pList = ((SORTPARAM *)lParamSort)->pList;
	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
	int irow1 = pList->FindItem(&info1, -1);
	int irow2 = pList->FindItem(&info2, -1);

	CString strItem1 = pList->GetItemText(irow1, iSortColumn);
	CString strItem2 = pList->GetItemText(irow2, iSortColumn);

	return bSortDirect ? strItem1.Compare(strItem2) : -strItem1.Compare(strItem2);

}
