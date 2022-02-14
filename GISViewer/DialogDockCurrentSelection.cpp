// DialogDockCurrentSelection.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "GISViewerView.h"
#include "DialogDockCurrentSelection.h"
#include "DialogDockRelation.h"
#include "DialogExChangeAll.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

using namespace std; 

IMPLEMENT_DYNAMIC(CDialogDockCurrentSelection, CDialogEx)

CDialogDockCurrentSelection::CDialogDockCurrentSelection(CWnd* pParent )
	: CDialogEx(CDialogDockCurrentSelection::IDD, pParent)
{
}

CDialogDockCurrentSelection::~CDialogDockCurrentSelection()
{
}

void CDialogDockCurrentSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CURRENT_SELECTION, m_ListCurrentSelection);
}


BEGIN_MESSAGE_MAP(CDialogDockCurrentSelection, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDOK, &CDialogDockCurrentSelection::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogDockCurrentSelection::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CURRENT_SELECTION, &CDialogDockCurrentSelection::OnLvnItemchangedList) 
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDialogDockCurrentSelection::OnHdnItemclickListCurrentSelection)
END_MESSAGE_MAP() 
int CDialogDockCurrentSelection::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CDialogDockCurrentSelection::OnBnClickedOk()
{ 
	return;
}


void CDialogDockCurrentSelection::OnBnClickedCancel()
{ 
	return;
}


void CDialogDockCurrentSelection::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 
	if (pNMLV->uChanged & LVIF_STATE)
	{
		if (pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED))
		{
			if (pNMLV->iItem < 0)
			{
				return;
			}

			POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
			int idx = 0; 
			CString objId;
			CString featureType;

			idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
			if (idx < 0)
			{
				return;
			}
			objId.Format(m_ListCurrentSelection.GetItemText(idx, 1));
			featureType.Format(m_ListCurrentSelection.GetItemText(idx, 7));
			__int64 objIdN = _tcstoui64(objId, NULL, 10);

			if (featureType == L"Feature")
			{ 
				__int64 key = ((__int64)100) << 32 | objIdN;

				auto feature = m_Cell->m_feaMap.PLookup(key);

				if (feature == NULL)
				{
					return;
				}

				R_FeatureRecord *rfr = feature->value; 
				R_FeatureRecord *pFe = rfr;
				S101Cell* cell = m_Cell;
				if (cell == nullptr)
				{ 
					return;
				}

				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(pFe->m_frid.m_nftc);
				Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC(); 
				FeatureType* ft = catalog->m_pCatalogueList.begin()->second->GetFeatureType(itor->second->m_code.GetBuffer()); 
				theApp.pView->m_pNewFeatureManager->SetFeatureType(catalog, ft);
				CString geoType = m_ListCurrentSelection.GetItemText(idx, 3);

				if (theApp.IsEditingMode())
				{
					theApp.m_DockablePaneAttributeList.SetShowTree(catalog, ft);
				}

				theApp.m_DockablePaneEditWindow.SetSpatialObject(cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(pFe);

				if (geoType != L"No geometry")
				{
					auto layer = cell->GetLayer();
					if (nullptr != layer)
					{
						if (true == layer->IsOn())
						{
							pView->SetPickReportFeature(pFe);
							pView->Invalidate();
						}
					}
				}
			}
			else if (featureType == L"Information")
			{
				__int64 key = ((__int64)150) << 32 | objIdN;

				if (m_Cell->m_infMap.GetCount() == 0)
				{
					int i = 0;
					return;
				}

				R_InformationRecord *rfr = m_Cell->m_infMap.PLookup(key)->value;
				S101Cell* cell = m_Cell;

				auto itor = cell->m_dsgir.m_itcs->m_arr.find(rfr->m_irid.m_nitc);
				Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();

				m_selectedInformationType = catalog->m_pCatalogueList.begin()->second->GetInformationType(itor->second->m_code.GetBuffer());

				theApp.m_DockablePaneAttributeList.SetShowTree(catalog, m_selectedInformationType);
				theApp.m_DockablePaneEditWindow.SetSpatialObject(cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(rfr);
			}

			pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
			idx = 0;

			std::list<R_FeatureRecord*> flist;
			std::list<R_InformationRecord*> infoList;

			while (pos)
			{
				CString objId;
				CString featureType;
				idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
				objId.Format(m_ListCurrentSelection.GetItemText(idx, 1));
				featureType.Format(m_ListCurrentSelection.GetItemText(idx, 7)); 
				__int64 objIdN = _tcstoui64(objId, NULL, 10);
				R_FeatureRecord *rfr;
				R_InformationRecord *ifr;

				if (featureType == L"Feature")
				{
					__int64 key = ((__int64)100) << 32 | objIdN;
					rfr = m_Cell->m_feaMap.PLookup(key)->value;
					flist.push_back(rfr);
				}
				else if (featureType == L"Information")
				{
					__int64 key = ((__int64)150) << 32 | objIdN;
					ifr = m_Cell->m_infMap.PLookup(key)->value;
					infoList.push_back(ifr);
				}
			}
			theApp.m_DockablePaneRelation.pDlg->SetFeatureList(m_Cell, flist, infoList);
		}
	}
	*pResult = 0;
}


