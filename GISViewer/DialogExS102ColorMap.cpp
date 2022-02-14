// DialogExS102ColorMap.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExS102ColorMap.h"
#include "afxdialogex.h"
#include "GISViewerView.h" 

IMPLEMENT_DYNAMIC(CDialogExS102ColorMap, CDialogEx)

CDialogExS102ColorMap::CDialogExS102ColorMap(CWnd* pParent )
: CDialogEx(CDialogExS102ColorMap::IDD, pParent)
{
	m_nBitmapIndex = 0;
	type = 0;
}

CDialogExS102ColorMap::~CDialogExS102ColorMap()
{
}

void CDialogExS102ColorMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COLOR_MAP, m_list);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_ComboEx);
	DDX_Control(pDX, IDC_COMBO1, m_comboCnt);
	DDX_Control(pDX, IDC_BUTTON_CLASSIFICATION, m_btnClassification);
}


BEGIN_MESSAGE_MAP(CDialogExS102ColorMap, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLASSIFICATION, &CDialogExS102ColorMap::OnBnClickedButtonClassification)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_COLOR_MAP, &CDialogExS102ColorMap::OnNMCustomdrawListColorMap)
	ON_BN_CLICKED(IDC_RADIO1, &CDialogExS102ColorMap::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO10, &CDialogExS102ColorMap::OnBnClickedRadio10)
	ON_BN_CLICKED(IDCANCEL, &CDialogExS102ColorMap::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDialogExS102ColorMap::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDOK, &CDialogExS102ColorMap::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &CDialogExS102ColorMap::OnCbnSelchangeComboboxex1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDialogExS102ColorMap::OnCbnSelchangeCombo1)
END_MESSAGE_MAP() 
BOOL CDialogExS102ColorMap::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	InitCatalog();
	InsertItemIntoComboBox();
	InsertItemIntoComboBoxCnt();

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.ModifyStyle(0, LVS_SINGLESEL);

	m_list.InsertColumn(0, _T("Color"), LVCFMT_LEFT, 100);

	std::vector<COLORREF> tmpColorMap;
	theApp.pView->m_pGisLib->GetS102ColorMapType(type, tmpColorMap);
	for (unsigned i = 0; i < tmpColorMap.size(); i++) {
		colormap.AddColor(tmpColorMap.at(i));
	}

	if (type == 0) {
		CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton->SetCheck(true);
		m_btnClassification.EnableWindow(FALSE);
		m_comboCnt.EnableWindow(FALSE);
	}
	else {
		CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO10);
		pButton->SetCheck(true);
	}

	m_comboCnt.SetCurSel(colormap.GetColorCount() - 4);

	for (int i = 0; i < colormap.GetColorCount(); i++) {
		m_list.InsertItem(i, _T(""));
	}

	OnBnClickedButtonClassification();

	return TRUE;  
}


void CDialogExS102ColorMap::InsertItemIntoComboBox()
{
	if (m_ImageList.Create(90, 20 , ILC_COLOR24, 2, 0))
	{
		if (m_Bitmap.LoadBitmap(IDB_BITMAPC_COLORMAPS))
		{
			m_nBitmapIndex = m_ImageList.Add(&m_Bitmap, (COLORREF)0x000000);
			m_ComboEx.SetImageList(&m_ImageList);
		}
	}

	LPWSTR name[9] = {
		_T("Blues"),
		_T("Oranges"),
		_T("Reds"),
		_T("Purples"),
		_T("PuOr"),
		_T("BuGn"),
		_T("RdOr"),
		_T("GnYl"),
		_T("Rainbow")
	};

	for (int i = 0; i < 9; i++) {
		COMBOBOXEXITEM cmbItem;

		cmbItem.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_TEXT;
		cmbItem.iImage = m_nBitmapIndex + i;
		cmbItem.iSelectedImage = m_nBitmapIndex + i;
		cmbItem.iItem = i;
		cmbItem.pszText = name[i];

		m_ComboEx.InsertItem(&cmbItem);
	}

	m_ComboEx.SetCurSel(0);
}



void CDialogExS102ColorMap::InsertItemIntoComboBoxCnt()
{
	for (int i = 0; i < 6; i++) {
		CString str;
		str.Format(_T("%d"), 4 + i);
		m_comboCnt.AddString(str);
	}

	m_comboCnt.SetCurSel(0);
}

void CDialogExS102ColorMap::OnBnClickedButtonClassification()
{
	int cnt = m_comboCnt.GetCurSel() + 4;

	COMBOBOXEXITEM cmbItem;
	m_ComboEx.GetItem(&cmbItem);

	colormap = calculator.Calculate(catalog.colorMap.at(m_ComboEx.GetCurSel()), cnt);

	m_list.DeleteAllItems();

	for (int i = 0; i < colormap.GetColorCount(); i++) {
		m_list.InsertItem(i, _T(" "));
	}
}


