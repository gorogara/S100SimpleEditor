// CDialogExCreateAutoRelation.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExCreateAutoRelation.h"

#include "afxdialogex.h"
#include "GISViewer.h"
#include "GISViewerView.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\CodeWithNumericCode.h"


#include <iostream>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExCreateAutoRelation, CDialogEx)


CDialogExCreateAutoRelation::CDialogExCreateAutoRelation(CWnd* pParent )
	: CDialogEx(CDialogExCreateAutoRelation::IDD, pParent)
{


}

CDialogExCreateAutoRelation::~CDialogExCreateAutoRelation()
{
}

void CDialogExCreateAutoRelation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CREATE_AUTO_RELATION_LIST, m_ListNoGeometry);
	DDX_Control(pDX, IDC_LIST_CREATE_AUTO_RELATION_INFORMATION_LIST, m_ListInformationFeature);
	
}


BEGIN_MESSAGE_MAP(CDialogExCreateAutoRelation, CDialogEx)
	ON_COMMAND(IDD_DIALOG_SELECT_FILTER, &CDialogExCreateAutoRelation::OnIddDialogCreateAutoRelation)
	ON_BN_CLICKED(IDOK, &CDialogExCreateAutoRelation::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExCreateAutoRelation::OnBnClickedCancel)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDialogExCreateAutoRelation::OnHdnItemclickListNoGeometryList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CREATE_AUTO_RELATION_LIST, &CDialogExCreateAutoRelation::OnLvnItemchangedListCreateAutoRelationList)
END_MESSAGE_MAP() 
void CDialogExCreateAutoRelation::OnIddDialogCreateAutoRelation()
{
}

#pragma warning(disable:4129)
void CDialogExCreateAutoRelation::OnBnClickedOk()
{
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create auto relation] process start")); 
	std::list<R_FeatureRecord*> flist;
	for (int i = 0; i<m_ListNoGeometry.GetItemCount();i++)
	{
		CString frid;
		frid.Format(m_ListNoGeometry.GetItemText(i, 0));

		if (frid != L"") 
		{

			__int64 fridN = _tcstoui64(frid, NULL, 10); 
			__int64 key = ((__int64)100) << 32 | fridN;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			flist.push_back(rfr); 
			SetFeatureList(m_cell, flist);
			flist.clear();
		}
		
	} 
	std::list<R_FeatureRecord*> infoFlist;
	for (int i = 0; i < m_ListInformationFeature.GetItemCount(); i++)
	{
		CString frid;
		frid.Format(m_ListInformationFeature.GetItemText(i, 0));

		if (frid != L"")
		{

			__int64 fridN = _tcstoui64(frid, NULL, 10); 
			__int64 key = ((__int64)100) << 32 | fridN;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			infoFlist.push_back(rfr); 
			SetInformationList(m_cell, infoFlist);
			infoFlist.clear();
		}

	} 

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create auto relation] process end"));

	CDialogEx::OnOK();
}

