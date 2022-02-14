// DialogDockLayerManager.cpp : implementation file

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogDockRelation.h"
#include "DialogExRelationView.h"
#include "GISViewerView.h"
#include "afxdialogex.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

using namespace std;
IMPLEMENT_DYNAMIC(CDialogDockRelation, CDialog)

CDialogDockRelation::CDialogDockRelation(CWnd* pParent )
: CDialog(CDialogDockRelation::IDD, pParent)
{
	nSelectedItem = -1;
}

CDialogDockRelation::~CDialogDockRelation()
{
}

void CDialogDockRelation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RELATION, m_ListRelation);
}


BEGIN_MESSAGE_MAP(CDialogDockRelation, CDialog)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDOK, &CDialogDockRelation::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogDockRelation::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RELATION, &CDialogDockRelation::OnLvnItemchangedList)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_NOTIFY(NM_CLICK, IDC_LIST_RELATION, &CDialogDockRelation::OnNMClickListLm)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RELATION, &CDialogDockRelation::OnNMDblclkListLm)
END_MESSAGE_MAP() 
int CDialogDockRelation::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CDialogDockRelation::OnBnClickedOk()
{ 
	return;
}


void CDialogDockRelation::OnBnClickedCancel()
{ 
	return;
}


void CDialogDockRelation::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 

	*pResult = 0;



}


void CDialogDockRelation::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CDialogDockRelation::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
} 
BOOL CDialogDockRelation::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	m_ListRelation.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListRelation.GetWindowRect(listRect);

	m_ListRelation.InsertColumn(0, _T("Type"), LVCFMT_LEFT, (int)(listRect.Width()*0.1)); 
	m_ListRelation.InsertColumn(1, _T("Relation name"), LVCFMT_LEFT, (int)(listRect.Width()*0.2)); 
	m_ListRelation.InsertColumn(2, _T("Feature Name"), LVCFMT_CENTER, (int)(listRect.Width()*0.25));
	m_ListRelation.InsertColumn(3, _T("Feature ID"), LVCFMT_LEFT, (int)(listRect.Width()*0));
	m_ListRelation.InsertColumn(4, _T("Role"), LVCFMT_CENTER, (int)(listRect.Width()*0.15));
	m_ListRelation.InsertColumn(5, _T("Association Feature Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.25)); 
	m_ListRelation.InsertColumn(6, _T("Association Feature ID"), LVCFMT_LEFT, (int)(listRect.Width()*0));

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	AdjustLayout();


	return TRUE; 

}

void CDialogDockRelation::UpdateList()
{
	m_ListRelation.DeleteAllItems();

}

void CDialogDockRelation::OnNMClickListLm(NMHDR *pNMHDR, LRESULT *pResult)
{ 

}

void CDialogDockRelation::OnNMDblclkListLm(NMHDR *pNMHDR, LRESULT *pResult)
{

	POSITION pos = m_ListRelation.GetFirstSelectedItemPosition();
	int idx = 0;
	idx = m_ListRelation.GetNextSelectedItem(pos);
	if (idx < 0)
	{
		return;
	}
	

	CString type;

	type.Format(m_ListRelation.GetItemText(idx, 0));
	if (type=="Feature")
	{
		OnMenuRelationView();
	}
	else if (type=="Information")
	{
		OnMenuRelationViewInformation();
	}
	
}


void CDialogDockRelation::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);

	CRect      rectENCs;

	if (m_ListRelation.GetSafeHwnd())
	{
		rectENCs = CRect(rectClient.left, rectClient.top, rectClient.Size().cx, rectClient.Size().cy);
		m_ListRelation.MoveWindow(rectENCs);						
		m_ListRelation.SetColumnWidth(0, (int)(rectENCs.Width()*0.1)); 
		m_ListRelation.SetColumnWidth(1, (int)(rectENCs.Width()*0.2)); 
		m_ListRelation.SetColumnWidth(2, (int)(rectENCs.Width()*0.25)); 
		m_ListRelation.SetColumnWidth(3, (int)(rectENCs.Width()*0)); 
		m_ListRelation.SetColumnWidth(4, (int)(rectENCs.Width()*0.15)); 
		m_ListRelation.SetColumnWidth(5, (int)(rectENCs.Width()*0.25)); 
		m_ListRelation.SetColumnWidth(6, (int)(rectENCs.Width()*0)); 
	}

}