void CDialogExS102ColorMap::InitCatalog()
{
	nmColorMap::ColorMap colorMap[9];
	colorMap[0].name = _T("Blues");
	colorMap[1].name = _T("Oranges");
	colorMap[2].name = _T("Reds");
	colorMap[3].name = _T("Purples");
	colorMap[4].name = _T("PuOr");
	colorMap[5].name = _T("BuGn");
	colorMap[6].name = _T("RdOr");
	colorMap[7].name = _T("GnYl");
	colorMap[8].name = _T("Rainbow");

	colorMap[0].AddColor(RGB(0, 0, 51));
	colorMap[0].AddColor(RGB(0, 0, 255));
	colorMap[0].AddColor(RGB(205, 205, 255));

	colorMap[1].AddColor(RGB(51, 25, 0));
	colorMap[1].AddColor(RGB(255, 128, 0));
	colorMap[1].AddColor(RGB(255, 229, 204));

	colorMap[2].AddColor(RGB(51, 0, 0));
	colorMap[2].AddColor(RGB(255, 0, 0));
	colorMap[2].AddColor(RGB(255, 204, 204));

	colorMap[3].AddColor(RGB(51, 0, 51));
	colorMap[3].AddColor(RGB(255, 0, 255));
	colorMap[3].AddColor(RGB(255, 204, 255));

	colorMap[4].AddColor(RGB(255, 0, 255));
	colorMap[4].AddColor(RGB(255, 128, 0));

	colorMap[5].AddColor(RGB(0, 0, 255));
	colorMap[5].AddColor(RGB(0, 255, 0));

	colorMap[6].AddColor(RGB(255, 0, 0));
	colorMap[6].AddColor(RGB(255, 128, 0));

	colorMap[7].AddColor(RGB(0, 255, 0));
	colorMap[7].AddColor(RGB(255, 255, 0));

	colorMap[8].AddColor(RGB(139, 0, 255));
	colorMap[8].AddColor(RGB(75, 0, 130));
	colorMap[8].AddColor(RGB(0, 0, 255));
	colorMap[8].AddColor(RGB(0, 255, 0));
	colorMap[8].AddColor(RGB(255, 255, 0));
	colorMap[8].AddColor(RGB(255, 127, 0));
	colorMap[8].AddColor(RGB(255, 0, 0));

	for (int i = 0; i < 9; i++) {
		catalog.AddColorMap(colorMap[i]);
	}
}

void CDialogExS102ColorMap::OnNMCustomdrawListColorMap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	switch (pNMLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
		pNMLVCD->clrTextBk = RGB(255, 255, 255);
		for (int i = 0; i < colormap.GetColorCount(); i++) {
			if ((pNMLVCD->nmcd.dwItemSpec == i) && (pNMLVCD->iSubItem == 0)) {
				pNMLVCD->clrTextBk = RGB(colormap.color.at(i).R(),
					colormap.color.at(i).G(),
					colormap.color.at(i).B());
			}
		} 
		break;
	}
}


void CDialogExS102ColorMap::OnBnClickedRadio1()
{
	m_comboCnt.SetCurSel(0);
	m_btnClassification.EnableWindow(FALSE);
	m_comboCnt.EnableWindow(FALSE);
	OnBnClickedButtonClassification();
}


void CDialogExS102ColorMap::OnBnClickedRadio10()
{
	m_btnClassification.EnableWindow(TRUE);
	m_comboCnt.EnableWindow(TRUE);
	OnBnClickedButtonClassification();
}


void CDialogExS102ColorMap::OnBnClickedCancel()
{
	DestroyWindow();
}


void CDialogExS102ColorMap::OnBnClickedButtonApply()
{
	OnBnClickedButtonClassification();

	std::vector<COLORREF> newColorMap;
	for (int i = 0; i < colormap.GetColorCount(); i++) {
		newColorMap.push_back(RGB(colormap.color.at(i).R(), colormap.color.at(i).G(), colormap.color.at(i).B()));
	}

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
	BOOL checked = pButton->GetCheck();

	if (checked) {
		theApp.pView->m_pGisLib->UpdateS102ColorMapType(0, newColorMap);
	}
	else {
		theApp.pView->m_pGisLib->UpdateS102ColorMapType(1, newColorMap);
	}

	theApp.pView->MapRefresh();
}


void CDialogExS102ColorMap::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	delete this;
}


void CDialogExS102ColorMap::OnBnClickedOk()
{
	OnBnClickedButtonClassification();

	std::vector<COLORREF> newColorMap;
	for (int i = 0; i < colormap.GetColorCount(); i++) {
		newColorMap.push_back(RGB(colormap.color.at(i).R(), colormap.color.at(i).G(), colormap.color.at(i).B()));
	}

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
	BOOL checked = pButton->GetCheck();

	if (checked) {
		theApp.pView->m_pGisLib->UpdateS102ColorMapType(0, newColorMap);
	}
	else {
		theApp.pView->m_pGisLib->UpdateS102ColorMapType(1, newColorMap);
	}

	theApp.pView->MapRefresh();

	DestroyWindow();
}

void CDialogExS102ColorMap::OnCbnSelchangeComboboxex1()
{
	OnBnClickedButtonClassification();
}


void CDialogExS102ColorMap::OnCbnSelchangeCombo1()
{
	OnBnClickedButtonClassification();
}
