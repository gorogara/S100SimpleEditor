// CDialogExRelationView.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExRelationView.h"
#include "afxdialogex.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "..\\FeatureCatalog\\Catalog.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include <iostream>
#include <locale.h>

const UINT WM_FILTER_LIST = ::RegisterWindowMessage(_T("WM_FILTER_LIST"));
using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExRelationView, CDialogEx)


CDialogExRelationView::CDialogExRelationView(CWnd* pParent )
	: CDialogEx(CDialogExRelationView::IDD, pParent)
{


}

CDialogExRelationView::~CDialogExRelationView()
{
}

void CDialogExRelationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RELATION_VIEW1, m_ListFeatureRelation);
}


BEGIN_MESSAGE_MAP(CDialogExRelationView, CDialogEx)
	ON_COMMAND(IDD_DIALOG_RELATION_VIEW, &CDialogExRelationView::OnIddDialogRelationView)
	ON_BN_CLICKED(IDOK, &CDialogExRelationView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExRelationView::OnBnClickedCancel)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CDialogExRelationView::OnHdnItemdblclickListRelationView)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_RELATION, &CDialogExRelationView::OnBnClickedButtonRelationDelete)
END_MESSAGE_MAP() 
void CDialogExRelationView::OnIddDialogRelationView()
{
}

#pragma warning(disable:4129)
void CDialogExRelationView::OnBnClickedOk()
{ 

	CDialogEx::OnOK();
}


void CDialogExRelationView::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL CDialogExRelationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListFeatureRelation.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListFeatureRelation.GetWindowRect(listRect);

	m_ListFeatureRelation.InsertColumn(0, _T("Type"), LVCFMT_LEFT, (int)(listRect.Width()*0.166)); 
	m_ListFeatureRelation.InsertColumn(1, _T("Relation Name"), LVCFMT_CENTER, (int)(listRect.Width()*0.166)); 
	m_ListFeatureRelation.InsertColumn(2, _T("Feature Name "), LVCFMT_LEFT, (int)(listRect.Width()*0.166)); 
	m_ListFeatureRelation.InsertColumn(3, _T("Feature ID"), LVCFMT_CENTER, (int)(listRect.Width()*0)); 
	m_ListFeatureRelation.InsertColumn(4, _T("Role"), LVCFMT_LEFT, (int)(listRect.Width()*0.166)); 
	m_ListFeatureRelation.InsertColumn(5, _T("Association Feature Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.166)); 
	m_ListFeatureRelation.InsertColumn(6, _T("Association Feature ID"), LVCFMT_LEFT, (int)(listRect.Width()*0)); 
	m_ListFeatureRelation.InsertColumn(7, _T("Org type"), LVCFMT_LEFT, (int)(listRect.Width() * 0));  
	if (m_viewMode == L"Feature"){
		SetDataOrg();
		SetDataObj();
	}
	else if (m_viewMode == L"Information1"){
		SetDataOrgInformation1();
		SetDataObjInformation1();
	}
	else if (m_viewMode == L"Information2"){
		SetDataOrgInformation2();
		SetDataObjInformation2();
	}

	return true;

}
void CDialogExRelationView::SetDataOrg()
{ 
	m_ListFeatureRelation.DeleteAllItems();

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_FeatureRecord *orgFr = m_fr; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	wstring orgFeatureName = orgFtItor->second->m_code;
	FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_FeatureRecord* objFr = NULL; 
		cell->m_feaMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
		{

			auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
			wstring objFeatureName = objFtItor->second->m_code;
			FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second); 

			F_FASC *fasc = *itt;

			auto objfaItor = cell->m_dsgir.m_facs->m_arr.find(fasc->m_nfac);
			if (objfaItor == cell->m_dsgir.m_facs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(fasc->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->featureBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_frid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_frid.m_name.RCID);

			__int64 key = ((__int64)100) << 32 | fasc->m_name.RCID;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, fasc->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), fasc->m_name.RCID); 
			if (fasc->m_name.RCID == orgFr->m_frid.m_name.RCID && colOrgAssociationName == m_assoName)
			{

				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Feature");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"Feature");

				UpdateData(false);
			}

		}

	}


}



