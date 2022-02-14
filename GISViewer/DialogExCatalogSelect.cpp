// DialogExCatalogSelect.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExCatalogSelect.h"
#include "afxdialogex.h"

#include "GISLibrary\\LayerManager.h"
#include "GISLibrary\\CatalogItem.h"

#include "../FeatureCatalog/FeatureCatalogue.h" 

bool CDialogExCatalogSelect::OpenFileMode = false;
IMPLEMENT_DYNAMIC(CDialogExCatalogSelect, CDialogEx)

CDialogExCatalogSelect::CDialogExCatalogSelect(CWnd* pParent )
	: CDialogEx(CDialogExCatalogSelect::IDD, pParent)
{ 
	m_selectedCatalog = NULL;
	m_selectedIndex = -1;


}

CDialogExCatalogSelect::~CDialogExCatalogSelect()
{
	for (auto itor = m_catalogItems.begin(); itor != m_catalogItems.end(); itor++)
	{
		delete (*itor);
	}
}

void CDialogExCatalogSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, SELECTPCFCBUTTON, SeletButton);
}


BEGIN_MESSAGE_MAP(CDialogExCatalogSelect, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDialogExCatalogSelect::OnBnClickedOk) 
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CATALOG_SELECT, &CDialogExCatalogSelect::OnLvnItemchangedListObject) 
	ON_BN_CLICKED(SELECTPCFCBUTTON, &CDialogExCatalogSelect::OnBnClickedSelectpcfcbutton)
END_MESSAGE_MAP() 


void CDialogExCatalogSelect::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CStatic* pGroupFileName = (CStatic*)GetDlgItem(IDC_STATIC_NEW_ENC_FILENAME);
	CEdit* pEditFileName = (CEdit*)GetDlgItem(IDC_EDIT_NEW_ENC_FILENAME);

	CStatic* pGroupCatalog = (CStatic*)GetDlgItem(IDC_STATIC_SEL_CATALOG);
	CListCtrl* pListCtrlCatalog = (CListCtrl*)GetDlgItem(IDC_LIST_CATALOG_SELECT);
	CButton* pOKButton = (CButton*)GetDlgItem(IDOK);
	CButton* pSELECTButton = (CButton*)GetDlgItem(SELECTPCFCBUTTON);

	if (pGroupFileName->GetSafeHwnd())
	{
		pGroupFileName->MoveWindow(0, 0, cx, 60);
	}

	if (pEditFileName->GetSafeHwnd())
	{
		pEditFileName->MoveWindow(5, 15, cx - 10, 40);
	}

	if (pGroupCatalog->GetSafeHwnd())
	{
		pGroupCatalog->MoveWindow(0, 60, cx, cy);
	}

	if (pListCtrlCatalog->GetSafeHwnd())
	{
		pListCtrlCatalog->MoveWindow(5, 75, cx - 10, cy - 135);

		pListCtrlCatalog->SetColumnWidth(0, (cx - 10) * 2 / 3);
		pListCtrlCatalog->SetColumnWidth(1, (cx - 10) / 3);  
	} 
	if (pOKButton->GetSafeHwnd())
	{
		pOKButton->MoveWindow((cx / 2)+2, cy - 40, (cx / 2) - 5, 30);
	} 
	if (pSELECTButton->GetSafeHwnd())
	{ 
		pSELECTButton->MoveWindow(5, cy -40, (cx/2)-5, 30);
	}
}

