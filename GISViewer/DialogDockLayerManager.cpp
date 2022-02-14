#include "stdafx.h"
#include "GISViewer.h"
#include "DialogDockLayerManager.h"
#include "GISViewerView.h"
#include "afxdialogex.h"
#include "CDialogExCreateLayersub.h"

#include "GISLibrary\\BAG.h"
#include "GISLibrary\\S102Cell.h"
#include "GISLibrary\\S111Cell.h"
#include "GISLibrary\\S413Cell.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\LayerManager.h"
#include "GISLibrary\\NewFeatureManager.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"
#include "GeoMetryLibrary\\Scaler.h"

#include "resource.h"

using namespace std;

IMPLEMENT_DYNAMIC(CDialogDockLayerManager, CDialog)

CDialogDockLayerManager::CDialogDockLayerManager(CWnd* pParent )
	: CDialog(CDialogDockLayerManager::IDD, pParent)
{
}

CDialogDockLayerManager::~CDialogDockLayerManager()
{
}

void CDialogDockLayerManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LM, m_ListLayer);
}


BEGIN_MESSAGE_MAP(CDialogDockLayerManager, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDialogDockLayerManager::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogDockLayerManager::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LM, &CDialogDockLayerManager::OnLvnItemchangedList1)

	ON_WM_SIZE()
	ON_WM_SIZING()

	ON_NOTIFY(NM_CLICK, IDC_LIST_LM, &CDialogDockLayerManager::OnNMClickListLm)
	ON_COMMAND(ID_BUTTON_LAYERDELETE, &CDialogDockLayerManager::OnButtonDelete)
	ON_COMMAND(ID_BUTTON_ON, &CDialogDockLayerManager::OnButtonOn)
	ON_COMMAND(ID_BUTTON_OFF, &CDialogDockLayerManager::OnButtonOff)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LM, &CDialogDockLayerManager::OnNMDblclkListLm)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_COMMAND(ID_BUTTON_INFO, &CDialogDockLayerManager::OnButtonLayerinfoON)
	ON_COMMAND(ID_BUTTON_LAYERINFO_OFF, &CDialogDockLayerManager::OnButtonLayerinfoOff)
	ON_COMMAND(ID_BUTTON_UP, &CDialogDockLayerManager::OnButtonUp)
	ON_COMMAND(ID_BUTTON_DOWN, &CDialogDockLayerManager::OnButtonDown)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LM, &CDialogDockLayerManager::OnNMRClickListLm)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_LM, &CDialogDockLayerManager::OnLvnKeydownListLm)
END_MESSAGE_MAP() 
int CDialogDockLayerManager::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CDialogDockLayerManager::OnBnClickedOk()
{ 
	return;
}

void CDialogDockLayerManager::OnBnClickedCancel()
{ 
	return;
}


void CDialogDockLayerManager::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 

	*pResult = 0;
}


void CDialogDockLayerManager::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CDialogDockLayerManager::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
} 
BOOL CDialogDockLayerManager::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	m_ListLayer.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListLayer.GetWindowRect(listRect);
	m_ListLayer.InsertColumn(0, _T("No. "), LVCFMT_CENTER, 40);
	m_ListLayer.InsertColumn(1, _T("Type "), LVCFMT_CENTER, 40);
	m_ListLayer.InsertColumn(2, _T("Name"), LVCFMT_CENTER, listRect.Width() - 130);
	m_ListLayer.InsertColumn(3, _T("On/Off"), LVCFMT_CENTER, 50); 

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1; 
	}
	InitPropList();
	AdjustLayout();


#ifdef _S57_EDITOR
	m_wndPropList.ShowWindow(FALSE);
#endif

	return TRUE;  
}

