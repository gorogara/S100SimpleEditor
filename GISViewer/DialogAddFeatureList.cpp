// DialogAddFeatureList.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogAddFeatureList.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "PLLibrary\\GeoObject.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h" 

IMPLEMENT_DYNAMIC(CDialogAddFeatureList, CDialogEx)

CDialogAddFeatureList::CDialogAddFeatureList(CWnd* pParent )
	: CDialogEx(CDialogAddFeatureList::IDD, pParent)
{ 
}

CDialogAddFeatureList::~CDialogAddFeatureList()
{
}

void CDialogAddFeatureList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_NEW_FEATURE, m_ListAddFeature);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT_FILTER, m_eFilter);
}


BEGIN_MESSAGE_MAP(CDialogAddFeatureList, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDialogAddFeatureList::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_FILTER, &CDialogAddFeatureList::OnEnChangeEditFilter)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NEW_FEATURE, &CDialogAddFeatureList::OnLvnItemchangedListNewFeature)
END_MESSAGE_MAP() 

void CDialogAddFeatureList::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_eFilter.GetSafeHwnd())
	{
		m_eFilter.MoveWindow(5, 10, cx - 10, 20);
	}

	if (m_ListAddFeature.GetSafeHwnd())
	{
		m_ListAddFeature.MoveWindow(5, 35, cx - 10, cy - 70);

		CRect rect;
		m_ListAddFeature.GetClientRect(rect);

		m_ListAddFeature.SetColumnWidth(0, 200);
		m_ListAddFeature.SetColumnWidth(1, (rect.Width() - 200));

	}
	if (m_btOK.GetSafeHwnd())
	{
		m_btOK.MoveWindow(cx - 200, cy - 30, 90, 25);
	}
	if (m_btCancel.GetSafeHwnd())
	{
		m_btCancel.MoveWindow(cx - 100, cy - 30, 90, 25);
	}
}

BOOL CDialogAddFeatureList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListAddFeature.SetExtendedStyle(m_ListAddFeature.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListAddFeature.InsertColumn(0, _T("Name"), LVCFMT_CENTER, 40);
	m_ListAddFeature.InsertColumn(1, _T("Definition"), LVCFMT_LEFT, 40);


	SetWindowPos(NULL, 0, 0, 500, 600, SWP_NOMOVE | SWP_NOZORDER);

	SetCatalogueList();

	return TRUE;
}

void CDialogAddFeatureList::OnBnClickedOk()//확인버튼이 클릭되면 넘어오는곳
{
	POSITION pos = m_ListAddFeature.GetFirstSelectedItemPosition();
	int cnt = m_ListAddFeature.GetNextSelectedItem(pos);

	if (cnt < 0)
	{

	}

	else if (m_pView->m_pNewFeatureManager->m_cell->m_FileType == S100_FileType::FILE_S_57)
	{
		CGeoObject* obj = (CGeoObject*)m_ListAddFeature.GetItemData(cnt);
		m_pView->m_pNewFeatureManager->m_featureType = obj->Code;
		m_pView->m_pNewFeatureManager->m_geometryType = m_mode;
	}
	else if (m_pView->m_pNewFeatureManager->m_cell->m_FileType == S100_FileType::FILE_S_100_VECTOR)
	{
		S101Cell* cell = (S101Cell*)m_pView->m_pNewFeatureManager->m_cell;
		m_pView->m_pNewFeatureManager->SetFeatureType(m_pView->m_pNewFeatureManager->GetCatalog() , (FeatureType*)m_ListAddFeature.GetItemData(cnt)); 

		auto itor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(m_pView->m_pNewFeatureManager->GetFeatureType()->code.GetValueString().c_str());
		if (itor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
		{
			CodeWithNumericCode* nc = itor->second; 
			m_pView->m_pNewFeatureManager->m_featureType = nc->m_nmcd;
			m_pView->m_pNewFeatureManager->m_geometryType = m_mode;
		}
		else
		{
			unsigned index = 0;
			for (unsigned i = 200; i < 1048575; i++)////?
			{
				auto fitor = cell->m_dsgir.m_ftcs->m_arr.find(i);

				if (fitor == cell->m_dsgir.m_ftcs->m_arr.end())
				{
					index = i;
					break;
				}
			}

			CodeWithNumericCode *cnc = new CodeWithNumericCode();
			cnc->m_nmcd = index;
			cnc->m_code = m_pView->m_pNewFeatureManager->GetFeatureType()->code.GetValueString().c_str();

			cell->m_dsgir.m_ftcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));
			cell->m_dsgir.m_ftcs->m_arrFindForCode.insert(std::unordered_map<std::wstring, CodeWithNumericCode*>::value_type(cnc->m_code.GetBuffer(), cnc));

			m_pView->m_pNewFeatureManager->m_featureType = cnc->m_nmcd;
			m_pView->m_pNewFeatureManager->m_geometryType = m_mode;
		}
	}

	CDialogEx::OnOK();
}

void CDialogAddFeatureList::SetView(CGISViewerView *pView)
{
	m_pView = pView;
}