void CDialogExRelationView::SetDataObj()
{

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_FeatureRecord *orgFr = m_tfr; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	wstring orgFeatureName = orgFtItor->second->m_code;
	FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_FeatureRecord* objFr = NULL; 
		cell->m_feaMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
		{

			auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
			wstring objFeatureName = objFtItor->second->m_code;
			FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second); 

			F_FASC *fasc = *itt;  

			auto objfaItor = cell->m_dsgir.m_facs->m_arr.find(fasc->m_nfac);
			if (objfaItor == cell->m_dsgir.m_facs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(fasc->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->featureBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_frid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_frid.m_name.RCID);

			__int64 key = ((__int64)100) << 32 | fasc->m_name.RCID;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, fasc->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), fasc->m_name.RCID); 
			if (fasc->m_name.RCID == orgFr->m_frid.m_name.RCID && colOrgAssociationName == m_assoName)
			{

				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Feature");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"Feature");

				UpdateData(false);
			}

		}

	}


}



void CDialogExRelationView::SetDataOrgInformation1()
{ 
	m_ListFeatureRelation.DeleteAllItems();

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_FeatureRecord *orgFr = m_tifr; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	wstring orgFeatureName = orgFtItor->second->m_code;
	FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_infMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_InformationRecord* objFr = NULL; 
		cell->m_infMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
		{

			auto objFtItor = cell->m_dsgir.m_itcs->m_arr.find(objFr->m_irid.m_nitc);
			wstring objFeatureName = objFtItor->second->m_code;
			InformationType *objFT = &(fc->informationTypes.informationType.find(objFeatureName)->second); 

			F_INAS *inas = *itt;

			auto objfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (objfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->informationBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_irid.m_nitc;
			auto itor = cell->m_dsgir.m_itcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_irid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_irid.m_name.RCID);

			__int64 key = ((__int64)100) << 32 | inas->m_name.RCID;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, inas->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			if (inas->m_name.RCID == orgFr->m_frid.m_name.RCID && colOrgAssociationName == m_assoName)
			{

				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Information");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"Information");

				UpdateData(false);
			}

		}

	}


}



void CDialogExRelationView::SetDataObjInformation1()
{

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_InformationRecord *orgFr = m_ifr; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_irid.m_nitc);
	wstring orgFeatureName = orgFtItor->second->m_code;
	FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_FeatureRecord* objFr = NULL; 
		cell->m_feaMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
		{

			auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
			wstring objFeatureName = objFtItor->second->m_code;
			FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second); 

			F_INAS *inas = *itt;  

			auto objfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (objfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->informationBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_frid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_frid.m_name.RCID);

			__int64 key = ((__int64)150) << 32 | inas->m_name.RCID;
			R_InformationRecord *rfr = m_cell->m_infMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_irid.m_nitc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, inas->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			if (inas->m_name.RCID == orgFr->m_irid.m_name.RCID && colOrgAssociationName == m_assoName)
			{

				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Information");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"feature");

				UpdateData(false);
			}

		}

	}


}






void CDialogExRelationView::SetDataOrgInformation2()
{ 
	m_ListFeatureRelation.DeleteAllItems();

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_FeatureRecord *orgFr = m_ifr1; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	wstring orgFeatureName = orgFtItor->second->m_code;
	FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_infMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_InformationRecord* objFr = NULL; 
		cell->m_infMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
		{

			auto objFtItor = cell->m_dsgir.m_itcs->m_arr.find(objFr->m_irid.m_nitc);
			wstring objFeatureName = objFtItor->second->m_code;
			InformationType *objFT = &(fc->informationTypes.informationType.find(objFeatureName)->second); 

			F_INAS *inas = *itt;

			auto objfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (objfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->informationBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_irid.m_nitc;
			auto itor = cell->m_dsgir.m_itcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_irid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_irid.m_name.RCID);

			__int64 key = ((__int64)100) << 32 | inas->m_name.RCID;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, inas->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			if (inas->m_name.RCID == orgFr->m_frid.m_name.RCID && colOrgAssociationName == m_assoName)
			{

				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Information");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"Information");

				UpdateData(false);
			}

		}

	}


}