void CDialogDockLayerManager::UpdateList()
{
	m_ListLayer.DeleteAllItems();

	for (auto i = 0; i < gisLib->GetLayerCount(); i++)
	{
		CString strNo, strName, strOnOff;

		strNo.Format(_T("%d"), i + 1);
		strName = gisLib->GetLayerName(i);

		if (gisLib->IsOn(i))
		{
			strOnOff.Format(_T("On"));
		}
		else
		{
			strOnOff.Format(_T("Off"));
		}

		m_ListLayer.InsertItem(i, strNo);

		CString fileType;

		Layer* l = gisLib->GetLayer(i);
		SpatialObject* so = l->m_spatialObject;
		S100_FileType ft = so->m_FileType;

		if (ft == FILE_S_57)
		{
			fileType == L"S-57";
		}
		else if (ft == FILE_S_100_VECTOR)
		{
			S101Cell* c = (S101Cell*)so;
			std::wstring ret = GetProductAsString(c->S100Product);
			fileType = ret.c_str();
		}
		else if (ft == FILE_S_100_GRID_BAG)
		{
			BAG* c = (BAG*)so;
			std::wstring ret = GetProductAsString(c->S100Product);
			fileType = ret.c_str();
		}
		else if (ft == FILE_S_100_GRID_H5)
		{
			S111Cell* c = (S111Cell*)so;
			std::wstring ret = GetProductAsString(c->S100Product);
			fileType = ret.c_str();
		}
		else if (ft == FILE_S_100_GRID_H5)
		{
			S102Cell* c = (S102Cell*)so;
			std::wstring ret = GetProductAsString(c->S100Product);
			fileType = ret.c_str();
		}
		else if (ft == FILE_S_100_GRID_H5)
		{
			S413Cell* c = (S413Cell*)so;
			std::wstring ret = GetProductAsString(c->S100Product);
			fileType = ret.c_str();
		}

		m_ListLayer.SetItemText(i, 1, fileType);

		int tmp = strName.ReverseFind(L'.');
		if (tmp >= 0)
		{
			strName = strName.Mid(0, tmp);
		}
		tmp = strName.ReverseFind(L'\\');
		if (tmp >= 0)
		{
			strName = strName.Mid(tmp + 1, strName.GetLength() - tmp - 1);
		}
		m_ListLayer.SetItemText(i, 2, strName);
		m_ListLayer.SetItemText(i, 3, strOnOff);
	}

	if (gisLib->GetLayerCount() > 0)
	{
		Layer *layer = (Layer *)gisLib->GetLayer(gisLib->GetLayerCount() - 1);

		if (layer->m_spatialObject->m_FileType == FILE_S_100_VECTOR)
		{
			S101Cell* c = (S101Cell*)layer->m_spatialObject;   
			{
				FillPropList(c);
				curCell = c;
			}
		}
	}
}
void CDialogDockLayerManager::SetSelectedInformation()
{
	Layer *layer = gisLib->GetLayer(nSelectedItem);

	if (!layer)
	{
		return;
	}       
	if (layer->m_spatialObject->m_FileType == FILE_S_100_VECTOR)
	{
		S101Cell* c = (S101Cell*)layer->m_spatialObject;
		if (c->S100Product == S100::S100_DataProduct::S_101)
		{
			FillPropList(c);
		}

		theApp.pView->m_pNewFeatureManager->m_cell = c;

		curCell = c;
	}
	else if (layer->m_spatialObject->m_FileType == FILE_S_100_GRID_H5)
	{

		auto cell = (S413Cell *)layer->m_spatialObject;
		FillPropList(cell);

		curCell = cell;
	}
	else
	{
		curCell = nullptr;
	}
}

void CDialogDockLayerManager::OnNMClickListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
	SelectdItem.clear();
	m_anDragIndexes.RemoveAll();
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 

	m_ListLayer.ModifyStyle(0, LVS_SHOWSELALWAYS);
	nSelectedItem = pNMItemActivate->iItem;


	int nItemCount = m_ListLayer.GetSelectedCount();

	POSITION pos = m_ListLayer.GetFirstSelectedItemPosition();
	for (int i = 0; i < nItemCount; i++)
	{ 
		Layer* layer = gisLib->GetLayerManager()->m_listLayer[m_ListLayer.GetNextSelectedItem(pos)];
		SelectdItem.push_back(layer->GetLayerPath());
	}    

	SetSelectedInformation();
	AdjustToolbarMenu();

	*pResult = 0;
}