void CDialogDockCurrentSelection::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CDialogDockCurrentSelection::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
} 
BOOL CDialogDockCurrentSelection::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	m_ListCurrentSelection.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListCurrentSelection.ModifyStyle(LVS_SINGLESEL, 0);   
	CRect listRect;
	m_ListCurrentSelection.GetWindowRect(listRect);
	m_ListCurrentSelection.InsertColumn(0, _T("Feature ID "), LVCFMT_LEFT, (int)(listRect.Width()*0.10));
	m_ListCurrentSelection.InsertColumn(1, _T("FrID "), LVCFMT_LEFT, (int)(listRect.Width() * 0)); 
	m_ListCurrentSelection.InsertColumn(2, _T("Name"), LVCFMT_LEFT, (int)(listRect.Width()*0.30));
	m_ListCurrentSelection.InsertColumn(3, _T("Geometry"), LVCFMT_LEFT, (int)(listRect.Width()*0.10));
	m_ListCurrentSelection.InsertColumn(4, _T("Lat"), LVCFMT_CENTER, (int)(listRect.Width()*0.15));
	m_ListCurrentSelection.InsertColumn(5, _T("Long"), LVCFMT_CENTER, (int)(listRect.Width()*0.15));
	m_ListCurrentSelection.InsertColumn(6, _T("Relation Cnt"), LVCFMT_LEFT, (int)(listRect.Width()*0.10));
	m_ListCurrentSelection.InsertColumn(7, _T("Feature type"), LVCFMT_LEFT, (int)(listRect.Width()*0.10));

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	AdjustLayout(); 

	return TRUE; 

} 
void CDialogDockCurrentSelection::UpdateListTest(CStringArray *csa, S101Cell *cell, CString isCtrlClicked)
{

	CString tmp;
	m_Cell = cell; 

	if (isCtrlClicked == L"0")
	{
		m_ListCurrentSelection.DeleteAllItems();
	}

	Catalog* catalog = ((S101Layer*)theApp.pView->m_pNewFeatureManager->m_cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;

	for (int i = 0; i < csa->GetSize(); i++)
	{

		int nTokenPos = 0;
		int cnt = 0;

		CString strToken = csa->GetAt(i).Tokenize(_T("|||"), nTokenPos);


		if (strToken != L"")
		{

			CString cs = csa->GetAt(i);
			std::string str1 = std::string(CT2CA(cs.operator LPCWSTR()));

			char toks[4] = { "|||" };
			string * tok = StringSplit(str1, toks);

			CString foid = CString::CStringT(CA2CT(tok[1].c_str()));
			CString frid = CString::CStringT(CA2CT(tok[2].c_str()));
			CString lat = CString::CStringT(CA2CT(tok[3].c_str()));
			CString lon = CString::CStringT(CA2CT(tok[4].c_str()));
			CString csType = CString::CStringT(CA2CT(tok[5].c_str())); 
			wstring ws_name = wstring(tok[6].begin(), tok[6].end());
			CString name;
			CString assoCnt = CString::CStringT(CA2CT(tok[7].c_str()));
			CString featureType = CString::CStringT(CA2CT(tok[8].c_str()));
			CString type;

			auto fc_featureTypeORG = fc->GetFeatureType(ws_name);

			if (fc_featureTypeORG)
				name.Format(_T("%s"), fc_featureTypeORG->name.c_str());
			else
				name.Format(_T("%s"), ws_name); 

			if (csType == "1") {
				type = "point";
			}
			else if (csType == "2") {
				type = "curve";
			}
			else if (csType == "3") {
				type = "surface";
			}
			else if (csType == "4") {
				type = "multipoint (sounding)";
			}
			else if (csType == "999") {
				type = "No geometry";
			}
			else {
				type = "-";
			}

			bool isExist = false; 
			for (int j = 0; j < m_ListCurrentSelection.GetItemCount(); j++)
			{
				if (frid == m_ListCurrentSelection.GetItemText(j, 0) && featureType == m_ListCurrentSelection.GetItemText(j, 7))
				{
					isExist = true;
				}
			}

			int count = m_ListCurrentSelection.GetItemCount();

			if (!isExist)
			{

				LVITEM firstItem = { 0 };
				m_ListCurrentSelection.InsertItem(&firstItem);  
				m_ListCurrentSelection.SetItemText(0, 0, frid);
				m_ListCurrentSelection.SetItemText(0, 1, frid);
				m_ListCurrentSelection.SetItemText(0, 2, name);
				m_ListCurrentSelection.SetItemText(0, 3, type);
				m_ListCurrentSelection.SetItemText(0, 4, lon);
				m_ListCurrentSelection.SetItemText(0, 5, lat);
				m_ListCurrentSelection.SetItemText(0, 6, assoCnt);
				m_ListCurrentSelection.SetItemText(0, 7, featureType);

				if (featureType == L"Feature")
				{ 

					auto it = fc->featureTypes.featureType.find(wstring(name));
					if (it == fc->featureTypes.featureType.end())
					{
						CString msg;
						msg.Format(L"[%s] Feature not found. -CURRENT SELECTION", name.GetBuffer());
						KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::FC);
					}
					else
					{
						FeatureType* ft = &it->second;
						m_ListCurrentSelection.SetItemData(0, (LPARAM)ft);
					}
				}
				else
				{ 
				}

				UpdateData(false);
			}
		}
	}
}

void CDialogDockCurrentSelection::DeleteItem(CString id)
{
	int count = m_ListCurrentSelection.GetItemCount();
	if (count == 0)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		auto itemid = m_ListCurrentSelection.GetItemText(i, 0);
		if (itemid == id)
		{
			m_ListCurrentSelection.DeleteItem(i);
			break;
		}
	}  
}


std::string* CDialogDockCurrentSelection::StringSplit(
	std::string strTarget,
	std::string strTok)
{
	int     nCutPos;
	int     nIndex = 0;
	string* strResult = new string[100];

	while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
	{
		if (nCutPos > 0)
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}
		strTarget = strTarget.substr(nCutPos + 1);
	}

	if (strTarget.length() > 0)
	{
		strResult[nIndex++] = strTarget.substr(0, nCutPos);
	}

	return strResult;
}


void CDialogDockCurrentSelection::UpdateList()
{
	int i = 0;
	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx = 0;

	CString objId;
	CString featureType;


	while (idx >= 0)
	{
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);

		objId.Format(m_ListCurrentSelection.GetItemText(idx, 1));
		featureType.Format(m_ListCurrentSelection.GetItemText(idx, 7));
		__int64 objIdN = _tcstoui64(objId, NULL, 10);

		if (featureType == L"Feature")
		{
			__int64 key = ((__int64)100) << 32 | objIdN;
			R_FeatureRecord *rfr = m_Cell->m_feaMap.PLookup(key)->value;

			int count = 0;

			int inforCount = rfr->m_inas.size();
			count += inforCount;
			if (0 < inforCount)
			{
				auto inas = *rfr->m_inas.begin();
				int arrCount = inas->m_arr.GetSize();
				count = count + arrCount;
			}


			int feaCount = rfr->m_fasc.size();
			count += feaCount;

			if (0 < feaCount)
			{
				auto fea = *rfr->m_fasc.begin();
				int arrCount = fea->m_arr.size();
				count = count + arrCount;
			}

			CString Countstring;
			Countstring.Format(_T("%d"), count);
			m_ListCurrentSelection.SetItemText(idx, 6, Countstring);
		}
		else if (featureType == L"Information")
		{

			__int64 key = ((__int64)150) << 32 | objIdN;

			if (m_Cell->m_infMap.GetCount() == 0)
			{
				int i = 0;
				return;
			}

			R_InformationRecord *rfr = m_Cell->m_infMap.PLookup(key)->value;

			int count = 0;
			int inforCount = rfr->m_inas.size();
			count = count + inforCount;

			if (0 < inforCount)
			{
				auto inas = *rfr->m_inas.begin();
				int arrCount = inas->m_arr.GetSize();
				count = count + arrCount;
			}

			CString Countstring;
			Countstring.Format(_T("%d"), inforCount);
			m_ListCurrentSelection.SetItemText(idx, 6, Countstring);
		}
	}
}  


