// ConfigrationDlg.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "ConfigrationDlg.h"
#include "GISViewerView.h"
#include "DialogDockLayerManager.h"

#include "..\\LibMFCUtil\\StringTokenizer.h"
#include "..\\LibMFCUtil\\LibMFCUtil.h"

#include "PLLibrary\\SymbolManager.h"
#include "PLLibrary\\GeoObject.h" 


#include "GISLibrary\\S101Layer.h"
#include "S101Portrayal\\PortrayalCatalogue.h"
#include "..\\FeatureCatalog\\Catalog.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"

IMPLEMENT_DYNAMIC(CConfigrationDlg, CDialogEx)

CConfigrationDlg::CConfigrationDlg(CWnd* pParent )
	: CDialogEx(CConfigrationDlg::IDD, pParent)
{
	m_config.APPLY_SCALE_MIN = ENCCommon::APPLY_SCALE_MIN;
	m_config.CONTOUR_LABELS = ENCCommon::CONTOUR_LABELS;
	m_config.DEEP_CONTOUR = ENCCommon::DEEP_CONTOUR;
	m_config.DISTANCE_TAGS = ENCCommon::DISTANCE_TAGS;
	m_config.DISPLAY_MODE = ENCCommon::DISPLAY_MODE;
	m_config.DrawingType = ENCCommon::DrawingType;
	m_config.LIGHTS = ENCCommon::LIGHTS;
	m_config.OVER_GROUP = ENCCommon::OVER_GROUP;
	m_config.SAFETY_DEPTH = ENCCommon::SAFETY_DEPTH;
	m_config.SAFETY_CONTOUR = ENCCommon::SAFETY_CONTOUR;
	m_config.SHALLOW_CONTOUR = ENCCommon::SHALLOW_CONTOUR;
	m_config.SHALLOW_PATTERN = ENCCommon::SHALLOW_PATTERN;
	m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER;
	m_config.FULL_SECTORS = ENCCommon::FULL_SECTORS;
	m_config.SHOW_NOBJNM = ENCCommon::SHOW_NOBJNM;
	m_config.AVOID_CLUTTER = ENCCommon::AVOID_CLUTTER;
	m_config.SHOW_LIST_ABBREVIATION = ENCCommon::SHOW_LIST_ABBREVIATION;
	m_config.WGS84_TEXT_TYPE = ENCCommon::WGS84_TEXT_TYPE;
	m_config.SOUNDING = ENCCommon::SOUNDING;
	m_config.SymbolizedAreaBoundary = ENCCommon::SymbolizedAreaBoundary;
	m_config.SeabedAreaType = ENCCommon::SeabedAreaType;
	m_config.TEXTOUT = ENCCommon::TEXTOUT;
	m_config.TWO_SHADES = ENCCommon::TWO_SHADES;
	m_config.USE_SPATIAL_QUERY = ENCCommon::USE_SPATIAL_QUERY;
	m_config.m_eColorTable = ENCCommon::m_eColorTable;
	m_config.UNIT_DISTANCE = ENCCommon::UNIT_DISTANCE;
	m_config.SHOW_USER_COAST_AREA = ENCCommon::SHOW_USER_COAST_AREA;
	m_config.SHOW_USER_COAST_AREA_DETAIL = ENCCommon::SHOW_USER_COAST_AREA_DETAIL;

	m_config.DISPLAY_FONT_NAME = ENCCommon::DISPLAY_FONT_NAME;
	m_config.DISPLAY_FONT_SIZE = ENCCommon::DISPLAY_FONT_SIZE; 
	m_config.objectDisplaySettings.insert(ENCCommon::objectDisplaySettings.begin(), ENCCommon::objectDisplaySettings.end());

	m_pParentView = (CGISViewerView*)pParent;

	bObjectDisplaySettingChanges = false;
}
void CConfigrationDlg::SetParentView(CGISViewerView *m_pView)
{
	m_pParentView = m_pView;
}
CConfigrationDlg::~CConfigrationDlg()
{
}

void CConfigrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_TAB, m_tab);
}


BEGIN_MESSAGE_MAP(CConfigrationDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_CONFIG_TAB, &CConfigrationDlg::OnTcnSelchangeConfigTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_CONFIG_TAB, &CConfigrationDlg::OnTcnSelchangingConfigTab)
	ON_BN_CLICKED(IDOK, &CConfigrationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfigrationDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_APPLY, &CConfigrationDlg::OnBnClickedApply)