void CDialogDockLayerManager::OnButtonDelete() 
{

	if (nSelectedItem < 0 || m_ListLayer.GetSelectedCount() == 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("삭제할 레이어를 선택해 주세요."));
		return;
	}

	if (1 < m_ListLayer.GetSelectedCount())
	{
		for (size_t i = 0; i < SelectdItem.size(); i++)
		{
			CString filepath = SelectdItem[i];

			gisLib->ClearInformationLayer(filepath);
			gisLib->DeleteLayer(filepath); 
		}
	}
	else
	{
		gisLib->ClearInformationLayer(nSelectedItem);
		gisLib->DeleteLayer(nSelectedItem); 

	} 

	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	RemoveAllPropList(); 
	theApp.m_DockablePaneCurrentSelection.RemoveAll(); 
	if (theApp.IsEditingMode())
	{

		theApp.m_DockablePaneAttributeList.RemoveAll(); 
	} 
	UpdateList();
	theApp.pView->ClearPickReport();
	theApp.MapRefresh();
}
void CDialogDockLayerManager::OnButtonDeleteAllLayer()
{
	m_ListLayer.DeleteAllItems();
	gisLib->DeleteAllLayer();
	gisLib->ClearAllInformationLayer();

	theApp.m_DockablePaneEditWindow.DeleteAllItems(); 
	RemoveAllPropList(); 
	theApp.m_DockablePaneCurrentSelection.RemoveAll(); 
	if (theApp.IsEditingMode())
	{
		theApp.m_DockablePaneAttributeList.RemoveAll(); 
	}

	UpdateList();
	theApp.pView->ClearPickReport();
	theApp.MapRefresh();
}
void CDialogDockLayerManager::OnButtonOn()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("표시할 레이어를 선택해 주세요."));
		return;
	}

	gisLib->LayerOn(nSelectedItem);
	UpdateList();
	theApp.MapRefresh();
}

void CDialogDockLayerManager::OnButtonOff()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("감출 레이어를 선택해 주세요."));
		return;
	}

	gisLib->ClearInformationLayer(nSelectedItem);
	gisLib->LayerOff(nSelectedItem);
	UpdateList();
	theApp.pView->ClearPickReport();
	theApp.MapRefresh();
}

void CDialogDockLayerManager::OnButtonLayerinfoON()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("레이어를 선택해 주세요."));
		return;
	}

	gisLib->LayerInfoOn(nSelectedItem);

	theApp.MapRefresh();
}

void CDialogDockLayerManager::OnButtonLayerinfoOff()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("레이어를 선택해 주세요."));
		return;
	}

	gisLib->LayerInfoOff(nSelectedItem); 
	theApp.MapRefresh();
}

void CDialogDockLayerManager::OnNMDblclkListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	*pResult = 0;
	nSelectedItem = pNMItemActivate->iItem;
	if (nSelectedItem < 0)
	{
		return;
	}

	SetSelectedInformation();

	Layer *layer = gisLib->GetLayer(nSelectedItem);
	auto layerMBR = layer->GetMBR();

	gisLib->GetLayerManager()->GetScaler()->SetMap(layerMBR);
	gisLib->AdjustScreenMap();
	theApp.MapRefresh();
}

void CDialogDockLayerManager::SaveLayer(CString filename, CString extend)
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"Select Save Layer", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	}
	gisLib->SaveLayer(filename, extend, nSelectedItem);
}

void CDialogDockLayerManager::SaveLayerTextPlacement(CString filename, CString extend)
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"Select Save Layer", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	}
	gisLib->SaveLayerTextPlacement(filename, extend, nSelectedItem);
}


void CDialogDockLayerManager::SetVSDotNetLook(BOOL bSet)
{
	m_wndPropList.SetVSDotNetLook(bSet);
	m_wndPropList.SetGroupNameFullWidth(bSet);
}