void CDialogDockRelation::OnMenuRelationView()
{ 
	CDialogExRelationView *dlg = new CDialogExRelationView(this);
	dlg->m_cell = m_cell;

	POSITION pos = m_ListRelation.GetFirstSelectedItemPosition();
	int idx = 0; 
	CString frid;
	CString tfrid;
	CString assoName;
	
	idx = m_ListRelation.GetNextSelectedItem(pos);
	if (idx < 0) return;

	assoName.Format(m_ListRelation.GetItemText(idx, 1));

	frid.Format(m_ListRelation.GetItemText(idx, 6));
	tfrid.Format(m_ListRelation.GetItemText(idx, 3));

	__int64 fridN = _tcstoui64(frid, NULL, 10);
	__int64 tfridN = _tcstoui64(tfrid, NULL, 10); 
	__int64 key = ((__int64)100) << 32 | fridN;
	__int64 tkey = ((__int64)100) << 32 | tfridN;

	dlg->m_viewMode = "Feature";
	dlg->m_fr = m_cell->m_feaMap.PLookup(key)->value;
	dlg->m_tfr = m_cell->m_feaMap.PLookup(tkey)->value; 
	dlg->m_assoName = assoName; 
}


void CDialogDockRelation::OnMenuRelationViewInformation()
{  
	CDialogExRelationView *dlg = new CDialogExRelationView(this);
	dlg->m_cell = m_cell;

	POSITION pos = m_ListRelation.GetFirstSelectedItemPosition();
	int idx = 0;

	CString frid;
	CString tfrid;
	CString orgName;
	CString assoName;

	idx = m_ListRelation.GetNextSelectedItem(pos);
	if (idx < 0)
	{
		return;
	}

	assoName.Format(m_ListRelation.GetItemText(idx, 1));
	
	orgName.Format(m_ListRelation.GetItemText(idx, 2)); 
	frid.Format(m_ListRelation.GetItemText(idx, 3)); 
	tfrid.Format(m_ListRelation.GetItemText(idx, 6)); 
	
	__int64 fridN = _tcstoui64(frid, NULL, 10);
	__int64 tfridN = _tcstoui64(tfrid, NULL, 10); 
	if (orgName.Find(L"ContactDetails") != -1 || orgName.Find(L"NauticalInformation") != -1 || orgName.Find(L"NonStandardWorkingDay") != -1 
		|| orgName.Find(L"ServiceHours") != -1 || orgName.Find(L"SpatialQuality") != -1 )
	{

		__int64 key = ((__int64)150) << 32 | fridN; 
		__int64 tkey = ((__int64)100) << 32 | tfridN; 

		dlg->m_viewMode = "Information1";
		dlg->m_ifr = m_cell->m_infMap.PLookup(key)->value; 
		dlg->m_tifr = m_cell->m_feaMap.PLookup(tkey)->value; 

	} 
	else
	{

		__int64 key = ((__int64)100) << 32 | fridN; 
		__int64 tkey = ((__int64)150) << 32 | tfridN; 

		dlg->m_viewMode = "Information2";
		dlg->m_ifr1 = m_cell->m_feaMap.PLookup(key)->value; 
		dlg->m_tifr1 = m_cell->m_infMap.PLookup(tkey)->value; 

	} 
	dlg->m_assoName = assoName; 
}