END_MESSAGE_MAP() 


BOOL CConfigrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString    strOne = _T("S-52");
	CString    strTwo = _T("S-57");
	CString    strThree = _T("ETC");
	CString    strS101 = _T("S-101");

	m_tab.InsertItem(1, strOne);

	if (theApp.IsEditingMode())
	{
		m_tab.InsertItem(2, strTwo);
	}

	m_tab.InsertItem(3, strS101);
	m_tab.InsertItem(4, strThree);

	CRect r;
	m_tab.GetWindowRect(&r);

	page1.Create(IDD_DIALOG_CONFIG_1, &m_tab);
	page1.ShowWindow(SW_SHOW);
	page1.GetWindowRect(&r);
	page1.MoveWindow(5, 25, r.Width() - 10, r.Height() - 30);
	
	if (theApp.IsEditingMode())
	{
		page2.Create(IDD_DIALOG_CONFIG_2, &m_tab);
		page2.ShowWindow(SW_HIDE);
		page2.MoveWindow(5, 25, r.Width() - 10, r.Height() - 30);
		page2.m_pParent = this;
	}

	page4.Create(IDD_DIALOG_CONFIG_4, &m_tab);
	page4.ShowWindow(SW_HIDE);
	page4.MoveWindow(5, 25, r.Width() - 10, r.Height() - 30);
	page4.m_pParent = this;

	page3.Create(IDD_DIALOG_CONFIG_3, &m_tab);
	page3.ShowWindow(SW_HIDE);
	page3.MoveWindow(5, 25, r.Width() - 10, r.Height() - 30);
	page3.m_pParent = this;

	m_tab.SetCurSel(0);

	page1.m_pParent = this;

	return true;
}


void CConfigrationDlg::OnTcnSelchangeConfigTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tab.GetCurSel(); 

	if (theApp.IsEditingMode())
	{
		switch (nTab)
		{
		case 0:
			page1.ShowWindow(SW_SHOW);
			break;
		case 1:
			page2.ShowWindow(SW_SHOW);
			break;
		case 2:
			page4.ShowWindow(SW_SHOW);
			break;
		case 3:
			page3.ShowWindow(SW_SHOW);
			break;
		}
		*pResult = 0;
	}
	else if(theApp.IsViewerMode())
	{
		switch (nTab)
		{
		case 0:
			page1.ShowWindow(SW_SHOW);
			break;
		case 1:
			page4.ShowWindow(SW_SHOW);
			break;
		case 2:
			page3.ShowWindow(SW_SHOW);
			break;
	
		}
		*pResult = 0;
	}

	
}


void CConfigrationDlg::OnTcnSelchangingConfigTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tab.GetCurSel(); 

	if (theApp.IsEditingMode()) 
	{
		switch (nTab)
		{
		case 0:
			page1.ShowWindow(SW_HIDE);
			break;
		case 1:
			page2.ShowWindow(SW_HIDE);
			break;
		case 2:
			page4.ShowWindow(SW_HIDE);
			break;
		case 3:
			page3.ShowWindow(SW_HIDE);
			break;
		}
		*pResult = 0;
	}
	else if (theApp.IsViewerMode())
	{
		switch (nTab)
		{
		case 0:
			page1.ShowWindow(SW_HIDE);
			break;
		case 1:
			page4.ShowWindow(SW_HIDE);
			break;
		case 2:
			page3.ShowWindow(SW_HIDE);
			break;
	
		}
		*pResult = 0;
	}

	
}

void CConfigrationDlg::OnBnClickedOk()
{
	OnBnClickedApply();
	CDialogEx::OnOK();
}

void CConfigrationDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CConfigrationDlg::OnClose()
{ 

	CDialogEx::OnClose();
}

