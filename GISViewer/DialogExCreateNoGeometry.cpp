// CDialogExCreateNoGeometry.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExCreateNoGeometry.h"
#include "afxdialogex.h"
#include "GISViewer.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\CodeWithNumericCode.h"


#include <iostream>
#include <locale.h>
#include <unordered_map>
#include <algorithm>
using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExCreateNoGeometry, CDialogEx)

CDialogExCreateNoGeometry::CDialogExCreateNoGeometry(CWnd* pParent )
	: CDialogEx(CDialogExCreateNoGeometry::IDD, pParent)
{
}

CDialogExCreateNoGeometry::~CDialogExCreateNoGeometry()
{
}

void CDialogExCreateNoGeometry::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RELATION_CREATE_LIST, m_ComboName);
	DDX_Control(pDX, IDC_LIST_NO_GEOMETRY_LIST, m_ListNoGeometry);
}

BEGIN_MESSAGE_MAP(CDialogExCreateNoGeometry, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExCreateNoGeometry::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExCreateNoGeometry::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_RELATION_CREATE_LIST, &CDialogExCreateNoGeometry::OnCbnSelchangeComboRelationCreateList)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NO_GEOMETRY_LIST, &CDialogExCreateNoGeometry::OnBnClickedButtonAddNoGeometryList)
	
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDialogExCreateNoGeometry::OnHdnItemclickListNoGeometryList)
	ON_BN_CLICKED(IDDELETE, &CDialogExCreateNoGeometry::OnBnClickedDelete)
END_MESSAGE_MAP() 
void CDialogExCreateNoGeometry::OnIddDialogCreateNoGeometry()
{


}

#pragma warning(disable:4129)
void CDialogExCreateNoGeometry::OnBnClickedOk()
{ 
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] process start"));

	POSITION index = m_cell->m_feaMap.GetStartPosition();
	long long key;
	R_FeatureRecord* value;
	while (index != nullptr)
	{
		 m_cell->m_feaMap.GetNextAssoc(index, key, value);
		 if (value->m_spas.size() == 0)
		 {
			 m_cell->m_feaMap.RemoveKey(key);
		 }
	}



	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CFeatureCodeString* cs = &(*fni);
		R_FeatureRecord* ifr = cs->_fr;
		__int64 keyN = ((__int64)ifr->m_frid.m_name.RCNM) << 32 | ((__int64)ifr->m_frid.m_name.RCID);
		m_cell->m_feaMap.SetAt(keyN, ifr);
	}


	m_ComboName.GetWindowText(SelectedFeatureName);

	CString isCtrlClicked = L"1";
	CStringArray csa;
	csa.SetSize(10);

	POSITION pos = m_ListNoGeometry.GetFirstSelectedItemPosition();
	int idx = 0;

	if (pos !=nullptr)
	{
		while (pos)
		{
			CString csFrid;
			CString csFeatureName;
			idx = m_ListNoGeometry.GetNextSelectedItem(pos);
			csFrid.Format(m_ListNoGeometry.GetItemText(idx, 0)); 
			csFeatureName.Format(m_ListNoGeometry.GetItemText(idx, 1)); 

			csa.Add(isCtrlClicked + _T("|||") + csFrid + _T("|||") + csFrid + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + L"999" + _T("|||") + csFeatureName + _T("|||") + L"0" + _T("|||") + L"Feature"); 
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
			csFrid.Format(m_ListNoGeometry.GetItemText(idx, 0)); 
			csFeatureName.Format(m_ListNoGeometry.GetItemText(idx, 1)); 

			csa.Add(isCtrlClicked + _T("|||") + csFrid + _T("|||") + csFrid + _T("|||") + L"-" + _T("|||") + L"-" + _T("|||") + L"999" + _T("|||") + csFeatureName + _T("|||") + L"0" + _T("|||") + L"Feature");
			theApp.m_DockablePaneCurrentSelection.UpdateListTest(&csa, m_cell, isCtrlClicked);
			idx++;
		}
	}
	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	theApp.m_DockablePaneAttributeList.RemoveAll(); 

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] process end"));
	CDialogEx::OnOK();
}