void CDialogDockCurrentSelection::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	CRect rectCombo;
	CRect rectENCs;

	GetClientRect(rectClient);

	if (m_ListCurrentSelection.GetSafeHwnd())
	{
		rectENCs = CRect(rectClient.left, rectClient.top, rectClient.Size().cx, rectClient.Size().cy);
		m_ListCurrentSelection.MoveWindow(rectENCs);

		m_ListCurrentSelection.SetColumnWidth(0, (int)(rectENCs.Width()*0.10)); 
		m_ListCurrentSelection.SetColumnWidth(1, (int)(rectENCs.Width() * 0)); 
		m_ListCurrentSelection.SetColumnWidth(2, (int)(rectENCs.Width()*0.30)); 
		m_ListCurrentSelection.SetColumnWidth(3, (int)(rectENCs.Width()*0.10)); 
		m_ListCurrentSelection.SetColumnWidth(4, (int)(rectENCs.Width()*0.15)); 
		m_ListCurrentSelection.SetColumnWidth(5, (int)(rectENCs.Width()*0.15)); 
		m_ListCurrentSelection.SetColumnWidth(6, (int)(rectENCs.Width()*0.10)); 
		m_ListCurrentSelection.SetColumnWidth(7, (int)(rectENCs.Width()*0.10));
	}
} 
void CDialogDockCurrentSelection::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_CURRENT_SELECTION); 
	if ((CWnd*)pList == pWnd && m_ListCurrentSelection.GetSelectedCount() > 0)
	{ 
		if (point.x == -1 && point.y == -1)
		{
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenuW(IDR_MENU_CURRENT_SELECTION)); 
		CMenu* pPopup = menu.GetSubMenu(0);

		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this; 



		while (pWndPopupOwner->GetStyle() & WS_CHILD)
		{
			pWndPopupOwner = pWndPopupOwner->GetParent();
			int selMenu = pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, pWndPopupOwner);

			switch (selMenu)
			{
			case ID_UL_CHANGE_ALL:
				OnMenuChangeAll();
				break;
			case ID_UL_COPY_FEATURE:
				OnMenuCopyFeature();
				break;
			case ID_UL_RELATION:
				OnMenuRelation();
				break;
			case ID_UL_RELATION_INFORMATION:
				OnMenuRelationInformation();
				break;
			case ID_UL_REMOVE:
				OnMenuRemove();
				break;
			case ID_UL_REMOVE_OTHERS:
				OnMenuRemoveOthers();
				break;
			case ID_UL_REMOVE_ALL:
				OnMenuRemoveAll();
				break;
			case ID_UL_DELETE_FEATURE:
				OnMenuDeleteFeature();
				break;
			case ID_MENU_TEXTPLACEMENT:
				OnMenuCreateTextPlacement();
			} 
			menu.DestroyMenu();

		}
	}
}

unsigned CDialogDockCurrentSelection::GetATIX(R_FeatureRecord* feature, unsigned natc, unsigned parentIndex)
{
	unsigned index = 1;

	for (auto ai = feature->m_attr.begin(); ai != feature->m_attr.end(); ai++)
	{
		auto attrParent = *ai;

		for (auto i = attrParent->m_arr.begin(); i != attrParent->m_arr.end(); i++)
		{
			ATTR* attr = *i;

			if (attr->m_paix == parentIndex)
			{
				index = attr->m_atix + 1;
			}
		}
	}

	return index;
} 
void CDialogDockCurrentSelection::OnMenuChangeAll()
{

	CDialogExChangeAll *dlg = new CDialogExChangeAll(this); 

	NewFeatureManager *nfm = ((CGISViewerView *)pView)->m_pNewFeatureManager;
	S101Cell *cell = (S101Cell*)(nfm->m_cell);
	S101Layer *l = (S101Layer *)nfm->m_cell->m_pLayer;

	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second;  

	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx = 0; 
	while (pos)
	{
		CString tmpFeatureType;
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
		tmpFeatureType.Format(m_ListCurrentSelection.GetItemText(idx, 2)); 
		auto ftfcit = fc->featureTypes.featureType.find(tmpFeatureType.GetBuffer());
		FeatureType* ft = &ftfcit->second;

		for (auto itor = ft->attributeBinding.begin(); itor != ft->attributeBinding.end(); itor++)
		{
			AttributeBinding* ab = &(*itor);

			std::wstring name;

			for (auto i = ab->attribute.Getattributes().begin(); i != ab->attribute.Getattributes().end(); i++)
			{
				if (i->Getname().compare(L"ref") == 0)
				{
					name = i->Getvalue();
				}
			}

			auto atitor = fc->simpleAttributes.simpleAttribute.find(name.c_str());
			if (atitor != fc->simpleAttributes.simpleAttribute.end())
			{
				SimpleAttribute* sa = &atitor->second;

				attr_map.insert(std::unordered_map<wstring, SimpleAttribute*>::value_type(sa->name, sa));
			}
		}
	}

	dlg->SetAttribute(fc, attr_map);


	if (IDOK == dlg->DoModal()) {

		theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] process start")); 
		POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
		int idx = 0; 
		while (pos)
		{
			CString frid;
			CString camelCase;
			idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
			frid.Format(m_ListCurrentSelection.GetItemText(idx, 1));

			__int64 fridN = _tcstoui64(frid, NULL, 10); 
			__int64 key = ((__int64)100) << 32 | fridN;
			R_FeatureRecord *rfr = m_Cell->m_feaMap.PLookup(key)->value;

			auto fi = m_Cell->m_dsgir.m_ftcs->m_arr.find(rfr->m_frid.m_nftc);

			CodeWithNumericCode* nc = fi->second; 
			auto ftfcit = fc->featureTypes.featureType.find(nc->m_code.GetBuffer());
			FeatureType* ft = &ftfcit->second;

			bool isEnable = false;

			for (auto itor = ft->attributeBinding.begin(); itor != ft->attributeBinding.end(); itor++)
			{
				AttributeBinding* ab = &(*itor);

				std::wstring name;

				for (auto i = ab->attribute.Getattributes().begin(); i != ab->attribute.Getattributes().end(); i++)
				{
					if (i->Getname().compare(L"ref") == 0)
					{
						name = i->Getvalue();
					}
				}

				auto atitor = fc->simpleAttributes.simpleAttribute.find(name.c_str());
				if (atitor != fc->simpleAttributes.simpleAttribute.end())
				{
					SimpleAttribute* sa = &atitor->second; 
					if (sa->name.compare(dlg->m_attribteName) == 0)
					{
						isEnable = true;
						camelCase = sa->code.GetValueString().c_str();
					}
				}
			}


			if (isEnable)
			{
				auto atitor2 = cell->m_dsgir.m_atcs->m_arrFindForCode.find(camelCase.GetBuffer());

				nc = atitor2->second;

				bool isChanged = false;
				if (rfr->m_attr.size() <= 0)
				{
					F_ATTR* attrField = new F_ATTR();
					rfr->m_attr.push_back(attrField);
				}

				for (auto it = rfr->m_attr.begin(); it != rfr->m_attr.end(); it++)
				{
					F_ATTR* attrField = *it;
					for (auto aitor = attrField->m_arr.begin(); aitor != attrField->m_arr.end(); aitor++)
					{
						ATTR* attr = *aitor;
						if (attr->m_natc == nc->m_nmcd)
						{
							auto it = fc->simpleAttributes.simpleAttribute.find(camelCase.GetBuffer());
							SimpleAttribute* sa = &it->second;

							if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
							{
								for (auto itor = sa->listedValues.begin(); itor != sa->listedValues.end(); itor++)
								{
									ListedValues* lvs = &(*itor);

									for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++) {
										ListedValue* lv = &(lvitor->second);  
										if (dlg->m_attribteValue.Compare(lv->label.c_str()) == 0)
										{
											attr->m_atvl.Format(L"%d", lv->code.GetvalueInteger());
										}
									}
								}
							}
							else
							{
								attr->m_atvl = dlg->m_attribteValue;
							}
							isChanged = true;
						} 

					}
				}
				if (!isChanged)
				{
					for (auto it = rfr->m_attr.begin(); it != rfr->m_attr.end(); it++)
					{
						F_ATTR* attrField = *it;

						unsigned nmcd = 1;
						auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(camelCase.GetBuffer());

						if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
						{
							for (unsigned i = 1; i < 65535; i++)
							{
								nmcd = i;

								auto itor = cell->m_dsgir.m_atcs->m_arr.find(nmcd);

								if (itor == cell->m_dsgir.m_atcs->m_arr.end())
								{
									break;
								}
							}

							CodeWithNumericCode *cnc = new CodeWithNumericCode();
							cnc->m_nmcd = nmcd;
							cnc->m_code = camelCase;

							cell->m_dsgir.m_atcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));
							cell->m_dsgir.m_atcs->m_arrFindForCode.insert(std::unordered_map<std::wstring, CodeWithNumericCode*>::value_type(cnc->m_code.GetBuffer(), cnc));
						}
						else
						{
							nmcd = itor->second->m_nmcd;
						}
						ATTR* attr = new ATTR();
						attr->m_natc = nmcd;
						attr->m_atix = GetATIX(rfr, attr->m_natc, 0);
						attr->m_paix = 0;
						attr->m_atin = 1;
						attr->m_atvl = L"";
						attrField->m_arr.push_back(attr);

						auto ait = fc->simpleAttributes.simpleAttribute.find(camelCase.GetBuffer());
						SimpleAttribute* sa = &ait->second;
						if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
						{
							for (auto itor = sa->listedValues.begin(); itor != sa->listedValues.end(); itor++)
							{
								ListedValues* lvs = &(*itor);

								for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++) {
									ListedValue* lv = &(lvitor->second);  
									if (dlg->m_attribteValue.Compare(lv->label.c_str()) == 0)
									{
										attr->m_atvl.Format(L"%d", lv->code.GetvalueInteger());
									}
								}
							}
						}
						else
						{
							attr->m_atvl = dlg->m_attribteValue;
						}
					}

				}
				theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Change All] process end"));
			}
			AfxMessageBox(L"Change all completed");

		}
	}
}