void CConfigrationDlg::OnBnClickedBtnLoadSetting()
{
	m_config.objectDisplaySettings.clear();
	for (int i = 1; i < 99999; i++)
	{
		CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(i);
		if (obj)
		{
			if (obj->Code == 81)
				m_config.objectDisplaySettings.insert(
					std::unordered_map<int, bool>::value_type(obj->Code, false)
				);
			else
				m_config.objectDisplaySettings.insert(
					std::unordered_map<int, bool>::value_type(obj->Code, true)
				);
		}
	} 

	wstring fileName = L"..\\ProgramData\\data\\관제모드.settings";

	TCHAR szDirectory[MAX_PATH] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
	CString settingInitPath = szDirectory;
	int index = settingInitPath.ReverseFind(L'\\');
	settingInitPath = settingInitPath.Left(index);
	settingInitPath.Append(_T("\\ProgramData\\data\\"));

	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY | OFN_FILEMUSTEXIST, _T("Setting Files(*.settings)|*.settings|"), this);
	dlg.m_ofn.lpstrTitle = L"Load Program Setting File";
	dlg.m_ofn.lpstrInitialDir = settingInitPath; 
	if (dlg.DoModal() == IDOK)
	{ 
		BeginWaitCursor(); 
		fileName = dlg.GetPathName();

		SettingLoadFromFile(fileName);
	}
	else
	{
		return;
	}
}
void CConfigrationDlg::InitS101FeatureTypes(Catalog* catalog)
{
	m_config.featureDisplaySettings.clear();

	auto ci = catalog->m_pCatalogueList.begin();

	if (ci == catalog->m_pCatalogueList.end())
	{
		return;
	}
	auto fc = ci->second;

	for (auto fti = fc->featureTypes.featureType.begin(); fti != fc->featureTypes.featureType.end(); fti++)
	{
		auto *ft = &fti->second;

		m_config.featureDisplaySettings.insert(
			std::unordered_map<std::wstring, bool>::value_type(ft->name, true)
		);
	}
}