void CDialogExCreateAutoRelation::SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist)
{

	m_cell = cell;
	CStringArray featureArr;
	CStringArray delFeatureArr;
	featureArr.SetSize(1000);
	delFeatureArr.SetSize(100);

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;
	for (auto ri = flist.begin(); ri != flist.end(); ri++)
	{
		R_FeatureRecord *orgFr = *ri; 
		
		auto orgFtItor = m_cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == m_cell->m_dsgir.m_ftcs->m_arr.end())  continue;
		wstring orgFeatureName = orgFtItor->second->m_code;

		FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second); 
		for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
		{
			F_FASC *fasc = *itt;

			auto orgfaItor = m_cell->m_dsgir.m_facs->m_arr.find(fasc->m_nfac);
			if (orgfaItor == m_cell->m_dsgir.m_facs->m_arr.end())  continue;
			CString faName = orgfaItor->second->m_code;

			auto orgarItor = m_cell->m_dsgir.m_arcs->m_arr.find(fasc->m_narc);
			if (orgarItor == m_cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = orgarItor->second->m_code;

			auto orgFBItor = orgFT->featureBinding.find(orgFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;
			CString colAssociationFeatureId = L"";

			int code = orgFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);

			__int64 key = ((__int64)100) << 32 | fasc->m_name.RCID;
			R_FeatureRecord *rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			colAssociationFeatureId.Format(_T("%d"), fasc->m_name.RCID);

			featureArr.Add(colAssociationFeatureId);

		}
	}

	OnMenuAutoRelation(&featureArr);

	for (auto ri = flist.begin(); ri != flist.end(); ri++)
	{
		R_FeatureRecord *rfr = *ri;
		__int64 key = ((__int64)100) << 32 | rfr->m_frid.m_name.RCID;

		int code = rfr->m_frid.m_nftc;
		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
		
		CString delFeatureName = itor->second->m_code;

		if (delFeatureName == L"updatedinformation" || delFeatureName == L"bridgeAggregation" || delFeatureName == L"structureEquipment"){
			cell->m_feaMap.RemoveKey(key);
		}
	}

	featureArr.RemoveAll();

} 
void CDialogExCreateAutoRelation::SetInformationList(S101Cell* cell, std::list<R_FeatureRecord*> flist)
{

	m_cell = cell;
	CStringArray featureArr;
	featureArr.SetSize(10);

	FeatureCatalogue *fc = ((S101Layer*)m_cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;
	for (auto ri = flist.begin(); ri != flist.end(); ri++)
	{
		R_FeatureRecord *orgFr = *ri; 


		auto orgFtItor = m_cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == m_cell->m_dsgir.m_ftcs->m_arr.end())  continue;
		wstring orgFeatureName = orgFtItor->second->m_code; 
		for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
		{
			F_INAS *inas = *itt;

			auto orgfaItor = m_cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (orgfaItor == m_cell->m_dsgir.m_iacs->m_arr.end())  continue;
			
			auto orgarItor = m_cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (orgarItor == m_cell->m_dsgir.m_arcs->m_arr.end())  continue;
			
			CString colAssociationFeatureId = L"";
			CString colOrgFeatureId = L"";
			
			int code = inas->m_name.RCID;
			auto itor = cell->m_dsgir.m_itcs->m_arr.find(code);

			__int64 key = ((__int64)150) << 32 | code;
			R_InformationRecord *rfr = m_cell->m_infMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_itcs->m_arr.find(rfr->m_irid.m_nitc);

			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID);
			colOrgFeatureId.Format(_T("%d"), orgFr->m_frid.m_name.RCID); 
			featureArr.Add(colAssociationFeatureId + _T("|||") + colOrgFeatureId);

		}
	}

	OnMenuAutoRelationInformation(&featureArr);
	featureArr.RemoveAll();

}

void CDialogExCreateAutoRelation::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
}

void CDialogExCreateAutoRelation::InitNonGeometryList()
{

	m_ListNoGeometry.DeleteAllItems();

	LVITEM firstItem = { 0 };
	m_ListNoGeometry.InsertItem(&firstItem); 


	int iItem = 0;
	for (auto fni = ngflist.begin(); fni != ngflist.end(); fni++)
	{
		CFeatureCodeStringAuto* cs = &(*fni);
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
		m_ListNoGeometry.SetItemText(indexItem, 2, L"Feature");

		iItem++;
	}
}

void CDialogExCreateAutoRelation::InitInformationFeatureList()
	{

		m_ListInformationFeature.DeleteAllItems();

		LVITEM firstItem = { 0 };
		m_ListInformationFeature.InsertItem(&firstItem); 


		int iItem = 0;
		for (auto fni = infoflist.begin(); fni != infoflist.end(); fni++)
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

			m_ListInformationFeature.SetItemText(indexItem, 0, id);
			m_ListInformationFeature.SetItemText(indexItem, 1, cs->_name.c_str());
			m_ListInformationFeature.SetItemText(indexItem, 2, L"Information");

			iItem++;
		}


	} 