void CDialogDockLayerManager::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);

	CRect      rectENCs;

	if (m_ListLayer.GetSafeHwnd())
	{
		rectENCs = CRect(rectClient.left, rectClient.top, rectClient.Size().cx, rectClient.Size().cy / 2);
		m_ListLayer.MoveWindow(rectENCs); 
		m_ListLayer.SetColumnWidth(0, 40); 
		m_ListLayer.SetColumnWidth(1, 40); 
		m_ListLayer.SetColumnWidth(2, rectENCs.Width() - 130); 
		m_ListLayer.SetColumnWidth(3, 50); 
	} 

	int cyCmb = rectCombo.Size().cy; 
	if (m_wndPropList.GetSafeHwnd())
		m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.Size().cy / 2, rectClient.Width(), rectClient.Size().cy / 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDialogDockLayerManager::InitPropList() 
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Data Set Identification"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification"), (_variant_t)_T("-"), L"Encoding specification that defines the encoding"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification edition"), (_variant_t)_T("-"), L"Edition of the encoding specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product identifier"), (_variant_t)_T("-"), L"Unique identifier for the data product as specified in the product specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product edition"), (_variant_t)_T("-"), L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application profile"), (_variant_t)_T("-"), L"Identifier that specifies a profile within the data product"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset file identifier"), (_variant_t)_T("-"), L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset title"), (_variant_t)_T("-"), L"The title of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset reference date"), (_variant_t)_T("-"), L"The reference date of the dataset Format: YYYYMMDD according to ISO 8601"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset language"), (_variant_t)_T("-"), L"The (primary) language used in this dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset abstract"), (_variant_t)_T("-"), L"The abstract of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset edition"), (_variant_t)_T("-"), L"The edition of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset topic category"), (_variant_t)_T("-"), L"A set of topic categories"));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Data Set Structure Information"));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin X"), (_variant_t)_T("-"), L"Shift used to adjust x-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Y"), (_variant_t)_T("-"), L"Shift used to adjust y-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Z"), (_variant_t)_T("-"), L"Shift used to adjust z-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for x-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the x-coordinate or longitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for y-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the y-coordinate or latitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for z-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the z-coordinate or depths or height"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Information Type records"), (_variant_t)_T("-"), L"Number of information records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Point records"), (_variant_t)_T("-"), L"Number of point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Multi Point records"), (_variant_t)_T("-"), L"Number of multi point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Curve records"), (_variant_t)_T("-"), L"Number of curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Composite Curve records"), (_variant_t)_T("-"), L"Number of composite curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Surface records"), (_variant_t)_T("-"), L"Number of surface records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Feature Type records"), (_variant_t)_T("-"), L"Number of feature records in the data set"));
	m_wndPropList.AddProperty(pGroup2);
}