void CDialogDockCurrentSelection::GetSelectionList(CStringArray* str)
{
	m_SelectedListCount = m_ListCurrentSelection.GetSelectedCount();
	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx, cnt = 0;


	while (pos)
	{
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
		str[cnt].Add(m_ListCurrentSelection.GetItemText(idx, 1));
	}

}

void CDialogDockCurrentSelection::OnMenuCopyFeature()
{

	pView = theApp.pView;
	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int nItem = m_ListCurrentSelection.GetNextSelectedItem(pos);

	if (m_ListCurrentSelection.GetSelectedCount() > 1 || m_ListCurrentSelection.GetItemText(nItem, 7) == L"Information" ||
		(m_ListCurrentSelection.GetItemText(nItem, 3) != L"point" && m_ListCurrentSelection.GetItemText(nItem, 3) != L"surface" && m_ListCurrentSelection.GetItemText(nItem, 3) != L"curve")) {
		AfxMessageBox(L"Cannot execute copy feature");
		return;
	}
	else {

		while (pos)
		{

			S101Cell* cell = (S101Cell*)pView->m_pNewFeatureManager->m_cell; 
			int geoType;
			if (m_ListCurrentSelection.GetItemText(nItem, 3) == "point")
			{
				geoType = 1;
				theApp.pView->m_Icon = FEATURE_ADD_POINT;
			}
			else if (m_ListCurrentSelection.GetItemText(nItem, 3) == "curve")
			{
				geoType = 2;
				theApp.pView->m_Icon = FEATURE_ADD_LINE;
			}
			else if (m_ListCurrentSelection.GetItemText(nItem, 3) == "surface")
			{
				geoType = 3;
				theApp.pView->m_Icon = FEATURE_ADD_AREA;
			} 
			POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
			int cnt = m_ListCurrentSelection.GetNextSelectedItem(pos);

			if (cnt < 0)
			{
			}

			cell = (S101Cell*)theApp.pView->m_pNewFeatureManager->m_cell;
			m_selectedFeatureType = (FeatureType*)m_ListCurrentSelection.GetItemData(cnt);

			auto itor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(m_selectedFeatureType->code.GetValueString().c_str());
			if (itor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			{
				CodeWithNumericCode* nc = itor->second;
				theApp.pView->m_pNewFeatureManager->m_featureType = nc->m_nmcd;
				theApp.pView->m_pNewFeatureManager->m_geometryType = geoType;
			}
			else
			{
				unsigned index = 0;
				for (unsigned i = 200; i < 1048575; i++)
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
				cnc->m_code = m_selectedFeatureType->code.GetValueString().c_str();
				cell->m_dsgir.m_ftcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));

				theApp.pView->m_pNewFeatureManager->m_featureType = cnc->m_nmcd;
				theApp.pView->m_pNewFeatureManager->m_geometryType = geoType;
			} 
			theApp.pView->SetEditSnapPoint();

		}

	}


}

void CDialogDockCurrentSelection::OnMenuCreateTextPlacement()
{
	R_FeatureRecord* newFeature = pView->OnMenuTextplacement();



}

