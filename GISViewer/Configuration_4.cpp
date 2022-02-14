// Configuration_4.cpp: 구현 파일 

#include "stdafx.h"
#include "GISViewer.h"
#include "Configuration_4.h"
#include "afxdialogex.h"
#include "ConfigrationDlg.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h" 

IMPLEMENT_DYNAMIC(CConfiguration_4, CDialogEx)

CConfiguration_4::CConfiguration_4(CWnd* pParent )
	: CDialogEx(CConfiguration_4::IDD, pParent)
{

}

CConfiguration_4::~CConfiguration_4()
{
}

void CConfiguration_4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_LIST_VIEW, m_visualFeatureList);
}

BEGIN_MESSAGE_MAP(CConfiguration_4, CDialogEx)
END_MESSAGE_MAP()

BOOL CConfiguration_4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	try
	{
		CRect rect;

		m_visualFeatureList.GetClientRect(rect);
		m_visualFeatureList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 80);
		m_visualFeatureList.InsertColumn(1, _T("definition"), LVCFMT_LEFT, rect.Width()-80); 
		auto itor = LayerManager::hash_FC->find(L"S-101");
		if (itor == LayerManager::hash_FC->end()) 
		{
			return false;
		}

		m_visualFeatureList.SetExtendedStyle(m_visualFeatureList.GetExtendedStyle() | LVS_EX_CHECKBOXES);
		m_visualFeatureList.Init();
		return true; 

	}
	catch (int exceptionCode)
	{
		exceptionCode = 0;
		return false;
	}
}