BOOL CDialogExCreateAutoRelation::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	m_ListNoGeometry.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListNoGeometry.GetWindowRect(listRect);

	m_ListNoGeometry.InsertColumn(0, _T("Relation ID"), LVCFMT_CENTER, (int)(listRect.Width()*0.20));
	m_ListNoGeometry.InsertColumn(1, _T("Relation Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.65));
	m_ListNoGeometry.InsertColumn(2, _T("Type"), LVCFMT_LEFT, (int)(listRect.Width()*0.15));
	

	m_ListInformationFeature.GetWindowRect(listRect);

	m_ListInformationFeature.InsertColumn(0, _T("Feature ID"), LVCFMT_CENTER, (int)(listRect.Width()*0.20));
	m_ListInformationFeature.InsertColumn(1, _T("Feature Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.65));
	m_ListInformationFeature.InsertColumn(2, _T("Type"), LVCFMT_LEFT, (int)(listRect.Width()*0.15));

	InitNonGeometryList();
	InitInformationFeatureList();
	return true;
}

void CDialogExCreateAutoRelation::SetNoGeometryFeatureList(S101Cell* cell)
{

	theApp.m_DockablePaneLogger.AppendList(_T("[Create auto relation] No geometry list initializing"));

  	ngflist.clear();
	fnhash.clear();

	Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;
	m_cell = cell; 

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
			FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType.find(codeStr)->second;

			CFeatureCodeStringAuto cs;
			cs._name = objFT->code.GetValueString();
			cs._id = fr->m_frid.m_name.RCID;
			cs._fr = fr;
			ngflist.push_back(cs);

		}

	}   
	pos = cell->m_infMap.GetStartPosition();

	while (pos != NULL)
	{

		__int64 key = 0; 
		R_InformationRecord* ir = nullptr; 
		cell->m_infMap.GetNextAssoc(pos, key, ir);  
			int code = ir->m_irid.m_nitc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			CodeWithNumericCode* nc = itor->second;

			std::wstring codeStr = nc->m_code;
			FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType.find(codeStr)->second;

			CInformationCodeString cs;
			cs._name = objFT->code.GetValueString();
			cs._id = ir->m_irid.m_name.RCID;
			cs._ir = ir;
			infoflist.push_back(cs); 
	} 


	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Create no geometry] No geometry list initializing complete"));

}

void CDialogExCreateAutoRelation::OnHdnItemclickListNoGeometryList(NMHDR *pNMHDR, LRESULT *pResult)
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

