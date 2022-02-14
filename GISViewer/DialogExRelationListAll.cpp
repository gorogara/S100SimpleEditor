// CDialogExRelationListAll.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "afxwin.h"
#include "DialogExRelationListAll.h"
#include "afxdialogex.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\R_PointRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"


#include <iostream>
using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExRelationListAll, CDialogEx)


CDialogExRelationListAll::CDialogExRelationListAll(CWnd* pParent )
	: CDialogEx(CDialogExRelationListAll::IDD, pParent)
{


}

CDialogExRelationListAll::~CDialogExRelationListAll()
{
}

void CDialogExRelationListAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDialogExRelationListAll, CDialogEx)
	ON_COMMAND(IDD_DIALOG_RELATIONALL_LIST, &CDialogExRelationListAll::OnIddDialogRelationListAll)
	ON_BN_CLICKED(IDOK, &CDialogExRelationListAll::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExRelationListAll::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RELATION, &CDialogExRelationListAll::OnLvnItemchangedListRelation)
	ON_NOTIFY(HDN_ITEMDBLCLICK, IDC_LIST_RELATION, &CDialogExRelationListAll::OnHdnItemdblclickListRelationAll)
END_MESSAGE_MAP() 
void CDialogExRelationListAll::OnIddDialogRelationListAll()
{
}

#pragma warning(disable:4129)
void CDialogExRelationListAll::OnBnClickedOk()
{ 

	CDialogEx::OnOK();
}


void CDialogExRelationListAll::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
}
void CDialogExRelationListAll::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
} 
BOOL CDialogExRelationListAll::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	CListCtrl* m_ListRelation = (CListCtrl*)GetDlgItem(IDC_LIST_RELATION_ALL);

	m_ListRelation->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListRelation->GetWindowRect(listRect);
	m_ListRelation->InsertColumn(0, _T("No. "), LVCFMT_CENTER, (int)(listRect.Width()*0.07));
	m_ListRelation->InsertColumn(1, _T("Feature ID "), LVCFMT_LEFT, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(2, _T("Relation"), LVCFMT_LEFT, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(3, _T("Acronym"), LVCFMT_LEFT, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(4, _T("Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(5, _T("Geometry"), LVCFMT_LEFT, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(6, _T("Lat"), LVCFMT_CENTER, (int)(listRect.Width()*0.13));
	m_ListRelation->InsertColumn(7, _T("Long"), LVCFMT_CENTER, (int)(listRect.Width()*0.13));
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	AdjustLayout();
	return true;
	
}


void CDialogExRelationListAll::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);
	CListCtrl* m_ListRelation = (CListCtrl*)GetDlgItem(IDC_LIST_RELATION_ALL);

	CRect      rectENCs;

	if (m_ListRelation->GetSafeHwnd())
	{
		rectENCs = CRect(rectClient.left, rectClient.top, rectClient.Size().cx, rectClient.Size().cy-35);
		m_ListRelation->MoveWindow(rectENCs);
		m_ListRelation->SetColumnWidth(0, (int)(rectENCs.Width()*0.07)); 
		m_ListRelation->SetColumnWidth(1, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(2, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(3, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(4, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(5, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(6, (int)(rectENCs.Width()*0.13)); 
		m_ListRelation->SetColumnWidth(7, (int)(rectENCs.Width()*0.13)); 
	}

}


void CDialogExRelationListAll::OnLvnItemchangedListRelation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	*pResult = 0;
}


void CDialogExRelationListAll::OnHdnItemdblclickListRelationAll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR); 
	*pResult = 0;  


}



void CDialogExRelationListAll::SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist)
{

	m_cell = cell; 
	m_ListRelation.DeleteAllItems();

	FeatureCatalogue *fc = ((S101Layer*)cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;
	for (auto ri = flist.begin(); ri != flist.end(); ri++)
	{
		R_FeatureRecord *orgFr = *ri; 

		auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  continue;
		wstring orgFeatureName = orgFtItor->second->m_code;

		FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);

		for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
		{
			F_FASC *fasc = *itt;

			auto orgfaItor = cell->m_dsgir.m_facs->m_arr.find(fasc->m_nfac);
			if (orgfaItor == cell->m_dsgir.m_facs->m_arr.end())  continue;
			CString faName = orgfaItor->second->m_code;

			auto orgarItor = cell->m_dsgir.m_arcs->m_arr.find(fasc->m_narc);
			if (orgarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = orgarItor->second->m_code;

			auto orgFBItor = orgFT->featureBinding.find(orgFeatureName);
			
			wstring orgAssociationName = faName;
			

			wstring orgRoleName = arName;
			


			LVITEM firstItem = { 0 };
			m_ListRelation.InsertItem(&firstItem); 

			CString colOrgFeatureName = L"";
			CString colAssociationName = L"";
			CString colOrgAssociationInfo = L""; 
			colOrgFeatureName.Format(_T("%d"), orgFr->m_frid.m_name.RCID); 
			colAssociationName.Format(_T("%d"), fasc->m_name.RCID);
			colOrgAssociationInfo.Format(_T("%s (%s)"), orgAssociationName.c_str(), orgRoleName.c_str()); 
			m_ListRelation.SetItemText(0, 0, colOrgFeatureName);
			m_ListRelation.SetItemText(0, 1, colAssociationName);
			m_ListRelation.SetItemText(0, 2, colOrgAssociationInfo);

			UpdateData(false);




		} 


	}
}
