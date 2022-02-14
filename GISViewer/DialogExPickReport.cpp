// DialogExPickReport.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExPickReport.h"
#include "afxdialogex.h"
#include "DialogAddFeatureList.h"
#include "GISViewerView.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "S100Geometry\\SGeometry.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"


#include <sstream>
#include <vector>
#include <algorithm> 

IMPLEMENT_DYNAMIC(CDialogExPickReport, CDialogEx)

bool CompareObject(const ObjectItem *&elem1, const ObjectItem *&elem2)
{ 
	if (elem1->_description == elem2->_description) 
		return elem1->_description < elem2->_description; 
	return elem1->_description < elem2->_description;
};          

CDialogExPickReport::CDialogExPickReport(CWnd* pParent )
	: CDialogEx(CDialogExPickReport::IDD, pParent)
{
	m_pView = nullptr;
	m_searchCode = L"";
	m_catalog = NULL;
}

CDialogExPickReport::~CDialogExPickReport()
{
	for (auto itor = m_allFeatureItems.begin(); itor != m_allFeatureItems.end(); itor++)
	{
		if ((*itor)->type == 0)
			delete (ObjectItem*)(*itor);
		else if ((*itor)->type == 1)
			delete (FeatureItem*)(*itor);
	}

	m_allFeatureItems.clear();

}


void CDialogExPickReport::SetView(CGISViewerView* v)
{
	m_pView = v;
}
void CDialogExPickReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PIC_POINT, m_pointSelect);
	DDX_Control(pDX, IDC_CHECK_PIC_CURVE, m_curveSelect);
	DDX_Control(pDX, IDC_CHECK_PIC_SURFACE, m_surfaceSelect);
	DDX_Control(pDX, IDC_EDIT_PIC_NAME, m_searchFeatureName);
	DDX_Control(pDX, IDC_BTN_PIC_SEARCH, m_searchButton);
	DDX_Control(pDX, IDC_BTN_PIC_FILTER, m_btnFilter);
}


BEGIN_MESSAGE_MAP(CDialogExPickReport, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDialogExPickReport::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExPickReport::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OBJECT, &CDialogExPickReport::OnLvnItemchangedListObject)
	ON_NOTIFY(NM_CLICK, IDC_LIST_OBJECT, &CDialogExPickReport::OnNMClickListObject)
	ON_BN_CLICKED(IDC_CHECK_PIC_POINT, &CDialogExPickReport::OnBnClickedCheckPicPoint)
	ON_BN_CLICKED(IDC_CHECK_PIC_CURVE, &CDialogExPickReport::OnBnClickedCheckPicCurve)
	ON_BN_CLICKED(IDC_CHECK_PIC_SURFACE, &CDialogExPickReport::OnBnClickedCheckPicSurface)
	ON_BN_CLICKED(IDC_BTN_PIC_SEARCH, &CDialogExPickReport::OnBnClickedBtnPicSearch)
	ON_BN_CLICKED(IDC_BTN_PIC_FILTER, &CDialogExPickReport::OnBnClickedBtnPicFilter)
END_MESSAGE_MAP() 


void CDialogExPickReport::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CStatic* pGroupObject          = (CStatic*)GetDlgItem(IDC_STATIC_OBJECT);
	CListCtrl* pListCtrlObject     = (CListCtrl*)GetDlgItem(IDC_LIST_OBJECT);


	if (m_pointSelect.GetSafeHwnd())
	{
		m_pointSelect.MoveWindow(10, 15, 55, 30);
	}
	if (m_curveSelect.GetSafeHwnd())
	{
		m_curveSelect.MoveWindow(70, 15, 60, 30);
	}
	if (m_surfaceSelect.GetSafeHwnd())
	{
		m_surfaceSelect.MoveWindow(135, 15, 60, 30);
	}

	if (m_btnFilter.GetSafeHwnd())
	{
		m_btnFilter.MoveWindow(5, 45, 50, 20);
	}

	if (m_searchFeatureName.GetSafeHwnd())
	{
		m_searchFeatureName.MoveWindow(60, 45, 170, 20);
	}

	if (m_searchButton.GetSafeHwnd())
	{
		m_searchButton.MoveWindow(235, 45, 50, 20);
	}


	if (pGroupObject->GetSafeHwnd())
	{
		pGroupObject->MoveWindow(0, 0, cx, cy - 10);
	}

	if (pListCtrlObject->GetSafeHwnd())
	{
		pListCtrlObject->MoveWindow(5, 70, cx - 10, cy - 85);

		CRect rect;
		pListCtrlObject->GetClientRect(rect);

		pListCtrlObject->SetColumnWidth(0, 0);
		pListCtrlObject->SetColumnWidth(1, rect.Width());  

		for (int i = 0; i < pListCtrlObject->GetHeaderCtrl()->GetItemCount(); ++i)
			pListCtrlObject->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}