void CDialogDockLayerManager::RemoveAllPropList()
{
	m_wndPropList.RemoveAll();

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;  

	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Data Set Identification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification"), (_variant_t)_T("-"), L"Encoding specification that defines the encoding"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification edition"), (_variant_t)_T("-"), L"Edition of the encoding specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product identifier"), (_variant_t)_T("-"), L"Unique identifier for the data product as specified in the product specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product edition"), (_variant_t)_T("-"), L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application profile"), (_variant_t)_T("-"), L"Identifier that specifies a profile within the data product"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset file identifier"), (_variant_t)_T("-"), L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset title"), (_variant_t)_T("-"), L"The title of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset reference date"), (_variant_t)_T("-"), L"The reference date of the dataset Format: YYYYMMDD according to ISO 8601"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset language"), (_variant_t)_T("-"), L"The (primary) language used in this dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset abstract"), (_variant_t)_T("-"), L"The abstract of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset edition"), (_variant_t)_T("-"), L"The edition of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset topic category"), (_variant_t)_T("-"), L"A set of topic categories"));
	m_wndPropList.AddProperty(pGroup1);


	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Data Set Structure Information"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin X"), (_variant_t)_T("-"), L"Shift used to adjust x-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Y"), (_variant_t)_T("-"), L"Shift used to adjust y-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Z"), (_variant_t)_T("-"), L"Shift used to adjust z-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for x-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the x-coordinate or longitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for y-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the y-coordinate or latitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for z-coordinate"), (_variant_t)_T("-"), L"Floating point to integer multiplication factor for the z-coordinate or depths or height"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Information Type records"), (_variant_t)_T("-"), L"Number of information records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Point records"), (_variant_t)_T("-"), L"Number of point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Multi Point records"), (_variant_t)_T("-"), L"Number of multi point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Curve records"), (_variant_t)_T("-"), L"Number of curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Composite Curve records"), (_variant_t)_T("-"), L"Number of composite curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Surface records"), (_variant_t)_T("-"), L"Number of surface records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Feature Type records"), (_variant_t)_T("-"), L"Number of feature records in the data set"));
	m_wndPropList.AddProperty(pGroup2);
} 
void CDialogDockLayerManager::FillPropList(S101Cell* cell)
{
	m_wndPropList.RemoveAll();

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;  

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Data Set Identification"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification"), (_variant_t)cell->m_dsgir.m_dsid.m_ensp, L"Encoding specification that defines the encoding"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Encoding specification edition"), (_variant_t)cell->m_dsgir.m_dsid.m_ened, L"Edition of the encoding specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product identifier"), (_variant_t)cell->m_dsgir.m_dsid.m_prsp, L"Unique identifier for the data product as specified in the product specification"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Product edition"), (_variant_t)cell->m_dsgir.m_dsid.m_pred, L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application profile"), (_variant_t)cell->m_dsgir.m_dsid.m_prof, L"Identifier that specifies a profile within the data product"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset file identifier"), (_variant_t)cell->m_dsgir.m_dsid.m_dsnm, L"The file identifier of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset title"), (_variant_t)cell->m_dsgir.m_dsid.m_dstl, L"The title of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset reference date"), (_variant_t)cell->m_dsgir.m_dsid.m_dsrd, L"The reference date of the dataset Format: YYYYMMDD according to ISO 8601"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset language"), (_variant_t)cell->m_dsgir.m_dsid.m_dslg, L"The (primary) language used in this dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset abstract"), (_variant_t)cell->m_dsgir.m_dsid.m_dsab, L"The abstract of the dataset"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset edition"), (_variant_t)cell->m_dsgir.m_dsid.m_dsed, L"The edition of the dataset"));

	for (int i = 0; i < cell->m_dsgir.m_dsid.m_dstc.GetSize(); i++)
	{
		int valueInt = cell->m_dsgir.m_dsid.m_dstc.GetAt(i);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(L"A set of topic categories", (_variant_t)valueInt, NULL, valueInt));
	}


	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Data Set Structure Information"));

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin X"), (_variant_t)cell->m_dsgir.m_dssi.m_dcox, L"Shift used to adjust x-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Y"), (_variant_t)cell->m_dsgir.m_dssi.m_dcoy, L"Shift used to adjust y-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Dataset Coordinate Origin Z"), (_variant_t)cell->m_dsgir.m_dssi.m_dcoz, L"Shift used to adjust z-coordinate before encoding"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for x-coordinate"), (_variant_t)cell->m_dsgir.m_dssi.m_cmfx, L"Floating point to integer multiplication factor for the x-coordinate or longitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for y-coordinate"), (_variant_t)cell->m_dsgir.m_dssi.m_cmfy, L"Floating point to integer multiplication factor for the y-coordinate or latitude"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Coordinate multiplication factor for z-coordinate"), (_variant_t)cell->m_dsgir.m_dssi.m_cmfz, L"Floating point to integer multiplication factor for the z-coordinate or depths or height"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Information Type records"), (_variant_t)cell->m_dsgir.m_dssi.m_noir, L"Number of information records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Point records"), (_variant_t)cell->m_dsgir.m_dssi.m_nopn, L"Number of point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Multi Point records"), (_variant_t)cell->m_dsgir.m_dssi.m_nomn, L"Number of multi point records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Curve records"), (_variant_t)cell->m_dsgir.m_dssi.m_nocn, L"Number of curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Composite Curve records"), (_variant_t)cell->m_dsgir.m_dssi.m_noxn, L"Number of composite curve records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Surface records"), (_variant_t)cell->m_dsgir.m_dssi.m_nosn, L"Number of surface records in the data set"));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Feature Type records"), (_variant_t)cell->m_dsgir.m_dssi.m_nofr, L"Number of feature records in the data set"));

	m_wndPropList.AddProperty(pGroup2);
}

void CDialogDockLayerManager::FillPropList(S413Cell* cell)
{
	m_wndPropList.RemoveAll();

	CString curType = libS413::GetTypeString(gisLib->s413Type);

	auto s413Property = new CMFCPropertyGridProperty(_T("S413"));
	auto s413Type = new CMFCPropertyGridProperty(_T("Type"), curType);
	s413Type->AddOption(_T("AvgWaveDir"));
	s413Type->AddOption(_T("AvgWavePrd"));
	s413Type->AddOption(_T("Humidity"));
	s413Type->AddOption(_T("MaxWaveDir"));
	s413Type->AddOption(_T("MaxWpkPrd"));
	s413Type->AddOption(_T("NewSnowAmout3hr"));
	s413Type->AddOption(_T("OceanCurrent"));
	s413Type->AddOption(_T("Pressure"));
	s413Type->AddOption(_T("RainAmount3hr"));
	s413Type->AddOption(_T("SkyStatus"));
	s413Type->AddOption(_T("Temperature3hr"));
	s413Type->AddOption(_T("Visibility"));
	s413Type->AddOption(_T("WaterSalt"));
	s413Type->AddOption(_T("WaterTemperature"));
	s413Type->AddOption(_T("WaveHeightInst"));
	s413Type->AddOption(_T("WaveLength"));
	s413Type->AddOption(_T("WaveWind"));
	s413Type->AllowEdit(FALSE);
	s413Type->SetData(100);
	s413Property->AddSubItem(s413Type);
	m_wndPropList.AddProperty(s413Property);                                    
	m_wndPropList.Invalidate();
}