void CDialogDockCurrentSelection::OnMenuDeleteFeature()
{
	POSITION startPos = m_ListCurrentSelection.GetFirstSelectedItemPosition(), comPos;
	comPos = startPos;
	int sidx = 0, cidx = 0;
	CString sfrid, cfrid; 
	while (startPos)
	{ 
		sidx = m_ListCurrentSelection.GetNextSelectedItem(startPos); 
		sfrid.Format(m_ListCurrentSelection.GetItemText(sidx, 1));
		__int64 sfridN = _tcstoui64(sfrid, NULL, 10);
		__int64 skey = ((__int64)100) << 32 | sfridN; 
		R_FeatureRecord *orgFr = m_Cell->m_feaMap.PLookup(skey)->value; 
		delete orgFr;

		m_Cell->m_feaMap.RemoveKey(skey); 


	}

	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx, cnt = 0;


	while (pos)
	{
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
		m_ListCurrentSelection.DeleteItem(idx);
		pos = m_ListCurrentSelection.GetFirstSelectedItemPosition(); 
	}

	pView->fePickGML = NULL;
	pView->fePick = NULL;
	pView->frPick = NULL;
	pView->m_pGisLib->GetLayerManager()->BuildS101Portrayal(m_Cell->m_pLayer);
	pView->MapRefresh();
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Delete] process end"));
}

void CDialogDockCurrentSelection::OnMenuRelationInformation()
{

	pView = theApp.pView;
	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process start"));  
	POSITION startPos = m_ListCurrentSelection.GetFirstSelectedItemPosition()/*, comPos*/;
	int fidx = 0;
	int fcnt = 0;
	int icnt = 0;
	CString featureType; 
	CStringArray featureFridArr;
	CStringArray infoIridArr;
	CStringArray setArr;
	featureFridArr.SetSize(1);
	infoIridArr.SetSize(1);
	setArr.SetSize(1); 
	while (startPos)
	{
		fidx = m_ListCurrentSelection.GetNextSelectedItem(startPos);

		featureType.Format(m_ListCurrentSelection.GetItemText(fidx, 7));
		CString id;
		if (featureType == "Feature") {
			id = m_ListCurrentSelection.GetItemText(fidx, 1);
			featureFridArr.Add(id);
			fcnt++;
		}
		else if (featureType == "Information") {
			id = m_ListCurrentSelection.GetItemText(fidx, 1);
			infoIridArr.Add(id);
			icnt++;
		}

	}

	if (fcnt == 0 || icnt == 0) {
		AfxMessageBox(L"Cannot execute Relation(info)");
		return;
	} 
	for (int i = 0; i < featureFridArr.GetSize(); i++) {
		setArr.Add(infoIridArr.GetAt(i) + _T("|||") + featureFridArr.GetAt(i));
	} 
	NewFeatureManager *nfm = pView->m_pNewFeatureManager; 
	S101Layer *l = (S101Layer *)m_Cell->m_pLayer; 
	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second; 
	int sidx = 0, cidx = 0;
	CString sfrid, cfrid; 
	for (int i = 0; i < setArr.GetSize(); i++)
	{

		int nTokenPos = 0; 
		CString strToken = setArr.GetAt(i).Tokenize(_T("|||"), nTokenPos); 
		if (strToken != L"") {

			CString cs = setArr.GetAt(i);
			std::string str1 = std::string(CT2CA(cs.operator LPCWSTR()));
			char toks[4] = { "|||" };
			string * tok = StringSplit(str1, toks); 
			cfrid = CString::CStringT(CA2CT(tok[0].c_str())); 
			sfrid = CString::CStringT(CA2CT(tok[1].c_str()));  
			__int64 sfridN = _tcstoui64(sfrid, NULL, 10);
			__int64 skey = ((__int64)100) << 32 | sfridN; 
			auto *pair = m_Cell->m_feaMap.PLookup(skey);
			if (!pair)
				continue;
			R_FeatureRecord *orgFr = m_Cell->m_feaMap.PLookup(skey)->value;  
			if (cfrid != L"" && cfrid != sfrid) {

				__int64 cfridN = _tcstoui64(cfrid, NULL, 10);
				__int64 ckey = ((__int64)150) << 32 | cfridN; 
				R_InformationRecord *objFr = m_Cell->m_infMap.PLookup(ckey)->value;  
				auto orgFtItor = m_Cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
				if (orgFtItor == m_Cell->m_dsgir.m_ftcs->m_arr.end())  break;
				wstring orgFeatureName = orgFtItor->second->m_code; 
				auto objFtItor = m_Cell->m_dsgir.m_itcs->m_arr.find(objFr->m_irid.m_nitc);
				if (objFtItor == m_Cell->m_dsgir.m_itcs->m_arr.end())  continue;
				wstring objFeatureName = objFtItor->second->m_code; 
				if ((orgFeatureName == L"NauticalInformation" || objFeatureName == L"NauticalInformation") && objFeatureName != orgFeatureName) { 
					bool isDuplicateUI = false;
					CString objRoleNameUI;
					CString orgRoleNameUI;

					F_INAS* checkINASUI = NULL;

					for (auto itt = objFr->m_inas.begin(); itt != objFr->m_inas.end(); itt++)
					{
						checkINASUI = *itt;
						if (checkINASUI->m_name.RCID == orgFr->m_frid.m_name.RCID &&
							checkINASUI->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (objFeatureName == L"NauticalInformation") {
						objRoleNameUI = L"informationProvidedFor";
					}
					else {
						objRoleNameUI = L"providesInformation";
					}

					if (!isDuplicateUI)
					{
						F_INAS* objF_INAS = new F_INAS();

						objF_INAS->m_name.RCID = orgFr->m_frid.m_name.RCID;
						objF_INAS->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
						objF_INAS->m_niac = ENC_S101_Factory::GetIACS(m_Cell, L"additionalInformation");
						objF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_Cell, (LPCTSTR)objRoleNameUI);
						objF_INAS->m_iuin = 1;

						objFr->m_inas.push_back(objF_INAS);
					}
					else {
						checkINASUI->m_niac = ENC_S101_Factory::GetIACS(m_Cell, L"additionalInformation");
						checkINASUI->m_narc = ENC_S101_Factory::GetARCS(m_Cell, (LPCTSTR)objRoleNameUI);
						checkINASUI->m_iuin = 1;
					}



					isDuplicateUI = false;
					checkINASUI = NULL;
					for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
					{
						checkINASUI = *itt;
						if (checkINASUI->m_name.RCID == objFr->m_irid.m_name.RCID &&
							checkINASUI->m_name.RCNM == objFr->m_irid.m_name.RCNM)
						{
							isDuplicateUI = true;
							break;
						}
					} 
					if (orgFeatureName == L"NauticalInformation") {
						orgRoleNameUI = L"providesInformation";
					}
					else {
						orgRoleNameUI = L"informationProvidedFor";
					}

					if (!isDuplicateUI)
					{
						F_INAS* orgF_INAS = new F_INAS();
						orgF_INAS->m_name.RCID = objFr->m_irid.m_name.RCID;
						orgF_INAS->m_name.RCNM = objFr->m_irid.m_name.RCNM;
						orgF_INAS->m_niac = ENC_S101_Factory::GetIACS(m_Cell, L"additionalInformation");;
						orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_Cell, (LPCTSTR)orgRoleNameUI);;
						orgF_INAS->m_iuin = 1;

						orgFr->m_inas.push_back(orgF_INAS);
					}
					else
					{
						checkINASUI->m_niac = ENC_S101_Factory::GetIACS(m_Cell, L"additionalInformation");;
						checkINASUI->m_narc = ENC_S101_Factory::GetARCS(m_Cell, (LPCTSTR)orgRoleNameUI);;
						checkINASUI->m_iuin = 1;
					} 


				}
				else {  
					FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second); 
					auto orgFBItor = orgFT->informationBinding.find(objFeatureName);
					if (orgFBItor == orgFT->informationBinding.end())		continue;
					InformationBinding* orgFB = &orgFBItor->second;                                       


					bool isDuplicate = false;
					F_INAS* checkINAS = NULL;                               

					wstring orgAssociationName = orgFB->association.Getvalue();
					if (orgAssociationName.compare(L"") == 0)
					{
						for (auto itor = orgFB->association.Getattributes().begin();
							itor != orgFB->association.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgAssociationName = attr->Getvalue();
							}
						}
					}


					wstring orgRoleName = orgFB->role.Getvalue();
					if (orgRoleName.compare(L"") == 0)
					{
						for (auto itor = orgFB->role.Getattributes().begin();
							itor != orgFB->role.Getattributes().end();
							itor++)
						{
							XML_Attribute* attr = &(*itor);
							if (attr->Getname().compare(L"ref") == 0)
							{
								orgRoleName = attr->Getvalue();
							}
						}
					}

					isDuplicate = false;
					checkINAS = NULL;
					for (auto itt = orgFr->m_inas.begin(); itt != orgFr->m_inas.end(); itt++)
					{
						checkINAS = *itt;
						if (checkINAS->m_name.RCID == objFr->m_irid.m_name.RCID &&
							checkINAS->m_name.RCNM == objFr->m_irid.m_name.RCNM)
						{
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate)
					{
						F_INAS* orgF_INAS = new F_INAS();
						orgF_INAS->m_name.RCID = objFr->m_irid.m_name.RCID;
						orgF_INAS->m_name.RCNM = objFr->m_irid.m_name.RCNM;
						orgF_INAS->m_niac = ENC_S101_Factory::GetFACS(m_Cell, orgAssociationName);;
						orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(m_Cell, orgRoleName);;
						orgF_INAS->m_iuin = 1;

						orgFr->m_inas.push_back(orgF_INAS);
					}
					else
					{
						checkINAS->m_niac = ENC_S101_Factory::GetFACS(m_Cell, orgAssociationName);;
						checkINAS->m_narc = ENC_S101_Factory::GetARCS(m_Cell, orgRoleName);;
						checkINAS->m_iuin = 1;
					}

				}

			}

		}
	}
	UpdateList();
	theApp.m_DockablePaneLogger.AppendList(_T("[Create Auto Relation] process end"));
}

