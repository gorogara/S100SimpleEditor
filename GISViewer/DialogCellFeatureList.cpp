// DialogCellFeatureList.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "DialogCellFeatureList.h"
#include "afxdialogex.h"
#include "GISViewer.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\R_InformationRecord.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\CodeWithNumericCode.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"

#include <sstream> 

IMPLEMENT_DYNAMIC(CDialogCellFeatureList, CDialogEx)

CDialogCellFeatureList::CDialogCellFeatureList(CWnd* pParent )
	: CDialogEx(CDialogCellFeatureList::IDD, pParent)
{

}

CDialogCellFeatureList::~CDialogCellFeatureList()
{
}

void CDialogCellFeatureList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_LIST_FEATURE_TYPES, m_listFeatureTypes);
	DDX_Control(pDX, IDC_BTN_FEATURE_LIST_REPORT, m_btnReport);
}


BEGIN_MESSAGE_MAP(CDialogCellFeatureList, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FEATURE_TYPES, &CDialogCellFeatureList::OnLvnItemchangedListFeatureTypes)
	ON_BN_CLICKED(IDOK, &CDialogCellFeatureList::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_FEATURE_LIST_REPORT, &CDialogCellFeatureList::OnBnClickedBtnFeatureListReport)
END_MESSAGE_MAP() 


void CDialogCellFeatureList::OnLvnItemchangedListFeatureTypes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}


void CDialogCellFeatureList::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CDialogCellFeatureList::OnClose()
{
	ShowWindow(SW_HIDE); 
}


void CDialogCellFeatureList::PostNcDestroy()
{
	theApp.m_pDialogCellFeatureList = NULL;
	delete this;

	CDialogEx::PostNcDestroy();
}

void CDialogCellFeatureList::SetList()
{
	int iItem = 0;
	m_listFeatureTypes.DeleteAllItems();

	for (auto itor = hash_cft.begin(); itor != hash_cft.end(); itor++)
	{
		CountedFeatureType* cft = &itor->second;
		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = iItem;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(cft->m_pFT->name.c_str());
		lvi.lParam = (LPARAM)cft;

		std::wstringstream wss;
		wss << cft->m_count;
		BOOL ret = 0;
		int indexItem = m_listFeatureTypes.InsertItem(&lvi);
		ret = m_listFeatureTypes.SetItemText(indexItem, 0, cft->m_pFT->name.c_str());
		ret = m_listFeatureTypes.SetItemText(indexItem, 1, wss.str().c_str());
		m_listFeatureTypes.SetItemData(indexItem, (LPARAM)cft);

		iItem++;
	}
}

void CDialogCellFeatureList::SetLayer(Layer* layer)
{
	hash_cft.clear();
	S101Layer* l = (S101Layer*)layer;

	if (layer == NULL)
		return;



	Catalog* catalog = ((S101Layer*)layer)->GetFC();
	
	S101Cell *cell = (S101Cell*)layer->m_spatialObject;
	POSITION pos = cell->m_feaMap.GetStartPosition();

	while (pos != NULL)
	{
		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);

		int code = fr->m_frid.m_nftc;

		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
		CodeWithNumericCode* nc = itor->second;

		std::wstring codeStr = nc->m_code;
		FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType.find(codeStr)->second;
				
		auto itorCFT = hash_cft.find(codeStr); 

		if (itorCFT == hash_cft.end())
		{
			CountedFeatureType cft(objFT);
			std::unordered_map<std::wstring, CountedFeatureType>::value_type ctfvt(codeStr, cft);
			
			hash_cft.insert(ctfvt);
		}
		else
		{
			itorCFT->second.m_count++;
		}
	}

	SetList();
}

void CDialogCellFeatureList::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FEATURE_TYPES);

	if (pList->GetSafeHwnd())
	{
		pList->MoveWindow(5, 10, cx - 10, cy - 40);


		CRect rect;
		pList->GetClientRect(rect);

		pList->SetColumnWidth(0, 0);
		pList->SetColumnWidth(1, rect.Width());  

		for (int i = 0; i < pList->GetHeaderCtrl()->GetItemCount(); ++i)
			pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
	if (m_btOK.GetSafeHwnd())
	{
		m_btOK.MoveWindow(cx - 85, cy - 30, 80, 25);
	}
	if (m_btnReport.GetSafeHwnd())
	{
		m_btnReport.MoveWindow(cx - 170, cy - 30, 80, 25);
	}
}


BOOL CDialogCellFeatureList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FEATURE_TYPES);

	if (pList->GetSafeHwnd())
	{
		pList->SetExtendedStyle(LVS_EX_FULLROWSELECT);

		pList->InsertColumn(0, _T("Feature Name"), LVCFMT_LEFT, 1, 1);
		pList->InsertColumn(1, _T("Count"), LVCFMT_LEFT, 1, 1);		
	}

	return TRUE;
}


void CDialogCellFeatureList::OnBnClickedBtnFeatureListReport()
{     
	wchar_t name_filter[] = L"All Files (*.*)|*.*|Text Files (*.txt)|*.txt|";      
	CFileDialog ins_dlg(FALSE, L"txt", L"*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, name_filter); 
	ins_dlg.m_ofn.nFilterIndex = 2; 
	if (ins_dlg.DoModal() == IDOK){

		CStdioFile file;
		if (file.Open(ins_dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText)){
			
			for (auto itor = hash_cft.begin(); itor != hash_cft.end(); itor++)
			{
				CountedFeatureType* cft = &itor->second;

				CString writeStr;
				writeStr.Format(L"%s : %d\n", cft->m_pFT->name.c_str(), cft->m_count);
				file.WriteString(writeStr);
			}
			file.Close();
		}
	}


}