void CDialogDockLayerManager::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList); 
}

LRESULT CDialogDockLayerManager::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp)
	{
		return 0;
	}
	if (pProp->GetData() == 100)
	{ 
		auto value = pProp->GetValue();
		CString str = value.bstrVal;
		if (curCell)
		{
			auto s413Cell = (S413Cell *)curCell;
			if (s413Cell != nullptr)
			{
				gisLib->s413Type = libS413::GetType(str);
				theApp.MapRefresh();
			}
		}
	}
	else
	{
		auto s101Cell = (S101Cell*)curCell;
		if (s101Cell != nullptr)
		{
			CString name = pProp->GetName();
			CString value = pProp->GetValue();

			if (name.Compare(L"Encoding specification") == 0)
			{
				s101Cell->SetEncodingSpecification(value);
			}

			else if (name.Compare(L"Encoding specification edition") == 0)
			{
				s101Cell->SetEncodingSpecificationEdition(value);
			}

			else if (name.Compare(L"Product identifier") == 0)
			{
				s101Cell->SetProductIdentifier(value);

			}
			else if (name.Compare(L"Product edition") == 0)
			{
				s101Cell->SetProductEdition(value);
			}
			else if (name.Compare(L"Application profile") == 0)
			{
				s101Cell->SetApplictionProfile(value);
			}

			else if (name.Compare(L"Dataset file identifier") == 0)
			{
				s101Cell->SetDatasetFileIdentifier(value);
				UpdateList();
			}

			else if (name.Compare(L"Dataset title") == 0)
			{
				s101Cell->SetDatasetTitle(value);
			}

			else if (name.Compare(L"Dataset reference date") == 0)
			{
				s101Cell->SetDatasetReferenceDate(value);
			}

			else if (name.Compare(L"Dataset language") == 0)
			{
				s101Cell->SetDatasetLanguage(value);
			}

			else if (name.Compare(L"Dataset abstract") == 0)
			{
				s101Cell->SetDatasetAbstract(value);
			}

			else if (name.Compare(L"Dataset edition") == 0)
			{
				s101Cell->SetDatasetEdition(value);
			}    
		}
	}
	return 1;
}

void CDialogDockLayerManager::AdjustToolbarMenu()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		return;
	}

	Layer *pLayer = gisLib->GetLayer(nSelectedItem);

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd; 
	if (pLayer->m_spatialObject->m_FileType == FILE_S_57)
	{                   
	}
	else
	{      
	}                       
}    

int CDialogDockLayerManager::GetSelectedIndexNum()
{
	return nSelectedItem;
}

int CDialogDockLayerManager::GetSafeSelectedIndex()
{
	auto result = GetSelectedIndexNum();
	if (result < 0)
	{
		auto layerCount = GetLayerCount();
		if (layerCount == 1)
		{
			return 0;
		}
	}

	return result;
}

int CDialogDockLayerManager::GetLayerCount()
{
	return m_ListLayer.GetItemCount();
}

void CDialogDockLayerManager::OnButtonUp()
{
	if (nSelectedItem < 0)
	{
		::AfxMessageBox(_T("레이어를 선택해주세요"));
		return;
	}
	gisLib->LayerUp(nSelectedItem);
	UpdateList(); 
}

void CDialogDockLayerManager::OnButtonDown()
{ 
	if (nSelectedItem < 0)
	{
		nSelectedItem = -1;
		::AfxMessageBox(_T("레이어를 선택해주세요"));
		return;
	}
	gisLib->LayerDown(nSelectedItem);
	UpdateList(); 
}

void CDialogDockLayerManager::OnNMRClickListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	nSelectedItem = pNMItemActivate->iItem;
	isclickLayerManager = true;
	int i = 0;

}