void CDialogExCreateNoGeometry::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
}

void CDialogExCreateNoGeometry::InitNonGeometryList()
{ 
	m_ListNoGeometry.DeleteAllItems();
	m_ComboName.ResetContent();



	for (auto fni = fnhash.begin(); fni != fnhash.end(); fni++)
	{
		m_ComboName.AddString(fni->first.c_str());
	}

	
	int iItem = 0;
	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CFeatureCodeString* cs = &(*fni);
		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = iItem;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(cs->_name.c_str());
		lvi.lParam = (LPARAM)cs->_fr;
		BOOL ret = 0;

		CString id;
		id.Format(L"%d", cs->_id);
		int indexItem = m_ListNoGeometry.InsertItem(&lvi);

		m_ListNoGeometry.SetItemText(indexItem, 0, id);
		m_ListNoGeometry.SetItemText(indexItem, 1, cs->_name.c_str());  
		iItem++;
	}
} 
BOOL CDialogExCreateNoGeometry::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	m_ListNoGeometry.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListNoGeometry.GetWindowRect(listRect);

	m_ListNoGeometry.InsertColumn(0, _T("ID"), LVCFMT_CENTER, (int)(listRect.Width()*0.30));
	m_ListNoGeometry.InsertColumn(1, _T("Feature Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.70));

	InitNonGeometryList();


	return true;
}

void CDialogExCreateNoGeometry::OnCbnSelchangeComboRelationCreateList()
{ 
}

void CDialogExCreateNoGeometry::SetNoGeometryFeatureList(S101Cell* cell)
{
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] No geometry list initializing"));

  	ngflist.clear();
	fnhash.clear();

	Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;
	m_cell = cell;
	
	for (auto i = fc->featureTypes.featureType.begin();
		i != fc->featureTypes.featureType.end();
		i++)
	{
 		auto featureType = &i->second;

		for (auto ppi = featureType->permittedPrimitives.begin();
			ppi != featureType->permittedPrimitives.end();
			ppi++)
		{
			SpatialPrimitiveType* spt = &(*ppi);

			if (spt->GetValueString().compare(L"noGeometry") == 0)
			{
				fnhash.insert({ featureType->code.GetValueString(), featureType });
			}
		}
	}

	POSITION pos = cell->m_feaMap.GetStartPosition();

	while (pos != NULL)
	{
		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);

		if (fr->m_spas.size() == 0)
		{
			int code = fr->m_frid.m_nftc;

			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			CodeWithNumericCode* nc = itor->second;

			std::wstring codeStr = nc->m_code;
			FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType .find(codeStr)->second;

			CFeatureCodeString cs;
			cs._name = objFT->code.GetValueString();
			cs._id = fr->m_frid.m_name.RCID;
			cs._fr = fr;
			ngflist.push_back(cs); 
		}
	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] No geometry list initializing complete"));

}