BOOL CDialogExPickReport::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	CListCtrl* pListCtrlObject     = (CListCtrl*)GetDlgItem(IDC_LIST_OBJECT);

	if (pListCtrlObject->GetSafeHwnd())
	{ 
		pListCtrlObject->SetExtendedStyle(LVS_EX_FULLROWSELECT);

		pListCtrlObject->InsertColumn(0, _T("Feature Name"), LVCFMT_LEFT, 1, 1);
		pListCtrlObject->InsertColumn(1, _T("Geo Type"), LVCFMT_LEFT, 1, 1);
		pListCtrlObject->InsertColumn(2, _T("ID"), LVCFMT_LEFT, 1, 1);
	}

	if (m_pointSelect.GetSafeHwnd())
	{
		m_pointSelect.SetCheck(TRUE);
	}
	if (m_curveSelect.GetSafeHwnd())
	{
		m_curveSelect.SetCheck(TRUE);
	}
	if (m_surfaceSelect.GetSafeHwnd())
	{
		m_surfaceSelect.SetCheck(TRUE);
	}

	return TRUE;  
}


void CDialogExPickReport::OnBnClickedOk()
{
}


void CDialogExPickReport::OnBnClickedCancel()
{
	m_pView->fePickGML = nullptr;
	m_pView->fePick = nullptr;
	m_pView->frPick = nullptr;
	m_pView->onPickArrow = false;  
	m_pView->Invalidate();
}


void CDialogExPickReport::InitObjectList()
{
	CListCtrl* pListCtrlObject     = (CListCtrl*)GetDlgItem(IDC_LIST_OBJECT);

	if (pListCtrlObject->GetSafeHwnd())
	{
		pListCtrlObject->DeleteAllItems();
	}

	for (auto itor = m_allFeatureItems.begin(); itor != m_allFeatureItems.end(); itor++)
	{
		if ((*itor)->type == 0)
			delete (ObjectItem*)(*itor);
		else if ((*itor)->type == 1)
			delete (FeatureItem*)(*itor);
	}

	m_allFeatureItems.clear();
	m_activeFeatureItems.clear(); 
}          


void CDialogExPickReport::AddObject(CString _description, CString _acronym, CString _cellName, ENC_Feature* _feature, ENCCell* cell)
{  
	std::unordered_map<int, bool>::iterator itor;
	itor = ENCCommon::objectDisplaySettings.find(_feature->m_frid.OBJL);

	if (itor != ENCCommon::objectDisplaySettings.end())
	{
		if (!itor->second)
		{
			return;
		}
	} 

	ObjectItem *oi = new ObjectItem();

	oi->_description = _description;
	oi->_acronym = _acronym;
	oi->_cellName = _cellName;
	oi->_feature = _feature;
	oi->_cell = cell;

	m_allFeatureItems.push_back(oi);
}

void CDialogExPickReport::AddObject(CString _description, CString _acronym, CString _cellName, R_FeatureRecord* _feature, S101Cell* cell)
{
	FeatureItem *fi = new FeatureItem();

	fi->_description = _description;
	fi->_acronym = _acronym;
	fi->_cellName = _cellName;
	fi->_feature = _feature;
	fi->_cell = cell;

	m_allFeatureItems.push_back(fi);
}

void CDialogExPickReport::ChangeObject(CString _description, CString _acronym, CString _cellName, R_FeatureRecord* _feature, S101Cell* cell, int index)
{
	CListCtrl* pListCtrlObject = (CListCtrl*)GetDlgItem(IDC_LIST_OBJECT);

	if (index == -1)
	{
		index = pListCtrlObject->GetNextItem(-1, LVNI_SELECTED);
		if (index == -1)
		{
			return;
		}
	}

	FeatureItem *fi = (FeatureItem *)m_activeFeatureItems[index];
	fi->_description = _description;
	fi->_acronym = _acronym;
	fi->_cellName = _cellName;
	fi->_feature = _feature;
	fi->_cell = cell;

	
	SetObjectListCtrl(((S101Layer*)cell->m_pLayer)->GetFC());
}

