// Configuration_2.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "Configuration_2.h"
#include "afxdialogex.h"
#include "ConfigrationDlg.h"

#include "PLLibrary/GeoObject.h"

IMPLEMENT_DYNAMIC(CConfiguration_2, CDialogEx)

CConfiguration_2::CConfiguration_2(CWnd* pParent )
	: CDialogEx(CConfiguration_2::IDD, pParent)
{

}

CConfiguration_2::~CConfiguration_2()
{
}

void CConfiguration_2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VS_OBJECT, m_visualObjectList);
	DDX_Control(pDX, IDC_CHECK_SOUNDING, m_sounding);
	DDX_Control(pDX, IDC_CHECK_LIGHT, m_lights);

	DDX_Control(pDX, IDC_CHECK_TEXT, m_text); 
	DDX_Control(pDX, IDC_CHECK_SCALEMIN, m_scaleMin);
	DDX_Control(pDX, IDC_CHECK_CONTOUR_LABLE, m_contourLabels);
	DDX_Control(pDX, IDC_CHECK_TEXT_CLUTTER, m_textClutter);
	DDX_Control(pDX, IDC_LIST_SETTINGS, m_settingsList);
	DDX_Control(pDX, IDC_CHECK_ABBREVIATION, m_abbreviationList); 
	DDX_Control(pDX, IDC_CHECK_WGS84, m_geo_wgs84_text);
	DDX_Control(pDX, IDC_CHECK_COAST_AREA, m_coast_area);
	DDX_Control(pDX, IDC_CHECK_DETAIL_COAST_AREA, m_coast_area_detail);
	DDX_Control(pDX, IDC_CHECK_SHOW_ISOLATED_DANGER, m_check_isd);
}

BEGIN_MESSAGE_MAP(CConfiguration_2, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SHOW_OBJECT_SETTINGS, &CConfiguration_2::OnBnClickedBtnShowObjectSettingsDefault)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SETTINGS, &CConfiguration_2::OnLvnItemchangedListSettings)
END_MESSAGE_MAP() 


BOOL CConfiguration_2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect; 
	m_visualObjectList.GetClientRect(rect);
	m_visualObjectList.InsertColumn(0, _T("Code"), LVCFMT_LEFT, 80);
	m_visualObjectList.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 60);
	m_visualObjectList.InsertColumn(2, _T("Description"), LVCFMT_LEFT, rect.Width() - 140);

	CString cs(_T(""));
	int i = 1;
	for (i = 1; i < 99999; i++)
	{
		CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(i);
		if (obj)
		{
			cs.Format(_T("%d"), obj->Code);
			int nItem = m_visualObjectList.InsertItem(i, cs);

			m_visualObjectList.SetItemText(nItem, 1, obj->Acronym);
			m_visualObjectList.SetItemText(nItem, 2, obj->Object_class);
		}
	}

	m_visualObjectList.SetExtendedStyle(m_visualObjectList.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	m_visualObjectList.Init();

	int nCount = m_visualObjectList.GetItemCount();
	std::unordered_map<int, bool>::iterator odsitor;

	for (i = 0; i < nCount; i++)
	{
		CString strCode = m_visualObjectList.GetItemText(i, 0);

		int code = _ttoi(strCode);

		odsitor = ENCCommon::objectDisplaySettings.find(code);
		if (odsitor != ENCCommon::objectDisplaySettings.end())
		{
			ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, odsitor->second);
		}
	}  
	m_settingsList.GetClientRect(rect);
	m_settingsList.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 0);
	m_settingsList.InsertColumn(1, _T("Customized Settings"), LVCFMT_LEFT, rect.Width());
	m_settingsList.InsertColumn(2, _T("Path"), LVCFMT_LEFT, 0);

	int nItem = m_settingsList.InsertItem(i, L"");
	m_settingsList.SetItemText(nItem, 1, L"Custom");
	m_settingsList.SetItemText(nItem, 2, _T("..\\ProgramData\\data\\settings.txt")); 

	CFileFind  finder;
	BOOL bWorking = finder.FindFile(_T("..\\ProgramData\\data\\*.settings"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory())
		{
			finder.GetFileName();

			int nItem = m_settingsList.InsertItem(i, L"");
			m_settingsList.SetItemText(nItem, 1, finder.GetFileName());
			m_settingsList.SetItemText(nItem, 2, finder.GetFilePath());
		}
	}
	m_settingsList.SetExtendedStyle(m_settingsList.GetExtendedStyle() | LVS_EX_FULLROWSELECT); 

	m_sounding.SetCheck(ENCCommon::SOUNDING);
	m_lights.SetCheck(ENCCommon::LIGHTS);
	m_contourLabels.SetCheck(ENCCommon::CONTOUR_LABELS);
	m_scaleMin.SetCheck(ENCCommon::APPLY_SCALE_MIN);
	m_textClutter.SetCheck(ENCCommon::AVOID_CLUTTER);

	m_check_isd.SetCheck(ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER); 
	m_text.SetCheck(ENCCommon::TEXTOUT); 


	m_abbreviationList.SetCheck(ENCCommon::SHOW_LIST_ABBREVIATION);
	m_geo_wgs84_text.SetCheck(ENCCommon::WGS84_TEXT_TYPE);
	m_coast_area.SetCheck(ENCCommon::SHOW_USER_COAST_AREA);
	m_coast_area_detail.SetCheck(ENCCommon::SHOW_USER_COAST_AREA_DETAIL);

	return true; 
}


void CConfiguration_2::OnBnClickedBtnShowObjectSettingsDefault()
{
	m_visualObjectList.DeleteAllItems();

	CString cs(_T(""));
	int i = 1;
	for (i = 1; i < 99999; i++)
	{
		CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(i);
		if (obj)
		{
			cs.Format(_T("%d"), obj->Code);
			int nItem = m_visualObjectList.InsertItem(i, cs);

			m_visualObjectList.SetItemText(nItem, 1, obj->Acronym);
			m_visualObjectList.SetItemText(nItem, 2, obj->Object_class);
		}
	}

	int nCount = m_visualObjectList.GetItemCount();
	std::unordered_map<int, bool>::iterator odsitor;

	for (i = 0; i < nCount; i++)
	{
		CString strCode = m_visualObjectList.GetItemText(i, 0);

		int code = _ttoi(strCode);

		if (code < 300)
		{
			ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, TRUE);

			if (code == 81)
			{
				ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, FALSE);
			}
			else if (code == 72)
			{
				ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, FALSE);
			}
			else if (code == 27)
			{
				ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, FALSE);
			}
			else if (code == 135)
			{
				ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, FALSE);
			}
		}
		else
		{
			ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, FALSE);

			if (code >= 30000)
			{
				ListView_SetCheckState(m_visualObjectList.GetSafeHwnd(), i, TRUE);
			}            
		}
	}
}


void CConfiguration_2::OnClose()
{ 

	CDialogEx::OnClose();
}


void CConfiguration_2::OnCancel()
{  

}


void CConfiguration_2::OnOK()
{  
}


void CConfiguration_2::OnLvnItemchangedListSettings(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if (pNMLV->uChanged & LVIF_STATE)
	{
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED))
		{
			int  iRow = pNMLV->iItem;
			wstring str = m_settingsList.GetItemText(iRow, 2);
			m_pParent->SettingLoadFromFile(str);
		}
	}
	*pResult = 0;
}