BOOL CDialogExCatalogSelect::OnInitDialog() 
{ 
	CDialogEx::OnInitDialog();

	SeletButton.ShowWindow(SW_HIDE); 
	CListCtrl* pListCtrlCatalog = (CListCtrl*)GetDlgItem(IDC_LIST_CATALOG_SELECT);

	CEdit* pEditFileName = (CEdit*)GetDlgItem(IDC_EDIT_NEW_ENC_FILENAME);
	pEditFileName->SetWindowText(m_fileName); 

	if (pListCtrlCatalog->GetSafeHwnd())
	{
		pListCtrlCatalog->SetExtendedStyle(LVS_EX_FULLROWSELECT);

		pListCtrlCatalog->InsertColumn(0, _T("Catalog Name"), LVCFMT_LEFT);
		pListCtrlCatalog->InsertColumn(1, _T("Version"), LVCFMT_LEFT);

	}  
	int iScreenCx = GetSystemMetrics(SM_CXSCREEN);
	int iScreenCy = GetSystemMetrics(SM_CYSCREEN);

	int width = 300;
	int height = 600;
	int l = (iScreenCx) / 2 - width / 2;
	int t = (iScreenCy) / 2 - height / 2;

	this->MoveWindow(l, t, width, height);


	for (auto itor = LayerManager::pS100Catalogs->begin(); 
		itor != LayerManager::pS100Catalogs->end();
		itor++)
	{
		Catalog* c = *itor;

		if (OpenFileMode != true) 
		{
			SeletButton.ShowWindow(SW_HIDE);
			if (wcscmp(c->m_pCatalogueList.begin()->first.c_str(), L"S-102") == 0||
				wcscmp(c->m_pCatalogueList.begin()->first.c_str(), L"S-111") == 0||
				wcscmp(c->m_pCatalogueList.begin()->first.c_str(), L"S-413") == 0) 
			{ 
			}
			else 
			{
				CatalogItem* ci = new CatalogItem();
				ci->m_catalog = c;
				ci->m_name = c->m_pCatalogueList.begin()->first.c_str();
				ci->m_version = c->m_pCatalogueList.begin()->second->versionNumber.c_str();
				
				m_catalogItems.push_back(ci);
			}
		}
		else 
		{
			SeletButton.ShowWindow(SW_SHOW);
			CatalogItem* ci = new CatalogItem();
			ci->m_catalog = c;
			ci->m_name = c->m_pCatalogueList.begin()->first.c_str();
			ci->m_version = c->m_pCatalogueList.begin()->second->versionNumber.c_str(); 
			m_catalogItems.push_back(ci);
		}
	}

	SetCatalogListCtrl();
	OpenFileMode = false;



	return true;  
	
}

void CDialogExCatalogSelect::OnBnClickedOk()
{
	CEdit* pEditFileName = (CEdit*)GetDlgItem(IDC_EDIT_NEW_ENC_FILENAME);
	pEditFileName->GetWindowText(m_fileName); 
	CDialogEx::OnOK();
}




void CDialogExCatalogSelect::SetCatalogListCtrl()
{
	CListCtrl* pListCtrlObject = (CListCtrl*)GetDlgItem(IDC_LIST_CATALOG_SELECT); 
	int cnt = 0;
	if (pListCtrlObject->GetSafeHwnd())
	{
		for (auto itor = m_catalogItems.rbegin(); itor != m_catalogItems.rend(); itor++)
		{
			CatalogItem *item = (CatalogItem *)*itor;

			pListCtrlObject->InsertItem(cnt, item->m_name);
			pListCtrlObject->SetItemText(cnt, 1, item->m_version);
		}
	}
}

void CDialogExCatalogSelect::OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult) 
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	if (pNMLV->uChanged & LVIF_STATE)
	{
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED))
		{
			if (pNMLV->iItem < 0) 
			{
				return;
			}
			CatalogItem* pItem = m_catalogItems[pNMLV->iItem];
			PortrayalCatalogue* pcitem = (*LayerManager::pPortrayalCatalogues)[pNMLV->iItem];
			m_selectedCatalog = pItem->m_catalog;
			m_selectedIndex = pNMLV->iItem;

		}
	}
	*pResult = 0;
}

void CDialogExCatalogSelect::OnBnClickedSelectpcfcbutton()
{
	m_selectedIndex = -10000000;
	CDialogEx::OnOK();
}
