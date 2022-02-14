// Configuration_1.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "Configuration_1.h"
#include "afxdialogex.h"
#include "ConfigrationDlg.h"

IMPLEMENT_DYNAMIC(CConfiguration_1, CDialogEx)

BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID aFontCount)
{
	int far * aiFontCount = (int far *) aFontCount;  

	if (FontType & RASTER_FONTTYPE)
		aiFontCount[0]++;
	else if (FontType & TRUETYPE_FONTTYPE)
		aiFontCount[2]++;
	else
		aiFontCount[1]++;

	if (aiFontCount[0] || aiFontCount[1] || aiFontCount[2])
		return TRUE;
	else
		return FALSE;

	UNREFERENCED_PARAMETER(lplf);
	UNREFERENCED_PARAMETER(lpntm);
}

CConfiguration_1::CConfiguration_1(CWnd* pParent )
	: CDialogEx(CConfiguration_1::IDD, pParent)
	, m_colorScheme(0)
	, m_SymbolizedAreaBoundary(0)
	, m_seabed_type(0)
	, m_DrawingType(0)
{
	m_pParent = nullptr;
}

CConfiguration_1::~CConfiguration_1()
{
}

void CConfiguration_1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TWO_SHADE, m_twoShade);
	DDX_Control(pDX, IDC_SAFETY_DEPTH, m_safetyDepth);
	DDX_Control(pDX, IDC_SAFETY_WATER_LEVEL, m_safetyWaterLevel);
	DDX_Control(pDX, IDC_VERY_SHALLOW_WATER, m_veryShallowWaterLevel);
	DDX_Control(pDX, IDC_VERY_DEEP_WATER, m_veryDeepWaterLevel);
	DDX_Control(pDX, IDC_DEPTH_CORRECTION_INTERVAL, m_depthCorrectionInterval);
	DDX_Radio(pDX, IDC_COLOR_DB, m_colorScheme);
	DDX_Radio(pDX, IDC_DPM_BASE, m_displayMode);
	DDX_Control(pDX, IDC_USE_NOBJNM, m_useNationalObjectName);
	DDX_Radio(pDX, IDC_SEABED_SYMPLIFIED, m_seabed_type); 
	DDX_Control(pDX, IDC_INTEND_TO_PERFORMANCE, m_useSpatailQuery);
	DDX_Control(pDX, IDC_EDIT_SETTING_FONT_SIZE, m_settingFontSize);
	DDX_Control(pDX, IDC_COMBO_SETTING_FONT_NAME, m_comboFontName);
	DDX_Control(pDX, IDC_BTN_LOAD_SETTING, m_loadSettingbutton);
}


BEGIN_MESSAGE_MAP(CConfiguration_1, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_LOAD_SETTING, &CConfiguration_1::OnBnClickedBtnLoadSetting)

END_MESSAGE_MAP() 



BOOL CConfiguration_1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_twoShade.SetCheck(ENCCommon::TWO_SHADES);
	m_useNationalObjectName.SetCheck(ENCCommon::SHOW_NOBJNM);

	m_useSpatailQuery.ShowWindow(SW_HIDE);
	m_loadSettingbutton.ShowWindow(SW_HIDE);
	if (theApp.IsEditingMode())
	{
		m_useSpatailQuery.ShowWindow(SW_SHOWNORMAL);
		m_loadSettingbutton.ShowWindow(SW_SHOWNORMAL);
		m_useSpatailQuery.SetCheck(ENCCommon::USE_SPATIAL_QUERY);
	}

	m_safetyDepth.SetWindowText(_bstr_t(ENCCommon::SAFETY_DEPTH));
	m_safetyWaterLevel.SetWindowText(_bstr_t(ENCCommon::SAFETY_CONTOUR));
	m_veryShallowWaterLevel.SetWindowText(_bstr_t(ENCCommon::SHALLOW_CONTOUR));
	m_veryDeepWaterLevel.SetWindowText(_bstr_t(ENCCommon::DEEP_CONTOUR));
	m_depthCorrectionInterval;

	m_colorScheme = ENCCommon::m_eColorTable;
	m_displayMode = ENCCommon::DISPLAY_MODE;
	m_DrawingType = ENCCommon::DrawingType;
	m_SymbolizedAreaBoundary = ENCCommon::SymbolizedAreaBoundary ? 0 : 1;
	m_seabed_type = ENCCommon::SeabedAreaType ? 0 : 1;

	for (auto fontIter = m_fontList.begin(); fontIter != m_fontList.end(); fontIter++)
	{
		CString fontName = *fontIter;
		m_comboFontName.AddString(fontName);
	}

	m_comboFontName.SetWindowText(ENCCommon::DISPLAY_FONT_NAME.c_str());
	m_settingFontSize.SetWindowText(_bstr_t(ENCCommon::DISPLAY_FONT_SIZE));

	UpdateData(FALSE);

	return TRUE;
}

void CConfiguration_1::OnClose()
{
	CDialogEx::OnClose();
}


void CConfiguration_1::OnOK()
{
}

void CConfiguration_1::OnCancel()
{
}

void CConfiguration_1::OnBnClickedBtnLoadSetting()
{
	m_pParent->OnBnClickedBtnLoadSetting();
}

void CConfiguration_1::SetFontList(std::vector<CString> fontList)
{
	m_fontList.clear();

	m_fontList.insert(m_fontList.begin(), fontList.begin(), fontList.end());
}

std::vector<CString>* CConfiguration_1::GetFontList()
{
	return &m_fontList;
}