void CDialogDockCurrentSelection::OnMenuRelation()
{ 
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Relation] process start")); 
	NewFeatureManager *nfm = ((CGISViewerView *)pView)->m_pNewFeatureManager; 
	S101Cell *cell = (S101Cell*)(nfm->m_cell); 
	S101Layer *l = (S101Layer *)nfm->m_cell->m_pLayer; 
	std::unordered_map<wstring, SimpleAttribute*> attr_map; 
	FeatureCatalogue* fc = l->GetFC()->m_pCatalogueList.begin()->second;   
	POSITION startPos = m_ListCurrentSelection.GetFirstSelectedItemPosition(), comPos;
	comPos = startPos;
	int sidx = 0, cidx = 0;
	CString sfrid, cfrid; 
	while (startPos)
	{ 
		sidx = m_ListCurrentSelection.GetNextSelectedItem(startPos); 
		sfrid.Format(m_ListCurrentSelection.GetItemText(sidx, 1));
		__int64 sfridN = _tcstoui64(sfrid, NULL, 10);
		__int64 skey = ((__int64)100) << 32 | sfridN; 
		auto *pairSkey = m_Cell->m_feaMap.PLookup(skey);
		if (!pairSkey)
		{
			theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Relation] Fail - no Feature"));
		}
		R_FeatureRecord *orgFr = m_Cell->m_feaMap.PLookup(skey)->value;   
		for (comPos = startPos; comPos != NULL;)
		{ 
			cidx = m_ListCurrentSelection.GetNextSelectedItem(comPos);
			cfrid.Format(m_ListCurrentSelection.GetItemText(cidx, 1));
			__int64 cfridN = _tcstoui64(cfrid, NULL, 10);
			__int64 ckey = ((__int64)100) << 32 | cfridN; 
			R_FeatureRecord *objFr = m_Cell->m_feaMap.PLookup(ckey)->value;  
			auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
			if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  break;
			wstring orgFeatureName = orgFtItor->second->m_code; 
			auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
			if (objFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  continue;
			wstring objFeatureName = objFtItor->second->m_code; 


			if ((orgFeatureName == L"UpdateInformation" || objFeatureName == L"UpdateInformation") && objFeatureName != orgFeatureName) { 
				bool isDuplicateUI = false;
				CString objRoleNameUI;
				CString orgRoleNameUI;

				F_FASC* checkAFSCUI = NULL;

				for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
				{
					checkAFSCUI = *itt;
					if (checkAFSCUI->m_name.RCID == orgFr->m_frid.m_name.RCID &&
						checkAFSCUI->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
					{
						isDuplicateUI = true;
						break;
					}
				} 
				if (objFeatureName == L"UpdateInformation") {
					objRoleNameUI = L"Updates";
				}
				else {
					objRoleNameUI = L"Identifies";
				}

				if (!isDuplicateUI)
				{
					F_FASC* objF_AFSC = new F_FASC();

					objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
					objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
					objF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, L"updatedInformation");
					objF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, (LPCTSTR)objRoleNameUI);
					objF_AFSC->m_faui = 1;

					objFr->m_fasc.push_back(objF_AFSC);
				}
				else {
					checkAFSCUI->m_nfac = ENC_S101_Factory::GetFACS(cell, L"updatedInformation");
					checkAFSCUI->m_narc = ENC_S101_Factory::GetARCS(cell, (LPCTSTR)objRoleNameUI);
					checkAFSCUI->m_faui = 1;
				}

				isDuplicateUI = false;
				checkAFSCUI = NULL;
				for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
				{
					checkAFSCUI = *itt;
					if (checkAFSCUI->m_name.RCID == objFr->m_frid.m_name.RCID &&
						checkAFSCUI->m_name.RCNM == objFr->m_frid.m_name.RCNM)
					{
						isDuplicateUI = true;
						break;
					}
				} 
				if (orgFeatureName == L"UpdateInformation")
				{
					orgRoleNameUI = L"Updates";
				}
				else
				{
					orgRoleNameUI = L"Identifies";
				}

				if (!isDuplicateUI)
				{
					F_FASC* orgF_AFSC = new F_FASC();
					orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
					orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
					orgF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, L"updatedInformation");;
					orgF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, (LPCTSTR)orgRoleNameUI);;
					orgF_AFSC->m_faui = 1;

					orgFr->m_fasc.push_back(orgF_AFSC);
					AfxMessageBox(L"Relation is created");
				}
				else
				{
					checkAFSCUI->m_nfac = ENC_S101_Factory::GetFACS(cell, L"updatedInformation");;
					checkAFSCUI->m_narc = ENC_S101_Factory::GetARCS(cell, (LPCTSTR)orgRoleNameUI);;
					checkAFSCUI->m_faui = 1;
					AfxMessageBox(L"Relation is not created. check [current selection] dialog");
				} 


			}
			else { 
				FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second); 
				auto orgFBItor = orgFT->featureBinding.find(objFeatureName);
				if (orgFBItor == orgFT->featureBinding.end())		continue;
				FeatureBinding* orgFB = &orgFBItor->second; 
				FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second);  
				auto objFBItor = objFT->featureBinding.find(orgFeatureName);
				if (objFBItor == objFT->featureBinding.end())		continue;
				FeatureBinding* objFB = &objFBItor->second;  
				wstring objAssociationName = objFB->association.Getvalue();
				if (objAssociationName.compare(L"") == 0)
				{
					for (auto itor = objFB->association.Getattributes().begin();
						itor != objFB->association.Getattributes().end();
						itor++)
					{
						XML_Attribute* attr = &(*itor);
						if (attr->Getname().compare(L"ref") == 0)
						{
							objAssociationName = attr->Getvalue();
						}
					}
				} 
				wstring objRoleName = objFB->role.Getvalue();
				if (objRoleName.compare(L"") == 0)
				{
					for (auto itor = objFB->role.Getattributes().begin();
						itor != objFB->role.Getattributes().end();
						itor++)
					{
						XML_Attribute* attr = &(*itor);
						if (attr->Getname().compare(L"ref") == 0)
						{
							objRoleName = attr->Getvalue();
						}
					}
				}

				bool isDuplicate = false; 
				F_FASC* checkAFSC = NULL;
				for (auto itt = objFr->m_fasc.begin(); itt != objFr->m_fasc.end(); itt++)
				{
					checkAFSC = *itt;
					if (checkAFSC->m_name.RCID == orgFr->m_frid.m_name.RCID &&
						checkAFSC->m_name.RCNM == orgFr->m_frid.m_name.RCNM)
					{
						isDuplicate = true;
						break;
					}
				} 
				if (!isDuplicate)
				{
					F_FASC* objF_AFSC = new F_FASC(); 
					objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
					objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
					objF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, objAssociationName);;
					objF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, objRoleName);;
					objF_AFSC->m_faui = 1; 
					objFr->m_fasc.push_back(objF_AFSC);
				} 
				else
				{
					checkAFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, objAssociationName);
					checkAFSC->m_narc = ENC_S101_Factory::GetARCS(cell, objRoleName);
					checkAFSC->m_faui = 1;
				}


				wstring orgAssociationName = orgFB->association.Getvalue();
				if (orgAssociationName.compare(L"") == 0)
				{
					for (auto itor = orgFB->association.Getattributes().begin();
						itor != orgFB->association.Getattributes().end();
						itor++)
					{
						XML_Attribute* attr = &(*itor);
						if (attr->Getname().compare(L"ref") == 0)
						{
							orgAssociationName = attr->Getvalue();
						}
					}
				}

				wstring orgRoleName = orgFB->role.Getvalue();
				if (orgRoleName.compare(L"") == 0)
				{
					for (auto itor = orgFB->role.Getattributes().begin();
						itor != orgFB->role.Getattributes().end();
						itor++)
					{
						XML_Attribute* attr = &(*itor);
						if (attr->Getname().compare(L"ref") == 0)
						{
							orgRoleName = attr->Getvalue();
						}
					}
				}

				isDuplicate = false;
				checkAFSC = NULL;
				for (auto itt = orgFr->m_fasc.begin(); itt != orgFr->m_fasc.end(); itt++)
				{
					checkAFSC = *itt;
					if (checkAFSC->m_name.RCID == objFr->m_frid.m_name.RCID &&
						checkAFSC->m_name.RCNM == objFr->m_frid.m_name.RCNM)
					{
						isDuplicate = true;
						break;
					}
				}

				if (!isDuplicate)
				{
					F_FASC* orgF_AFSC = new F_FASC();
					orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
					orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
					orgF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, orgAssociationName);
					orgF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, orgRoleName);
					orgF_AFSC->m_faui = 1;

					orgFr->m_fasc.push_back(orgF_AFSC);
					AfxMessageBox(L"Relation is created");
				}
				else
				{
					checkAFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, orgAssociationName);
					checkAFSC->m_narc = ENC_S101_Factory::GetARCS(cell, orgRoleName);
					checkAFSC->m_faui = 1;
					AfxMessageBox(L"Relation is not created. check [current selection] dialog");
				}
			}
		}
	}

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Relation] process end"));
}