void CDialogExRelationView::SetDataObjInformation2()
{

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	R_InformationRecord *orgFr = m_tifr1; 
	S101Cell *cell = m_cell;
	auto orgFtItor = cell->m_dsgir.m_itcs->m_arr.find(orgFr->m_irid.m_nitc);
	
	if (orgFtItor == cell->m_dsgir.m_itcs->m_arr.end())
	{
		CString msg;
		msg.Format(L"[%d] Inforation code not exist in cell Information type codelist. -REALATION", orgFr->m_irid.m_nitc);
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::FC);
		return;
	}

	wstring orgFeatureName = orgFtItor->second->m_code;
	InformationType *orgFT = &(fc->informationTypes.informationType.find(orgFeatureName)->second);  
	POSITION pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{

		__int64 key = 0;
		R_FeatureRecord* objFr = NULL; 
		cell->m_feaMap.GetNextAssoc(pos, key, objFr); 
		for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
		{
			auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
			wstring objFeatureName = objFtItor->second->m_code;
			FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second); 

			F_INAS *inas = *itt;  

			auto objfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (objfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = objfaItor->second->m_code;

			auto objarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (objarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = objarItor->second->m_code;

			auto objFBItor = objFT->informationBinding.find(objFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L"";

			int code = objFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			colOrgFeatureName.Format(_T("%s (%d)"), itor->second->m_code, objFr->m_frid.m_name.RCID);

			colOrgAssociationName.Format(_T("%s"), orgAssociationName.c_str());
			colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str());

			colOrgFeatureId.Format(_T("%d"), objFr->m_frid.m_name.RCID);

			__int64 key = ((__int64)150) << 32 | inas->m_name.RCID;
			R_InformationRecord *rfr = m_cell->m_infMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_irid.m_nitc);

			colAssociationFeatureName.Format(_T("%s (%d)"), itors->second->m_code, inas->m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			if (inas->m_name.RCID == orgFr->m_irid.m_name.RCID && colOrgAssociationName == m_assoName)
			{
				LVITEM firstItem = { 0 };
				m_ListFeatureRelation.InsertItem(&firstItem);  
				m_ListFeatureRelation.SetItemText(0, 0, L"Information");
				m_ListFeatureRelation.SetItemText(0, 1, colOrgAssociationName); 
				m_ListFeatureRelation.SetItemText(0, 2, colOrgFeatureName); 
				m_ListFeatureRelation.SetItemText(0, 3, colOrgFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 4, colOrgAssociationRole); 
				m_ListFeatureRelation.SetItemText(0, 5, colAssociationFeatureName);  
				m_ListFeatureRelation.SetItemText(0, 6, colAssociationFeatureId); 
				m_ListFeatureRelation.SetItemText(0, 7, L"Feature");

				UpdateData(false);
			}
		}
	}
}









void CDialogExRelationView::OnHdnItemdblclickListRelationView(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR); 
	*pResult = 0;  
}



