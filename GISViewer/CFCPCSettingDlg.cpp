// CFCPCSettingDlg.cpp: 구현 파일 

#include "stdafx.h" 
#include "GISViewer.h"
#include "GISViewerView.h"
#include "CFCPCSettingDlg.h"
#include "afxdialogex.h"

#include "S101Portrayal\\PortrayalCatalogue.h" 

IMPLEMENT_DYNAMIC(CFCPCSettingDlg, CDialogEx)

CFCPCSettingDlg::CFCPCSettingDlg(CWnd* pParent )
	: CDialogEx(IDD_DIALOG_PC_FC_SETTING, pParent)
{

}

CFCPCSettingDlg::~CFCPCSettingDlg()
{
}

void CFCPCSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FC, m_fclist);
	DDX_Control(pDX, IDC_LIST_PC, m_pclist);
}


BEGIN_MESSAGE_MAP(CFCPCSettingDlg, CDialogEx)
	ON_BN_CLICKED(ID_FC_CHANGE_BUTTON, &CFCPCSettingDlg::OnBnClickedFcChangeButton)
	ON_BN_CLICKED(ID_PC_CHANGE_BUTTON, &CFCPCSettingDlg::OnBnClickedPcChangeButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FC, &CFCPCSettingDlg::OnNMClickListFc)
END_MESSAGE_MAP() 

void CFCPCSettingDlg::SettingPCFC()
{ 
}

void CFCPCSettingDlg::OnBnClickedFcChangeButton()
{ 
	POSITION pos;
	pos = m_fclist.GetFirstSelectedItemPosition();
	std::vector<int> selectedList;

	while (pos)
	{
		int nSelected = m_fclist.GetNextSelectedItem(pos);
		selectedList.push_back(nSelected);

		wstring fileType = m_fclist.GetItemText(nSelected, 0);
		wstring filepath = m_fclist.GetItemText(nSelected, 1);

		Catalog* value = new Catalog(filepath);
		if (LayerManager::hash_FC->find(fileType)!=LayerManager::hash_FC->end()) 
		{
			LayerManager::hash_FC->at(fileType) = value;
			LayerManager::pS100Catalogs->at(nSelected) = value;
		}
		
		for each (auto list in LayerManager::CatalogueList)
		{
			auto fc = list.first;
			auto pc = list.second;

			if (fc->GetFilePath().compare(filepath))
			{
				fc = value;
			}
		}
	}  
	AfxMessageBox(L"Reload complete!");
}

void CFCPCSettingDlg::OnBnClickedPcChangeButton()
{
	POSITION pos;
	pos = m_pclist.GetFirstSelectedItemPosition();
	std::vector<int> selectedList;

	while (pos)
	{
		int nSelected = m_pclist.GetNextSelectedItem(pos);
		selectedList.push_back(nSelected);

		wstring fileType = m_pclist.GetItemText(nSelected, 0);
		wstring filepath = m_pclist.GetItemText(nSelected, 1);  

		if (LayerManager::hash_PC->find(fileType) != LayerManager::hash_PC->end())
		{
			auto pc = LayerManager::hash_PC->at(fileType);
			pc->Delete();
			pc->Init();
			pc->Open(filepath);
			auto lm = gisLib->GetLayerManager();
			if (lm)
			{
				lm->ChangeS100ColorPalette(pc->GetCurrentPaletteName());
			}  
		}               
	}   
	
	theApp.pView->MapRefresh();
	AfxMessageBox(L"Reload complete!");
}

BOOL CFCPCSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect listRect;
	m_fclist.GetWindowRect(listRect);

	m_fclist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_fclist.InsertColumn(0, _T("type"), LVCFMT_CENTER, (int)(listRect.Width()*0.10));
	m_fclist.InsertColumn(1, _T("path"), LVCFMT_CENTER, (int)(listRect.Width()*0.90));

	int i = 0;
	for each (Catalog* fc in *LayerManager::pS100Catalogs)
	{
		m_fclist.InsertItem(i, fc->m_pCatalogueList.begin()->first.c_str());
		m_fclist.SetItemText(i, 1, fc->GetFilePath().c_str());
		i++;
	}


	m_pclist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_pclist.InsertColumn(0, _T("type"), LVCFMT_CENTER, (int)(listRect.Width()*0.10));
	m_pclist.InsertColumn(1, _T("path"), LVCFMT_CENTER, (int)(listRect.Width()*0.90));

	int j = 0;
	for each (auto pc in *LayerManager::pPortrayalCatalogues)
	{

		std::wstring filepath = pc->rootPath;

		m_pclist.InsertItem(j, pc->product.c_str());
		m_pclist.SetItemText(j, 1, filepath.c_str());
		j++;
	}  
	return false;
}

void CFCPCSettingDlg::OnNMClickListFc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	*pResult = 0;
}
