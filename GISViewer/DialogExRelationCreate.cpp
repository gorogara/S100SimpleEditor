// CDialogExRelationCreate.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "DialogExRelationCreate.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include <iostream>
#include <locale.h>

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogExRelationCreate, CDialogEx)


CDialogExRelationCreate::CDialogExRelationCreate(CWnd* pParent )
	: CDialogEx(CDialogExRelationCreate::IDD, pParent)
{


}

CDialogExRelationCreate::~CDialogExRelationCreate()
{
}

void CDialogExRelationCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDialogExRelationCreate, CDialogEx)
	ON_COMMAND(IDD_DIALOG_RELATION_CREATE, &CDialogExRelationCreate::OnIddDialogRelationCreate)
	ON_BN_CLICKED(IDCANCEL, &CDialogExRelationCreate::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDialogExRelationCreate::OnBnClickedOk)
END_MESSAGE_MAP() 
void CDialogExRelationCreate::OnIddDialogRelationCreate()
{
}

#pragma warning(disable:4129)



void CDialogExRelationCreate::OnBnClickedCancel()
{ 
	CDialogEx::OnCancel();
} 
BOOL CDialogExRelationCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	return true;
	
}




void CDialogExRelationCreate::OnBnClickedOk()
{          


	CDialog *dlg = new CDialog(IDD_DIALOG_RELATION_INFO, this);
	if (IDOK == dlg->DoModal()){

		NewFeatureManager *nfm = ((CGISViewerView *)pView)->m_pNewFeatureManager; 
		R_FeatureRecord* orgFr = NULL; 
		R_FeatureRecord* objFr = NULL;
		S101Cell* cell = (S101Cell*)nfm->m_cell;
		S101Layer* layer = (S101Layer*)nfm->m_cell->m_pLayer;
		FeatureCatalogue *fc = layer->GetFC()->m_pCatalogueList.begin()->second;

		auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
		if (objFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  return;
		wstring objFeatureName = objFtItor->second->m_code;

		auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  return;
		wstring orgFeatureName = orgFtItor->second->m_code;

		FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second);
		auto objFBItor = objFT->featureBinding.find(orgFeatureName);
		if (objFBItor == objFT->featureBinding.end())		return;
		FeatureBinding* objFB = &objFBItor->second;

		FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);
		auto orgFBItor = orgFT->featureBinding.find(objFeatureName);
		if (orgFBItor == orgFT->featureBinding.end())		return;
		FeatureBinding* orgFB = &orgFBItor->second; 

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

		auto objAssocItor = cell->m_dsgir.m_facs->m_arrFindForCode.find(objAssociationName);
		auto objRoleItor = cell->m_dsgir.m_arcs->m_arrFindForCode.find(objRoleName);

		CodeWithNumericCode *objAssoc = objAssocItor->second;
		CodeWithNumericCode *objRole = objRoleItor->second;

		F_FASC* objF_AFSC = new F_FASC();
		objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
		objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
		objF_AFSC->m_nfac = objAssoc->m_nmcd;
		objF_AFSC->m_narc = objRole->m_nmcd;
		objF_AFSC->m_faui = 1;

		objFr->m_fasc.push_back(objF_AFSC);


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
		auto orgAssocItor = cell->m_dsgir.m_facs->m_arrFindForCode.find(orgAssociationName);
		auto orgRoleItor = cell->m_dsgir.m_arcs->m_arrFindForCode.find(orgRoleName);

		CodeWithNumericCode *orgAssoc = orgAssocItor->second;
		CodeWithNumericCode *orgRole = orgRoleItor->second;

		F_FASC* orgF_AFSC = new F_FASC();
		orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
		orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
		orgF_AFSC->m_nfac = orgAssoc->m_nmcd;
		orgF_AFSC->m_narc = orgRole->m_nmcd;
		orgF_AFSC->m_faui = 1;

		orgFr->m_fasc.push_back(orgF_AFSC);
	}
	else {

	}
}