void CDialogExPickReport::SortObjectList()
{
	m_activeFeatureItems.clear();

	for (auto itor = m_allFeatureItems.begin(); itor != m_allFeatureItems.end(); itor++)
	{
		if ((*itor)->type == 0)
		{
			ObjectItem* item = (ObjectItem*)(*itor);
			if (item->_feature->m_frid.PRIM == 1)
			{
				if (m_pointSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
			else if (item->_feature->m_frid.PRIM == 2)
			{
				if (m_curveSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
			else if (item->_feature->m_frid.PRIM == 3)
			{
				if (m_surfaceSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
		}
		else if ((*itor)->type == 1)
		{
			FeatureItem *item = (FeatureItem*)(*itor);

			if (item->_acronym.Compare(m_searchCode.c_str()) != 0 && m_searchCode.compare(L"") != 0)
				continue;

			if (item->_feature->m_geometry->type == 1)
			{
				if (m_pointSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
			else if (item->_feature->m_geometry->type == 2)
			{
				if (m_curveSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
			else if (item->_feature->m_geometry->type == 3)
			{
				if (m_surfaceSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
			else if (item->_feature->m_geometry->type == 4)
			{
				if (m_pointSelect.GetCheck())
				{
					m_activeFeatureItems.push_back(item);
				}
			}
		}
	}

	m_pView->fePickGML = nullptr;
	m_pView->fePick = nullptr;
	m_pView->frPick = nullptr;
	m_pView->Invalidate();
	SetObjectListCtrl(m_catalog);

}

void CDialogExPickReport::SetObjectListCtrl(Catalog *catalog)
{
	CListCtrl* pListCtrlObject     = (CListCtrl*)GetDlgItem(IDC_LIST_OBJECT);

	if (pListCtrlObject->GetSafeHwnd())
	{
		pListCtrlObject->DeleteAllItems();
	} 
	int cnt = 0;
	if (pListCtrlObject->GetSafeHwnd())
	{
		m_catalog = catalog;
		for (auto itor = m_activeFeatureItems.rbegin(); itor != m_activeFeatureItems.rend(); itor++)
		{
			if ((*itor)->type == 0)
			{
				ObjectItem *item = (ObjectItem *)*itor;
				pListCtrlObject->InsertItem(cnt, item->_description);
				pListCtrlObject->SetItemText(cnt, 1, item->_acronym);
				pListCtrlObject->SetItemText(cnt, 2, item->_cellName.Mid(0, item->_cellName.GetLength() - 4));
			}
			else if((*itor)->type == 1)
			{
				FeatureItem *item = (FeatureItem *)*itor;
				FeatureCatalogue *fc = catalog->m_pCatalogueList.begin()->second;
				FeatureType* ft = fc->GetFeatureType(item->_acronym.GetBuffer());
				if (ft)
				{
					pListCtrlObject->InsertItem(cnt, ft->name.c_str());
				}
				else
				{
					pListCtrlObject->InsertItem(cnt, item->_acronym.GetBuffer());
				}
				
				if (item->_feature->m_geometry->type == 1)
					pListCtrlObject->SetItemText(cnt, 1, L"Point");
				else if (item->_feature->m_geometry->type == 2)
					pListCtrlObject->SetItemText(cnt, 1, L"Curve");
				else if (item->_feature->m_geometry->type == 3)
					pListCtrlObject->SetItemText(cnt, 1, L"Surface");
				else if (item->_feature->m_geometry->type == 4)
					pListCtrlObject->SetItemText(cnt, 1, L"Multi Point");

				std::wstringstream wss;
				wss << item->_feature->m_frid.m_name.RCID;
				pListCtrlObject->SetItemText(cnt, 2, wss.str().c_str());
			}

		}
	}

	
}


void CDialogExPickReport::OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	if (pNMLV->uChanged & LVIF_STATE)
	{
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED))
		{
			if (pNMLV->iItem < 0)
				return;

			ENCItem* pItem = m_activeFeatureItems[pNMLV->iItem];
			if (pItem->type == 1)
			{
				FeatureItem* pFi = (FeatureItem* )pItem;
				R_FeatureRecord *pFe = pFi->_feature;
				S101Cell* cell = pFi->_cell;

				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(pFe->m_frid.m_nftc);
				Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
				FeatureType* ft = catalog->m_pCatalogueList.begin()->second->GetFeatureType(itor->second->m_code.GetBuffer());

				theApp.m_DockablePaneAttributeList.SetShowTree(catalog, ft);
				theApp.m_DockablePaneEditWindow.SetSpatialObject(cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(pFe);
				
				m_pView->EndOfEditing();
			}
			else if (pItem->type == 0)
			{
				ObjectItem* pOi = (ObjectItem*)pItem;
				ENC_Feature *pFe = pOi->_feature;
				ENCCell* cell = pOi->_cell;

				CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(pFe->m_frid.OBJL);   

				theApp.m_DockablePaneAttributeList.SetShowTree(obj);
				theApp.m_DockablePaneEditWindow.SetSpatialObject(cell); 
			}
		}
	}

	*pResult = 0;
}


void CDialogExPickReport::OnNMClickListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	if (pNMItemActivate->iItem < 0)
		return;
	if (pNMItemActivate->iItem >= 0)
	{
		if (m_activeFeatureItems[pNMItemActivate->iItem]->type == 0)
		{
			m_pView->fePick = ((ObjectItem*)m_activeFeatureItems[pNMItemActivate->iItem])->_feature;
		}
		else if (m_activeFeatureItems[pNMItemActivate->iItem]->type == 1)
		{
			m_pView->SetPickReportFeature(((FeatureItem*)m_activeFeatureItems[pNMItemActivate->iItem])->_feature);
		}
		m_pView->ptPick.x = -100;
		m_pView->ptPick.y = -100;

		m_pView->Invalidate();

	}
	*pResult = 0;
}


void CDialogExPickReport::OnBnClickedCheckPicPoint()
{
	SortObjectList();
}


void CDialogExPickReport::OnBnClickedCheckPicCurve()
{
	SortObjectList();
}


void CDialogExPickReport::OnBnClickedCheckPicSurface()
{
	SortObjectList();
}


void CDialogExPickReport::OnBnClickedBtnPicSearch()
{
	m_allFeatureItems.clear();

	CDialogAddFeatureList dlg;

	dlg.SetView(m_pView);
	dlg.m_mode = 0;

	Layer* layer = m_pView->GetCurrentLayer();

	if (layer == NULL)
		return;

	m_pView->m_pNewFeatureManager->m_cell = layer->m_spatialObject;
	Catalog* catalog = ((S101Layer*)layer)->GetFC();

	if (dlg.DoModal() == IDOK)
	{
		if (!m_pView->m_pNewFeatureManager->GetFeatureType())
		{
			S101Cell *cell = (S101Cell*)layer->m_spatialObject;
			POSITION pos = cell->m_feaMap.GetStartPosition();

			while (pos != NULL)
			{
				__int64 key = 0;
				R_FeatureRecord* fr = NULL;
				cell->m_feaMap.GetNextAssoc(pos, key, fr);

				int code = fr->m_frid.m_nftc;

				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);

				AddObject(itor->second->m_code,
					itor->second->m_code,
					cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
					fr,
					cell);
			}
		}
		else 
		{
			m_searchCode = m_pView->m_pNewFeatureManager->GetFeatureType()->code.GetValueString().c_str();
			std::wstring value = m_pView->m_pNewFeatureManager->GetFeatureType()->name.c_str();
			m_searchFeatureName.SetWindowText(value.c_str());
		
			S101Cell *cell = (S101Cell*)layer->m_spatialObject;
			POSITION pos = cell->m_feaMap.GetStartPosition();

			while (pos != NULL) 
			{
				__int64 key = 0;
				R_FeatureRecord* fr = NULL;
				cell->m_feaMap.GetNextAssoc(pos, key, fr);
			
				int code = fr->m_frid.m_nftc;

				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);

				if (m_searchCode.compare(itor->second->m_code) == 0)
				{ 
					AddObject(itor->second->m_code,
						itor->second->m_code,
						cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
						fr,
						cell);
				}
			}
		} 
		SortObjectList();
	}
}


void CDialogExPickReport::OnBnClickedBtnPicFilter()
{
	CDialogAddFeatureList dlg;

	dlg.SetView(m_pView);
	dlg.m_mode = 0;

	Layer* layer = m_pView->GetCurrentLayer();

	if (layer == NULL)
		return;

	m_pView->m_pNewFeatureManager->m_cell = layer->m_spatialObject;
	Catalog* catalog = ((S101Layer*)layer)->GetFC();

	if (dlg.DoModal() == IDOK)
	{
		if (!m_pView->m_pNewFeatureManager->GetFeatureType())
		{
			m_searchCode = L"";
		}
		else 
		{
			m_searchCode = m_pView->m_pNewFeatureManager->GetFeatureType()->code.GetValueString().c_str();
			std::wstring value = m_pView->m_pNewFeatureManager->GetFeatureType()->name.c_str();
			m_searchFeatureName.SetWindowText(value.c_str());
		}
		SortObjectList();
	}
}