int CALLBACK CDialogExCreateAutoRelation::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
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
void CDialogExCreateAutoRelation::OnMenuAutoRelation(CStringArray* featureArr)
{

	pView = theApp.pView; 
	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process start")); 
	NewFeatureManager *nfm = pView->m_pNewFeatureManager; 
	S101Layer *l = (S101Layer *)m_cell->m_pLayer; 
	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second; 
	int sidx = 0, cidx = 0;
 	CString sfrid, cfrid; 
	for (int i = 0; i < featureArr->GetSize(); i++)
	{ 
		sfrid.Format(_T("%s"), featureArr->GetAt(i)); 
		if (sfrid != L"") {


			__int64 sfridN = _tcstoui64(sfrid, NULL, 10);
			__int64 skey = ((__int64)100) << 32 | sfridN; 
			R_FeatureRecord *orgFr = m_cell->m_feaMap.PLookup(skey)->value;  
			for (int j = 0; j < featureArr->GetSize(); j++)
			{ 
				cfrid.Format(_T("%s"), featureArr->GetAt(j)); 
				if (cfrid != L"" && cfrid != sfrid) {

					__int64 cfridN = _tcstoui64(cfrid, NULL, 10);
				__int64 ckey = ((__int64)100) << 32 | cfridN; 
				R_FeatureRecord *objFr = m_cell->m_feaMap.PLookup(ckey)->value;  
				auto orgFtItor = m_cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
				if (orgFtItor == m_cell->m_dsgir.m_ftcs->m_arr.end())  break;
				wstring orgFeatureName = orgFtItor->second->m_code; 
				auto objFtItor = m_cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
				if (objFtItor == m_cell->m_dsgir.m_ftcs->m_arr.end())  continue;
				wstring objFeatureName = objFtItor->second->m_code; 


				if ((orgFeatureName == L"UpdateInformation" || objFeatureName == L"UpdateInformation") && objFeatureName != orgFeatureName) { 
					bool isDuplicateUI = false;
					CString objRoleNameUI;
					CString orgRoleNameUI;

					F_FASC* checkAFSCUI = NULL;

					for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
					{
						checkAFSCUI = *itt;
						if (checkAFSCUI->m_name.RCID == orgFr->m_frid.m_name.RCID &&
							checkAFSCUI->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (objFeatureName == L"UpdateInformation")
					{
						objRoleNameUI = L"Updates";
					}
					else
					{
						objRoleNameUI = L"Identifies";
					}

					if (!isDuplicateUI)
					{
						F_FASC* objF_AFSC = new F_FASC();

						objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
						objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
						objF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, L"updatedInformation");
						objF_AFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)objRoleNameUI);
						objF_AFSC->m_faui = 1;

						objFr->m_fasc.push_back(objF_AFSC);
					}
					else
					{
						checkAFSCUI->m_nfac = ENC_S101_Factory::GetFACS(m_cell, L"updatedInformation");
						checkAFSCUI->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)objRoleNameUI);
						checkAFSCUI->m_faui = 1;
					}



					isDuplicateUI = false;
					checkAFSCUI = NULL;
					for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
					{
						checkAFSCUI = *itt;
						if (checkAFSCUI->m_name.RCID == objFr->m_frid.m_name.RCID &&
							checkAFSCUI->m_name.RCNM == objFr->m_frid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (orgFeatureName == L"UpdateInformation")
					{
						orgRoleNameUI = L"Updates";
					}
					else 
					{
						orgRoleNameUI = L"Identifies";
					}

					if (!isDuplicateUI)
					{
						F_FASC* orgF_AFSC = new F_FASC();
						orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
						orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
						orgF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, L"updatedInformation");;
						orgF_AFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)orgRoleNameUI);;
						orgF_AFSC->m_faui = 1;

						orgFr->m_fasc.push_back(orgF_AFSC);
					}
					else
					{
						checkAFSCUI->m_nfac = ENC_S101_Factory::GetFACS(m_cell, L"updatedInformation");;
						checkAFSCUI->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)orgRoleNameUI);;
						checkAFSCUI->m_faui = 1;
					} 


				}
				else { 
					FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second); 
					auto orgFBItor = orgFT->featureBinding.find(objFeatureName);
					if (orgFBItor == orgFT->featureBinding.end())		continue;
					FeatureBinding* orgFB = &orgFBItor->second; 
					FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second);  
					auto objFBItor = objFT->featureBinding.find(orgFeatureName);
					if (objFBItor == objFT->featureBinding.end())		continue;
					FeatureBinding* objFB = &objFBItor->second;  
					wstring objAssociationName = objFB->association.Getvalue();
					if (objAssociationName.compare(L"") == 0)
					{
						for (auto itor = objFB->association.Getattributes().begin();
							itor != objFB->association.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								objAssociationName = attr->Getvalue();
							}
						}
					} 
					wstring objRoleName = objFB->role.Getvalue();
					if (objRoleName.compare(L"") == 0)
					{
						for (auto itor = objFB->role.Getattributes().begin();
							itor != objFB->role.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								objRoleName = attr->Getvalue();
							}
						}
					}

					bool isDuplicate = false; 
					F_FASC* checkAFSC = NULL;
					for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
					{
						checkAFSC = *itt;
						if (checkAFSC->m_name.RCID == orgFr->m_frid.m_name.RCID &&
							checkAFSC->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
						{
							isDuplicate = true;
							break;
						}
					} 
					if (!isDuplicate)
					{
						F_FASC* objF_AFSC = new F_FASC(); 
						objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
						objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
						objF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, objAssociationName);;
						objF_AFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, objRoleName);;
						objF_AFSC->m_faui = 1; 
						objFr->m_fasc.push_back(objF_AFSC);
					} 
					else
					{
						checkAFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, objAssociationName);
						checkAFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, objRoleName);
						checkAFSC->m_faui = 1;
					}


					wstring orgAssociationName = orgFB->association.Getvalue();
					if (orgAssociationName.compare(L"") == 0)
					{
						for (auto itor = orgFB->association.Getattributes().begin();
							itor != orgFB->association.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgAssociationName = attr->Getvalue();
							}
						}
					}


					wstring orgRoleName = orgFB->role.Getvalue();
					if (orgRoleName.compare(L"") == 0)
					{
						for (auto itor = orgFB->role.Getattributes().begin();
							itor != orgFB->role.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgRoleName = attr->Getvalue();
							}
						}
					}

					isDuplicate = false;
					checkAFSC = NULL;
					for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
					{
						checkAFSC = *itt;
						if (checkAFSC->m_name.RCID == objFr->m_frid.m_name.RCID &&
							checkAFSC->m_name.RCNM == objFr->m_frid.m_name.RCNM)
						{
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate)
					{
						F_FASC* orgF_AFSC = new F_FASC();
						orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
						orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
						orgF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, orgAssociationName);;
						orgF_AFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, orgRoleName);;
						orgF_AFSC->m_faui = 1;

						orgFr->m_fasc.push_back(orgF_AFSC);
					}
					else
					{
						checkAFSC->m_nfac = ENC_S101_Factory::GetFACS(m_cell, orgAssociationName);;
						checkAFSC->m_narc = ENC_S101_Factory::GetARCS(m_cell, orgRoleName);;
						checkAFSC->m_faui = 1;
					}
				}

			}

			}

		}

	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process end"));
} 
void CDialogExCreateAutoRelation::OnMenuAutoRelationInformation(CStringArray* featureArr)
{
	
	pView = theApp.pView; 
	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process start")); 
	NewFeatureManager *nfm = pView->m_pNewFeatureManager; 
	S101Layer *l = (S101Layer *)m_cell->m_pLayer; 
	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second; 
	int sidx = 0, cidx = 0;
	CString sfrid, cfrid; 
	for (int i = 0; i < featureArr->GetSize(); i++)
	{

		int nTokenPos = 0; 
		CString strToken = featureArr->GetAt(i).Tokenize(_T("|||"), nTokenPos); 
		if (strToken != L"") {

			CString cs = featureArr->GetAt(i);
			std::string str1 = std::string(CT2CA(cs.operator LPCWSTR()));
			char toks[4] = { "|||" };
			string * tok = StringSplitInformation(str1, toks); 
			cfrid = CString::CStringT(CA2CT(tok[0].c_str())); 
			sfrid = CString::CStringT(CA2CT(tok[1].c_str()));  
			__int64 sfridN = _tcstoui64(sfrid, NULL, 10);
			__int64 skey = ((__int64)100) << 32 | sfridN; 
			R_FeatureRecord *orgFr = m_cell->m_feaMap.PLookup(skey)->value;  
			if (cfrid != L"" && cfrid != sfrid) {

				__int64 cfridN = _tcstoui64(cfrid, NULL, 10);
				__int64 ckey = ((__int64)150) << 32 | cfridN; 
				R_InformationRecord *objFr = m_cell->m_infMap.PLookup(ckey)->value;  
				auto orgFtItor = m_cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
				if (orgFtItor == m_cell->m_dsgir.m_ftcs->m_arr.end())  break;
				wstring orgFeatureName = orgFtItor->second->m_code; 
				auto objFtItor = m_cell->m_dsgir.m_itcs->m_arr.find(objFr->m_irid.m_nitc);
				if (objFtItor == m_cell->m_dsgir.m_itcs->m_arr.end())  continue;
				wstring objFeatureName = objFtItor->second->m_code; 
				if ((orgFeatureName == L"NauticalInformation" || objFeatureName == L"NauticalInformation") && objFeatureName != orgFeatureName) { 
					bool isDuplicateUI = false;
					CString objRoleNameUI;
					CString orgRoleNameUI;

					F_INAS* checkINASUI = NULL;

					for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
					{
						checkINASUI = *itt;
						if (checkINASUI->m_name.RCID == orgFr->m_frid.m_name.RCID &&
							checkINASUI->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (objFeatureName == L"NauticalInformation"){
						objRoleNameUI = L"informationProvidedFor";
					}
					else {
						objRoleNameUI = L"providesInformation";
					}

					if (!isDuplicateUI)
					{
						F_INAS* objF_INAS = new F_INAS();

						objF_INAS->m_name.RCID = orgFr->m_frid.m_name.RCID;
						objF_INAS->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
						objF_INAS->m_niac = ENC_S101_Factory::GetIACS(m_cell, L"additionalInformation");
						objF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)objRoleNameUI);
						objF_INAS->m_iuin = 1;

						objFr->m_inas.push_back(objF_INAS);
					}
					else {
						checkINASUI->m_niac = ENC_S101_Factory::GetIACS(m_cell, L"additionalInformation");
						checkINASUI->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)objRoleNameUI);
						checkINASUI->m_iuin = 1;
					}



					isDuplicateUI = false;
					checkINASUI = NULL;
					for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
					{
						checkINASUI = *itt;
						if (checkINASUI->m_name.RCID == objFr->m_irid.m_name.RCID &&
							checkINASUI->m_name.RCNM == objFr->m_irid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (orgFeatureName == L"NauticalInformation"){
						orgRoleNameUI = L"providesInformation";
					}
					else {
						orgRoleNameUI = L"informationProvidedFor";
					}

					if (!isDuplicateUI)
					{
						F_INAS* orgF_INAS = new F_INAS();
						orgF_INAS->m_name.RCID = objFr->m_irid.m_name.RCID;
						orgF_INAS->m_name.RCNM = objFr->m_irid.m_name.RCNM;
						orgF_INAS->m_niac = ENC_S101_Factory::GetIACS(m_cell, L"additionalInformation");;
						orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)orgRoleNameUI);;
						orgF_INAS->m_iuin = 1;

						orgFr->m_inas.push_back(orgF_INAS);
					}
					else
					{
						checkINASUI->m_niac = ENC_S101_Factory::GetIACS(m_cell, L"additionalInformation");;
						checkINASUI->m_narc = ENC_S101_Factory::GetARCS(m_cell, (LPCTSTR)orgRoleNameUI);;
						checkINASUI->m_iuin = 1;
					} 


				}
				else {  
					FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second); 
					auto orgFBItor = orgFT->featureBinding.find(orgFeatureName);
					if (orgFBItor == orgFT->featureBinding.end())		continue;
					FeatureBinding* orgFB = &orgFBItor->second; 
					InformationType *objFT = &(fc->informationTypes.informationType.find(objFeatureName)->second); 
					auto objFBItor = objFT->informationBinding.find(objFeatureName);
					if (objFBItor == objFT->informationBinding.end())		continue; 
					InformationBinding *objFB = &objFBItor->second;  
					wstring objAssociationName = objFB->association.Getvalue();
					if (objAssociationName.compare(L"") == 0)
					{
						for (auto itor = objFB->association.Getattributes().begin();
							itor != objFB->association.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								objAssociationName = attr->Getvalue();
							}
						}
					} 
					wstring objRoleName = objFB->role.Getvalue();
					if (objRoleName.compare(L"") == 0)
					{
						for (auto itor = objFB->role.Getattributes().begin();
							itor != objFB->role.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								objRoleName = attr->Getvalue();
							}
						}
					}



					bool isDuplicate = false; 
					F_INAS* checkINAS = NULL;
					for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
					{
						checkINAS = *itt;
						if (checkINAS->m_name.RCID == orgFr->m_frid.m_name.RCID &&
							checkINAS->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
						{
							isDuplicate = true;
							break;
						}
					} 
					if (!isDuplicate)
					{
						F_INAS* objF_INAS = new F_INAS(); 
						objF_INAS->m_name.RCID = orgFr->m_frid.m_name.RCID;
						objF_INAS->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
						objF_INAS->m_niac = ENC_S101_Factory::GetFACS(m_cell, objAssociationName);;
						objF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, objRoleName);;
						objF_INAS->m_iuin = 1; 
						objFr->m_inas.push_back(objF_INAS);
					} 
					else
					{
						checkINAS->m_niac = ENC_S101_Factory::GetFACS(m_cell, objAssociationName);
						checkINAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, objRoleName);
						checkINAS->m_iuin = 1;
					}


					wstring orgAssociationName = orgFB->association.Getvalue();
					if (orgAssociationName.compare(L"") == 0)
					{
						for (auto itor = orgFB->association.Getattributes().begin();
							itor != orgFB->association.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgAssociationName = attr->Getvalue();
							}
						}
					}


					wstring orgRoleName = orgFB->role.Getvalue();
					if (orgRoleName.compare(L"") == 0)
					{
						for (auto itor = orgFB->role.Getattributes().begin();
							itor != orgFB->role.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgRoleName = attr->Getvalue();
							}
						}
					}

					isDuplicate = false;
					checkINAS = NULL;
					for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
					{
						checkINAS = *itt;
						if (checkINAS->m_name.RCID == objFr->m_irid.m_name.RCID &&
							checkINAS->m_name.RCNM == objFr->m_irid.m_name.RCNM)
						{
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate)
					{
						F_INAS* orgF_INAS = new F_INAS();
						orgF_INAS->m_name.RCID = objFr->m_irid.m_name.RCID;
						orgF_INAS->m_name.RCNM = objFr->m_irid.m_name.RCNM;
						orgF_INAS->m_niac = ENC_S101_Factory::GetFACS(m_cell, orgAssociationName);;
						orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, orgRoleName);;
						orgF_INAS->m_iuin = 1;

						orgFr->m_inas.push_back(orgF_INAS);
					}
					else
					{
						checkINAS->m_niac = ENC_S101_Factory::GetFACS(m_cell, orgAssociationName);;
						checkINAS->m_narc = ENC_S101_Factory::GetARCS(m_cell, orgRoleName);;
						checkINAS->m_iuin = 1;
					}

				}

			}

		}
	}
	
	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process end"));
	
}

string* CDialogExCreateAutoRelation::StringSplitInformation(string strTarget, string strTok)
{
	int     nCutPos;
	int     nIndex = 0;
	string* strResult = new string[100];

	while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
	{
		if (nCutPos > 0)
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}
		strTarget = strTarget.substr(nCutPos + 1);
	}

	if (strTarget.length() > 0)
	{
		strResult[nIndex++] = strTarget.substr(0, nCutPos);
	}

	return strResult;
}

void CDialogExCreateAutoRelation::OnLvnItemchangedListCreateAutoRelationList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	*pResult = 0;
}