void CDialogDockCurrentSelection::GetFeatureCatalogue()
{
	CDialog *dlg = new CDialog(IDD_DIALOG_RELATION_INFO, this);
	if (IDOK == dlg->DoModal()) {

		NewFeatureManager *nfm = ((CGISViewerView *)pView)->m_pNewFeatureManager; 
		R_FeatureRecord* orgFr = NULL; 
		R_FeatureRecord* objFr = NULL;
		S101Cell* cell = (S101Cell*)nfm->m_cell;
		S101Layer* layer = (S101Layer*)nfm->m_cell->m_pLayer;

		FeatureCatalogue *fc = layer->GetFC()->m_pCatalogueList.begin()->second;

		auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
		if (objFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  return;
		wstring objFeatureName = objFtItor->second->m_code;

		auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
		if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  return;
		wstring orgFeatureName = orgFtItor->second->m_code;

		FeatureType *objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second);
		auto objFBItor = objFT->featureBinding.find(orgFeatureName);
		if (objFBItor == objFT->featureBinding.end())		return;
		FeatureBinding* objFB = &objFBItor->second;

		FeatureType *orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);
		auto orgFBItor = orgFT->featureBinding.find(objFeatureName);
		if (orgFBItor == orgFT->featureBinding.end())		return;
		FeatureBinding* orgFB = &orgFBItor->second; 

		wstring objAssociationName = objFB->association.Getvalue();
		if (objAssociationName.compare(L"") == 0)
		{
			for (auto itor = objFB->association.Getattributes().begin();
				itor != objFB->association.Getattributes().end();
				itor++)
			{
				XML_Attribute* attr = &(*itor);
				if (attr->Getname().compare(L"ref") == 0)
				{
					objAssociationName = attr->Getvalue();
				}
			}
		}

		wstring objRoleName = objFB->role.Getvalue();
		if (objRoleName.compare(L"") == 0)
		{
			for (auto itor = objFB->role.Getattributes().begin();
				itor != objFB->role.Getattributes().end();
				itor++)
			{
				XML_Attribute* attr = &(*itor);
				if (attr->Getname().compare(L"ref") == 0)
				{
					objRoleName = attr->Getvalue();
				}
			}
		}

		auto objAssocItor = cell->m_dsgir.m_facs->m_arrFindForCode.find(objAssociationName);
		auto objRoleItor = cell->m_dsgir.m_arcs->m_arrFindForCode.find(objRoleName);

		CodeWithNumericCode *objAssoc = objAssocItor->second;
		CodeWithNumericCode *objRole = objRoleItor->second;

		F_FASC* objF_AFSC = new F_FASC();
		objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
		objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
		objF_AFSC->m_nfac = objAssoc->m_nmcd;
		objF_AFSC->m_narc = objRole->m_nmcd;
		objF_AFSC->m_faui = 1;

		objFr->m_fasc.push_back(objF_AFSC);


		wstring orgAssociationName = orgFB->association.Getvalue();
		if (orgAssociationName.compare(L"") == 0)
		{
			for (auto itor = orgFB->association.Getattributes().begin();
				itor != orgFB->association.Getattributes().end();
				itor++)
			{
				XML_Attribute* attr = &(*itor);
				if (attr->Getname().compare(L"ref") == 0)
				{
					orgAssociationName = attr->Getvalue();
				}
			}
		}


		wstring orgRoleName = orgFB->role.Getvalue();
		if (orgRoleName.compare(L"") == 0)
		{
			for (auto itor = orgFB->role.Getattributes().begin();
				itor != orgFB->role.Getattributes().end();
				itor++)
			{
				XML_Attribute* attr = &(*itor);
				if (attr->Getname().compare(L"ref") == 0)
				{
					orgRoleName = attr->Getvalue();
				}
			}
		}
		auto orgAssocItor = cell->m_dsgir.m_facs->m_arrFindForCode.find(orgAssociationName);
		auto orgRoleItor = cell->m_dsgir.m_arcs->m_arrFindForCode.find(orgRoleName);

		CodeWithNumericCode *orgAssoc = orgAssocItor->second;
		CodeWithNumericCode *orgRole = orgRoleItor->second;

		F_FASC* orgF_AFSC = new F_FASC();
		orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
		orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
		orgF_AFSC->m_nfac = orgAssoc->m_nmcd;
		orgF_AFSC->m_narc = orgRole->m_nmcd;
		orgF_AFSC->m_faui = 1;

		orgFr->m_fasc.push_back(orgF_AFSC);
	}
	else {

	}

}