void CConfigrationDlg::InitControlValues()
{
	page1.m_twoShade.SetCheck(m_config.TWO_SHADES);
	page1.m_useNationalObjectName.SetCheck(m_config.SHOW_NOBJNM);
	page1.m_useSpatailQuery.SetCheck(m_config.USE_SPATIAL_QUERY);

	page1.m_safetyDepth.SetWindowText(_bstr_t(m_config.SAFETY_DEPTH));
	page1.m_safetyWaterLevel.SetWindowText(_bstr_t(m_config.SAFETY_CONTOUR));
	page1.m_veryShallowWaterLevel.SetWindowText(_bstr_t(m_config.SHALLOW_CONTOUR));
	page1.m_veryDeepWaterLevel.SetWindowText(_bstr_t(m_config.DEEP_CONTOUR));
	page1.m_depthCorrectionInterval;//.SetWindowText(_bstr_t(m_config.SHALLOW_CONTOUR));

	page1.m_colorScheme = m_config.m_eColorTable;
	page1.m_displayMode = m_config.DISPLAY_MODE;
	page1.m_SymbolizedAreaBoundary = m_config.SymbolizedAreaBoundary ? 0 : 1;
	page1.m_seabed_type = m_config.SeabedAreaType ? 0 : 1;


	page1.m_comboFontName.SetWindowText(m_config.DISPLAY_FONT_NAME.c_str());
	page1.m_settingFontSize.SetWindowText(_bstr_t(m_config.DISPLAY_FONT_SIZE));

	page2.m_visualObjectList.DeleteAllItems();
	CString cs(_T(""));
	int i = 1;
	for (i = 1; i < 99999; i++)
	{
		CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(i);
		if (obj)
		{
			cs.Format(_T("%d"), obj->Code);
			int nItem = page2.m_visualObjectList.InsertItem(i, cs);

			page2.m_visualObjectList.SetItemText(nItem, 1, obj->Acronym);
			page2.m_visualObjectList.SetItemText(nItem, 2, obj->Object_class);
		}
	}

	page2.m_visualObjectList.SetExtendedStyle(page2.m_visualObjectList.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	page2.m_visualObjectList.Init();

	int nCount = page2.m_visualObjectList.GetItemCount();
	std::unordered_map<int, bool>::iterator odsitor;

	for (i = 0; i < nCount; i++)
	{
		CString strCode = page2.m_visualObjectList.GetItemText(i, 0);

		int code = _ttoi(strCode);

		odsitor = m_config.objectDisplaySettings.find(code);
		if (odsitor != m_config.objectDisplaySettings.end())
		{
			ListView_SetCheckState(page2.m_visualObjectList.GetSafeHwnd(), i, odsitor->second);
		}
	}

	page2.m_sounding.SetCheck(m_config.SOUNDING);
	page2.m_lights.SetCheck(m_config.LIGHTS);
	page2.m_contourLabels.SetCheck(m_config.CONTOUR_LABELS);
	page2.m_text.SetCheck(m_config.TEXTOUT);
	page2.m_scaleMin.SetCheck(m_config.APPLY_SCALE_MIN);
	page2.m_textClutter.SetCheck(m_config.AVOID_CLUTTER);
	page2.m_check_isd.SetCheck(m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER);
	page2.m_abbreviationList.SetCheck(m_config.SHOW_LIST_ABBREVIATION);
	page2.m_geo_wgs84_text.SetCheck(m_config.WGS84_TEXT_TYPE);
	page2.m_coast_area.SetCheck(m_config.SHOW_USER_COAST_AREA);
	page2.m_coast_area_detail.SetCheck(m_config.SHOW_USER_COAST_AREA_DETAIL);


	page4.m_visualFeatureList.DeleteAllItems();

	for (auto fdsi = m_config.featureDisplaySettings.begin(); fdsi != m_config.featureDisplaySettings.end(); fdsi++)
	{
		cs.Format(_T("%s"), fdsi->first.c_str());
		int nItem = page4.m_visualFeatureList.InsertItem(i, cs);
	}

	page4.m_visualFeatureList.SetExtendedStyle(page4.m_visualFeatureList.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	page4.m_visualFeatureList.Init();

	nCount = page4.m_visualFeatureList.GetItemCount();
	std::unordered_map<std::wstring, bool>::iterator fdsitor;

	for (i = 0; i < nCount; i++)
	{
		std::wstring strCode = page4.m_visualFeatureList.GetItemText(i, 0);

		fdsitor = m_config.featureDisplaySettings.find(strCode);
		if (fdsitor != m_config.featureDisplaySettings.end())
		{
			ListView_SetCheckState(page4.m_visualFeatureList.GetSafeHwnd(), i, odsitor->second);
		}
	}

	page1.UpdateData(FALSE);
	if (theApp.IsEditingMode())
	{
		page2.UpdateData(FALSE);
	}

	page4.UpdateData(FALSE);
}

void CConfigrationDlg::OnBnClickedApply()
{
	page1.UpdateData();
	if (theApp.IsEditingMode())
	{
		page2.UpdateData();
	}

	page3.UpdateData();
	page4.UpdateData();

	CString value;

	m_config.TWO_SHADES = page1.m_twoShade.GetCheck() ? true : false;
	m_config.SHOW_NOBJNM = page1.m_useNationalObjectName.GetCheck() ? true : false;
	m_config.USE_SPATIAL_QUERY = page1.m_useSpatailQuery.GetCheck() ? true : false;

	page1.m_safetyDepth.GetWindowText(value);
	m_config.SAFETY_DEPTH = _ttoi(value);

	page1.m_safetyWaterLevel.GetWindowText(value);
	m_config.SAFETY_CONTOUR = _ttoi(value);

	page1.m_veryShallowWaterLevel.GetWindowText(value);
	m_config.SHALLOW_CONTOUR = _ttoi(value);

	page1.m_veryDeepWaterLevel.GetWindowText(value);
	m_config.DEEP_CONTOUR = _ttof(value);

	page1.m_comboFontName.GetWindowText(value);
	m_config.DISPLAY_FONT_NAME = value;

	page1.m_settingFontSize.GetWindowText(value);
	m_config.DISPLAY_FONT_SIZE = _ttoi(value);

	page1.m_depthCorrectionInterval;

	ASSERT(!(page1.m_colorScheme < ENCCommon::Day || page1.m_colorScheme > ENCCommon::Night));
	m_config.m_eColorTable = static_cast<ENCCommon::ColorTable>(page1.m_colorScheme);
	ASSERT(page1.m_displayMode == ENCCommon::base || page1.m_displayMode == ENCCommon::standard || page1.m_displayMode == ENCCommon::all);
	m_config.DISPLAY_MODE = static_cast<ENCCommon::DisplayModeTable>(page1.m_displayMode);

	m_config.UNIT_DISTANCE = static_cast<ENCCommon::UnitDistance>(page3.m_ComboBoxUnitDistance.GetCurSel());

	m_config.DrawingType = page1.m_DrawingType;

	m_config.SymbolizedAreaBoundary = page1.m_SymbolizedAreaBoundary ? false : true;
	m_config.SeabedAreaType = page1.m_seabed_type ? false : true;

	
	if (theApp.IsEditingMode())
	{
		m_config.SOUNDING = page2.m_sounding.GetCheck() ? true : false;
		m_config.LIGHTS = page2.m_lights.GetCheck() ? true : false;
		m_config.CONTOUR_LABELS = page2.m_contourLabels.GetCheck() ? true : false;
		m_config.TEXTOUT = page2.m_text.GetCheck() ? true : false;
		m_config.APPLY_SCALE_MIN = page2.m_scaleMin.GetCheck() ? true : false;
		m_config.AVOID_CLUTTER = page2.m_textClutter.GetCheck() ? true : false;
		m_config.SHOW_LIST_ABBREVIATION = page2.m_abbreviationList.GetCheck() ? true : false;
		m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = page2.m_check_isd.GetCheck() ? true : false;

		m_config.WGS84_TEXT_TYPE = page2.m_geo_wgs84_text.GetCheck() ? true : false;
		m_config.SHOW_USER_COAST_AREA = page2.m_coast_area.GetCheck() ? true : false;
		m_config.SHOW_USER_COAST_AREA_DETAIL = page2.m_coast_area_detail.GetCheck() ? true : false;

		int nCount = page2.m_visualObjectList.GetItemCount();
		std::unordered_map<int, bool>::iterator odsitor;

		for (int i = 0; i < nCount; i++)
		{
			CString strCode = page2.m_visualObjectList.GetItemText(i, 0);

			int code = _ttoi(strCode);

			odsitor = m_config.objectDisplaySettings.find(code);

			if (odsitor != m_config.objectDisplaySettings.end())
			{
				UINT check = ListView_GetCheckState(page2.m_visualObjectList.GetSafeHwnd(), i);
				(*odsitor).second = check == 0 ? false : true;
			}
		}
	}


	if (ENCCommon::APPLY_SCALE_MIN != m_config.APPLY_SCALE_MIN)
	{
		ENCCommon::APPLY_SCALE_MIN = m_config.APPLY_SCALE_MIN;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::CONTOUR_LABELS != m_config.CONTOUR_LABELS)
	{
		ENCCommon::CONTOUR_LABELS = m_config.CONTOUR_LABELS;
		m_pParentView->MapRefresh();
	}


	if (ENCCommon::SHOW_USER_COAST_AREA != m_config.SHOW_USER_COAST_AREA)
	{
		ENCCommon::SHOW_USER_COAST_AREA = m_config.SHOW_USER_COAST_AREA;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SHOW_USER_COAST_AREA_DETAIL != m_config.SHOW_USER_COAST_AREA_DETAIL)
	{
		ENCCommon::SHOW_USER_COAST_AREA_DETAIL = m_config.SHOW_USER_COAST_AREA_DETAIL;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::DISPLAY_MODE != m_config.DISPLAY_MODE)
	{
		ENCCommon::DISPLAY_MODE = m_config.DISPLAY_MODE;
		m_pParentView->m_pGisLib->ChangeDisplayMode();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::DrawingType != m_config.DrawingType)
	{
		ENCCommon::DrawingType = m_config.DrawingType;
		m_pParentView->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::CHANGED_MARINER_SETTING*/);
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::LIGHTS != m_config.LIGHTS)
	{
		ENCCommon::LIGHTS = m_config.LIGHTS;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SAFETY_DEPTH != m_config.SAFETY_DEPTH)
	{
		ENCCommon::SAFETY_DEPTH = m_config.SAFETY_DEPTH;
		m_pParentView->m_pGisLib->UpdateCS_SafetyDepth();
		m_pParentView->S101RebuildPortrayal();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SAFETY_CONTOUR != m_config.SAFETY_CONTOUR)
	{
		ENCCommon::SAFETY_CONTOUR = m_config.SAFETY_CONTOUR;
		m_pParentView->m_pGisLib->UpdateCS_SafetyContour();
		m_pParentView->S101RebuildPortrayal();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SHALLOW_CONTOUR != m_config.SHALLOW_CONTOUR ||
		ENCCommon::DEEP_CONTOUR != m_config.DEEP_CONTOUR
		) {
		ENCCommon::SHALLOW_CONTOUR = m_config.SHALLOW_CONTOUR;
		ENCCommon::DEEP_CONTOUR = m_config.DEEP_CONTOUR;
		m_pParentView->m_pGisLib->UpdateCS_ShadeType();
		m_pParentView->S101RebuildPortrayal();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SOUNDING != m_config.SOUNDING)
	{
		ENCCommon::SOUNDING = m_config.SOUNDING;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::m_eColorTable != m_config.m_eColorTable)
	{
		ENCCommon::m_eColorTable = m_config.m_eColorTable;

		auto lm = gisLib->GetLayerManager();
		if (nullptr != lm)
		{
			if (m_config.m_eColorTable == ENCCommon::Day)
			{
				lm->ChangeS100ColorPalette(L"Day");
			}
			else if (m_config.m_eColorTable == ENCCommon::Dusk)
			{
				lm->ChangeS100ColorPalette(L"Dusk");
			}
			else if (m_config.m_eColorTable == ENCCommon::Night)
			{
				lm->ChangeS100ColorPalette(L"Night");
			}
		}

		auto LayerList = gisLib->GetAllLayer();
		if (LayerList.size() != 0)
		{
			for each (auto layer in LayerList)
			{
				auto layerType = layer->GetLayerType();
				if (layerType.Compare(_T("FILE_S_100_VECTOR")) == 0 ||
					layerType.Compare(_T("FILE_S_100_GRID_H5")) == 0 ||
					layerType.Compare(_T("FILE_S_100_GRID_BAG")) == 0)
				{ 

					if (m_config.m_eColorTable == ENCCommon::Day)
					{
						ENCCommon::m_eColorTable = ENCCommon::Day;
						m_pParentView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\day_bright.dic"));
						m_pParentView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\day_bright.dic")); 
						m_pParentView->MapRefresh();
					}

					else if (m_config.m_eColorTable == ENCCommon::Dusk)
					{
						ENCCommon::m_eColorTable = ENCCommon::Dusk;
						m_pParentView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\dusk_blackback.dic"));
						m_pParentView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\dusk_blackback.dic")); 
						m_pParentView->MapRefresh();
					}

					else if (m_config.m_eColorTable == ENCCommon::Night)
					{
						ENCCommon::m_eColorTable = ENCCommon::Night;
						m_pParentView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\night.dic"));
						m_pParentView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\night.dic")); 
						m_pParentView->MapRefresh();
					}
				}
			}
		}
	}

	if (ENCCommon::UNIT_DISTANCE != m_config.UNIT_DISTANCE)
	{
		if (m_config.UNIT_DISTANCE == ENCCommon::unitDistance_km)
		{
			ENCCommon::UNIT_DISTANCE = ENCCommon::unitDistance_km;
		}
		else if (m_config.UNIT_DISTANCE == ENCCommon::unitDistance_nautical_mile)
		{
			ENCCommon::UNIT_DISTANCE = ENCCommon::unitDistance_nautical_mile;
		}
		else
		{
			ENCCommon::UNIT_DISTANCE = ENCCommon::unitDistance_km;
		}

		m_pParentView->Invalidate();
	}

	if (ENCCommon::TWO_SHADES != m_config.TWO_SHADES) {
		ENCCommon::TWO_SHADES = m_config.TWO_SHADES;
		m_pParentView->m_pGisLib->UpdateCS_ShadeType();
		m_pParentView->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::CHANGED_MARINER_SETTING*/);
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SHOW_NOBJNM != m_config.SHOW_NOBJNM) {
		ENCCommon::SHOW_NOBJNM = m_config.SHOW_NOBJNM;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::AVOID_CLUTTER != m_config.AVOID_CLUTTER)
	{
		ENCCommon::AVOID_CLUTTER = m_config.AVOID_CLUTTER;
		m_pParentView->MapRefresh();
	} 

	if (ENCCommon::SHOW_LIST_ABBREVIATION != m_config.SHOW_LIST_ABBREVIATION)
	{
		ENCCommon::SHOW_LIST_ABBREVIATION = m_config.SHOW_LIST_ABBREVIATION;
		m_pParentView->MapRefresh();
	}
	if (ENCCommon::WGS84_TEXT_TYPE != m_config.WGS84_TEXT_TYPE)
	{
		ENCCommon::WGS84_TEXT_TYPE = m_config.WGS84_TEXT_TYPE;
		m_pParentView->Invalidate();
	}
	if (ENCCommon::TEXTOUT != m_config.TEXTOUT)
	{
		ENCCommon::TEXTOUT = m_config.TEXTOUT;
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SymbolizedAreaBoundary != m_config.SymbolizedAreaBoundary)
	{
		ENCCommon::SymbolizedAreaBoundary = m_config.SymbolizedAreaBoundary;
		m_pParentView->m_pGisLib->UpdateCS_ShadeType();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SeabedAreaType != m_config.SeabedAreaType)
	{
		ENCCommon::SeabedAreaType = m_config.SeabedAreaType;
		m_pParentView->MapRefresh();
	}   

	if (ENCCommon::SHALLOW_PATTERN != m_config.SHALLOW_PATTERN)
	{
		ENCCommon::SHALLOW_PATTERN = m_config.SHALLOW_PATTERN;
		m_pParentView->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::CHANGED_MARINER_SETTING*/);
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER != m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER) {
		ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER;
		m_pParentView->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::CHANGED_MARINER_SETTING*/);
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::FULL_SECTORS != m_config.FULL_SECTORS)
	{
		ENCCommon::FULL_SECTORS = m_config.FULL_SECTORS;
		m_pParentView->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::CHANGED_MARINER_SETTING*/);
		m_pParentView->MapRefresh();
	}

	ENCCommon::SymbolizedAreaBoundary = m_config.SymbolizedAreaBoundary;
	ENCCommon::SeabedAreaType = m_config.SeabedAreaType;

	ENCCommon::DEEP_CONTOUR = m_config.DEEP_CONTOUR;
	ENCCommon::DISTANCE_TAGS = m_config.DISTANCE_TAGS;
	ENCCommon::OVER_GROUP = m_config.OVER_GROUP;

	std::unordered_map<int, bool>::iterator itor1;
	std::unordered_map<int, bool>::iterator itor2;

	for (itor1 = ENCCommon::objectDisplaySettings.begin(); itor1 != ENCCommon::objectDisplaySettings.end(); itor1++)
	{
		itor2 = m_config.objectDisplaySettings.find(itor1->first);
		if (itor2 != m_config.objectDisplaySettings.end())
		{
			if (itor1->second != itor2->second)
			{
				itor1->second = itor2->second;
				bObjectDisplaySettingChanges = true;
			}
		}
	}

	if (ENCCommon::USE_SPATIAL_QUERY != m_config.USE_SPATIAL_QUERY) {
		ENCCommon::USE_SPATIAL_QUERY = m_config.USE_SPATIAL_QUERY;
		m_pParentView->m_pGisLib->UpdateCS_SafetyDepth();
		m_pParentView->MapRefresh();
	}

	if (ENCCommon::DISPLAY_FONT_NAME.compare(m_config.DISPLAY_FONT_NAME) != 0
		|| ENCCommon::DISPLAY_FONT_SIZE != m_config.DISPLAY_FONT_SIZE
		) {
		ENCCommon::DISPLAY_FONT_NAME = m_config.DISPLAY_FONT_NAME;
		ENCCommon::DISPLAY_FONT_SIZE = m_config.DISPLAY_FONT_SIZE;

		m_pParentView->m_pGisLib->ChangeDisplayFont();
		m_pParentView->MapRefresh();
	}

	theApp.SaveSettings();
}

