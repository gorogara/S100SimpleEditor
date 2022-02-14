// AddFeatureSelectDlg.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogOriginFeatureSelect.h"
#include "afxdialogex.h"

#include "GISLibrary\\NewFeatureManager.h" 

IMPLEMENT_DYNAMIC(CDialogOriginFeatureSelect, CDialogEx)

CDialogOriginFeatureSelect::CDialogOriginFeatureSelect(CWnd* pParent )
	: CDialogEx(CDialogOriginFeatureSelect::IDD, pParent)
{

}

CDialogOriginFeatureSelect::~CDialogOriginFeatureSelect()
{
}

void CDialogOriginFeatureSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogOriginFeatureSelect, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDialogOriginFeatureSelect::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ADD_FEATURE_SELECT, &CDialogOriginFeatureSelect::OnLvnItemchangedListObject)
END_MESSAGE_MAP() 


void CDialogOriginFeatureSelect::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CStatic* pGroupFeatureList = (CStatic*)GetDlgItem(IDC_STATIC_ADD_FEATURE_SELECT);
	CListCtrl* pListCtrlFeatureList = (CListCtrl*)GetDlgItem(IDC_LIST_ADD_FEATURE_SELECT);
	CButton* pOKButton = (CButton*)GetDlgItem(IDOK);

	if (pGroupFeatureList->GetSafeHwnd())
	{
		pGroupFeatureList->MoveWindow(0, 0, cx, cy);
	}

	if (pListCtrlFeatureList->GetSafeHwnd())
	{
		pListCtrlFeatureList->MoveWindow(5, 35, cx - 10, cy - 75);

		CRect rect;
		pListCtrlFeatureList->GetClientRect(rect);

		pListCtrlFeatureList->SetColumnWidth(0, rect.Width());  
	}

	if (pOKButton->GetSafeHwnd())
	{
		pOKButton->MoveWindow(5, cy - 40, cx - 10, 30);
	}
}

BOOL CDialogOriginFeatureSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	CListCtrl* pListCtrlFeatureList = (CListCtrl*)GetDlgItem(IDC_LIST_ADD_FEATURE_SELECT);

	if (pListCtrlFeatureList->GetSafeHwnd())
	{
		pListCtrlFeatureList->SetExtendedStyle(LVS_EX_FULLROWSELECT);

		pListCtrlFeatureList->InsertColumn(0, _T("Feature Name"), LVCFMT_LEFT, 1, 1);
	}

	CRect r;
	::GetClientRect(::GetParent(this->GetSafeHwnd()), r);

	int width = 300;
	int height = 600;
	int l = (r.right - r.left) / 2 - width / 2;
	int t = (r.bottom - r.top) / 2 - height / 2;

	this->MoveWindow(l, t, width, height);

	SetCatalogListCtrl();

	return TRUE;  
}

void CDialogOriginFeatureSelect::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CDialogOriginFeatureSelect::SetCatalogListCtrl()
{
	CListCtrl* pListCtrlFeatureList = (CListCtrl*)GetDlgItem(IDC_LIST_ADD_FEATURE_SELECT); 
	int cnt = 0;
	if (pListCtrlFeatureList->GetSafeHwnd())
	{
		for (auto itor = m_pNewFeatureManager->m_pPickedFeatureRecords.rbegin(); itor != m_pNewFeatureManager->m_pPickedFeatureRecords.rend(); itor++)
		{
			S100NamedFeature* namedFeature = &(*itor);

			pListCtrlFeatureList->InsertItem(cnt, namedFeature->m_name.c_str());
		}
	}
}


void CDialogOriginFeatureSelect::OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	if (pNMLV->uChanged & LVIF_STATE)
	{
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED))
		{
			if (pNMLV->iItem < 0)
				return;

			S100NamedFeature pItem = m_pNewFeatureManager->m_pPickedFeatureRecords[pNMLV->iItem];
			m_pNewFeatureManager->m_pOrgFeatureRecord = pItem.m_fe;
		}
	}

	*pResult = 0;
}