void CDialogDockCurrentSelection::OnMenuRemove()
{
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove] process start"));

	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx, cnt = 0;
	while (pos)
	{
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
		m_ListCurrentSelection.DeleteItem(idx);
		pos = m_ListCurrentSelection.GetFirstSelectedItemPosition(); 


	}
	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	theApp.m_DockablePaneAttributeList.RemoveAll(); 

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove] process end"));
}

void CDialogDockCurrentSelection::OnMenuRemoveOthers()
{

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove Others] process start"));

	CString state;  
	for (int i = 0; m_ListCurrentSelection.GetItemCount() > i; i++)
	{

		state.Format(_T("%d"), m_ListCurrentSelection.GetItemState(i, LVIS_SELECTED));

		if (state == _T("2"))
		{
			m_ListCurrentSelection.SetItemState(i, 0, LVIS_SELECTED);

		}
		else {
			m_ListCurrentSelection.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		}
	}


	POSITION pos = m_ListCurrentSelection.GetFirstSelectedItemPosition();
	int idx = 0; 
	while (pos)
	{
		idx = m_ListCurrentSelection.GetNextSelectedItem(pos);
		m_ListCurrentSelection.DeleteItem(idx);
		pos = m_ListCurrentSelection.GetFirstSelectedItemPosition(); 
	}

	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	theApp.m_DockablePaneAttributeList.RemoveAll(); 

	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove Others] process end"));

}

void CDialogDockCurrentSelection::OnMenuRemoveAll()
{
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove All] process start"));
	m_ListCurrentSelection.DeleteAllItems();

	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	if (theApp.IsEditingMode())
	{
		theApp.m_DockablePaneAttributeList.RemoveAll(); 
	}
	theApp.m_DockablePaneLogger.AppendList(_T("[Current Selection > Remove All] process end"));
}

void CDialogDockCurrentSelection::OnHdnItemclickListCurrentSelection(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	int nColumn = phdr->iItem;
	for (int i = 0; i < (m_ListCurrentSelection.GetItemCount()); i++)
	{
		m_ListCurrentSelection.SetItemData(i, i);
	} 
	m_bAscending = !m_bAscending; 
	SORTPARAM sortparams;
	sortparams.pList = &m_ListCurrentSelection;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending ? true : false; 
	m_ListCurrentSelection.SortItems(&CompareItem, (LPARAM)&sortparams);

	*pResult = 0;

}

int CALLBACK CDialogDockCurrentSelection::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pList = ((SORTPARAM *)lParamSort)->pList;
	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
	int irow1 = pList->FindItem(&info1, -1);
	int irow2 = pList->FindItem(&info2, -1);

	CString strItem1 = pList->GetItemText(irow1, iSortColumn);
	CString strItem2 = pList->GetItemText(irow2, iSortColumn);

	return bSortDirect ? strItem1.Compare(strItem2) : -strItem1.Compare(strItem2);
}