void CConfigrationDlg::SettingLoadFromFile(wstring fileName)
{ 
	ifstream ifs;
	ifs.open(fileName, std::ios::in);

	if (!ifs.is_open())
	{
		return;
	}

	string strTrue = "true";
	string strFalse = "false";
	string strLine;

	while (getline(ifs, strLine))
	{
		string opt = strLine.substr(0, 1);
		if (opt.compare("*") == 0)
			continue;

		StringTokenizer *pstringTokenizer = new StringTokenizer(strLine, " \t");
		strLine.clear();

		if (pstringTokenizer->hasMoreTokens())
		{
			string token = pstringTokenizer->nextToken();

			if (token.compare("APPLY_SCALE_MIN") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.APPLY_SCALE_MIN = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.APPLY_SCALE_MIN = false;
					}
				}
			}
			else if (token.compare("CONTOUR_LABELS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.CONTOUR_LABELS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.CONTOUR_LABELS = false;
					}
				}
			}
			else if (token.compare("DEEP_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.DEEP_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("DISTANCE_TAGS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.DISTANCE_TAGS = atoi(token.c_str());
				}
			}
			else if (token.compare("DISPLAY_MODE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.DISPLAY_MODE = static_cast<ENCCommon::DisplayModeTable>(atoi(token.c_str()));
				}
			}
			else if (token.compare("DrawingType") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.DrawingType = atoi(token.c_str());
				}
			}
			else if (token.compare("LIGHTS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.LIGHTS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.LIGHTS = false;
					}
				}
			}
			else if (token.compare("OVER_GROUP") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.OVER_GROUP = _atoi64(token.c_str());
				}
			}
			else if (token.compare("SAFETY_DEPTH") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.SAFETY_DEPTH = atof(token.c_str());
				}
			}
			else if (token.compare("SAFETY_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.SAFETY_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("SHALLOW_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.SHALLOW_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("DISPLAY_FONT_NAME") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();

					auto fontName = LibMFCUtil::ConvertCtoWC((char*)token.c_str());

					m_config.DISPLAY_FONT_NAME = fontName;

					delete[] fontName;
				}
			}
			else if (token.compare("DISPLAY_FONT_SIZE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.DISPLAY_FONT_SIZE = atoi(token.c_str());
				}
			}
			else if (token.compare("SHALLOW_PATTERN") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHALLOW_PATTERN = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHALLOW_PATTERN = false;
					}
				}
			}
			else if (token.compare("SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = false;
					}
				}
			}
			else if (token.compare("FULL_SECTORS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.FULL_SECTORS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.FULL_SECTORS = false;
					}
				}
			}
			else if (token.compare("SHOW_NOBJNM") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHOW_NOBJNM = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHOW_NOBJNM = false;
					}
				}
			}
			else if (token.compare("AVOID_CLUTTER") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.AVOID_CLUTTER = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.AVOID_CLUTTER = false;
					}
				}
			} 
			else if (token.compare("SHOW_LIST_ABBREVIATION") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHOW_LIST_ABBREVIATION = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHOW_LIST_ABBREVIATION = false;
					}
				}
			}
			else if (token.compare("WGS84_TEXT_TYPE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.WGS84_TEXT_TYPE = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.WGS84_TEXT_TYPE = false;
					}
				}
			}
			else if (token.compare("SOUNDING") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SOUNDING = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SOUNDING = false;
					}
				}
			}
			else if (token.compare("SymbolizedAreaBoundary") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SymbolizedAreaBoundary = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SymbolizedAreaBoundary = false;
					}
				}
			}
			else if (token.compare("SeabedType") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SeabedAreaType = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SeabedAreaType = false;
					}
				}
			}
			else if (token.compare("TEXTOUT") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.TEXTOUT = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.TEXTOUT = false;
					}
				}
			}
			else if (token.compare("TWO_SHADES") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.TWO_SHADES = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.TWO_SHADES = false;
					}
				}
			}
			else if (token.compare("USE_SPATIAL_QUERY") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.USE_SPATIAL_QUERY = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.USE_SPATIAL_QUERY = false;
					}
				}
			}
			else if (token.compare("SHOW_USER_COAST_AREA") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHOW_USER_COAST_AREA = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHOW_USER_COAST_AREA = false;
					}
				}
			}
			else if (token.compare("SHOW_USER_COAST_AREA_DETAIL") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						m_config.SHOW_USER_COAST_AREA_DETAIL = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						m_config.SHOW_USER_COAST_AREA_DETAIL = false;
					}
				}
			}
			else if (token.compare("m_eColorTable") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					m_config.m_eColorTable = static_cast<ENCCommon::ColorTable>(atoi(token.c_str()));
				}
			}
			else if (token.compare("OBJECT_SHOW_SETTING_BEGIN") == 0)
			{
				getline(ifs, strLine);
				while (strLine.compare("OBJECT_SHOW_SETTING_END") != 0)
				{
					int objectCode = 0;
					bool objectValue = 0;

					StringTokenizer *pstringTokenizerObjSettings = new StringTokenizer(strLine, " \t");

					if (pstringTokenizerObjSettings->hasMoreTokens())
					{
						token = pstringTokenizerObjSettings->nextToken();

						objectCode = atoi(token.c_str());
						if (pstringTokenizerObjSettings->hasMoreTokens())
						{
							token = pstringTokenizerObjSettings->nextToken();

							int value = atoi(token.c_str());

							value ? objectValue = true : objectValue = false;
						}
					}

					delete pstringTokenizerObjSettings;

					if (objectCode > 0)
					{
						std::unordered_map<int, bool>::iterator ositor;

						ositor = m_config.objectDisplaySettings.find(objectCode);
						if (ositor != m_config.objectDisplaySettings.end())
						{
							ositor->second = objectValue;

						}
					}
					getline(ifs, strLine);
				}
			}
		}
		delete pstringTokenizer;
	}

	InitControlValues();
}

CConfiguration_1* CConfigrationDlg::GetConfigPage1()
{
	return &page1;
}