void CDialogDockRelation::SetFeatureList(S101Cell* cell, std::list<R_FeatureRecord*> flist, std::list<R_InformationRecord*> infoList)
{
	m_cell = cell; 
	m_ListRelation.DeleteAllItems();

	FeatureCatalogue *fc = ((S101Layer*)cell->m_pLayer)->GetFC()->m_pCatalogueList.begin()->second;

	for (auto ri = flist.begin(); ri != flist.end(); ri++)
	{
		R_FeatureRecord *orgFr = *ri; 

		auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())
		{
			continue;
		}

		wstring orgFeatureName = orgFtItor->second->m_code;

		auto fit = fc->featureTypes.featureType.find(orgFeatureName);
		if (fit == fc->featureTypes.featureType.end())
		{
			CString msg;
			msg.Format(L"[%s] Feature not found. -REALATION", orgFeatureName.c_str());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, msg,KRS_MSG_PROCESS::User_Developer_Mode,KRS_MSG_PROCESS::FC);
			continue;
		}

		FeatureType *orgFT = &(fit->second); 
		int count = orgFr->m_fasc.size();
		for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
		{
			F_FASC *fasc = *itt;

			auto orgfaItor = cell->m_dsgir.m_facs->m_arr.find(fasc->m_nfac);
			if (orgfaItor == cell->m_dsgir.m_facs->m_arr.end())
			{
				continue;
			}

		    CString faName = orgfaItor->second->m_code;

			auto orgarItor = cell->m_dsgir.m_arcs->m_arr.find(fasc->m_narc);
			if (orgarItor == cell->m_dsgir.m_arcs->m_arr.end())
			{
			
				continue;
			}

			CString arName = orgarItor->second->m_code;

			auto orgFBItor = orgFT->featureBinding.find(orgFeatureName);
			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			LVITEM firstItem = { 0 };
			m_ListRelation.InsertItem(&firstItem); 

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L""; 
			int n_code = orgFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(n_code);
			auto ws_objectCode1 = itor->second->m_code.GetBuffer();
			itor->second->m_code.ReleaseBuffer();
			auto fc_featureTypeORG = fc->GetFeatureType(ws_objectCode1);
			auto fc_featureAssociation = fc->GetFeatureAssociation(orgAssociationName);
			auto fc_role = fc->GetRole(orgRoleName);

			__int64 key = ((__int64)100) << 32 | fasc->m_name.RCID;

			auto associatedFeature = m_cell->m_feaMap.PLookup(key);
			if (associatedFeature == nullptr)
			{
				CString msg;
				msg.Format(L"[%s] Feature not found. -REALATION", faName);
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::FC);
				int i = 0;
				continue;
			}

			R_FeatureRecord* rfr = m_cell->m_feaMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);
			auto ws_objectCode2 = itors->second->m_code.GetBuffer();
			itors->second->m_code.ReleaseBuffer();
			auto fc_informationTypeOBJ = fc->GetFeatureType(ws_objectCode2); 

			if(fc_featureTypeORG)
				colOrgFeatureName.Format(_T("%s (%d)"), fc_featureTypeORG->name.c_str(), orgFr->m_frid.m_name.RCID);
			else
				colOrgFeatureName.Format(_T("%s (%d)"), ws_objectCode1, orgFr->m_frid.m_name.RCID); 
			if(fc_featureAssociation)
				colOrgAssociationName.Format(_T("%s"), fc_featureAssociation->name.c_str());
			else
				colOrgAssociationName.Format(_T("%s"), orgAssociationName); 
			if(fc_role)
				colOrgAssociationRole.Format(_T("%s"), fc_role->name.c_str());
			else 
				colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str()); 
			if(fc_informationTypeOBJ)
				colAssociationFeatureName.Format(_T("%s (%d)"), fc_informationTypeOBJ->name.c_str(), fasc->m_name.RCID);
			else 
				colAssociationFeatureName.Format(_T("%s (%d)"), ws_objectCode2, fasc->m_name.RCID); 

			colOrgFeatureId.Format(_T("%d"), orgFr->m_frid.m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), fasc->m_name.RCID); 
			m_ListRelation.SetItemText(0, 0, L"Feature");
			m_ListRelation.SetItemText(0, 1, colOrgAssociationName); 
			m_ListRelation.SetItemText(0, 2, colOrgFeatureName); 
			m_ListRelation.SetItemText(0, 3, colOrgFeatureId); 
			m_ListRelation.SetItemText(0, 4, colOrgAssociationRole); 
			m_ListRelation.SetItemText(0, 5, colAssociationFeatureName);  
			m_ListRelation.SetItemText(0, 6, colAssociationFeatureId);  

			UpdateData(false);

		} 
		for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
		{
			F_INAS *inas = *itt;

			auto orgfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (orgfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = orgfaItor->second->m_code;

			auto orgarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (orgarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = orgarItor->second->m_code;

			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			LVITEM firstItem = { 0 };
			m_ListRelation.InsertItem(&firstItem); 

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L""; 
			int n_code = orgFr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(n_code);
			auto ws_objectCode1 = itor->second->m_code.GetBuffer();
			itor->second->m_code.ReleaseBuffer();
			auto fc_featureType = fc->GetFeatureType(ws_objectCode1);
			auto fc_featureAssociation = fc->GetInformationAssociation(orgAssociationName);
			auto fc_role = fc->GetRole(orgRoleName);

			__int64 key = ((__int64)150) << 32 | inas->m_name.RCID;
			R_InformationRecord* rfr = m_cell->m_infMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_itcs->m_arr.find(rfr->m_irid.m_nitc);
			auto ws_objectCode2 = itors->second->m_code.GetBuffer();
			itors->second->m_code.ReleaseBuffer();
			auto fc_informationType = fc->GetInformationType(ws_objectCode2); 

			if (fc_featureType)
				colOrgFeatureName.Format(_T("%s (%d)"), fc_featureType->name.c_str(), orgFr->m_frid.m_name.RCID);
			else
				colOrgFeatureName.Format(_T("%s (%d)"), ws_objectCode1, orgFr->m_frid.m_name.RCID); 
			if (fc_featureAssociation)
				colOrgAssociationName.Format(_T("%s"), fc_featureAssociation->name.c_str());
			else
				colOrgAssociationName.Format(_T("%s"), orgAssociationName); 
			if (fc_role)
				colOrgAssociationRole.Format(_T("%s"), fc_role->name.c_str());
			else
				colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str()); 
			if (fc_informationType)
				colAssociationFeatureName.Format(_T("%s (%d)"), fc_informationType->name.c_str(), inas->m_name.RCID);
			else
				colAssociationFeatureName.Format(_T("%s (%d)"), ws_objectCode2, inas->m_name.RCID); 


			colOrgFeatureId.Format(_T("%d"), orgFr->m_frid.m_name.RCID);

			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			m_ListRelation.SetItemText(0, 0, L"Information");

			m_ListRelation.SetItemText(0, 1, colOrgAssociationName); 
			m_ListRelation.SetItemText(0, 2, colOrgFeatureName); 
			m_ListRelation.SetItemText(0, 3, colOrgFeatureId); 
			m_ListRelation.SetItemText(0, 4, colOrgAssociationRole); 
			m_ListRelation.SetItemText(0, 5, colAssociationFeatureName); 
			m_ListRelation.SetItemText(0, 6, colAssociationFeatureId); 

			UpdateData(false);
		}
	} 
	for (auto ri = infoList.begin(); ri != infoList.end(); ri++)
	{
		R_InformationRecord *orgIr = *ri; 

		auto orgItItor = cell->m_dsgir.m_itcs->m_arr.find(orgIr->m_irid.m_nitc);
		if (orgItItor == cell->m_dsgir.m_itcs->m_arr.end())  continue;
		wstring orgFeatureName = orgItItor->second->m_code;

		InformationType *orgIt = &(fc->informationTypes.informationType.find(orgFeatureName)->second); 
		for (auto itt = orgIr->m_inas.begin(); itt != orgIr->m_inas.end(); itt++)
		{
			F_INAS *inas = *itt;
			
			auto orgfaItor = cell->m_dsgir.m_iacs->m_arr.find(inas->m_niac);
			if (orgfaItor == cell->m_dsgir.m_iacs->m_arr.end())  continue;
			CString faName = orgfaItor->second->m_code;

			auto orgarItor = cell->m_dsgir.m_arcs->m_arr.find(inas->m_narc);
			if (orgarItor == cell->m_dsgir.m_arcs->m_arr.end())  continue;
			CString arName = orgarItor->second->m_code;

			wstring orgAssociationName = faName;
			wstring orgRoleName = arName;

			LVITEM firstItem = { 0 };
			m_ListRelation.InsertItem(&firstItem); 

			CString colOrgFeatureId = L"";
			CString colOrgFeatureName = L"";
			CString colAssociationFeatureId = L"";
			CString colAssociationFeatureName = L"";
			CString colOrgAssociationName = L"";
			CString colOrgAssociationRole = L""; 
			int n_code = orgIr->m_irid.m_nitc;
			auto itor = cell->m_dsgir.m_itcs->m_arr.find(n_code);
			auto ws_objectCode1 = itor->second->m_code.GetBuffer();
			itor->second->m_code.ReleaseBuffer();
			auto fc_informationTypeORG = fc->GetInformationType(ws_objectCode1);
			auto fc_featureAssociation = fc->GetInformationAssociation(orgAssociationName);
			auto fc_role = fc->GetRole(orgRoleName);

			__int64 key = ((__int64)150) << 32 | inas->m_name.RCID;
			R_InformationRecord* rfr = m_cell->m_infMap.PLookup(key)->value;
			auto itors = cell->m_dsgir.m_itcs->m_arr.find(rfr->m_irid.m_nitc);
			auto ws_objectCode2 = itors->second->m_code.GetBuffer();
			itors->second->m_code.ReleaseBuffer();
			auto fc_informationTypeOBJ = fc->GetInformationType(ws_objectCode2); 

			if (fc_informationTypeORG)
				colOrgFeatureName.Format(_T("%s (%d)"), fc_informationTypeORG->name.c_str(), orgIr->m_irid.m_name.RCID);
			else
				colOrgFeatureName.Format(_T("%s (%d)"), ws_objectCode1, orgIr->m_irid.m_name.RCID); 
			if (fc_featureAssociation)
				colOrgAssociationName.Format(_T("%s"), fc_featureAssociation->name.c_str());
			else
				colOrgAssociationName.Format(_T("%s"), orgAssociationName); 
			if (fc_role)
				colOrgAssociationRole.Format(_T("%s"), fc_role->name.c_str());
			else
				colOrgAssociationRole.Format(_T("%s"), orgRoleName.c_str()); 
			if (fc_informationTypeOBJ)
				colAssociationFeatureName.Format(_T("%s (%d)"), fc_informationTypeOBJ->name.c_str(), inas->m_name.RCID);
			else
				colAssociationFeatureName.Format(_T("%s (%d)"), ws_objectCode2, inas->m_name.RCID); 

			colOrgFeatureId.Format(_T("%d"), orgIr->m_irid.m_name.RCID);
			colAssociationFeatureId.Format(_T("%d"), inas->m_name.RCID); 
			m_ListRelation.SetItemText(0, 0, L"Information");

			m_ListRelation.SetItemText(0, 1, colOrgAssociationName); 
			m_ListRelation.SetItemText(0, 2, colOrgFeatureName); 
			m_ListRelation.SetItemText(0, 3, colOrgFeatureId); 
			m_ListRelation.SetItemText(0, 4, colOrgAssociationRole); 
			m_ListRelation.SetItemText(0, 5, colAssociationFeatureName); 
			m_ListRelation.SetItemText(0, 6, colAssociationFeatureId); 

			UpdateData(false);
 		}
	}
}