void CDialogAddFeatureList::SetCatalogueList() 
{ 
	theApp.GetDockFeatureInformationList().SetindexNum(0);
	theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);

	m_ListAddFeature.DeleteAllItems();
	int iItem = 0;
	if (m_pView->m_pNewFeatureManager->m_cell->m_FileType == S100_FileType::FILE_S_57)
	{
		ENCCell* cell = (ENCCell*)m_pView->m_pNewFeatureManager->m_cell;     

		CGeoObjectMap::Geometric_type type;
		switch (m_mode)
		{
		case 1:
			type = CGeoObjectMap::Geometric_type::POINT1;
			break;
		case 2:
			type = CGeoObjectMap::Geometric_type::LINE1;
			break;
		case 3:
			type = CGeoObjectMap::Geometric_type::AREA1;
			break;
		}

		for (int i = 0; i < ENCGeometry::pObject->GetSize(); i++)
		{
			CGeoObject* obj = ENCGeometry::pObject->GetAt(i);

			if (!obj)
				continue;

			if (obj->Geometric_primitives & type)
			{
				LVITEM lvi;
				lvi.mask = LVIF_TEXT;
				lvi.iItem = iItem;
				lvi.iSubItem = 0;
				lvi.pszText = (LPTSTR)(LPCTSTR)(obj->Object_class);
				lvi.lParam = (LPARAM)obj;
				BOOL ret = 0;
				int indexItem = m_ListAddFeature.InsertItem(&lvi);
				ret = m_ListAddFeature.SetItemText(indexItem, 0, obj->Acronym);
				ret = m_ListAddFeature.SetItemText(indexItem, 1, obj->Object_class);
				m_ListAddFeature.SetItemData(indexItem, (LPARAM)obj);

				iItem++;
			}
		}
	}
	else if (m_pView->m_pNewFeatureManager->m_cell->m_FileType == S100_FileType::FILE_S_100_VECTOR)
	{
		Catalog *catalog = ((S101Layer*)m_pView->m_pNewFeatureManager->m_cell->m_pLayer)->GetFC();
		FeatureCatalogue *fc = catalog->m_pCatalogueList.begin()->second;

		std::wstring type = L"";

		switch (m_mode)
		{
		case 1:
			type = L"point";
			break;
		case 2:
			type = L"curve";
			break;
		case 3:
			type = L"surface";
			break;
		case 4:
			type = L"pointSet";
			break;
		}

		for (auto itor = fc->featureTypes.featureType.begin();
			itor != fc->featureTypes.featureType.end();
			itor++)
		{

			FeatureType* ft = &(itor->second); 
			if (m_strFilter.size() > 0)
			{
				wstring name = ft->name;
				std::transform(name.begin(), name.end(), name.begin(), tolower);
				std::transform(m_strFilter.begin(), m_strFilter.end(), m_strFilter.begin(), tolower);

				size_t searchSize = name.find(m_strFilter);
				if (searchSize > ft->name.size())
					continue;
			} 

			bool isInsert = false;
			for (auto itorPermitted = ft->permittedPrimitives.begin();
				itorPermitted != ft->permittedPrimitives.end();
				itorPermitted++)
			{
				std::wstring curType = itorPermitted->GetValueString();

				if (type.compare(curType) == 0 || type.compare(L"") == 0)
				{
					isInsert = true;
				}
			}

			if (isInsert)
			{
				LVITEM lvi;

				lvi.mask = LVIF_TEXT;
				lvi.iItem = iItem;
				lvi.iSubItem = 0;
				lvi.pszText = (LPTSTR)(LPCTSTR)(ft->name.c_str());
				lvi.lParam = (LPARAM)ft;
				BOOL ret = m_ListAddFeature.InsertItem(&lvi);

				CString str;
				if (ft->alias.size() > 0)
				{
					std::wstring t = *ft->alias.begin();
					str.Format(L"[S-101 : %s] %s", t.c_str(), ft->name.c_str());
				}
				else
				{
					str.Format(L"%s", ft->name.c_str());
				}
				ret = m_ListAddFeature.SetItemText(iItem, 0, str);
				ret = m_ListAddFeature.SetItemText(iItem, 1, ft->definition.c_str());
				m_ListAddFeature.SetItemData(iItem, (LPARAM)ft);

				iItem++;
			}
		}
	}
}

void CDialogAddFeatureList::OnEnChangeEditFilter()
{    
	CString msg;
	m_eFilter.GetWindowText(msg);
	m_strFilter = msg;
	SetCatalogueList();
}

BOOL CDialogAddFeatureList::PreTranslateMessage(MSG* pMsg)
{ 
	if (pMsg->wParam == VK_RETURN )
	{
		POSITION pos = m_ListAddFeature.GetFirstSelectedItemPosition();
		int cnt = m_ListAddFeature.GetNextSelectedItem(pos);
		if (cnt < 0)
			return TRUE;
		else
		{
			FeatureType* ft = (FeatureType*)m_ListAddFeature.GetItemData(cnt);
			m_strFilter = ft->code.GetValueString();
			m_pView->m_pNewFeatureManager->SetFeatureType(NULL, ft);
			SetCatalogueList();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDialogAddFeatureList::OnLvnItemchangedListNewFeature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	*pResult = 0;
}