void CDialogDockLayerManager::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_LM);
	
	if (!isclickLayerManager)
	{
		return;
	}


	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	CMenu menu;
	CMenu* pPopup = nullptr;
	
	
	if (theApp.IsEditingMode())
	{
		if ((CWnd*)pList == pWnd && m_ListLayer.GetSelectedCount() > 0)
		{
			VERIFY(menu.LoadMenuW(IDR_MENU_LAYERMANAGER)); 
			pPopup = menu.GetSubMenu(1);
		}
		else
		{
			VERIFY(menu.LoadMenuW(IDR_MENU_LAYERMANAGER)); 
			pPopup = menu.GetSubMenu(0);
		}
	}

	if (theApp.IsViewerMode())
	{
		if ((CWnd*)pList == pWnd && m_ListLayer.GetSelectedCount() > 0)
		{
			VERIFY(menu.LoadMenuW(IDR_MENU_LAYERMANAGER)); 
			pPopup = menu.GetSubMenu(3);
		}
		else
		{
			VERIFY(menu.LoadMenuW(IDR_MENU_LAYERMANAGER)); 
			pPopup = menu.GetSubMenu(2);
		}
	}



	CWnd* pWndPopupOwner = this; 
	while (pWndPopupOwner->GetStyle()&WS_CHILD)
	{
		pWndPopupOwner = pWndPopupOwner->GetParent();
		int selMenu = pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, pWndPopupOwner);

		switch (selMenu)
		{

		case ID_OPEN_OPEN:
			theApp.pView->OnFileOpen();
			break;

		case ID_SAVE_SAVE:
			theApp.pView->OnFileSave();
			break;

		case ID_SAVE_DELETE:
			OnButtonDelete();
			break;
		case ID_SAVE_DELETE_ALL_LAYER:
			OnButtonDeleteAllLayer();
			break;

		case ID_SAVE_LAYERSHOW:
			OnButtonOn();
			break;

		case ID_SAVE_LAYERHIDDEN:
			OnButtonOff();
			break;

		case ID_SAVE_INFOSHOW:
			OnButtonLayerinfoON();
			break;

		case ID_SAVE_INFOHIDDEN:
			OnButtonLayerinfoOff();
			break;

		case ID_SAVE_LAYERUP:
			OnButtonUp();
			break;

		case ID_SAVE_LAYERDOWN:
			OnButtonDown();
			break;

		case ID_SAVE_SHOWSUBITEM:
			ShowSuBItemDialog();
			break;

		case ID_OPEN_NEW_FEATURE:
			theApp.pView->OnENCNewCell();
			break; 
		case ID_OPEN_NEW_NO_GEOMETRY:
			theApp.pView->OnBtnCreateNoGeometry();
			break; 
		case ID_OPEN_NEW_INFORMATION:
			theApp.pView->OnBtnCreateInformationFeature();
			break;

		case ID_SAVE_NEWFEATURETYPE:
			theApp.pView->OnFeatureAddPoint();
			break;
		}
		menu.DestroyMenu();
	}
	isclickLayerManager = false;

}

void CDialogDockLayerManager::ShowSuBItemDialog()
{
	CDialogExCreateLayersub dia;
	auto MultiSelectionCount = m_anDragIndexes.GetCount();
	if (MultiSelectionCount > 0)
	{
		for (int i = 0; i < m_anDragIndexes.GetCount(); i++) 
		{
			int index = m_anDragIndexes[i];
			Layer *layer = gisLib->GetLayer(index);
			if (!layer)
			{
				return;
			}
			S101Cell* LayerData = (S101Cell*)layer->GetSpatialObject();
			dia.SetLayerFeatureData(LayerData);
		}
	}
	else if (0 <= nSelectedItem)
	{
		Layer *layer = gisLib->GetLayer(nSelectedItem); 
		if (!layer)
		{
			return;
		}
		S101Cell* LayerData = (S101Cell*)layer->GetSpatialObject();
		dia.SetLayerFeatureData(LayerData);
	}
	else
	{
		return;
	}

	if (IDOK == dia.DoModal())
	{

	}
}

void CDialogDockLayerManager::OnLvnKeydownListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR); 
	*pResult = 0;

	if (pLVKeyDow->wVKey == VK_SHIFT || pLVKeyDow->wVKey == VK_CONTROL) 
	{
		int i = 0;
	}
}