void CDialogExRelationView::OnBnClickedButtonRelationDelete()
{
	if (MessageBox(_T("Do you delete selected relation?"), _T("Delete relation"), MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2) == IDYES)
	{

		int idx = 0;
		CString orgFrid;
		CString objFrid;
		CString relationType;
		CString orgType;

		POSITION pos = m_ListFeatureRelation.GetFirstSelectedItemPosition();
		idx = m_ListFeatureRelation.GetNextSelectedItem(pos);

		relationType = m_ListFeatureRelation.GetItemText(idx, 0);
		orgFrid = m_ListFeatureRelation.GetItemText(idx, 3);
		objFrid = m_ListFeatureRelation.GetItemText(idx, 6);
		orgType = m_ListFeatureRelation.GetItemText(idx, 7);

		__int64 okey = ((__int64)100) << 32 | _ttoi(orgFrid); 
		__int64 bkey = ((__int64)100) << 32 | _ttoi(objFrid); 
		__int64 oikey = ((__int64)150) << 32 | _ttoi(orgFrid); 
		__int64 bikey = ((__int64)150) << 32 | _ttoi(objFrid); 

		if (relationType == L"Feature"){

			R_FeatureRecord *ofr = m_cell->m_feaMap.PLookup(okey)->value;
			R_FeatureRecord *bfr = m_cell->m_feaMap.PLookup(bkey)->value; 
			for (auto itt = ofr->m_fasc.begin(); itt != ofr->m_fasc.end(); itt++)
			{
				F_FASC *ofasc = *itt;

				if (ofasc->m_name.RCID == bfr->m_frid.m_name.RCID){
					ofr->m_fasc.remove(ofasc); 
					break;
				}

			}

			for (auto bitt = bfr->m_fasc.begin(); bitt != bfr->m_fasc.end(); bitt++)
			{
				F_FASC *bfasc = *bitt;

				if (bfasc->m_name.RCID == ofr->m_frid.m_name.RCID){
					bfr->m_fasc.remove(bfasc);
					break;
				}
			}

			SetDataOrg();
			SetDataObj();

		}
 		else if (relationType == L"Information"){

			R_FeatureRecord *ofr = NULL;
			R_InformationRecord *oifr = NULL;
			               
			R_FeatureRecord *bfr = NULL;
			R_InformationRecord *bifr = NULL; 
			if (orgType == "Information"){
				oifr = m_cell->m_infMap.PLookup(oikey)->value; 
				bfr = m_cell->m_feaMap.PLookup(bkey)->value; 
			}
			else {
				ofr = m_cell->m_feaMap.PLookup(okey)->value; 
				bifr = m_cell->m_infMap.PLookup(bikey)->value; 
			} 
			if (ofr == NULL){
				
				for (auto itt = oifr->m_inas.begin(); itt != oifr->m_inas.end(); itt++)
				{
					F_INAS *oinas = *itt;

					if (oinas->m_name.RCID == bfr->m_frid.m_name.RCID){
						oifr->m_inas.remove(oinas); 
						break;
					}

				}

				for (auto bitt = bfr->m_inas.begin(); bitt != bfr->m_inas.end(); bitt++)
				{
					F_INAS *binas = *bitt;

					if (binas->m_name.RCID == oifr->m_irid.m_name.RCID){
						bfr->m_inas.remove(binas);
						break;
					}
				}

			} 
			else {

				for (auto itt = ofr->m_inas.begin(); itt != ofr->m_inas.end(); itt++)
				{
					F_INAS *oinas = *itt;

					if (oinas->m_name.RCID == bifr->m_irid.m_name.RCID){
						ofr->m_inas.remove(oinas); 
						break;
					}

				}

				for (auto bitt = bifr->m_inas.begin(); bitt != bifr->m_inas.end(); bitt++)
				{
					F_INAS *binas = *bitt;

					if (binas->m_name.RCID == ofr->m_frid.m_name.RCID){
						bifr->m_inas.remove(binas);
						break;
					}
				}

			}
			
			if (m_viewMode == L"Information1"){
				SetDataOrgInformation1();
				SetDataObjInformation1();
			}
			else if (m_viewMode == L"Information2"){
				SetDataOrgInformation2();
				SetDataObjInformation2();
			}

			UpdateData(false);


		}


		AfxMessageBox(L"Delete relation completed.");
	}

}