void CDialogExCreateNoGeometry::OnBnClickedButtonAddNoGeometryList()
{ 
	CString str;
	m_ComboName.GetWindowText(str);

	if (str.GetLength() == 0)
	{
		return;
	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] Add no geometry process start"));

	auto it = fnhash.find(wstring(str));
	FeatureType* ft = it->second;
	auto it2 = m_cell->m_dsgir.m_ftcs->m_arrFindForCode.find(ft->code.GetValueString());

	if (m_cell->m_dsgir.m_ftcs->m_arrFindForCode.find(ft->code.GetValueString()) == m_cell->m_dsgir.m_ftcs->m_arrFindForCode.end()){
	
		for (unsigned i = 1; i < 1048575; i++)
		{
			auto fitor = m_cell->m_dsgir.m_ftcs->m_arr.find(i);
			if (fitor == m_cell->m_dsgir.m_ftcs->m_arr.end())
			{
				CodeWithNumericCode *cnc = new CodeWithNumericCode();
				cnc->m_nmcd = i;
				cnc->m_code = ft->code.GetValueString().c_str();
				m_cell->m_dsgir.m_ftcs->m_arrFindForCode.insert(std::unordered_map<std::wstring, CodeWithNumericCode*>::value_type(ft->code.GetValueString(), cnc));
				m_cell->m_dsgir.m_ftcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));

				it2 = m_cell->m_dsgir.m_ftcs->m_arrFindForCode.find(ft->code.GetValueString());
				
				break;
			}
		}

	}

	CodeWithNumericCode* nc = it2->second;

	R_FeatureRecord* fr = new R_FeatureRecord();
	fr->m_frid.m_name.RCNM = 100; 
	fr->m_frid.m_name.RCID =GetItemsId();
	fr->m_frid.m_nftc = nc->m_nmcd;
	fr->m_frid.m_ruin = 0;
	fr->m_frid.m_rver = 1;
	fr->m_foid.m_objName.m_agen = 1;
	fr->m_foid.m_objName.m_fids = 1;
	fr->m_foid.m_objName.m_fidn = ENC_S101_Factory::GetFeatureID_FOID(m_cell, fr->m_foid.m_objName.m_agen, fr->m_foid.m_objName.m_fids);

	fr->m_scaleMin = 0;    
	Catalog *catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;

	std::wstring codeStr = nc->m_code;
	FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType.find(codeStr)->second;

	CFeatureCodeString cs;
	cs._name = objFT->code.GetValueString();
	cs._id = fr->m_frid.m_name.RCID;
	cs._fr = fr;
	AddNoGeometryFeatureItem(&cs);
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] Add no geometry process end"));
}


void CDialogExCreateNoGeometry::AddNoGeometryFeatureItem(CFeatureCodeString* cf)
{ 
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = Item;
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(cf->_name.c_str());
	lvi.lParam = (LPARAM)cf->_fr;
	BOOL ret = 0;

	CString id;
	id.Format(L"%d", cf->_id);
	int indexItem = m_ListNoGeometry.InsertItem(&lvi);

	m_ListNoGeometry.SetItemText(indexItem, 0, id);
	m_ListNoGeometry.SetItemText(indexItem, 1, cf->_name.c_str());

	ngflist.push_back(*cf); 
	Item++;

}

void CDialogExCreateNoGeometry::OnHdnItemclickListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	int nColumn = phdr->iItem;
	for (int i = 0; i<(m_ListNoGeometry.GetItemCount()); i++)
	{
		m_ListNoGeometry.SetItemData(i, i);
	} 
	m_bAscending = !m_bAscending; 
	SORTPARAM sortparams;
	sortparams.pList = &m_ListNoGeometry;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending ? true : false; 
	m_ListNoGeometry.SortItems(&CompareItem, (LPARAM)&sortparams);

	*pResult = 0;
}

int CALLBACK CDialogExCreateNoGeometry::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
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

int CDialogExCreateNoGeometry::GetItemsId()
{
	vector<int> idlist;

	if (ngflist.size() == 0)
	{
		return 1;
	}

	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CFeatureCodeString* cs = &(*fni);
		idlist.push_back(cs->_id);
	}

	sort(idlist.begin(), idlist.end());//정렬합니다. 
	for (size_t num = 0; num < idlist.size(); num++)
	{
		if (idlist[num] == (int)(num + 1))
		{
			continue;
		}
		else if (idlist[num] < (int)(num + 1))
		{ 
			return idlist[num];
		}
		else if (idlist[num] > (int)(num + 1))
		{
			return num + 1;
		}
	}
	return idlist.size() + 1;
}

void CDialogExCreateNoGeometry::OnBnClickedDelete()
{
	POSITION pos = m_ListNoGeometry.GetFirstSelectedItemPosition();
	int idx = 0;
	while (pos)
	{ 
		idx = m_ListNoGeometry.GetNextSelectedItem(pos);
	}
	CString csFrid;
	csFrid.Format(m_ListNoGeometry.GetItemText(idx, 0)); 

	m_ListNoGeometry.DeleteItem(idx);
	ngflist.erase(ngflist.begin() + idx); 
	theApp.m_DockablePaneCurrentSelection.DeleteItem(csFrid);
}
