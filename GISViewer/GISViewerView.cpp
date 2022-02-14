#include "stdafx.h"  
#ifndef SHARED_HANDLERS
#include "GISViewer.h"
#endif

#include "GISViewerView.h"
#include "GISViewerDoc.h"
#include "DialogDockCurrentSelection.h"
#include "DialogDockLayerManager.h"
#include "DialogExMovePointDegree.h"
#include "DialogExMovePoint3.h"
#include "DialogExShowYourMessage.h"
#include "DialogExCreateNoGeometry.h"
#include "DialogExCreateInformationFeature.h"
#include "DialogExCreateAutoRelation.h"
#include "DialogExSelectFilter.h"
#include "DialogAddFeatureList.h"
#include "DialogExCatalogSelect.h"
#include "DialogOriginFeatureSelect.h"
#include "DialogExS102ColorMap.h"
#include "DialogExAddRoute.h"
#include "DialogExRoutePlan.h"
#include "DialogExChangeRouteName.h"
#include "DialogExDeleteRoute.h"
#include "DialogExAddWaypoint.h"
#include "DialogExDeleteWaypoint.h"
#include "DialogExSetSoundingValue.h"
#include "CSVparser.hpp"

#include "PLLibrary\\SymbolManager.h"
#include "PLLibrary\\GeoObject.h"

#include "GeoMetryLibrary\\ENCSounding.h"
#include "GeoMetryLibrary\\ENCLine.h"
#include "GeoMetryLibrary\\ENCArea.h"
#include "GeoMetryLibrary\\GeometricFuc.h"
#include "GeoMetryLibrary\\GeoCommonFuc.h"

#include "..\\DLL_InteroperabilityCatalog\\DLL_InteroperabilityCatalog.h"

#include "..\\S100ExchangeSet\\S100ExchangeSet.h"

#include "..\\S100EditingResource\\EditingContent.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include "..\\RoutePlanner\\Route.h"
#include "..\\RoutePlanner\\Waypoint.h"
#include "..\\RoutePlanner\\BufLeg.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\GML_Feature.h"
#include "GISLibrary\\ATTF.h"
#include "GISLibrary\\F_C2IL.h"
#include "GISLibrary\\Catalogue.h"
#include "GISLibrary\\F_C3IT.h"
#include "GISLibrary\\F_C2IT.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\R_CurveRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\R_PointRecord.h"
#include "GISLibrary\\F_SPAS.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\IC2D.h"
#include "GISLibrary\\CodeWithNumericCode.h"
#include "GISLibrary\\SPAS.h"

#include "S100Geometry\\SPoint.h"
#include "S100Geometry\\SMultiPoint.h"
#include "S100Geometry\\SCompositeCurve.h"
#include "S100Geometry\\SSurface.h"
#include "S100Geometry\\SGeometricFuc.h"

#include "LatLonUtility\\LatLonUtility.h"
#include "..\\LibMFCUtil\\LibMFCUtil.h"

#include <locale> 
#include <codecvt> 
#include <d2d1_1.h>
#include <iomanip>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace LatLonUtility;
#pragma comment(lib, "d2d1.lib")

std::vector<LOG> CGISViewerView::LogList;
CDialogExPickReport* CGISViewerView::m_pDlgPickReport;

IMPLEMENT_DYNCREATE(CGISViewerView, CView)
BEGIN_MESSAGE_MAP(CGISViewerView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()

	ON_COMMAND(ID_FILE_OPEN, &CGISViewerView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CGISViewerView::OnFileSave)
	ON_COMMAND(ID_BTN_S100_LOAD_EXCHANGE_SET, &CGISViewerView::OnS100ExchangeSetOpen)
	ON_COMMAND(ID_BTN_LAYER_FEATURE_SEARCH, &CGISViewerView::OnBtnLayerFeatureSearch)
	ON_COMMAND(ID_BUTTON_SELECT_FILTER, &CGISViewerView::OnBtnSelectFilter)
	ON_COMMAND(ID_BUTTON_RELATION_ALL_LIST, &CGISViewerView::OnBtnRelationListAll)
	ON_COMMAND(ID_BUTTON_CREATE_NO_GEOMETRY, &CGISViewerView::OnBtnCreateNoGeometry)
	ON_COMMAND(ID_BUTTON_CREATE_AUTO_RELATION, &CGISViewerView::OnBtnCreateAutoRelation)
	ON_COMMAND(ID_BUTTON_CREATE_SOUNDING_BY_XYZ_FILE, &CGISViewerView::OnBtnCreateSoundingByXyzFile)
	ON_COMMAND(ID_BUTTON_CREATE_INFORMATION_TYPE_FEATURE, &CGISViewerView::OnBtnCreateInformationFeature)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_LOGGER, &CGISViewerView::OnBtnShowLayoutLogger)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_LAYER_MANAGER, &CGISViewerView::OnBtnShowLayoutLayerManager)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_ATTRIBUTE_LIST, &CGISViewerView::OnBtnShowLayoutAttributeList)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_FEATURE_INFORMATION, &CGISViewerView::OnBtnShowLayoutFeatureInformation)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_RELATION, &CGISViewerView::OnBtnShowLayoutRelation)
	ON_COMMAND(ID_BUTTON_SHOW_DIALOG_CURRENT_SELECTION, &CGISViewerView::OnBtnShowLayoutCurrentSelection)
	ON_COMMAND(ID_BUTTON_ZOOM_IN, &CGISViewerView::OnButtonZoomIn)
	ON_COMMAND(ID_BUTTON_ZOOM_OUT, &CGISViewerView::OnButtonZoomOut)
	ON_COMMAND(ID_BUTTON_VIEW_ALL, &CGISViewerView::OnButtonViewAll)
	ON_COMMAND(ID_BUTTON_ROTATE_CLOCKWISE, &CGISViewerView::OnButtonRotateClockwise)
	ON_COMMAND(ID_BUTTON_ROTATE_ANTICLOCKWISE, &CGISViewerView::OnButtonRotateAnticlockwise)
	ON_COMMAND(ID_BUTTON_NORTH_UP, &CGISViewerView::OnButtonNorthUp)

	ON_UPDATE_COMMAND_UI(ID_EDIT_SCALE, &CGISViewerView::OnUpdateEditScale)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LATITUDE, &CGISViewerView::OnUpdateEditLatitude)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LONGITUDE, &CGISViewerView::OnUpdateEditLongitude)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TMP_LONG, &CGISViewerView::OnUpdateEditTmpLong)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TMP_LAT, &CGISViewerView::OnUpdateEditTmpLat)
	ON_BN_CLICKED(IDC_BUTTON_LM_ADD, &CGISViewerView::OnBnClickedButtonLmAdd)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN_EXCHANGE, &CGISViewerView::OnFileOpenExchange)
	ON_UPDATE_COMMAND_UI(ID_COMBO_SCALE, &CGISViewerView::OnUpdateComboScale)
	ON_COMMAND(ID_COMBO_SCALE, &CGISViewerView::OnComboScale)
	ON_COMMAND(ID_BUTTON_CAPTURE, &CGISViewerView::OnButtonCapture)
	ON_COMMAND(ID_BUTTON_MOVE_POINT, &CGISViewerView::OnButtonMovePoint)
	ON_WM_MOVE()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_BUTTON_DISTANCE, &CGISViewerView::OnButtonDistance)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISTANCE, &CGISViewerView::OnUpdateButtonDistance)
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTON_MEASURE_AREA, &CGISViewerView::OnButtonMeasureArea)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MEASURE_AREA, &CGISViewerView::OnUpdateButtonMeasureArea)

	ON_COMMAND(ID_BUTTON_MOVE_TWO_POINT, &CGISViewerView::OnButtonMoveByLatAndLon) 
	ON_COMMAND(ID_FEATURE_ADD_MULTI_POINT, &CGISViewerView::OnFeatureAddMultiPoint)
	ON_COMMAND(ID_FEATURE_ADD_POINT, &CGISViewerView::OnFeatureAddPoint)
	ON_COMMAND(ID_FEATURE_ADD_LINE, &CGISViewerView::OnFeatureAddLine)
	ON_COMMAND(ID_FEATURE_ADD_AREA, &CGISViewerView::OnFeatureAddArea)
	ON_COMMAND(ID_FEATURE_CHANGE, &CGISViewerView::OnFeatureChange)
	ON_COMMAND(ID_ENC_NEW_CELL, &CGISViewerView::OnENCNewCell)
	ON_COMMAND(ID_FEATURE_ADD_USE_EXISTING_VECTOR, &CGISViewerView::OnFeatureAddUseExistingVector)
	ON_COMMAND(ID_FEATURE_ADD_FEATURE_RELATION, &CGISViewerView::OnFeatureAddFeatureRelation)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_MULTI_POINT, &CGISViewerView::OnUpdateFeatureAddMultiPoint)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_POINT, &CGISViewerView::OnUpdateFeatureAddPoint)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_LINE, &CGISViewerView::OnUpdateFeatureAddLine)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_AREA, &CGISViewerView::OnUpdateFeatureAddArea)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_USE_EXISTING_VECTOR, &CGISViewerView::OnUpdateFeatureAddUseExistingVector)
	ON_UPDATE_COMMAND_UI(ID_FEATURE_ADD_FEATURE_RELATION, &CGISViewerView::OnUpdateFeatureAddFeatureRelation)

	ON_COMMAND(ID_BUTTON_READ_PC_OUTPUT_XML, &CGISViewerView::OnButtonReadPcOutputXml)
	ON_MESSAGE(MSG_GETCATALOG, &CGISViewerView::GetCatalogType)
	ON_COMMAND(ID_BUTTON_S102_COLOR, &CGISViewerView::OnButtonS102Color) 

	ON_COMMAND(ID_BUTTON_ROUTE_ADD, &CGISViewerView::OnButtonRouteAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROUTE_ADD, &CGISViewerView::OnUpdateButtonRouteAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROUTE_MODIFY, &CGISViewerView::OnUpdateButtonRouteModify)
	ON_COMMAND(ID_BUTTON_ROUTE_MODIFY, &CGISViewerView::OnButtonRouteModify)
	ON_COMMAND(ID_BUTTON_ROUTE_DELETE, &CGISViewerView::OnButtonRouteDelete)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROUTE_DELETE, &CGISViewerView::OnUpdateButtonRouteDelete)
	ON_COMMAND(ID_BUTTON_WAYPOINT_ADD, &CGISViewerView::OnButtonWaypointAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_ADD, &CGISViewerView::OnUpdateButtonWaypointAdd)
	ON_COMMAND(ID_BUTTON_WAYPOINT_MODIFY, &CGISViewerView::OnButtonWaypointModify)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_MODIFY, &CGISViewerView::OnUpdateButtonWaypointModify)
	ON_COMMAND(ID_BUTTON_WAYPOINT_DELETE, &CGISViewerView::OnButtonWaypointDelete)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_DELETE, &CGISViewerView::OnUpdateButtonWaypointDelete)
	ON_COMMAND(ID_BUTTON_WAYPOINT_MOUSE_ADD, &CGISViewerView::OnButtonWaypointMouseAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_MOUSE_ADD, &CGISViewerView::OnUpdateButtonWaypointMouseAdd)
	ON_COMMAND(ID_BUTTON_WAYPOINT_MOUSE_MODIFY, &CGISViewerView::OnButtonWaypointMouseModify)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_MOUSE_MODIFY, &CGISViewerView::OnUpdateButtonWaypointMouseModify)
	ON_COMMAND(ID_BUTTON_WAYPOINT_MOUSE_DELETE, &CGISViewerView::OnButtonWaypointMouseDelete)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WAYPOINT_MOUSE_DELETE, &CGISViewerView::OnUpdateButtonWaypointMouseDelete)
	ON_COMMAND(ID_BUTTON_ROUTE_LOAD, &CGISViewerView::OnButtonRouteLoad)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROUTE_LOAD, &CGISViewerView::OnUpdateButtonRouteLoad)
	ON_COMMAND(ID_BUTTON_ROUTE_SAVE, &CGISViewerView::OnButtonRouteSave)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROUTE_SAVE, &CGISViewerView::OnUpdateButtonRouteSave)
	ON_COMMAND(ID_BUTTON_ROUTE_CHECK, &CGISViewerView::OnButtonRouteCheck)
	ON_COMMAND(ID_SLIDER_ROUTE, &CGISViewerView::OnSliderRoute)

	ON_COMMAND(ID_BUTTON_ROUTE_NEXT, &CGISViewerView::OnButtonRouteNext)

	ON_COMMAND(ID_BUTTON_ROUTE_SLOW, &CGISViewerView::OnButtonRouteSlow)
	ON_COMMAND(ID_BUTTON_ROUTE_PREV, &CGISViewerView::OnButtonRoutePrev)
	ON_COMMAND(ID_BUTTON_ROUTE_PLAY, &CGISViewerView::OnButtonRoutePlay)
	ON_COMMAND(ID_BUTTON_ROUTE_PAUSE, &CGISViewerView::OnButtonRoutePause)
	ON_COMMAND(ID_BUTTON_ROUTE_STOP, &CGISViewerView::OnButtonRouteStop)
	ON_COMMAND(ID_BUTTON_ROUTE_NEXT, &CGISViewerView::OnButtonRouteNext)
	ON_COMMAND(ID_BUTTON_ROUTE_FAST, &CGISViewerView::OnButtonRouteFast)


	ON_COMMAND(ID_BUTTON_EDIT_AREA_INNER_CIRCLE, &CGISViewerView::OnButtonEditAraeInnerCircle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_EDIT_AREA_INNER_CIRCLE, &CGISViewerView::OnUpdateButtonEditAraeInnerCircle)

	ON_COMMAND(ID_BUTTON_EDIT_MOUSE_VECTOR, &CGISViewerView::OnButtonEditMouseVector)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_EDIT_MOUSE_VECTOR, &CGISViewerView::OnUpdateButtonEditMouseVector)
	ON_COMMAND(ID_BUTTON_EDIT_UNDO, &CGISViewerView::OnButtonEditUndo)
	ON_COMMAND(ID_BUTTON_EDIT_REDO, &CGISViewerView::OnButtonEditRedo)
	ON_COMMAND(ID_VECTOR_EDIT_DEL_MOUSE, &CGISViewerView::OnButtonEditMouseVectorDelete)
	ON_COMMAND(ID_VECTOR_EDIT_ADD_MOUSE, &CGISViewerView::OnButtonEditMouseVectorAdd)

	ON_COMMAND(ID_BUTTON_S111_INDEX_UP, &CGISViewerView::OnButtonS111IndexUp)
	ON_COMMAND(ID_BUTTON_S111_INDEX_DN, &CGISViewerView::OnButtonS111IndexDn)
	ON_COMMAND(ID_BUTTON_ZOOM_AREA, &CGISViewerView::OnButtonZoomArea)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ZOOM_AREA, &CGISViewerView::OnUpdateButtonZoomArea)

	ON_COMMAND(ID_BTN_IC_OPEN, &CGISViewerView::OnButtonICOpen)
	ON_COMMAND(ID_CB_IC_LEVEL, &CGISViewerView::OnComboICLevel)
	ON_COMMAND(ID_BUTTON_S111_INDEX_PLAY, &CGISViewerView::OnButtonS111IndexPlay)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_S111_INDEX_PLAY, &CGISViewerView::OnUpdateButtonS111IndexPlay)
	ON_COMMAND(ID_BUTTON_S111_INDEX_STOP, &CGISViewerView::OnButtonS111IndexStop)
	ON_COMMAND(ID_BTN_GET_DEPTH_AREA_INFO, &CGISViewerView::OnButtonGetDepthAreaInfo)   

	ON_COMMAND(ID_BTN_COVERAGE_OVERSCALE_SHOW, &CGISViewerView::OnButtonShowOverscale)

	ON_COMMAND(ID_BUTTON_EDIT_SNAP, &CGISViewerView::OnButtonEditSnap)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_EDIT_SNAP, &CGISViewerView::OnUpdateButtonEditSnap)


	ON_COMMAND(ID_BUTTON_UNCERTAINTY, &CGISViewerView::OnButtonUncertainty)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_UNCERTAINTY, &CGISViewerView::OnUpdateButtonUncertainty)

	ON_COMMAND(ID_BUTTON_TEXT_PLACEMENT, &CGISViewerView::OnButtonTextPlacement_ON_OFF)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TEXT_PLACEMENT, &CGISViewerView::OnUpdateButtonTextPlacement_ON_OFF)

	ON_COMMAND(ID_BUTTON_SAVE_TEXT_PLACEMENT, &CGISViewerView::OnButtonTextPlacement_SAVE) 

	ON_COMMAND(ID_BUTTON_GO_TO_KOREA, &CGISViewerView::OnButtonGoToKoreaArea)


	ON_COMMAND(ID_BUTTON_BASEMAP_ON_OFF, &CGISViewerView::OnButtonBaseMapOnOff)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BASEMAP_ON_OFF, &CGISViewerView::OnUpdateButtonBaseMapOnOff)


	ON_COMMAND(ID_BUTTON_SCALED_SYMBOL, &CGISViewerView::OnButtonScaledSymbolSize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SCALED_SYMBOL, &CGISViewerView::OnUpdateButtonScaledSymbolSize)

	ON_COMMAND(ID_BTN_APPLY_COVERAGE_SCALE, &CGISViewerView::OnButtonApplyDataCoverageScale)
	ON_UPDATE_COMMAND_UI(ID_BTN_APPLY_COVERAGE_SCALE, &CGISViewerView::OnUpdateButtonApplyDataCoverageScale)

	ON_WM_COPYDATA()

	ON_COMMAND(PCFCSAVEBUTTON, &CGISViewerView::OnPcfcsavebutton)
	ON_COMMAND(DATASETSAVEBUTTON, &CGISViewerView::OnDatasetsavebutton)
	ON_COMMAND(ID_BUTTON_ZOON_TO_LAYER, &CGISViewerView::OnZooninlayer)
		ON_WM_DROPFILES()
		ON_COMMAND(ID_BUTTON_GENERATE_TILE_MAP, &CGISViewerView::OnButtonGenerateTileMap)
		END_MESSAGE_MAP()



int g_editInnerCircle = 0;

long CGISViewerView::GetCatalogType(UINT wParam, LONG lParam)
{
	CDialogExCatalogSelect dlg;
	int ret = dlg.DoModal();

	return ret;
}

void CGISViewerView::OnButtonS102Color()
{
	CDialogExS102ColorMap* dlg = new CDialogExS102ColorMap(this);
	dlg->Create(IDD_DIALOG_S102_COLOR);
	dlg->ShowWindow(SW_SHOW);
}

CGISViewerView::CGISViewerView() 
{
#ifdef ROUTE_CHECK
	pRouteForCheck = nullptr;
	pRouteCheckResult = nullptr;
	pRoutePlannerForCheck = nullptr;
	pRoutePlannerForCheckResult = nullptr;
	m_bRouteCheckOwnShip = false;
	int ownShipR = 10;
	int ownShipTheta = 30;
	ownShipVector[0].X = 0; 
	ownShipVector[0].Y = 0;
	ownShipVector[1].X = (INT)(ownShipR * cos(ownShipTheta * DEG2RAD));
	ownShipVector[1].Y = (INT)(ownShipR * sin(ownShipTheta * DEG2RAD) + ownShipR);
	ownShipVector[2].X = (INT)(-ownShipR * cos(ownShipTheta * DEG2RAD));
	ownShipVector[2].Y = (INT)(ownShipR * sin(ownShipTheta * DEG2RAD) + ownShipR);
	m_bRouteCheckOwnShipCent = true;
	m_bRoutePlay = false;
	routeSpeed = 1;
#endif 

	m_Icon = 0; 
	m_bLButtonDown = false; 
	m_bMoveStart = false;
	m_bMapRefesh = false;

	beModifyWaypoint = false; 
	m_pDlgPickReport = nullptr;
	ptPick.x = -100;
	ptPick.y = -100;
	ptOldPickX = 0;
	ptOldPickY = 0;
	isMoved = false;
	onPickArrow = false;
	ptPickX = 0;
	ptPickY = 0; 
	m_pSelectedLayer = nullptr;

	moveMX = 0.0;
	moveMY = 0.0; 
	m_pGisLib = new CGISLibraryApp();
	gisLib = m_pGisLib;
	m_pGisLib->InitLibrary(); 
	m_pSymbolManager = new CSymbolManager(); 

	ENCGeometry::pSymbolManager = m_pSymbolManager; 

	CString strFolderPath;
	::GetModuleFileName(NULL, strFolderPath.GetBuffer(MAX_PATH), MAX_PATH);
	strFolderPath.ReleaseBuffer();
	if (strFolderPath.Find('\\') != -1)
	{
		for (int i = strFolderPath.GetLength() - 1; i >= 0; i--)
		{
			TCHAR ch = strFolderPath[i];
			strFolderPath.Delete(i);
			if (ch == '\\') break;

		}
	}

	CString pathColor(_T("..\\ProgramData\\dic\\day_blackback.dic"));
	CString pathSymbol(_T("..\\ProgramData\\symbol\\symbol.txt"));
	CString pathPattern(_T("..\\ProgramData\\symbol\\Symbol_Pattern.txt"));
	CString pathComposite(_T("..\\ProgramData\\symbol\\Composite_Line.txt"));
	CString pathCompositeSymbol(_T("..\\ProgramData\\symbol\\Composite_Line_Symbol.txt")); 
	m_pSymbolManager->OpenColor(pathColor);
	m_pSymbolManager->OpenSymbol(pathSymbol);
	m_pSymbolManager->OpenPattern(pathPattern);
	m_pSymbolManager->OpenCompositeSymbol(pathCompositeSymbol);
	m_pSymbolManager->OpenComposite(pathComposite); 

	m_bLMove = false;
	m_bRMove = false;

	feSearchObject = nullptr;
	bDrawMovePoint = false;

	pRoutePlanner = new RT::RoutePlanner();
	m_pNewFeatureManager = new NewFeatureManager();

	m_bEditUseExistingVector = false;
	m_bEditFeatureRelation = false;

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	m_RenderTarget.Create(props);
	m_pBlackBrush = new CD2DSolidColorBrush(&m_RenderTarget, D2D1::ColorF(D2D1::ColorF::Crimson));

	m_bZoomArea = false;

	m_pEditingContent = NULL;

	m_pDirect2dFactory = nullptr;
	pWICFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pDirect2dSolidColorBrush = nullptr;

}


CGISViewerView::~CGISViewerView() 
{
	SaveLastPosScale();
	theApp.SaveSettings();

	delete m_pGisLib;

	delete m_pSymbolManager; 

	if (mem_dc.GetSafeHdc())
	{
		mem_dc.DeleteDC();
		memBitmap.DeleteObject();
	}
	if (transDC.GetSafeHdc())
	{
		transDC.DeleteDC();
		transBitmap.DeleteObject();
	}
	if (map_dc.GetSafeHdc())
	{
		map_dc.DeleteDC();
		mapBitmap.DeleteObject();
	}

	if (pRoutePlanner)
		delete pRoutePlanner;
	if (m_pNewFeatureManager)
		delete m_pNewFeatureManager;

	if (mp_factory)
		mp_factory->Release();
	if (mp_render_target)
		mp_render_target->Release();


	if (m_pEditingContent)
		delete m_pEditingContent;     



	CoUninitialize();


}


BOOL CGISViewerView::PreCreateWindow(CREATESTRUCT& cs)
{  

	return CView::PreCreateWindow(cs);
} 

void CGISViewerView::OnDraw(CDC* pDC) 
{
	CGISViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	ENCGeometry::typeOfDrawing = 1;
	ENCGeometry::InitTextRect();
	ENCGeometry::InitSoundingTextRect();
	ENCGeometry::InitIsobathTextRect(); 
	CRect rect;
	GetClientRect(&rect);
	
	{        
	}

	if (!mem_dc.GetSafeHdc())
	{
		if (mem_dc.CreateCompatibleDC(pDC))
		{
			if (memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = mem_dc.SelectObject(&memBitmap);
				if (pOldBitmap != NULL)
					pOldBitmap->DeleteObject();
			}
			mem_dc.SetBkMode(TRANSPARENT);
		}
		if (transDC.CreateCompatibleDC(pDC))
		{
			if (transBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = transDC.SelectObject(&transBitmap);
				if (pOldBitmap != NULL)
					pOldBitmap->DeleteObject();
			}
			transDC.SetBkMode(TRANSPARENT);
		}
		if (map_dc.CreateCompatibleDC(pDC))
		{
			if (mapBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = map_dc.SelectObject(&mapBitmap);
				if (pOldBitmap != NULL)
					pOldBitmap->DeleteObject();
			}
			map_dc.SetBkMode(TRANSPARENT);
		}
	}

	static int bFirstDrawOverlayLayerToMapLayer = 0;

	if (m_bMoveStart)
	{
		if (bFirstDrawOverlayLayerToMapLayer)
		{
			HDC overlayDC = map_dc.GetSafeHdc();
			m_pGisLib->DrawOverlay(overlayDC, 1);
			bFirstDrawOverlayLayerToMapLayer = 0;
		}

		CRect er;
		er.SetRect(0, 0, rect.Width(), m_ep.y - m_sp.y);
		transDC.FillSolidRect(&er, RGB(200, 200, 200));

		er.SetRect(0, 0, m_ep.x - m_sp.x, rect.Height());
		transDC.FillSolidRect(&er, RGB(200, 200, 200));

		er.SetRect(rect.Width() - (m_sp.x - m_ep.x), 0, rect.Width(), rect.Height());
		transDC.FillSolidRect(&er, RGB(200, 200, 200));

		er.SetRect(0, rect.Height() - (m_sp.y - m_ep.y), rect.Width(), rect.Height());
		transDC.FillSolidRect(&er, RGB(200, 200, 200));

		transDC.BitBlt(rect.left - (m_sp.x - m_ep.x), rect.top - (m_sp.y - m_ep.y), rect.Width(), rect.Height(), &map_dc, 0, 0, SRCCOPY);

		HDC transHDC = transDC.GetSafeHdc();
		DrawPickReport(transHDC, m_ep.x - m_sp.x, m_ep.y - m_sp.y);
		DrawDistance(&transDC, m_ep.x - m_sp.x, m_ep.y - m_sp.y);
		DrawMeasureArea(&transDC, m_ep.x - m_sp.x, m_ep.y - m_sp.y);
		DrawMovePoint(&transDC, pDrawMoveMPoint, m_ep.x - m_sp.x, m_ep.y - m_sp.y);
		DrawRoute(CDC::FromHandle(transHDC), true, m_ep.x - m_sp.x, m_ep.y - m_sp.y);

		if (m_Icon == EDIT_VECTOR)
		{ 
			if (m_pEditingContent != nullptr)
			{
				m_pEditingContent->Draw(&transDC, m_pGisLib, m_ep.x - m_sp.x, m_ep.y - m_sp.y);
			}

		}
		bDrawMovePoint = false;

		HRESULT hr = S_OK; 
		{
			m_RenderTarget.BindDC(transDC, rect);
			m_RenderTarget.BeginDraw();
			m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

			DrawEditingResource(&m_RenderTarget, m_ep.x - m_sp.x, m_ep.y - m_sp.y);

			hr = m_RenderTarget.EndDraw();
		}

		DrawZoomArea(CDC::FromHandle(transDC));

		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &transDC, 0, 0, SRCCOPY);
	} 
	else if (m_bMapRefesh)
	{
		bFirstDrawOverlayLayerToMapLayer = 1;

		map_dc.FillSolidRect(&rect, RGB(255, 255, 255));
		HDC hdc = map_dc.GetSafeHdc();

		HRGN rgn = CreateRectRgn(0, 0, rect.Width(), rect.Height());
		::SelectClipRgn(hdc, rgn);

		m_pGisLib->SetViewMBR(rect);

#ifndef TILE_MAP
		m_pGisLib->Draw(hdc);
#else
		gisLib->GetLayerManager()->DrawLayerList(hdc);
#endif

		::DeleteObject(rgn);

		mem_dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &map_dc, 0, 0, SRCCOPY);  

		HDC overlayDC = mem_dc.GetSafeHdc();
		DrawDistance(&mem_dc);
		DrawMeasureArea(&mem_dc);

		DrawPickReport(overlayDC);
		DrawSelectedLayerRect(overlayDC);

		DrawMovePoint(&mem_dc, pDrawMoveMPoint);

		if (m_Icon == EDIT_VECTOR)
		{
			if (m_pEditingContent != nullptr)
			{
				m_pEditingContent->Draw(&mem_dc, m_pGisLib);
			} 

		}

		DrawRoute(&mem_dc);

		HRESULT hr = S_OK; 
		{
			m_RenderTarget.BindDC(mem_dc, rect);
			m_RenderTarget.BeginDraw();
			m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

			DrawEditingResource(&m_RenderTarget);

			hr = m_RenderTarget.EndDraw();
		}
		DrawZoomArea(&mem_dc);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &mem_dc, 0, 0, SRCCOPY);


		theApp.m_pDockablePaneLayerManager.UpdateList();
		m_bMapRefesh = false;
	}
	else
	{
		mem_dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &map_dc, 0, 0, SRCCOPY);

		HDC overlayDC = mem_dc.GetSafeHdc();
		m_pGisLib->DrawOverlay(overlayDC, 1);
		DrawDistance(&mem_dc);
		DrawMeasureArea(&mem_dc);

		DrawPickReport(overlayDC);
		DrawSelectedLayerRect(overlayDC);
		DrawRoute(&mem_dc);

		HRESULT hr = S_OK; 
		{
			m_RenderTarget.BindDC(mem_dc, rect);
			m_RenderTarget.BeginDraw();
			m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

			DrawEditingResource(&m_RenderTarget);

			hr = m_RenderTarget.EndDraw();
		}

		DrawMovePoint(&mem_dc, pDrawMoveMPoint);


		if (m_Icon == EDIT_VECTOR)
		{ 
			if (m_pEditingContent != nullptr)
			{
				m_pEditingContent->Draw(&mem_dc, m_pGisLib);
			} 
		}
		DrawZoomArea(CDC::FromHandle(overlayDC));

		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &mem_dc, 0, 0, SRCCOPY);
	}

	DrawUIScale();
	if (!ENCCommon::WGS84_TEXT_TYPE)
	{
		DrawUILatDegree();
		DrawUILonDegree();
	}
	else
	{
		DrawUILatDMS();
		DrawUILonDMS();
	}
	DrawIndexMap();
}

void CGISViewerView::DrawUIScale()
{ 
	if (m_pGisLib->GetLayerCount() >= 0) {
		double Scale = m_pGisLib->GetCurrentScale();

		CString str, newStr, strComma;

		strComma.Format(_T(","));

		str.Format(_T("%.lf"), Scale);

		int addedLength;

		if ((str.GetLength() % 3) == 0) {
			addedLength = (str.GetLength() / 3) - 1;
		}
		else {
			addedLength = (str.GetLength() / 3);
		}

		newStr = str;

		for (int k = 0; k < addedLength; k++) {
			newStr.AppendChar('a');
		}

		int cnt = 0;

		int i = str.GetLength() - 1;
		int j = newStr.GetLength() - 1;

		for (; i >= 0;) {
			newStr.SetAt(j, str.GetAt(i));
			j--;
			i--;
			cnt++;

			if ((cnt == 3) && (j >= 0)) {
				newStr.SetAt(j, strComma.GetAt(0));
				j--;
				cnt = 0;
			}
		}

		str.Format(_T("1 : "));
		str.AppendFormat(newStr);
		m_strScale = str;
	}

	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_pMainFrame->m_wndRibbonBar.FindByID(ID_COMBO_SCALE));
	pComboBox->SetEditText(m_strScale);
}

void CGISViewerView::DrawUILatDegree()
{
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(m_ptCurrent.x, m_ptCurrent.y, &curLong, &curLat);
	m_pGisLib->InverseProjection(&curLong, &curLat);

	m_strLatitude.Format(_T("Lat : %lf"), curLat);;

	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_pMainFrame->m_wndRibbonBar.FindByID(ID_EDIT_LATITUDE));
	pEdit->SetEditText(m_strLatitude);
}

void CGISViewerView::DrawUILatDMS()
{
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(m_ptCurrent.x, m_ptCurrent.y, &curLong, &curLat);
	m_pGisLib->InverseProjection(&curLong, &curLat); 
	if (curLong < -180) {
		curLong += 360;
	}

	if (curLong > 180) {
		curLong -= 360;
	}

	double degree, minute, second;

	degree = (int)curLat;

	minute = (curLat - degree) * 60;

	second = (minute - (int)minute) * 60;

	LatLonUtility::DegreeToDMS(curLat, degree, minute, second);

	CString str;
	str.Format(_T("Lat : %.0lf˚ %.0lf' %0.2lf"), degree, minute, second);

	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_pMainFrame->m_wndRibbonBar.FindByID(ID_EDIT_LATITUDE));
	pEdit->SetEditText(str);
}

void CGISViewerView::DrawUILonDegree()
{
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(m_ptCurrent.x, m_ptCurrent.y, &curLong, &curLat);
	m_pGisLib->InverseProjection(&curLong, &curLat); 
	if (curLong < -180) {
		curLong += 360;
	}

	if (curLong > 180) {
		curLong -= 360;
	}

	m_strLongitude.Format(_T("Lon : %lf"), curLong);

	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_pMainFrame->m_wndRibbonBar.FindByID(ID_EDIT_LONGITUDE));
	pEdit->SetEditText(m_strLongitude);
}

void CGISViewerView::DrawUILonDMS()
{
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(m_ptCurrent.x, m_ptCurrent.y, &curLong, &curLat);
	m_pGisLib->InverseProjection(&curLong, &curLat); 
	if (curLong < -180) {
		curLong += 360;
	}

	if (curLong > 180) {
		curLong -= 360;
	}

	double degree, minute, second;

	degree = (int)curLong;

	minute = (curLong - degree) * 60;

	second = (minute - (int)minute) * 60;

	DegreeToDMS(curLong, degree, minute, second);


	CString str;
	str.Format(_T("Lon : %.0lf˚ %.0lf' %.2lf"), degree, minute, second);

	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_pMainFrame->m_wndRibbonBar.FindByID(ID_EDIT_LONGITUDE));
	pEdit->SetEditText(str);
}

void CGISViewerView::DrawIndexMap()
{         
}


void CGISViewerView::GetPickedFeature(CPoint _point)
{
	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;

	double wgs84x = m_pNewFeatureManager->m_addFeaturePoint.x, wgs84y = m_pNewFeatureManager->m_addFeaturePoint.y;
	m_pGisLib->Projection(&wgs84x, &wgs84y);

	long px, py;
	m_pGisLib->WorldToDevice(wgs84x, wgs84y, &px, &py);

	m_pGisLib->DeviceToWorld((long)(px - 5), (long)(px + 5), &xmin, &ymin);
	m_pGisLib->DeviceToWorld((long)(py + 5), (long)(py - 5), &xmax, &ymax);

	if (!m_pNewFeatureManager->m_cell)
	{
		return;
	} 
	if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_57)
	{
		ENCCell *cell = (ENCCell*)m_pNewFeatureManager->m_cell;
		Layer *l = m_pNewFeatureManager->m_cell->m_pLayer;
		__int64 key = 0;
		ENCGeometry *sgeo = NULL;
		MBR pickMBR(xmin, ymin, xmax, ymax);

		m_pNewFeatureManager->m_pPickedFeatureRecords.clear();

		switch (m_Icon)
		{
		case FEATURE_ADD_AREA:
			for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
			{
				ENC_Feature* fr = iter->second;
				if (fr->m_geometry == nullptr) continue;
				sgeo = (ENCGeometry *)fr->m_geometry;

				if (fr->m_frid.PRIM == 3) 
				{
					if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
					{
						int code = fr->m_frid.OBJL;
						double centerX = 0;
						double centerY = 0;

						m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY);

						if (GeometricFuc::inside(centerX, centerY, (ENCArea*)fr->m_geometry) == 1)
						{
							CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fr->m_frid.OBJL);

							S57NamedFeature namedFeature;
							namedFeature.m_fe = fr;
							namedFeature.m_name = obj->Object_class;
							m_pNewFeatureManager->m_pPickedObjectRecords.push_back(namedFeature);
						}
					}
				}
			}
			break;

		case FEATURE_ADD_LINE:
			for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
			{
				ENC_Feature* fr = iter->second;
				if (fr->m_geometry == nullptr) continue;
				sgeo = (ENCGeometry *)fr->m_geometry;

				if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
				{
					if (fr->m_frid.PRIM == 2) 
					{
						ENCArea* mbrArea = new ENCArea;
						mbrArea->NumParts = 1;
						mbrArea->NumPoints = 5;
						mbrArea->Parts = new int[1];
						mbrArea->Parts = 0;
						mbrArea->Points = new GeoPoint[5];
						mbrArea->Points[0].x = xmin;
						mbrArea->Points[0].y = ymin;
						mbrArea->Points[1].x = xmax;
						mbrArea->Points[1].y = ymin;
						mbrArea->Points[2].x = xmax;
						mbrArea->Points[2].y = ymax;
						mbrArea->Points[3].x = xmin;
						mbrArea->Points[3].y = ymax;
						mbrArea->Points[4].x = xmin;
						mbrArea->Points[4].y = ymin;
						mbrArea->m_mbr.xmin = xmin;
						mbrArea->m_mbr.ymin = ymin;
						mbrArea->m_mbr.xmax = xmax;
						mbrArea->m_mbr.ymax = ymax;

						if (GeometricFuc::overlap((ENCLine*)(fr->m_geometry), mbrArea) == 1)
						{
							CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fr->m_frid.OBJL);

							S57NamedFeature namedFeature;
							namedFeature.m_fe = fr;
							namedFeature.m_name = obj->Object_class;
							m_pNewFeatureManager->m_pPickedObjectRecords.push_back(namedFeature);
						}
						delete mbrArea;
					}
				}
			}
			break;

		case FEATURE_ADD_POINT:

			for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
			{
				ENC_Feature* fr = iter->second;
				if (fr->m_geometry == nullptr) continue;
				sgeo = (ENCGeometry *)fr->m_geometry;

				if (fr->m_frid.PRIM == 1) 
				{
					double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
					double geoY = ((SPoint*)fr->m_geometry)->m_point.y;
					long x, y;
					m_pGisLib->WorldToDevice(geoX, geoY, &x, &y);

					double distance = (x - px) * (x - px) + (y - py)*(y - py);
					double shortestDistance = 145;
					if (shortestDistance > distance)
					{
						CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fr->m_frid.OBJL);

						S57NamedFeature namedFeature;
						namedFeature.m_fe = fr;
						namedFeature.m_name = obj->Object_class;
						m_pNewFeatureManager->m_pPickedObjectRecords.push_back(namedFeature);
					}
				}
			}
			break;
		case FEATURE_ADD_MULTI_POINT:
			for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
			{
				ENC_Feature* fr = iter->second;
				if (fr->m_geometry == nullptr) continue;
				sgeo = (ENCGeometry *)fr->m_geometry;

				if (fr->m_frid.PRIM == 1) 
				{
					double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
					double geoY = ((SPoint*)fr->m_geometry)->m_point.y;
					long x, y;
					m_pGisLib->WorldToDevice(geoX, geoY, &x, &y);

					double distance = (x - px) * (x - px) + (y - py)*(y - py);
					double shortestDistance = 145;
					if (shortestDistance > distance)
					{
						CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fr->m_frid.OBJL);

						S57NamedFeature namedFeature;
						namedFeature.m_fe = fr;
						namedFeature.m_name = obj->Object_class;
						m_pNewFeatureManager->m_pPickedObjectRecords.push_back(namedFeature);
					}
				}
			}

			break;
		}

	}
	else if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)            
	{
		S101Cell *cell = (S101Cell*)m_pNewFeatureManager->m_cell;
		Layer *l = m_pNewFeatureManager->m_cell->m_pLayer;

		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		POSITION pos = NULL;
		MBR pickMBR(xmin, ymin, xmax, ymax);
		SGeometry *sgeo = NULL;

		m_pNewFeatureManager->m_pPickedFeatureRecords.clear();

		switch (m_Icon)
		{
		case FEATURE_ADD_AREA:
		case FEATURE_ADD_POINT:
		case FEATURE_ADD_MULTI_POINT:
		case FEATURE_ADD_LINE:

			pos = cell->m_feaMap.GetStartPosition();

			SSurface* mbrArea = new SSurface;
			mbrArea->m_numParts = 1;
			mbrArea->m_numPoints = 5;
			mbrArea->m_pParts = new int[1];
			mbrArea->m_pParts[0] = 0;
			mbrArea->m_pPoints = new GeoPoint[5];
			mbrArea->m_pPoints[0].x = xmin;
			mbrArea->m_pPoints[0].y = ymin;
			mbrArea->m_pPoints[1].x = xmax;
			mbrArea->m_pPoints[1].y = ymin;
			mbrArea->m_pPoints[2].x = xmax;
			mbrArea->m_pPoints[2].y = ymax;
			mbrArea->m_pPoints[3].x = xmin;
			mbrArea->m_pPoints[3].y = ymax;
			mbrArea->m_pPoints[4].x = xmin;
			mbrArea->m_pPoints[4].y = ymin;
			mbrArea->m_mbr.xmin = xmin;
			mbrArea->m_mbr.ymin = ymin;
			mbrArea->m_mbr.xmax = xmax;
			mbrArea->m_mbr.ymax = ymax;

			while (pos != NULL) 
			{
				cell->m_feaMap.GetNextAssoc(pos, key, fr);
				if (fr->m_geometry == nullptr) continue;
				sgeo = (SGeometry *)fr->m_geometry;

				if (sgeo->type == 3) 
				{
					if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
					{
						int code = fr->m_frid.m_nftc;
						auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
						double centerX = 0;
						double centerY = 0;

						m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY);

						if (SGeometricFuc::inside(centerX, centerY, (SSurface*)fr->m_geometry) == 1)
						{
							S100NamedFeature namedFeature;
							namedFeature.m_fe = fr;
							namedFeature.m_name = itor->second->m_code;
							m_pNewFeatureManager->m_pPickedFeatureRecords.push_back(namedFeature);
						}
					}
				}
				else if (sgeo->type == 2) 
				{
					if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
					{
						int code = fr->m_frid.m_nftc;
						auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
						if (SGeometricFuc::overlap((SCurve*)(fr->m_geometry), mbrArea) == 1)
						{
							S100NamedFeature namedFeature;
							namedFeature.m_fe = fr;
							namedFeature.m_name = itor->second->m_code;
							m_pNewFeatureManager->m_pPickedFeatureRecords.push_back(namedFeature);
						}

					}
				}
				else if (sgeo->type == 1) 
				{
					int code = fr->m_frid.m_nftc; 

					auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code); 
					double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
					double geoY = ((SPoint*)fr->m_geometry)->m_point.y;
					long x, y;
					m_pGisLib->WorldToDevice(geoX, geoY, &x, &y);

					double distance = (x - px) * (x - px) + (y - py)*(y - py);
					double shortestDistance = 145;
					if (shortestDistance > distance)
					{
						S100NamedFeature namedFeature;
						namedFeature.m_fe = fr;
						namedFeature.m_name = itor->second->m_code;
						m_pNewFeatureManager->m_pPickedFeatureRecords.push_back(namedFeature);
					}
				}
				else if (sgeo->type == 4) 
				{
					int code = fr->m_frid.m_nftc; 

					auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code); 
					double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
					double geoY = ((SPoint*)fr->m_geometry)->m_point.y;
					long x, y;
					m_pGisLib->WorldToDevice(geoX, geoY, &x, &y);

					double distance = (x - px) * (x - px) + (y - py)*(y - py);
					double shortestDistance = 145;
					if (shortestDistance > distance)
					{
						S100NamedFeature namedFeature;
						namedFeature.m_fe = fr;
						namedFeature.m_name = itor->second->m_code;
						m_pNewFeatureManager->m_pPickedFeatureRecords.push_back(namedFeature);
					}
				}
			}
			delete mbrArea;
			break;
		}
	}
}

void CGISViewerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_ptRUp = point;

	R_FeatureRecord* fr = nullptr;
	ENC_Feature* fe = nullptr;

	bool bCreateRelation = false;

	switch (m_Icon)
	{
	case FEATURE_ADD_INNER_AREA:
		m_Icon = MOVE;
		if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)
		{
			fr = m_pNewFeatureManager->m_pWorkFeatureRecord;

			if (!fr)
			{
				m_pNewFeatureManager->m_addFeaturePoints.clear();
				return;
			}

			if (m_pNewFeatureManager->m_featureType)
			{
				S101Cell *cell = (S101Cell*)m_pNewFeatureManager->m_cell;

				fr = ENC_S101_Factory::CreateInnerCircle(m_pNewFeatureManager, m_pGisLib->GetScaler());

				cell->MakeFullSpatialData();

				m_pNewFeatureManager->m_addFeaturePoints.clear();

				cell->CalcMBR();   
				m_pGisLib->GetLayerManager()->BuildS101Portrayal(cell->m_pLayer/*, fr->m_frid.m_name.GetName()*//*, PORTRAYAL_BUILD_TYPE::CHANGED_FEATURE*/);
				MapRefresh();
			}
		}


		return;
	case FEATURE_ADD_POINT:
	case FEATURE_ADD_LINE:
	case FEATURE_ADD_AREA:
	case FEATURE_ADD_MULTI_POINT:

		GetPickedFeature(point);

		if (m_bEditUseExistingVector && m_pNewFeatureManager->m_addFeaturePoints.size() <= 1)
		{
			CDialogOriginFeatureSelect dlg;
			dlg.m_pNewFeatureManager = m_pNewFeatureManager;
			dlg.DoModal();

			bCreateRelation = true;
		}

		if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_57)
		{
			fe = ENC_S101_Factory::CreateObject(m_pNewFeatureManager, m_pGisLib->GetScaler(), bCreateRelation);

			if (fe)
			{
				ENCCell *cell = (ENCCell*)m_pNewFeatureManager->m_cell;
				fePick = fe;
				frPick = NULL;
				int code = fe->m_frid.OBJL;

				m_pDlgPickReport->InitObjectList();
				m_pDlgPickReport->AddObject(ENCGeometry::pObject->GetDiscriptionFromCode(code),
					ENCGeometry::pObject->GetAcronymFromCode(code),
					cell->m_pLayer->GetLayerName(),
					fe,
					cell);
				m_pDlgPickReport->SetObjectListCtrl(NULL);

				CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fe->m_frid.OBJL);

				theApp.m_DockablePaneEditWindow.SetSpatialObject(m_pNewFeatureManager->m_cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(fePick);

				theApp.m_DockablePaneAttributeList.SetShowTree(obj); 
				cell->MakeFullSpatialData();
				cell->CalcMBR();
				cell->m_pLayer->m_mbr = cell->m_mbr;

				cell->GetAllFeatureDisplayOptions();
				cell->GetEffectiveFeatures();
				cell->GetDisplayFeatures();
				MapRefresh();
			}
		}
		else if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)
		{
			if (m_pNewFeatureManager->m_geometryType == 4)
			{
				DialogExSetSoundingValue dlg;
				if (dlg.DoModal())
				{
					m_pNewFeatureManager->m_addFeaturePoint.z = dlg.GetSoundingValue();
				}
				else
				{
					break;
				}
			}

			fr = ENC_S101_Factory::CreateFeature(m_pNewFeatureManager, m_pGisLib->GetScaler(), m_bEditFeatureRelation, m_bEditUseExistingVector);

			S101Cell* cell = (S101Cell*)m_pNewFeatureManager->m_cell;
			for (auto itorParent = fr->m_spas.begin(); itorParent != fr->m_spas.end(); itorParent++)
			{
				F_SPAS *spasParent = *itorParent;

				for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
				{
					SPAS* spas = *itor;

					if (spas->m_name.RCNM == 110)
					{
						cell->MakePointData(fr);
					}
					else if (spas->m_name.RCNM == 115)
					{
						cell->MakeSoundingData(fr);
					}
					else if (spas->m_name.RCNM == 120 || spas->m_name.RCNM == 125)
					{
						cell->MakeLineData(fr);
					}
					else if (spas->m_name.RCNM == 130)
					{
						cell->MakeAreaData(fr);
					}
				}
			}

			if (fr)//좌표를 선택한다음에 넘어옵니다
			{
				SetPickReportFeature(fr);
				int code = fr->m_frid.m_nftc;
				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
				m_pDlgPickReport->InitObjectList();
				m_pDlgPickReport->AddObject(itor->second->m_code,
					itor->second->m_code,
					cell->m_dsgir.m_dsid.m_dsnm,
					fr,
					cell);

				Catalog* catalog = ((S101Layer*)m_pNewFeatureManager->m_cell->m_pLayer)->GetFC();

				m_pDlgPickReport->SetObjectListCtrl(catalog);

				SelectedFeatureType = catalog->m_pCatalogueList.begin()->second->GetFeatureType(std::wstring(itor->second->m_code));

				theApp.m_DockablePaneEditWindow.SetSpatialObject(m_pNewFeatureManager->m_cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(frPick);
				theApp.m_DockablePaneAttributeList.SetShowTree(catalog, SelectedFeatureType); 

				cell->CalcMBR();
				m_pGisLib->GetLayerManager()->BuildS101Portrayal(cell->m_pLayer/*, fr->m_frid.m_name.GetName()*//*, PORTRAYAL_BUILD_TYPE::CHANGED_FEATURE*/);
				MapRefresh();
			}
		}
		m_Icon = MOVE;
		return;
	case MEASURE_AREA:
		RButtonUpMeasureArea(nFlags, point);
		return;
	case DISTANCE:
		RButtonUpDistance(nFlags, point);
		return;
	case EDIT_VECTOR:
		if (m_pEditingContent->MouseButtonDown(point.x, point.y, m_pGisLib))
		{
			CPoint point;
			::GetCursorPos(&point);
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_EDIT_PANE)); 
			CMenu* popup = menu.GetSubMenu(2);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
		else if (m_pEditingContent->MouseButtonDownOnLine(point.x, point.y, m_pGisLib))
		{
			CPoint point;
			::GetCursorPos(&point);
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_EDIT_PANE)); 
			CMenu* popup = menu.GetSubMenu(3);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
		MapRefresh();
		return;
	}

	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGISViewerView::OnContextMenu(CWnd* , CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
} 

#ifdef _DEBUG
void CGISViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CGISViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGISViewerDoc* CGISViewerView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGISViewerDoc)));
	return (CGISViewerDoc*)m_pDocument;
}
#endif  
void CGISViewerView::OnFileOpen()
{
#ifdef _LOAD_MPA_GML
	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY, _T("Usable Files(*.shp, *.000, *.gml)|*.shp;*.000;*.gml|SHP Files (*.shp)|*.shp|ENC Files (*.000)|*.000|MIO GML Files (*.xml, *.gml)|*.xml;*.gml|All Files (*.*)|*.*|"), this);
#else
	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("Usable Files(*.shp, *.000, *.gml, *.bag, *.xml, h5)|*.shp;*.000;*.gml;*.bag;*.xml;*.h5|SHP Files (*.shp)|*.shp|ENC Files (*.000)|*.000|S-10X GML Files (*.gml)|*.gml|S-10X XML Files (*.xml)|*.xml|S-102 Files (*.bag)|*.bag|S-111 Files (*.h5)|*.h5|All Files (*.*)|*.*|"), this);
#endif



	CString strFileList;

	const int c_cMaxFiles = 400 ; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;


	if (OpenExFilePath(_T("..\\TEMP\\OpenLog.txt")))
	{ 
		dlg.m_ofn.lpstrInitialDir = DataPath;
		int i = 0;
	}
	else
	{
		int i = 0;
	}

	CString pcpath;
	CString fcpath;
	bool addlayer = false;

	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;) 
		{
			CString filePath = dlg.GetNextPathName(pos);//경로+파일명

			DataPath = LibMFCUtil::GetFolderPathFromFilePath(filePath);//경로+파일명;
			if (CheckFilePath(filePath))
			{
				addlayer =m_pGisLib->AddLayer(filePath); 
				if (addlayer==true)
				{
					pcpath = m_pGisLib->GetExFCPath();
					fcpath = m_pGisLib->GetExPCPath();
				}
			}
		}
		MapRefresh();
	}

	if (addlayer == true)
	{
		SaveExFilePath(DataPath, pcpath, fcpath);
	}

	
	
}

bool CGISViewerView::OpenExFilePath(CString txtFilepath) 
{

	CStdioFile file;
	if (file.Open(txtFilepath, CFile::modeRead))
	{
		std::vector<CString> content;
		CString value;
		try
		{
			setlocale(LC_ALL, "korean");
			while (file.ReadString(value))
			{
				content.push_back(value);
			}

			if (content.size() == 0)
			{
				return false;
			}

			CString Data= content[0];
			CString fc = content[1];
			CString pc = content[2];

			DataPath = Data;
			m_pGisLib->SetExFCPath(fc);
			m_pGisLib->SetExPCPath(pc);
			return true;
		}
		catch (exception e)
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}

void CGISViewerView::SaveExFilePath(CString data, CString pc, CString fc) 
{
	std::locale::global(std::locale("Korean"));
	ofstream ofs;
	ofs.open(L"..\\TEMP\\OpenLog.txt", std::ios::out | ios::trunc | ios::binary);           



	std::string datastring= CT2CA(data)+"\n";
	ofs.write(datastring.c_str(), datastring.size());


	std::string pcstring= CT2CA(pc) + "\n";
	ofs.write(pcstring.c_str(), pcstring.size());

    std::string fcstring = CT2CA(fc) + "\n";
	ofs.write(fcstring.c_str(), fcstring.size()),

	ofs.close();
	
}                                              

bool CGISViewerView::CheckFilePath(CString filePath)
{

	int  LayerCount = gisLib->GetLayerManager()->m_listLayer.size();
	if (LayerCount==0)
	{
		return true;
	}

	auto LayerList = gisLib->GetLayerManager()->m_listLayer;
	for (int i=0; i< LayerCount; i++)
	{
		Layer* layer=LayerList[i];
		if (StrCmp(layer->GetLayerPath(),filePath)==0)
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"There is duplicate information and it crosses", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
			return false;
		}
	}
	return true;
} 
void CGISViewerView::OnFileSave()
{  
	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);

	if (!l)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"Failed to save file because there was no layer.", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	}

	if (m_pEditingContent!=nullptr)
	{
		if (m_pEditingContent->workingList.size() > 0) 
		{
			int ret = AfxMessageBox(L"수정 사항을 적용하시겠습니까?", MB_OKCANCEL);

			if (ret == IDOK)
			{
				m_pEditingContent->Apply();
				MapRefresh();
			}
			else
			{
				m_pEditingContent->Cancel();
			}
			g_editInnerCircle = 0;
			m_Icon = MOVE;
			Invalidate();
		}
	}
	
	wstring name =LibMFCUtil::GetFileName(l->m_spatialObject->GetFileName()); 
	CFileDialog dlg(FALSE, L"000", name.c_str(), OFN_OVERWRITEPROMPT, _T("S-10X GML Files (*.gml)|*.gml|ENC Files (*.000)|*.000|Usable Files(*.000, *.gml)|*.000;*.gml|All Files (*.*)|*.*|"), NULL); 
	if (dlg.DoModal() != IDOK)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"file Save Dialog is not open ", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	} 
	CString filepath;
	filepath = dlg.GetPathName();

	std::wstring iso8211Path = L"..\\ProgramData\\S100_PC_IO_XML\\8211\\";
	iso8211Path.append(dlg.GetFileTitle());
	bool copySuccess = CopyFile(filepath, iso8211Path.c_str(), FALSE); 
	if (copySuccess)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"Savefile copySuccess", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
	} 
	BeginWaitCursor(); 
	theApp.m_pDockablePaneLayerManager.SaveLayer(filepath, dlg.GetFileExt()); 
	EndWaitCursor();
}

BOOL CGISViewerView::OnEraseBkgnd(CDC* pDC)
{  
	return FALSE;
}


void CGISViewerView::OnButtonZoomIn()
{
	m_pGisLib->ZoomIn(ZOOM_FACTOR);
	MapRefresh();
}


void CGISViewerView::OnButtonZoomOut()
{
	m_pGisLib->ZoomOut(ZOOM_FACTOR);
	MapRefresh();
}


BOOL CGISViewerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	if ((CWnd*)this != GetFocus())
	{
		return TRUE;
	} 
	if (zDelta > 0) {
		m_pGisLib->ZoomIn(ZOOM_FACTOR, m_ptCurrent.x, m_ptCurrent.y);

	} 
	else {
		m_pGisLib->ZoomOut(ZOOM_FACTOR, m_ptCurrent.x, m_ptCurrent.y);
	}

	MapRefresh();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}




void CGISViewerView::OnButtonViewAll()
{ 
	double xmin, ymin, xmax, ymax;
	xmin = m_pGisLib->GetMBR()->xmin;
	ymin = m_pGisLib->GetMBR()->ymin;
	xmax = m_pGisLib->GetMBR()->xmax;
	ymax = m_pGisLib->GetMBR()->ymax;

	m_pGisLib->SetMap(xmin, ymin, xmax, ymax);
	m_pGisLib->AdjustScreenMap(); 
	m_pGisLib->UpdateScale();

	MapRefresh();
}


void CGISViewerView::OnMButtonDown(UINT nFlags, CPoint point)
{  
	int selItem = theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem;
	int cellCnt = m_pGisLib->GetLayerCount();
	if (theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem >= m_pGisLib->GetLayerCount() || theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem == -1)
		return;

	Layer *l = (Layer*)m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);

	m_pNewFeatureManager->m_cell = (S101Cell*)l->m_spatialObject; 

	m_ptMDown = point;
	m_sp = point;
	m_pGisLib->DeviceToWorld(point.x, point.y, &moveMX, &moveMY);

	CView::OnMButtonDown(nFlags, point);
}



void CGISViewerView::OnMButtonUp(UINT nFlags, CPoint point)
{
	m_ptMUp = point;
	m_ep = point;
	isMoved = false;
	PickReport(point);
	Invalidate();
	m_bMoveStart = FALSE;
	CView::OnMButtonUp(nFlags, point);
}

void CGISViewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();  
	int selItem = theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem;
	int cellCnt = m_pGisLib->GetLayerCount();

	if (theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem >= m_pGisLib->GetLayerCount() || theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem == -1)
	{
	}
	else
	{
		Layer *l = (Layer*)m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
		m_pNewFeatureManager->m_cell = (S101Cell*)l->m_spatialObject;
	} 

	m_ptLDown = point;
	m_pGisLib->DeviceToWorld(point.x, point.y, &moveMX, &moveMY);

	m_sp = point;
	m_ep = point;
	isMoved = false;

	switch (m_Icon)
	{
	case MOVE:
		break;
	case EDIT_VECTOR:
		EditLButtonDown(point);
		break;
	case MOUSE_MODIFY_WP:
	{  
		beModifyWaypoint = true;
		double x, y;

		m_pGisLib->DeviceToWorld(point.x, point.y, &x, &y); 

		int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();
		modifyWaypointIndex = pRoutePlanner->GetWaypointIndex(routeIndex, x, y);
		RT::Waypoint* wp = pRoutePlanner->GetWaypoint(routeIndex, modifyWaypointIndex);

		double wpX = wp->GetX();
		double wpY = wp->GetY();
		long iwpX, iwpY;
		m_pGisLib->WorldToDevice(wpX, wpY, &iwpX, &iwpY);
		int distance = (iwpX - point.x)*(iwpX - point.x) + (iwpY - point.y)*(iwpY - point.y);

		if (distance > 100)
		{
			modifyWaypointIndex = -1;
			beModifyWaypoint = false;
		}

		break;
	}
	case ZOOM_AREA:
	{
		m_ptStartZoomArea = point;
		m_bZoomArea = true;
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOM_AREA));
		break;
	}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CGISViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	m_ptCurrent = point; 
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(point.x, point.y, &curLong, &curLat);
	m_pGisLib->InverseProjection(&curLong, &curLat); 
	if (curLong < -180) {
		curLong += 360;
	}

	if (curLong > 180) {
		curLong -= 360;
	}

	m_strLatitude.Format(_T("Lat : %lf"), curLat);
	m_strLongitude.Format(_T("Lon : %lf"), curLong);

	double degree, minute, second;
	DegreeToDMS(curLong, degree, minute, second); 

	CString strLon = m_strLongitude;
	strLon.Format(_T("Lon : %03d˚ %02d' %0.2lf"), (int)degree, (int)minute, second); 
	if (curLat < -180) {
		curLat += 360;
	}

	if (curLat > 180) {
		curLat -= 360;
	}

	degree = (int)curLat;

	minute = (curLat - degree) * 60;

	second = (minute - (int)minute) * 60;

	CString strLat = m_strLatitude;
	strLat.Format(_T("Lat : %02d˚ %02d' %0.2lf"), (int)degree, (int)minute, second);

	m_ep = point;

	if (m_Icon == EDIT_VECTOR)
	{
		EditMouseMove(nFlags, point);
	} 
	else if (!(beModifyWaypoint ||
		ZOOM_AREA == m_Icon
		))
	{
		if (abs(m_sp.x - m_ep.x) + abs(m_sp.y - m_ep.y) > 3)
		{
			isMoved = true;
		}

		if ((nFlags & MK_LBUTTON))
		{
			m_bMoveStart = TRUE;
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_GRAB));
			Invalidate();
		}
	}

	else
	{
		switch (m_Icon)
		{
		case MOVE:
			break;
		case FEATURE_ADD_POINT:
		case FEATURE_ADD_MULTI_POINT:
		case FEATURE_ADD_LINE:
		case FEATURE_ADD_AREA:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_PEN));
			Invalidate();
			break;
		case DISTANCE:
			Invalidate();
			break;
		case MOUSE_MODIFY_WP:
		{   
			if (beModifyWaypoint)
			{
				double x, y;

				m_pGisLib->DeviceToWorld(point.x, point.y, &x, &y); 

				int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

				double speed = 0;

				speed = pRoutePlanner->GetSpeed(routeIndex, modifyWaypointIndex);

				pRoutePlanner->SetWaypoint(routeIndex, modifyWaypointIndex, x, y, speed, speed); 
			}
			Invalidate();
			break;
		}
		case ZOOM_AREA:
		{
			if (m_bZoomArea)
			{
				m_ptEndZoomArea = point;
				Invalidate();
			}
			SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOM_AREA));
			break;
		}
		}
	}
	UpdateData(FALSE);
	Invalidate();

	CView::OnMouseMove(nFlags, point);
} 
void CGISViewerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	m_ptLUp = point;

	if (!(
		(m_Icon == ZOOM_AREA) ||
		(m_Icon == MOUSE_ADD_WP) ||
		(m_Icon == MOUSE_MODIFY_WP) ||
		(m_Icon == MOUSE_REMOVE_WP) ||
		(m_Icon == DISTANCE) ||
		(m_Icon == MEASURE_AREA) ||
		(m_Icon == FEATURE_ADD_POINT) ||
		(m_Icon == FEATURE_ADD_MULTI_POINT) ||
		(m_Icon == FEATURE_ADD_LINE) ||
		(m_Icon == FEATURE_ADD_AREA) ||
		(m_Icon == EDIT_VECTOR) ||
		(m_Icon == FEATURE_ADD_INNER_AREA)
		))
	{
		if (isMoved == false)
		{
			fePickGML = nullptr;
			fePick = nullptr;
			frPick = nullptr;
			PickReport(point);
		}
	}

	if (isMoved == true)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		m_pGisLib->MoveMap(point.x, point.y, moveMX, moveMY);
		m_pGisLib->AdjustScreenMap();
		MapRefresh();
	}
	else
	{
		switch (m_Icon)
		{
		case MOVE:
			break;
		case DISTANCE:
			LButtonUpDistance(nFlags, point);
			break;
		case MEASURE_AREA:
			LButtonUpMeasureArea(nFlags, point);
			break;
		case FEATURE_ADD_POINT:
		case FEATURE_ADD_MULTI_POINT:
			LButtonUpFeatureAddPoint(nFlags, point);
			break;
		case FEATURE_ADD_LINE:
		case FEATURE_ADD_AREA:
		case FEATURE_ADD_INNER_AREA:
			LButtonUpFeatureAddPoints(nFlags, point);
			break;
		case EDIT_VECTOR:
			if (m_pEditingContent)
			{
				long x, y;
				int compX = m_pEditingContent->pWorkSheet->m_dsgir.m_dssi.m_cmfx;
				int compY = m_pEditingContent->pWorkSheet->m_dsgir.m_dssi.m_cmfy;
				double dx = 0, dy = 0;
				int cx = 0;
				int cy = 0;

				if (m_bEditUseExistingVector)
				{
					double shortestDistance = 145;
					for (auto itor = snapEditPoint.begin(); itor != snapEditPoint.end(); itor++)
					{
						EditPoint* ep = &(*itor);

						m_pGisLib->WorldToDevice(ep->x, ep->y, &x, &y);

						double distance = (x - m_ptCurrent.x) * (x - m_ptCurrent.x) + (y - m_ptCurrent.y)*(y - m_ptCurrent.y);

						if (shortestDistance > distance)
						{
							shortestDistance = distance;
							point.x = x;
							point.y = y;
						}
					}

					if (shortestDistance == 145)
					{
						point.x = m_ptCurrent.x;
						point.y = m_ptCurrent.y;
					}
				}
				else
				{
					point.x = m_ptCurrent.x;
					point.y = m_ptCurrent.y;
				}


				m_pGisLib->DeviceToWorld(point.x, point.y, &dx, &dy);
				m_pGisLib->InverseProjection(&dx, &dy);

				cx = (int)(dx * compX);
				cy = (int)(dy * compY);

				if (m_pEditingContent->LButtonUp(cx, cy))
				{
					theApp.m_DockablePaneEditWindow.MoveVectorToPoint(cx, cy);
				}
				Invalidate();

			}
			break;

		case MOUSE_ADD_WP:
		{
			double x, y;

			m_pGisLib->DeviceToWorld(point.x, point.y, &x, &y);
			m_pGisLib->InverseProjection(&x, &y);

			CString strLon;
			CString strLat;

			int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

			if (routeIndex < 0)
			{
				break;
			}

			int waypointCount = pRoutePlanner->GetWaypointCount(routeIndex);

			strLon.Format(_T("%lf"), x);
			strLat.Format(_T("%lf"), y);

			CDialogExAddWaypoint dlg;

			dlg.m_fLon = x;
			dlg.m_fLat = y;
			dlg.m_dSpeed = 10.0;

			if (dlg.DoModal() != IDOK)
			{
				return;
			}

			if (routeIndex >= 0)
			{
				double lon = dlg.m_fLon;
				double lat = dlg.m_fLat;

				pRoutePlanner->AddWaypoint(routeIndex, lon, lat, dlg.m_dSpeed, dlg.m_dSpeed);
				theApp.m_DockablePaneRoutePlan.pDlg->UpdateWaypointList();
				Invalidate();
			}

			break;
		}
		case MOUSE_MODIFY_WP:
		{  
			if (beModifyWaypoint)
			{
				beModifyWaypoint = false;

				double x, y;

				m_pGisLib->DeviceToWorld(point.x, point.y, &x, &y); 

				int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

				double speed = pRoutePlanner->GetSpeed(routeIndex, modifyWaypointIndex);;

				pRoutePlanner->SetWaypoint(routeIndex, modifyWaypointIndex, x, y, speed, speed);
				theApp.m_DockablePaneRoutePlan.pDlg->UpdateWaypointList();
			}

			break;
		}
		case MOUSE_REMOVE_WP:
		{
			double x, y;

			m_pGisLib->DeviceToWorld(point.x, point.y, &x, &y); 

			int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();
			int waypointIndex = pRoutePlanner->GetWaypointIndex(routeIndex, x, y);

			if (waypointIndex < 0)
			{
				AfxMessageBox(_T("변침점이 없습니다."));
				return;
			}

			CDialogExDeleteWaypoint dlg;
			dlg.m_strWaypointNumber.Format(_T("%d번"), waypointIndex + 1);

			if (dlg.DoModal() == IDOK)
			{
				pRoutePlanner->DeleteWaypoint(routeIndex, waypointIndex);
				theApp.m_DockablePaneRoutePlan.pDlg->UpdateWaypointList();
			}

			Invalidate();

			break;
		}
		case ZOOM_AREA:
		{
			m_Icon = MOVE;
			m_bZoomArea = false;
			m_ptEndZoomArea = point;

			if ((m_ptStartZoomArea.x != m_ptEndZoomArea.x) &&
				(m_ptStartZoomArea.y != m_ptEndZoomArea.y))
			{
				double startX = 0;
				double startY = 0;
				double endX = 0;
				double endY = 0;

				m_pGisLib->DeviceToWorld(
					m_ptStartZoomArea.x,
					m_ptStartZoomArea.y,
					&startX,
					&startY);

				m_pGisLib->DeviceToWorld(
					m_ptEndZoomArea.x,
					m_ptEndZoomArea.y,
					&endX,
					&endY);

				double xmin = 0;
				double ymin = 0;
				double xmax = 0;
				double ymax = 0;

				if (startX < endX)
				{
					xmin = startX;
					xmax = endX;
				}
				else
				{
					xmin = endX;
					xmax = startX;
				}

				if (startY < endY)
				{
					ymin = startY;
					ymax = endY;
				}
				else
				{
					ymin = endY;
					ymax = startY;
				}

				m_pGisLib->SetMap(xmin, ymin, xmax, ymax);

				CRect viewRect;
				GetClientRect(viewRect);

				m_pGisLib->SetScreen(viewRect);
				m_pGisLib->ZoomOut(0, viewRect.Width() / 2, viewRect.Height() / 2);
				m_pGisLib->UpdateScale();

				m_pGisLib->AdjustScreenMap();

				MapRefresh();
			}
			break;
		}
		}
	}

	Invalidate();
	m_bMoveStart = FALSE;
	isMoved = false;
	CView::OnLButtonUp(nFlags, point);
}



void CGISViewerView::LButtonUpFeatureAddPoint(UINT nFlags, CPoint point)
{ 
	double mx = 0;
	double my = 0;
	long x, y;

	if (m_bEditUseExistingVector)
	{
		double shortestDistance = 145;

		for (auto itor = snapEditPoint.begin(); itor != snapEditPoint.end(); itor++)
		{
			EditPoint* ep = &(*itor);

			m_pGisLib->WorldToDevice(ep->x, ep->y, &x, &y);

			double distance = (x - m_ptCurrent.x) * (x - m_ptCurrent.x) + (y - m_ptCurrent.y)*(y - m_ptCurrent.y);

			if (shortestDistance > distance)
			{
				shortestDistance = distance; 
				if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_57)
				{
					ENCCell *cell = (ENCCell*)m_pNewFeatureManager->m_cell;
					m_pNewFeatureManager->m_addFeaturePoint.x = ep->m_pSG2D->XCOO / (double)cell->COMF;
					m_pNewFeatureManager->m_addFeaturePoint.y = ep->m_pSG2D->YCOO / (double)cell->COMF;
					m_pNewFeatureManager->m_pOrgObjectRecord = m_pNewFeatureManager->SearchFeatureRecordHasVector(ep->m_pVec);

				}
				else if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)            
				{
					m_pNewFeatureManager->m_addFeaturePoint.x = ep->m_pC2IT->m_xcoo / 10000000.;
					m_pNewFeatureManager->m_addFeaturePoint.y = ep->m_pC2IT->m_ycoo / 10000000.;

					m_pNewFeatureManager->m_pOrgFeatureRecord = m_pNewFeatureManager->SearchFeatureRecordHasVector(ep->m_pPR);
				}
			}
		}

		if (shortestDistance == 145)
		{
			m_pNewFeatureManager->m_pOrgFeatureRecord = NULL;
			m_pGisLib->DeviceToWorld(point.x, point.y, &mx, &my);
			m_pGisLib->InverseProjection(&mx, &my);

			m_pNewFeatureManager->m_addFeaturePoint.x = mx;
			m_pNewFeatureManager->m_addFeaturePoint.y = my;
			m_pNewFeatureManager->m_pOrgFeatureRecord = NULL;
		}
	}
	else
	{
		m_pGisLib->DeviceToWorld(point.x, point.y, &mx, &my);
		m_pGisLib->InverseProjection(&mx, &my);

		m_pNewFeatureManager->m_addFeaturePoint.x = mx;
		m_pNewFeatureManager->m_addFeaturePoint.y = my;
		m_pNewFeatureManager->m_pOrgFeatureRecord = NULL;
	}
	Invalidate();
}

void CGISViewerView::LButtonUpFeatureAddPoints(UINT nFlags, CPoint point)
{
	double mx = 0;
	double my = 0;

	m_pGisLib->DeviceToWorld(point.x, point.y, &mx, &my);
	m_pGisLib->InverseProjection(&mx, &my);

	PointD pt;
	pt.x = mx;
	pt.y = my;

	m_pNewFeatureManager->m_addFeaturePoints.push_back(pt);
	m_pNewFeatureManager->m_addFeaturePoint.x = mx;
	m_pNewFeatureManager->m_addFeaturePoint.y = my;

	Invalidate();
}

void CGISViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();  
	m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	m_pMainFrame->m_pView = this;
	KRS_MSG_PROCESS::SetTargetMainViewClass(this); 
	m_pDockablePaneRoutePlan = &(theApp.m_DockablePaneRoutePlan); 
	m_Icon = MOVE;

	theApp.m_DockablePanePickReport.pDlg->SetView(this);
	m_pDlgPickReport = theApp.m_DockablePanePickReport.pDlg;
	m_pDockablePaneRoutePlan->pDlg->pView = this;
	m_pDockablePaneRoutePlan->pDlg->pRoutePlanner = pRoutePlanner;

	theApp.m_DockablePaneEditWindow.m_pView = this;

	theApp.m_DockablePaneCurrentSelection.SetView(this);
	theApp.pView = this;

	m_pGisLib->GetLayerManager()->InitPortrayal(theApp.pView->GetDC()); 
	DragAcceptFiles(TRUE);
}

void CGISViewerView::OnUpdateEditScale(CCmdUI *pCmdUI)
{  
}


void CGISViewerView::OnUpdateEditLatitude(CCmdUI *pCmdUI)
{  
}


void CGISViewerView::OnUpdateEditLongitude(CCmdUI *pCmdUI)
{  
}


void CGISViewerView::OnButtonRotateClockwise()
{  
	m_pGisLib->RotateMap(15);
	MapRefresh();
}


void CGISViewerView::OnButtonRotateAnticlockwise()
{ 

	m_pGisLib->RotateMap(-15); 
	MapRefresh();
}


void CGISViewerView::OnButtonNorthUp()
{  
	m_pGisLib->NorthUp();
	MapRefresh();
}


void CGISViewerView::OpenWorldMap()
{
	m_pGisLib->AddBackgroundLayer(_T("..\\ProgramData\\World\\World.shp")); 
	m_pGisLib->SetMap(*m_pGisLib->GetMBR());

	MapRefresh();

	CRect rect;
	GetClientRect(rect);
	m_pGisLib->AdjustScreenMap(); 
	m_pGisLib->UpdateScale(); 
	theApp.m_pDockablePaneLayerManager.pDlg->UpdateList();
}

void CGISViewerView::OpenDefaultExchangeSet()
{
	m_pGisLib->AddExchangeSet(_T("..\\ENCData\\CATALOG.031"));

	MapRefresh();
}

void CGISViewerView::MapRefresh()
{
#ifdef BNT_MODULE
	BNTReload();
#endif
	m_bMapRefesh = true;
	Invalidate();
}


void CGISViewerView::S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE type*/)
{ 
	m_pGisLib->S101RebuildPortrayal(/*type*/);
}


void CGISViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ 

	switch (nChar)
	{
	case VK_LEFT:
	{
		m_pGisLib->MoveMap(-10, 0);
		MapRefresh();
		break;
	}
	case VK_RIGHT:
	{
		m_pGisLib->MoveMap(10, 0);
		MapRefresh();
		break;
	}
	case VK_UP:
	{
		m_pGisLib->MoveMap(0, -10);
		MapRefresh();
		break;
	}
	case VK_DOWN:
	{
		m_pGisLib->MoveMap(0, 10);
		MapRefresh();
		break;
	}
	case VK_ESCAPE:
	{
		m_pSelectedLayer = nullptr;
		fePickGML = nullptr;
		fePick = nullptr;
		frPick = nullptr;
		onPickArrow = false;
		bDrawMovePoint = false; 
		MapRefresh();
		break;
	}
	case VK_OEM_PLUS:
	{
		MapRefresh();
		break;
	}
	case VK_OEM_MINUS:
	{
		MapRefresh();
		break;
	}
	} 
	double curLat, curLong;
	m_pGisLib->DeviceToWorld(m_ptCurrentPoint.x, m_ptCurrentPoint.y, &curLong, &curLat); 
	if (curLong < -180) {
		curLong += 360;
	}

	if (curLong > 180) {
		curLong -= 360;
	}

	m_strLatitude.Format(_T("Lat : %lf"), curLat);
	m_strLongitude.Format(_T("Lon : %lf"), curLong);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGISViewerView::OnUpdateEditTmpLong(CCmdUI *pCmdUI)
{

}

void CGISViewerView::OnUpdateEditTmpLat(CCmdUI *pCmdUI)
{

}

void CGISViewerView::OnBnClickedButtonAdd()
{ 
	this->OnFileOpen();
}

void CGISViewerView::OnBnClickedButtonLmAdd()
{ 
	this->OnFileOpen();
}

void CGISViewerView::OnFileOpenExchange()
{
	m_Icon = 0;  
	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY, _T("Usable Files(*.031)|*.031|All Files (*.*)|*.*|"), NULL); 
	if (dlg.DoModal() != IDOK) {
		m_Icon = MOVE;
		return;
	} 
	CString filepath;
	filepath = dlg.GetPathName(); 
	BeginWaitCursor(); 
	m_pGisLib->AddExchangeSet(filepath); 
	EndWaitCursor(); 
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	MapRefresh(); 
	m_Icon = MOVE;
}

void CGISViewerView::MoveMapToMyPosition()
{
	CRect r;

	GetClientRect(&r);

	m_pGisLib->MoveToOwnShipLocation(r.Width() / 2, r.Height() / 2);

	MapRefresh();
}

void CGISViewerView::GetGMLAttributesString(GML_Attribute*& attr, std::wstring &str, int depth)
{
	for (int i = 0; i < depth * 2 - 1; i++)
	{
		str.append(L" ");
	}
	if (depth > 0)
	{
		str.append(L"└ ");
	}

	str.append(attr->m_name);

	if (attr->m_attributes.size() == 0)
	{
		str.append(L" : ");
		str.append(attr->m_value);
		str.append(L"\n");
	}
	else
	{
		str.append(L"\n");
		for (auto itor = attr->m_attributes.begin(); itor != attr->m_attributes.end(); itor++)
		{
			GetGMLAttributesString(*itor, str, depth + 1);
		}
	}
}

void CGISViewerView::DrawPickReport(HDC& _hdc, int offsetX, int offsetY)
{
	Graphics gPick(_hdc);
	if (fePickGML != nullptr)
	{
		std::wstring str;
		str.append(L"S-100 GML Pick Report Information\n");

		str.append(L"Feature Attributes\n");
		for (auto itor = fePickGML->m_attributes.begin(); itor != fePickGML->m_attributes.end(); itor++)
		{
			GML_Attribute* attr = *itor;
			GetGMLAttributesString(attr, str);
		}

		POINT point;
		Graphics gPick(_hdc);
		SolidBrush brush(Color(250, 250, 250, 250));
		SolidBrush brushText(Color(255, 20, 20, 20));
		GraphicsPath gPath;

		int height = 0;
		int width = 0;

		RECT r;
		::GetClientRect(GetSafeHwnd(), &r);
		RectF layoutRect((REAL)0, (REAL)0, (REAL)r.right, (REAL)r.bottom);
		RectF boundRect;
		int logPixelsY = ::GetDeviceCaps(_hdc, LOGPIXELSY);
		int nHeight = 11;
		REAL emSize = (REAL)MulDiv(nHeight, 72, logPixelsY);
		Gdiplus::FontFamily fontFamily(L"맑은 고딕");
		Gdiplus::Font font(&fontFamily, emSize, FontStyleRegular);

		gPick.MeasureString(str.c_str(), str.length(), &font, layoutRect, &boundRect);

		m_pGisLib->WorldToDevice(ptPickX, ptPickY,
			&(point.x), &(point.y));

		point.x += offsetX;
		point.y += offsetY;
		boundRect.X = (REAL)point.x;
		boundRect.Y = (REAL)point.y;

		StringFormat strFormat;
		gPick.FillRectangle(&brush, boundRect);
		gPick.DrawString(str.c_str(), str.length(), &font, boundRect, &strFormat, &brushText);
	}

	if (fePick != nullptr)
	{
		if (fePick->m_frid.PRIM == 1)
		{
			if (fePick->m_frid.OBJL == 129)
			{
				int pickNumPoints = ((ENCSounding*)(fePick->m_geometry))->m_numPoints;

				for (auto i = 0; i < pickNumPoints; i++)
				{
					long x = 0;
					long y = 0;

					m_pGisLib->WorldToDevice(((ENCSounding*)(fePick->m_geometry))->m_pPoints[i].x, ((ENCSounding*)(fePick->m_geometry))->m_pPoints[i].y, &x, &y);
					x += offsetX;
					y += offsetY;
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 15, y + 15, x, y + 75);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x, y + 75, x + 15, y + 19);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 15, y + 19, x + 75, y + 40);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 75, y + 40, x + 20, y);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y, x + 70, y - 21);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 70, y - 21, x + 15, y - 25);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 15, y - 25, x + 10, y - 75);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 10, y - 75, x - 15, y - 17);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 15, y - 17, x - 75, y - 15);
					gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 75, y - 15, x - 15, y + 15);
				}
			}
			else
			{
				long x = 0;
				long y = 0;

				m_pGisLib->WorldToDevice(((ENCPoint*)(fePick->m_geometry))->m_pPoints[0].x, ((ENCSounding*)(fePick->m_geometry))->m_pPoints[0].y, &x, &y);
				x += offsetX;
				y += offsetY;

				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 15, y + 15, x, y + 75);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x, y + 75, x + 15, y + 19);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 15, y + 19, x + 75, y + 40);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 75, y + 40, x + 20, y);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y, x + 70, y - 21);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 70, y - 21, x + 15, y - 25);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 15, y - 25, x + 10, y - 75);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x + 10, y - 75, x - 15, y - 17);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 15, y - 17, x - 75, y - 15);
				gPick.DrawLine(&Pen(Color(255, 0, 0), 4), x - 75, y - 15, x - 15, y + 15);
			}
		}
		else if (fePick->m_frid.PRIM == 2)
		{
			SolidBrush brush(Color(255, 0, 0));

			Gdiplus::Point* pickPoints = new Gdiplus::Point[((ENCArea*)(fePick->m_geometry))->NumPoints];

			int pickNumPoints = 0;

			if (((ENCArea*)(fePick->m_geometry))->NumParts == 1)
			{
				pickNumPoints = ((ENCArea*)(fePick->m_geometry))->NumPoints;
			}
			else
			{
				pickNumPoints = ((ENCArea*)(fePick->m_geometry))->Parts[1] - ((ENCArea*)(fePick->m_geometry))->Parts[0];
			}

			for (auto i = 0; i < pickNumPoints; i++)
			{
				pickPoints[i].X = (INT)((ENCArea*)(fePick->m_geometry))->Points[i].x;
				pickPoints[i].Y = (INT)((ENCArea*)(fePick->m_geometry))->Points[i].y;
				m_pGisLib->WorldToDevice(((ENCArea*)(fePick->m_geometry))->Points[i].x, ((ENCArea*)(fePick->m_geometry))->Points[i].y, (long*)(&pickPoints[i].X), (long*)(&pickPoints[i].Y));

				pickPoints[i].X += offsetX;
				pickPoints[i].Y += offsetY;
			}

			gPick.DrawLines(&Pen(&brush, 4), pickPoints, pickNumPoints);

			delete[] pickPoints;
		}
		else if (fePick->m_frid.PRIM == 3)
		{
			SolidBrush brush(Color(100, 255, 0, 0)); 

			ENCArea *area = (ENCArea*)(fePick->m_geometry);
			GraphicsPath gPath;
			int  partsIndex = 1;
			POINT exteriorEndP;

			m_pGisLib->WorldToDevice(area->Points[0].x, area->Points[0].y, &exteriorEndP.x, &exteriorEndP.y);

			for (int j = 0; j < area->NumPoints - 1; j++)
			{
				if (j == area->Parts[partsIndex] - 1 || j == area->NumPoints - 1)
				{
					gPath.AddLine(area->CPoints[1].x + offsetX, area->CPoints[1].y + offsetY, exteriorEndP.x + offsetX, exteriorEndP.y + offsetY);
					if (j == area->Parts[partsIndex] - 1)
					{
						m_pGisLib->WorldToDevice(area->Points[j].x, area->Points[j].y, &area->CPoints[0].x, &area->CPoints[0].y);
						m_pGisLib->WorldToDevice(area->Points[j + 1].x, area->Points[j + 1].y, &area->CPoints[1].x, &area->CPoints[1].y);
						gPath.AddLine(area->CPoints[0].x + offsetX, area->CPoints[0].y + offsetY, exteriorEndP.x + offsetX, exteriorEndP.y + offsetY);
						gPath.AddLine(exteriorEndP.x + offsetX, exteriorEndP.y + offsetY, area->CPoints[1].x + offsetX, area->CPoints[1].y + offsetY);
					}
					partsIndex++;
				}
				else
				{
					m_pGisLib->WorldToDevice(area->Points[j].x, area->Points[j].y, &area->CPoints[0].x, &area->CPoints[0].y);
					m_pGisLib->WorldToDevice(area->Points[j + 1].x, area->Points[j + 1].y, &area->CPoints[1].x, &area->CPoints[1].y);

					gPath.AddLine(area->CPoints[0].x + offsetX, area->CPoints[0].y + offsetY, area->CPoints[1].x + offsetX, area->CPoints[1].y + offsetY);
				}
			}

			gPick.FillPath(&brush, &gPath); 
		}
	}  
	if (frPick != nullptr)
	{
		DrawS101PickReport(gPick, offsetX, offsetY);
	}

	if (onPickArrow == true && false) 
	{
		HRSRC hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PICK_ARROW_PNG), TEXT("PNG"));
		if (!hResource) return;

		DWORD imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
		HGLOBAL hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
		LPVOID pData = LockResource(hGlobal);

		HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
		LPVOID pBuffer = GlobalLock(hBuffer);

		CopyMemory(pBuffer, pData, imageSize);
		GlobalUnlock(hBuffer);

		IStream *pStream;
		HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

		Image imagePNG(pStream);

		pStream->Release();
		if (imagePNG.GetLastStatus() != Ok) return;

		CPoint ptPickPosition;

		m_pGisLib->WorldToDevice(ptPickX, ptPickY, &(ptPickPosition.x), &(ptPickPosition.y));

		ptPickPosition.x += offsetX;
		ptPickPosition.y += offsetY;
		gPick.DrawImage(&imagePNG,
			(INT)(ptPickPosition.x - (imagePNG.GetWidth() / 2)),
			(INT)(ptPickPosition.y - (imagePNG.GetHeight() / 2)),
			(INT)(imagePNG.GetWidth()),
			(INT)(imagePNG.GetHeight()));
	}

	RECT r;
	::GetClientRect(GetSafeHwnd(), &r);
}



void CGISViewerView::DrawS101PickReport(Graphics& g, int offsetX, int offsetY)
{ 
	if (frPick->m_geometry->IsPoint())
	{
		long x = 0;
		long y = 0;

		m_pGisLib->WorldToDevice(((SPoint*)(frPick->m_geometry))->m_point.x, ((SPoint*)(frPick->m_geometry))->m_point.y, &x, &y);
		x += offsetX;
		y += offsetY;          


		g.DrawLine(&Pen(Color(255, 0, 0), 4), x - 20, y + 8, x - 20, y + 20);
		g.DrawLine(&Pen(Color(255, 0, 0), 4), x - 20, y + 20, x - 8, y + 20);

		g.DrawLine(&Pen(Color(255, 0, 0), 4), x - 20, y - 8, x - 20, y - 20);
		g.DrawLine(&Pen(Color(255, 0, 0), 4), x - 20, y - 20, x - 8, y - 20);

		g.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y + 8, x + 20, y + 20);
		g.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y + 20, x + 8, y + 20);

		g.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y - 8, x + 20, y - 20);
		g.DrawLine(&Pen(Color(255, 0, 0), 4), x + 20, y - 20, x + 8, y - 20);

	}
	else if (frPick->m_geometry->IsMultiPoint())
	{
		auto multiPoint = (SMultiPoint*)frPick->m_geometry;

		for (int i = 0; i < multiPoint->GetNumPoints(); i++)
		{
			long x = 0;
			long y = 0;

			m_pGisLib->WorldToDevice(multiPoint->GetX(i), multiPoint->GetY(i), &x, &y);
			x += offsetX;
			y += offsetY;

			g.DrawEllipse(&Pen(Color(255, 0, 0), 4), x - 20, y - 20, 40, 40);
		}
	} 
	else if (frPick->m_geometry->IsCurve())
	{
		SolidBrush brush(Color(255, 0, 0));

		SCompositeCurve* cc = (SCompositeCurve*)(frPick->m_geometry);

		for (auto it = cc->m_listCurveLink.begin(); it != cc->m_listCurveLink.end(); it++)
		{
			SCurve* c = (*it).GetCurve();
			Gdiplus::Point* pickPoints = new Gdiplus::Point[c->m_numPoints];

			int pickNumPoints = 0;

			pickNumPoints = c->GetNumPoints();

			if ((*it).GetParentOrient()) {
				for (auto i = 0; i < pickNumPoints; i++)
				{
					pickPoints[i].X = (INT)c->m_pPoints[i].x;
					pickPoints[i].Y = (INT)c->m_pPoints[i].y;
					m_pGisLib->WorldToDevice(c->m_pPoints[i].x, c->m_pPoints[i].y,
						(long*)(&pickPoints[i].X), (long*)(&pickPoints[i].Y));

					pickPoints[i].X += offsetX;
					pickPoints[i].Y += offsetY;
				}
			}
			else
			{
				for (auto i = 0; i < pickNumPoints; i++)
				{
					pickPoints[i].X = (INT)c->m_pPoints[pickNumPoints - 1 - i].x;
					pickPoints[i].Y = (INT)c->m_pPoints[pickNumPoints - 1 - i].y;
					m_pGisLib->WorldToDevice(c->m_pPoints[i].x, c->m_pPoints[i].y,
						(long*)(&pickPoints[i].X), (long*)(&pickPoints[i].Y));

					pickPoints[i].X += offsetX;
					pickPoints[i].Y += offsetY;
				}
			}
			g.DrawLines(&Pen(&brush, 4), pickPoints, pickNumPoints);

			delete[] pickPoints;
		}
	} 
	else if (frPick->m_geometry->IsSurface())
	{
		SolidBrush brush(Color(100, 255, 0, 0));

		SSurface *area = (SSurface*)(frPick->m_geometry);
		GraphicsPath gPath;
		int  partsIndex = 1;
		POINT exteriorEndP;

		m_pGisLib->WorldToDevice(area->m_pPoints[0].x, area->m_pPoints[0].y, &exteriorEndP.x, &exteriorEndP.y);
		m_pGisLib->WorldToDevice(area->m_pPoints[1].x, area->m_pPoints[1].y, &SGeometry::viewPoints[1].x, &SGeometry::viewPoints[1].y);
		for (int j = 0; j < area->m_numPoints - 1; j++)
		{
			if (j == area->m_pParts[partsIndex] - 1 || j == area->m_numPoints - 1)
			{
				gPath.AddLine(SGeometry::viewPoints[1].x + offsetX, SGeometry::viewPoints[1].y + offsetY, exteriorEndP.x + offsetX, exteriorEndP.y + offsetY);
				if (j == area->m_pParts[partsIndex] - 1)
				{
					m_pGisLib->WorldToDevice(area->m_pPoints[j].x, area->m_pPoints[j].y, &SGeometry::viewPoints[0].x, &SGeometry::viewPoints[0].y);
					m_pGisLib->WorldToDevice(area->m_pPoints[j + 1].x, area->m_pPoints[j + 1].y, &SGeometry::viewPoints[1].x, &SGeometry::viewPoints[1].y);
					gPath.AddLine(SGeometry::viewPoints[0].x + offsetX, SGeometry::viewPoints[0].y + offsetY, exteriorEndP.x + offsetX, exteriorEndP.y + offsetY);
					gPath.AddLine(exteriorEndP.x + offsetX, exteriorEndP.y + offsetY, SGeometry::viewPoints[1].x + offsetX, SGeometry::viewPoints[1].y + offsetY);
				}
				partsIndex++;
			}
			else
			{
				m_pGisLib->WorldToDevice(area->m_pPoints[j].x, area->m_pPoints[j].y, &SGeometry::viewPoints[0].x, &SGeometry::viewPoints[0].y);
				m_pGisLib->WorldToDevice(area->m_pPoints[j + 1].x, area->m_pPoints[j + 1].y, &SGeometry::viewPoints[1].x, &SGeometry::viewPoints[1].y);

				gPath.AddLine(SGeometry::viewPoints[0].x + offsetX, SGeometry::viewPoints[0].y + offsetY, SGeometry::viewPoints[1].x + offsetX, SGeometry::viewPoints[1].y + offsetY);
			}
		}

		g.FillPath(&brush, &gPath);
	}
}

void CGISViewerView::ClearPickReport()
{
	fePick = nullptr;
	fePickGML = nullptr;
	frPick = nullptr;
}

void CGISViewerView::DrawSelectedLayerRect(HDC& _hdc, int offsetX, int offsetY)
{
	Graphics g(_hdc);

	if (m_pSelectedLayer)
	{ 
		if (m_pSelectedLayer->m_spatialObject->m_FileType == FILE_S_57)
		{
			return;
		}

		ENCCell* cell = (ENCCell*)m_pSelectedLayer->m_spatialObject;
		list<ENC_Feature*> *covers = &cell->m_M_COVR;

		Color color((BYTE)140, (BYTE)255, (BYTE)50, (BYTE)50);
		SolidBrush solidBrush(color);

		for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
		{
			if (iter->second->m_frid.PRIM == 3)
			{
				if ((*iter).second->m_frid.OBJL == 302)
				{
					ENCArea* area = (ENCArea*)(*iter).second->m_geometry;

					GraphicsPath gPath;
					for (int i = 0; i < area->NumPoints - 1; i++)
					{
						m_pGisLib->WorldToDevice(area->Points[i].x, area->Points[i].y,
							&area->CPoints[0].x, &area->CPoints[0].y);
						m_pGisLib->WorldToDevice(area->Points[i + 1].x, area->Points[i + 1].y,
							&area->CPoints[1].x, &area->CPoints[1].y);

						gPath.AddLine(area->CPoints[0].x, area->CPoints[0].y, area->CPoints[1].x, area->CPoints[1].y);
					}
					g.FillPath(&solidBrush, &gPath);
				}
			}
		}

	}
}

void CGISViewerView::PickReportS57(CPoint _point, ENCCell* cell)
{
	ENCLayer* layer = (ENCLayer*)(cell->m_pLayer); 
	if (layer->m_spatialObject->m_FileType != FILE_S_57)
	{
		return;
	}
	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;   
	if (m_ptMUp.x == 0 || m_sp == m_ep)
	{
		m_pGisLib->DeviceToWorld(_point.x - 5, _point.y + 5, &xmin, &ymin); 
		m_pGisLib->DeviceToWorld(_point.x + 5, _point.y - 5, &xmax, &ymax); 
	}
	else { 
		if (m_ptMDown.x < m_ptMUp.x && m_ptMDown.y > m_ptMUp.y) {
			m_pGisLib->DeviceToWorld(m_ptMUp.x, m_ptMUp.y, &xmin, &ymin);
			m_pGisLib->DeviceToWorld(m_ptMDown.x, m_ptMDown.y, &xmax, &ymax);
		} 
		else if (m_ptMDown.x < m_ptMUp.x && m_ptMDown.y < m_ptMUp.y) {
			m_pGisLib->DeviceToWorld(m_ptMDown.x, m_ptMUp.y, &xmin, &ymin);
			m_pGisLib->DeviceToWorld(m_ptMUp.x, m_ptMDown.y, &xmax, &ymax);
		} 
		else if (m_ptMDown.x > m_ptMUp.x && m_ptMDown.y > m_ptMUp.y) {
			m_pGisLib->DeviceToWorld(m_ptMUp.x, m_ptMUp.y, &xmin, &ymin);
			m_pGisLib->DeviceToWorld(m_ptMDown.x, m_ptMDown.y, &xmax, &ymax);
		} 
		else if (m_ptMDown.x > m_ptMUp.x && m_ptMDown.y < m_ptMUp.y) {
			m_pGisLib->DeviceToWorld(m_ptMDown.x, m_ptMDown.y, &xmin, &ymin);
			m_pGisLib->DeviceToWorld(m_ptMUp.x, m_ptMUp.y, &xmax, &ymax);
		}
	}



	MBR pickMBR(xmin, ymin, xmax, ymax);

	for (auto iter = cell->m_feMap.begin(); iter != cell->m_feMap.end(); iter++)
	{
		if ((*iter).second->m_geometry == nullptr) continue;

		if (MBR::CheckOverlap(pickMBR, (*iter).second->m_geometry->m_mbr))
		{
			int code = (*iter).second->m_frid.OBJL;

			if ((*iter).second->m_frid.PRIM == 1) 
			{
				if ((*iter).second->m_frid.OBJL == 129) 
				{
					for (unsigned int i = 0;
						i < ((ENCSounding*)(*iter).second->m_geometry)->m_numPoints;
						i++)
					{
						double geoX = ((ENCSounding*)(*iter).second->m_geometry)->m_pPoints[i].x;
						double geoY = ((ENCSounding*)(*iter).second->m_geometry)->m_pPoints[i].y;

						if (((pickMBR.xmin <= geoX) && (geoX <= pickMBR.xmax))
							&& ((pickMBR.ymin <= geoY) && (geoY <= pickMBR.ymax)))
						{
							m_pDlgPickReport->AddObject(ENCGeometry::pObject->GetDiscriptionFromCode(code),
								ENCGeometry::pObject->GetAcronymFromCode(code),
								layer->GetLayerName(),//m_pGisLib->GetLayerName(layerCount), 
								(*iter).second,
								cell);
							break;
						}
					}
				}
				else
				{
					double geoX = ((ENCPoint*)(*iter).second->m_geometry)->m_pPoints[0].x;
					double geoY = ((ENCPoint*)(*iter).second->m_geometry)->m_pPoints[0].y;

					if (((pickMBR.xmin <= geoX) && (geoX <= pickMBR.xmax))
						&& ((pickMBR.ymin <= geoY) && (geoY <= pickMBR.ymax)))
					{
						m_pDlgPickReport->AddObject(ENCGeometry::pObject->GetDiscriptionFromCode(code),
							ENCGeometry::pObject->GetAcronymFromCode(code),
							layer->GetLayerName(),//m_pGisLib->GetLayerName(layerCount),
							(*iter).second,
							cell);
					}
				}
			}
			else if ((*iter).second->m_frid.PRIM == 2) 
			{
				ENCArea* mbrArea = new ENCArea;
				mbrArea->NumParts = 1;
				mbrArea->NumPoints = 5;
				mbrArea->Parts = new int[1];
				mbrArea->Parts[0] = 0;
				mbrArea->Points = new GeoPoint[5];
				mbrArea->Points[0].x = xmin;
				mbrArea->Points[0].y = ymin;
				mbrArea->Points[1].x = xmax;
				mbrArea->Points[1].y = ymin;
				mbrArea->Points[2].x = xmax;
				mbrArea->Points[2].y = ymax;
				mbrArea->Points[3].x = xmin;
				mbrArea->Points[3].y = ymax;
				mbrArea->Points[4].x = xmin;
				mbrArea->Points[4].y = ymin;
				mbrArea->m_mbr.xmin = xmin;
				mbrArea->m_mbr.ymin = ymin;
				mbrArea->m_mbr.xmax = xmax;
				mbrArea->m_mbr.ymax = ymax;

				if (GeometricFuc::overlap((ENCLine*)((*iter).second->m_geometry), mbrArea) == 1)
				{
					m_pDlgPickReport->AddObject(ENCGeometry::pObject->GetDiscriptionFromCode(code),
						ENCGeometry::pObject->GetAcronymFromCode(code),
						layer->GetLayerName(),//m_pGisLib->GetLayerName(layerCount),
						(*iter).second,
						cell);
				}

				delete mbrArea;
			}
			else if ((*iter).second->m_frid.PRIM == 3) 
			{
				bool noCoverageAvailable = false;
				if ((*iter).second->m_frid.OBJL == 302) 
				{
					list<ATTF*>::iterator itor;

					for (itor = (*iter).second->m_attfList.begin(); itor != (*iter).second->m_attfList.end(); itor++)
					{
						if ((*itor)->ATTL == 18 && (_ttoi((*itor)->ATVL.c_str()) == 2))
						{
							noCoverageAvailable = true;
						}
					}
				}
				if (noCoverageAvailable)
					continue;

				double centerX = 0;
				double centerY = 0;

				m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY);

				if (GeometricFuc::inside(centerX, centerY, (ENCArea*)(*iter).second->m_geometry) == 1)
				{
					m_pDlgPickReport->AddObject(ENCGeometry::pObject->GetDiscriptionFromCode(code),
						ENCGeometry::pObject->GetAcronymFromCode(code),
						layer->GetLayerName(),//m_pGisLib->GetLayerName(layerCount),
						(*iter).second,
						cell);
				}
			}
		}
	}
}


void CGISViewerView::PickReport(CPoint _point)
{
	if (isMoved == false)
	{
		onPickArrow = true;

		m_pGisLib->DeviceToWorld(_point.x, _point.y, &ptPickX, &ptPickY);

		ptPick = _point;

		m_pSelectedLayer = nullptr;
		m_pDlgPickReport->InitObjectList();

		int selItem = theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem;
		int cellCnt = m_pGisLib->GetLayerCount();
		if (selItem >= cellCnt || selItem == -1)
		{
			return;
		}

		Layer *l = (Layer*)m_pGisLib->GetLayer(selItem);
		if (l->m_spatialObject->m_FileType == FILE_S_100_VECTOR && l->IsOn())
		{
			PickReportS101(_point, (S101Cell*)l->m_spatialObject);
		}
		else if (l->m_spatialObject->m_FileType == FILE_S_57 && l->IsOn())
		{
			PickReportS57(_point, (ENCCell*)l->m_spatialObject);
		}

		if (m_pDlgPickReport->m_allFeatureItems.size() > 0)
		{
			auto itor = --(m_pDlgPickReport->m_allFeatureItems.end());
			ENCItem* item = *itor;

			if (item->type == 0)
			{
				return;
				ObjectItem* oitem = (ObjectItem*)item;
				fePick = oitem->_feature;
				m_pDlgPickReport->SetObjectListCtrl(NULL);
				m_pDlgPickReport->SortObjectList();

				if (m_pDlgPickReport->m_activeFeatureItems.size() > 0)
				{
					auto itor = --(m_pDlgPickReport->m_activeFeatureItems.end());
					oitem = (ObjectItem*)*itor;

					CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(fePick->m_frid.OBJL);

					theApp.m_DockablePaneAttributeList.SetShowTree(obj);
					theApp.m_DockablePaneEditWindow.SetSpatialObject(oitem->_cell);
					theApp.m_DockablePaneEditWindow.SetFeatureRecord(oitem->_feature);
				}
			}
			else if (item->type == 1) 
			{
				FeatureItem* fitem = (FeatureItem*)item;

				Catalog* catalog = ((S101Layer*)fitem->_cell->m_pLayer)->GetFC();
				m_pDlgPickReport->SetObjectListCtrl(catalog);
				m_pDlgPickReport->SortObjectList();

				if (m_pDlgPickReport->m_activeFeatureItems.size() > 0)
				{
					auto fitor = --(m_pDlgPickReport->m_activeFeatureItems.end());
					fitem = (FeatureItem*)*fitor;
					SetPickReportFeature(fitem->_feature);

					theApp.m_DockablePaneEditWindow.SetSpatialObject(fitem->_cell);
					theApp.m_DockablePaneEditWindow.SetFeatureRecord(fitem->_feature);

					auto itor = fitem->_cell->m_dsgir.m_ftcs->m_arr.find(frPick->m_frid.m_nftc);
					SelectedFeatureType = catalog->m_pCatalogueList.begin()->second->GetFeatureType(std::wstring(itor->second->m_code));
					if (theApp.IsEditingMode())
					{
						theApp.m_DockablePaneAttributeList.SetShowTree(catalog, SelectedFeatureType);
					}

					theApp.m_DockablePaneEditWindow.SetEditingContent(m_pEditingContent);

				}
			}
		}
	}
}



void CGISViewerView::PickReportS101(CPoint _point, S101Cell* cell)
{  
	int pickType = 1;

	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;

	LONG spt_x = m_ptMDown.x;
	LONG spt_y = m_ptMDown.y;

	LONG ept_x = m_ptMUp.x;
	LONG ept_y = m_ptMUp.y; 
	if (m_ptMUp.x == 0 || m_sp == m_ep)
	{
		m_pGisLib->DeviceToWorld(_point.x - 5, _point.y + 5, &xmin, &ymin); 
		m_pGisLib->DeviceToWorld(_point.x + 5, _point.y - 5, &xmax, &ymax); 

		pickType = 1;
	} 
	else
	{
		if (spt_x < ept_x && spt_y > ept_y)
		{
			m_pGisLib->DeviceToWorld(spt_x, ept_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(ept_x, spt_y, &xmax, &ymin);
		}
		else if (spt_x < ept_x && spt_y < ept_y)
		{
			m_pGisLib->DeviceToWorld(spt_x, spt_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(ept_x, ept_y, &xmax, &ymin);
		}
		else if (spt_x > ept_x && spt_y > ept_y)
		{
			m_pGisLib->DeviceToWorld(ept_x, ept_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(spt_x, spt_y, &xmax, &ymin);
		}
		else if (spt_x > ept_x && spt_y < ept_y)
		{
			m_pGisLib->DeviceToWorld(ept_x, spt_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(spt_x, ept_y, &xmax, &ymin);
		}

		pickType = 2; 
	}

	MBR pickMBR(xmin, ymin, xmax, ymax);

	POSITION pos = cell->m_feaMap.GetStartPosition();

	__int64 key = 0;
	R_FeatureRecord* fr = nullptr; 
	while (pos != NULL)
	{
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;

		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->type == 3 && pickType == 1) 
			{
				double centerX = 0;
				double centerY = 0;

				m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY);
				if (SGeometricFuc::inside(centerX, centerY, (SSurface*)fr->m_geometry) == 1)
				{
					m_pDlgPickReport->AddObject(itor->second->m_code,
						itor->second->m_code,
						cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
						fr,
						cell);
				}
			}
			else if (sgeo->type == 3 && pickType == 1) 
			{
				double centerX = 0;
				double centerY = 0;

				m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY);
				if (SGeometricFuc::inside(centerX, centerY, (SSurface*)fr->m_geometry) == 1)
				{
					m_pDlgPickReport->AddObject(itor->second->m_code,
						itor->second->m_code,
						cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
						fr,
						cell);
				}
			}
		}
	}

	pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;
		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;

			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->type == 2) 
			{
				SSurface* mbrArea = new SSurface;
				mbrArea->m_numParts = 1;
				mbrArea->m_numPoints = 5;
				mbrArea->m_pParts = new int[1];
				mbrArea->m_pParts[0] = 0;
				mbrArea->m_pPoints = new GeoPoint[5];
				mbrArea->m_pPoints[0].x = xmin;
				mbrArea->m_pPoints[0].y = ymin;
				mbrArea->m_pPoints[1].x = xmax;
				mbrArea->m_pPoints[1].y = ymin;
				mbrArea->m_pPoints[2].x = xmax;
				mbrArea->m_pPoints[2].y = ymax;
				mbrArea->m_pPoints[3].x = xmin;
				mbrArea->m_pPoints[3].y = ymax;
				mbrArea->m_pPoints[4].x = xmin;
				mbrArea->m_pPoints[4].y = ymin;
				mbrArea->m_mbr.xmin = xmin;
				mbrArea->m_mbr.ymin = ymin;
				mbrArea->m_mbr.xmax = xmax;
				mbrArea->m_mbr.ymax = ymax;

				if (SGeometricFuc::overlap((SCompositeCurve*)(fr->m_geometry), mbrArea) == 1)
				{

					m_pDlgPickReport->AddObject(itor->second->m_code,
						itor->second->m_code,
						cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
						fr,
						cell);
				}

				delete mbrArea;
			}
		}
	}

	pos = cell->m_feaMap.GetStartPosition(); 
	while (pos != NULL)
	{
		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;
		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;

			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->IsMultiPoint()) 
			{
				auto multiPoint = (SMultiPoint*)fr->m_geometry;

				for (int i = 0; i < multiPoint->GetNumPoints(); i++)
				{
					double geoX = multiPoint->GetX(i);
					double geoY = multiPoint->GetY(i);

					if (pickMBR.PtInMBR(geoX, geoY))
					{ 
						m_pDlgPickReport->AddObject(itor->second->m_code,
							itor->second->m_code,
							cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
							fr,
							cell);
						break;
					}
				}
			}
			else if (sgeo->IsPoint())
			{
				double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
				double geoY = ((SPoint*)fr->m_geometry)->m_point.y;

				if (((pickMBR.xmin <= geoX) && (geoX <= pickMBR.xmax))
					&& ((pickMBR.ymin <= geoY) && (geoY <= pickMBR.ymax)))
				{
					m_pDlgPickReport->AddObject(itor->second->m_code,
						itor->second->m_code,
						cell->m_dsgir.m_dsid.m_dsnm, 
						fr,
						cell);
				}
			}
		}
	}

	Invalidate();

	CurrentSelectionS101(_point, cell);
}


void CGISViewerView::CurrentSelectionS101(CPoint _point, S101Cell* cell)
{ 
	BOOL isCtrl = (0x8000 == (0x8000 & GetKeyState(VK_CONTROL)));
	CString isCtrlClicked;
	CString featureType = L"Feature";
	isCtrlClicked = isCtrl ? "1" : "0";
	CStringArray csa;
	csa.SetSize(10000);

	map<CString, S101Cell*> cellMap;

	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;


	LONG spt_x = m_ptMDown.x;
	LONG spt_y = m_ptMDown.y;

	LONG ept_x = m_ptMUp.x;
	LONG ept_y = m_ptMUp.y; 
	if (m_ptMUp.x == 0 || m_sp == m_ep)
	{
		m_pGisLib->DeviceToWorld(_point.x - 5, _point.y + 5, &xmin, &ymin); 
		m_pGisLib->DeviceToWorld(_point.x + 5, _point.y - 5, &xmax, &ymax); 
	} 
	else {

		if (spt_x < ept_x && spt_y > ept_y) {

			m_pGisLib->DeviceToWorld(spt_x, ept_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(ept_x, spt_y, &xmax, &ymin);

		}

		else if (spt_x < ept_x && spt_y < ept_y) {

			m_pGisLib->DeviceToWorld(spt_x, spt_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(ept_x, ept_y, &xmax, &ymin);

		}

		else if (spt_x > ept_x && spt_y > ept_y) {

			m_pGisLib->DeviceToWorld(ept_x, ept_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(spt_x, spt_y, &xmax, &ymin);
		}

		else if (spt_x > ept_x && spt_y < ept_y) {

			m_pGisLib->DeviceToWorld(ept_x, spt_y, &xmin, &ymax);
			m_pGisLib->DeviceToWorld(spt_x, ept_y, &xmax, &ymin);

		}

	}
	MBR pickMBR(xmin, ymin, xmax, ymax);

	POSITION pos = cell->m_feaMap.GetStartPosition();

	__int64 key = 0;
	R_FeatureRecord* fr = NULL;



	while (pos != NULL) 
	{
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;

		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->type == 3) 
			{
				double centerX = 0;
				double centerY = 0;

				m_pGisLib->DeviceToWorld(_point.x, _point.y, &centerX, &centerY); 
				if (SGeometricFuc::inside(centerX, centerY, (SSurface*)fr->m_geometry) == 1)
				{

					CString csFrid, csFoid, csLat, csLon, csType, csName, csAssoCnt;

					SSurface* sr = (SSurface*)fr->m_geometry;
					double lat = sr->m_pPoints[0].x;
					double lon = sr->m_pPoints[0].y;

					m_pGisLib->InverseProjection(&lat, &lon);

					vector<int>::size_type assoCnt;
					assoCnt = fr->m_fasc.size() + fr->m_inas.size();


					csFrid.Format(_T("%d"), fr->m_frid.m_name.RCID);
					csFoid.Format(_T("%d"), fr->m_foid.m_objName.m_fidn);
					csLat.Format(_T("%f"), lat);
					csLon.Format(_T("%f"), lon);
					csType.Format(_T("%d"), sr->type);
					csName.Format(_T("%s"), itor->second->m_code);
					csAssoCnt.Format(_T("%d"), assoCnt); 

					csa.Add(isCtrlClicked + _T("|||") + csFoid + _T("|||") + csFrid + _T("|||") + csLat + _T("|||") + csLon + _T("|||") + csType + _T("|||") + csName + _T("|||") + csAssoCnt + _T("|||") + featureType);


				} 


			}
		}
	} 

	pos = cell->m_feaMap.GetStartPosition();

	while (pos != NULL) 
	{
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;
		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;

			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->type == 2) 
			{
				SSurface* mbrArea = new SSurface;
				mbrArea->m_numParts = 1;
				mbrArea->m_numPoints = 5;
				mbrArea->m_pParts = new int[1];
				mbrArea->m_pParts[0] = 0;
				mbrArea->m_pPoints = new GeoPoint[5];
				mbrArea->m_pPoints[0].x = xmin;
				mbrArea->m_pPoints[0].y = ymin;
				mbrArea->m_pPoints[1].x = xmax;
				mbrArea->m_pPoints[1].y = ymin;
				mbrArea->m_pPoints[2].x = xmax;
				mbrArea->m_pPoints[2].y = ymax;
				mbrArea->m_pPoints[3].x = xmin;
				mbrArea->m_pPoints[3].y = ymax;
				mbrArea->m_pPoints[4].x = xmin;
				mbrArea->m_pPoints[4].y = ymin;
				mbrArea->m_mbr.xmin = xmin;
				mbrArea->m_mbr.ymin = ymin;
				mbrArea->m_mbr.xmax = xmax;
				mbrArea->m_mbr.ymax = ymax; 
				if (SGeometricFuc::overlap((SCompositeCurve*)(fr->m_geometry), mbrArea) == 1)
				{

					CString csFoid, csFrid, csLat, csLon, csType, csName, csAssoCnt;

					SCompositeCurve* sr = (SCompositeCurve*)fr->m_geometry;

					double lat = 0;
					double lon = 0;
					if (sr->m_listCurveLink.size() > 0)
					{
						lat = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].x;
						lon = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].y;
					}

					m_pGisLib->InverseProjection(&lat, &lon);

					vector<int>::size_type assoCnt;
					assoCnt = fr->m_fasc.size() + fr->m_inas.size();;

					csFoid.Format(_T("%d"), fr->m_foid.m_objName.m_fidn);
					csFrid.Format(_T("%d"), fr->m_frid.m_name.RCID);
					csLat.Format(_T("%f"), lat);
					csLon.Format(_T("%f"), lon);
					csType.Format(_T("%d"), sr->type);
					csName.Format(_T("%s"), itor->second->m_code);
					csAssoCnt.Format(_T("%d"), assoCnt); 
					csa.Add(isCtrlClicked + _T("|||") + csFoid + _T("|||") + csFrid + _T("|||") + csLat + _T("|||") + csLon + _T("|||") + csType + _T("|||") + csName + _T("|||") + csAssoCnt + _T("|||") + featureType);

				} 

				delete mbrArea;
			}
		}
	}

	pos = cell->m_feaMap.GetStartPosition();

	while (pos != NULL)
	{
		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);
		if (fr->m_geometry == nullptr) continue;
		SGeometry *sgeo = (SGeometry *)fr->m_geometry;
		if (MBR::CheckOverlap(pickMBR, fr->m_geometry->m_mbr))
		{
			int code = fr->m_frid.m_nftc;

			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
			if (sgeo->IsMultiPoint()) 
			{
				auto multiPoint = (SMultiPoint*)fr->m_geometry;

				for (int i = 0; i < multiPoint->GetNumPoints(); i++)
				{
					double geoX = multiPoint->GetX(i);
					double geoY = multiPoint->GetY(i);

					if (pickMBR.PtInMBR(geoX, geoY))
					{
						CString csFoid, csFrid, csLat, csLon, csType, csName, csAssoCnt;

						m_pGisLib->InverseProjection(&geoX, &geoY);

						vector<int>::size_type assoCnt;
						assoCnt = fr->m_fasc.size() + fr->m_inas.size();;

						csFoid.Format(_T("%d"), fr->m_foid.m_objName.m_fidn);
						csFrid.Format(_T("%d"), fr->m_frid.m_name.RCID);
						csLat.Format(_T("%f"), geoX);
						csLon.Format(_T("%f"), geoY);
						csType.Format(_T("%d"), multiPoint->GetType());
						csName.Format(_T("%s"), itor->second->m_code);
						csAssoCnt.Format(_T("%d"), assoCnt);
						csa.Add(isCtrlClicked + _T("|||") + csFoid + _T("|||") + csFrid + _T("|||") + csLat + _T("|||") + csLon + _T("|||") + csType + _T("|||") + csName + _T("|||") + csAssoCnt + _T("|||") + featureType);

						break;
					}
				}
			}
			else if (sgeo->IsPoint())
			{
				double geoX = ((SPoint*)fr->m_geometry)->m_point.x;
				double geoY = ((SPoint*)fr->m_geometry)->m_point.y;

				if (((pickMBR.xmin <= geoX) && (geoX <= pickMBR.xmax))
					&& ((pickMBR.ymin <= geoY) && (geoY <= pickMBR.ymax)))
				{

					CString csFoid, csFrid, csLat, csLon, csType, csName, csAssoCnt;

					SPoint* sr = (SPoint*)fr->m_geometry;
					double lat = sr->m_point.x;
					double lon = sr->m_point.y;

					m_pGisLib->InverseProjection(&lat, &lon);

					vector<int>::size_type assoCnt;
					assoCnt = fr->m_fasc.size() + fr->m_inas.size();;

					csFoid.Format(_T("%d"), fr->m_foid.m_objName.m_fidn);
					csFrid.Format(_T("%d"), fr->m_frid.m_name.RCID);
					csLat.Format(_T("%f"), lat);
					csLon.Format(_T("%f"), lon);
					csType.Format(_T("%d"), sr->type);
					csName.Format(_T("%s"), itor->second->m_code);
					csAssoCnt.Format(_T("%d"), assoCnt);
					csa.Add(isCtrlClicked + _T("|||") + csFoid + _T("|||") + csFrid + _T("|||") + csLat + _T("|||") + csLon + _T("|||") + csType + _T("|||") + csName + _T("|||") + csAssoCnt + _T("|||") + featureType);
				}
			}
		}
	} 
	theApp.m_DockablePaneCurrentSelection.UpdateListTest(&csa, cell, isCtrlClicked);
}


void CGISViewerView::SetPickReportFeature(R_FeatureRecord* _fr)
{
	frPick = _fr;

	if (m_pEditingContent)
	{
		delete m_pEditingContent;
	}

	Layer *l = (Layer*)m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);

	if (l == NULL)
	{
		CString str;
		str.Format(_T("레이어(%d)를 불러올 수 없습니다."), theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
		AfxMessageBox(str);
		return;
	}

	m_pEditingContent = new EditingContent();
	m_pEditingContent->ImportFeature((S101Cell*)l->m_spatialObject, frPick); 
	theApp.m_DockablePaneEditWindow.SetEditingContent(m_pEditingContent);

	Invalidate();
} 

void CGISViewerView::OnUpdateComboScale(CCmdUI *pCmdUI)
{  
}


void CGISViewerView::OnComboScale()
{ 
	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_pMainFrame->m_wndRibbonBar.FindByID(ID_COMBO_SCALE));

	CString curStr = pComboBox->GetEditText();

	CString strScale;
	int scale;

	int scaleData[10] = { 1000000,
						 500000,
						 250000,
						 100000,
						 50000,
						 25000,
						 10000,
						 5000,
						 2500,
						 1000 };

	int nCurSel = pComboBox->GetCurSel();

	if (nCurSel >= 0)
	{
		scale = scaleData[nCurSel];
	}
	else
	{
		curStr.Replace(_T("1 : "), _T(""));
		curStr.Replace(_T(","), _T(""));
		scale = _ttoi(curStr);
	}

	if (scale < 1000)
	{
		scale = 1000;
	}

	m_pGisLib->SetScale(scale);
	m_pGisLib->AdjustScreenMap();
	MapRefresh();
}


void CGISViewerView::OnButtonCapture()
{
	static TCHAR BASED_CODE szFilter[] = _T("Bitmap (*.bmp)|*.bmp|")
		_T("JPG (*.jpg)|*.jpg|")
		_T("PNG (*.png)|*.png|")
		_T("GIF (*.gif)|*.gif|");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL, 0, TRUE);
	if (IDOK == dlg.DoModal())
	{
		CImage capImage; 
		HDC hProcessDC = ::GetDC(m_hWnd);

		CRect rect;
		::GetClientRect(m_hWnd, rect);

		if (!capImage.Create(rect.Width(), rect.Height(), 32)) return;

		HDC hDC = capImage.GetDC();

		BitBlt(hDC, 0, 0, rect.Width(), rect.Height(), hProcessDC, 0, 0, SRCCOPY);

		CString fileName = dlg.GetPathName();

		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			fileName += _T(".bmp");
			break;
		case 2:
			fileName += _T(".jpg");
			break;
		case 3:
			fileName += _T(".png");
			break;
		case 4:
			fileName += _T(".gif");
			break;
		}

		capImage.Save(fileName);
		capImage.ReleaseDC();
	}
}


void CGISViewerView::OnButtonMovePoint()
{
	CDialogExMovePoint3 dlg;

	if (IDOK == dlg.DoModal())
	{

		if (!dlg.m_EditPos.CheckForm()) return;
		if (!dlg.m_EditPos.CheckValue()) return;

		bDrawMovePoint = true;
		pDrawMoveMPoint.x = dlg.m_EditPos.GetLon();
		pDrawMoveMPoint.y = dlg.m_EditPos.GetLat();
		double mx = dlg.m_EditPos.GetLon();
		double my = dlg.m_EditPos.GetLat();
		m_pGisLib->Projection(&mx, &my);

		CRect rect;
		GetClientRect(rect);
		m_pGisLib->MoveMap(rect.Width() / 2, rect.Height() / 2, mx, my);

		MapRefresh();
	}
}

void CGISViewerView::DrawMovePoint(CDC* pDC, const PointD _p, const int _offX, const int _offY) const
{
	if (bDrawMovePoint)
	{
		double mx = _p.x;
		double my = _p.y;
		long sx = 0;
		long sy = 0;

		m_pGisLib->Projection(&mx, &my);
		m_pGisLib->WorldToDevice(mx, my, &sx, &sy);

		CPen newPen;
		newPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen* oldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(sx - 30 + _offX, sy + _offY);
		pDC->LineTo(sx + 30 + _offX, sy + _offY);

		pDC->MoveTo(sx + _offX, sy - 30 + _offY);
		pDC->LineTo(sx + _offX, sy + 30 + _offY);

		pDC->SelectObject(oldPen);
		newPen.DeleteObject();
	}
}

void CGISViewerView::SaveLastPosScale()
{
	double scale = m_pGisLib->GetCurrentScale();
	int sox = m_pGisLib->GetCenterXScreen();
	int soy = m_pGisLib->GetCenterYScreen();

	MBR mbr;
	m_pGisLib->GetMap(&mbr);

	double mox = (mbr.xmax + mbr.xmin) / 2;
	double moy = (mbr.ymax + mbr.ymin) / 2;

	m_pGisLib->InverseProjection(&mox, &moy);  

	CString strScale;
	CString strSox;
	CString strSoy;

	strScale.Format(_T("%lf\n"), scale);
	strSox.Format(_T("%lf\n"), mox);
	strSoy.Format(_T("%lf\n"), moy);

	CStdioFile file;
	if (file.Open(_T("..\\ProgramData\\data\\init.txt"), CFile::modeWrite | CFile::modeCreate))
	{
		file.WriteString(strScale);
		file.WriteString(strSox);
		file.WriteString(strSoy);
	}
	file.Close();
}     

void CGISViewerView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

}


void CGISViewerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect viewRect;
	GetClientRect(viewRect);

	m_pGisLib->SetScreen(viewRect);
	m_pGisLib->ZoomOut(0, viewRect.Width() / 2, viewRect.Height() / 2);
	m_pGisLib->UpdateScale();

	mem_dc.DeleteDC();
	memBitmap.DeleteObject();
	transDC.DeleteDC();
	transBitmap.DeleteObject();
	map_dc.DeleteDC();
	mapBitmap.DeleteObject();

	m_bMapRefesh = true;


	if (mp_factory)
	{
		mp_factory->Release();
	}
	if (mp_render_target)
	{
		mp_render_target->Release();
	}

	if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &mp_factory)) 
	{
		CRect r;
		GetClientRect(&r);

		m_target_cx = r.Width();
		m_target_cy = r.Height();

		if (S_OK == mp_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(m_target_cx, m_target_cy)), &mp_render_target)) {
			m_render_size = mp_render_target->GetSize();
			m_rate_cx = m_render_size.width / m_target_cx;
			m_rate_cy = m_render_size.height / m_target_cy;
		}
	}
	else
	{
		MessageBox(L"Factory 생성에 실패했습니다!", L"D2D1CreateFactory", MB_ICONERROR);
	}
}



int CGISViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1; 
	HRESULT hr;

	hr = CreateDirect2dDeviceIndependentResources();

	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("Failed to created Direct2D device indepentent resources!"));
	}

	CreateDirect2dDeviceResources();

	m_pGisLib->m_pDirect2dFactory = m_pDirect2dFactory;
	m_pGisLib->pWICFactory = pWICFactory;
	m_pGisLib->m_pRenderTarget = m_pRenderTarget;
	m_pGisLib->m_pDirect2DSolibBrush = m_pDirect2dSolidColorBrush;
	m_pGisLib->m_pDWriteFactory = m_pDWriteFactory;
	m_pGisLib->m_pTextFormat = m_pTextFormat;
	m_pGisLib->m_pStroke = m_pStrokeStyleS101Solid; 
	auto svgManager = S100_SVG_D2D1_DLL::GetApp()->GetSVGManager();
	if (svgManager)
	{
		svgManager->SetD2Resource(gisLib->D2.pD2Factory, gisLib->D2.pRT, gisLib->D2.pBrush, gisLib->D2.D2D1StrokeStyleGroup[0]);
	}

	m_pGisLib->InitS100Engine();

	return 0;
}

BOOL CGISViewerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{ 
	if (nHitTest == HTCLIENT)
	{
		CPoint point;
		::GetCursorPos(&point); 
		ScreenToClient(&point); 
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGISViewerView::OnButtonDistance()
{
	(m_Icon == DISTANCE) ? m_Icon = MOVE : m_Icon = DISTANCE;

	m_vectorCurrentDistance.clear();

	if (m_Icon == DISTANCE)
	{
		Invalidate();
	}
}

void CGISViewerView::OnUpdateButtonDistance(CCmdUI *pCmdUI)
{
	if (m_Icon == DISTANCE)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnButtonMeasureArea()
{
	(m_Icon == MEASURE_AREA) ? m_Icon = MOVE : m_Icon = MEASURE_AREA;

	m_vecCurMeasureArea.clear();
}


void CGISViewerView::OnUpdateButtonMeasureArea(CCmdUI *pCmdUI)
{
	if (m_Icon == MEASURE_AREA)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CGISViewerView::LButtonUpDistance(UINT nFlags, CPoint point)
{
	if (isMoved == false)
	{
		double mx = 0;
		double my = 0;
		m_pGisLib->DeviceToWorld(point.x, point.y, &mx, &my);
		m_pGisLib->InverseProjection(&mx, &my);

		PointD p;
		p.x = mx;
		p.y = my;
		m_vectorCurrentDistance.push_back(p);
	}
}

void CGISViewerView::LButtonUpMeasureArea(UINT nFlags, CPoint point)
{
	if (isMoved == false)
	{
		double mx = 0;
		double my = 0;
		m_pGisLib->DeviceToWorld(point.x, point.y, &mx, &my);
		m_pGisLib->InverseProjection(&mx, &my);
		PointD p;
		p.x = mx;
		p.y = my;
		m_vecCurMeasureArea.push_back(p);
	}
}


void CGISViewerView::RButtonUpMeasureArea(UINT nFlags, CPoint point)
{
	if (m_vecCurMeasureArea.size() < 3)
	{
		m_vecCurMeasureArea.clear();
		return;
	}
	double lam1 = 0;
	double lam2 = 0;
	double beta1 = 0;
	double beta2 = 0;
	double cosB1 = 0;
	double cosB2 = 0;
	double hav = 0;
	double sum = 0;

	for (unsigned j = 0; j < m_vecCurMeasureArea.size(); j++)
	{
		int k = j + 1;
		if (j == 0)
		{
			lam1 = m_vecCurMeasureArea.at(j).x * DEG2RAD;
			beta1 = m_vecCurMeasureArea.at(j).y * DEG2RAD;
			lam2 = m_vecCurMeasureArea.at(j + 1).x * DEG2RAD;
			beta2 = m_vecCurMeasureArea.at(j + 1).y * DEG2RAD;
			cosB1 = cos(beta1);
			cosB2 = cos(beta2);
		}
		else
		{
			k = (j + 1) % m_vecCurMeasureArea.size();
			lam1 = lam2;
			beta1 = beta2;
			lam2 = m_vecCurMeasureArea.at(k).x * DEG2RAD;
			beta2 = m_vecCurMeasureArea.at(k).y * DEG2RAD;
			cosB1 = cosB2;
			cosB2 = cos(beta2);
		}
		if (lam1 != lam2)
		{
			hav = Haversine(beta2 - beta1) +
				cosB1 * cosB2 * Haversine(lam2 - lam1);
			double a = 2 * asin(sqrt(hav));
			double b = acos(-1.0) / 2 - beta2;
			double c = acos(-1.0) / 2 - beta1;
			double s = 0.5 * (a + b + c);
			double t = tan(s / 2) * tan((s - a) / 2) *
				tan((s - b) / 2) * tan((s - c) / 2);

			double excess = abs(4 * tan(sqrt(
				abs(t))));

			if (lam2 < lam1)
			{
				excess = -excess;
			}

			sum += excess;
		}
	}

	sum = abs(sum) * RADIAN * RADIAN * 1000 * 1000;

	Area area;
	area.points = m_vecCurMeasureArea;
	area.area = sum;
	m_vecMeasureArea.push_back(area);

	m_vecCurMeasureArea.clear();
}

double CGISViewerView::Haversine(double x)
{
	return (1.0 - cos(x)) / 2.0;
}

void CGISViewerView::DrawDistance(CDC* pDC, int offsetX, int offsetY)
{
	DrawDistanceCurrent(pDC, offsetX, offsetY);

	for (unsigned int i = 0; i < m_vectorDistance.size(); i++)
	{
		DrawDistanceSegment(pDC, m_vectorDistance.at(i), offsetX, offsetY);
	}
}

void CGISViewerView::DrawDistanceSegment(CDC* pDC, Distance distance, int offsetX, int offsetY)
{
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();

	if (distance.size() > 0)
	{
		double sumDistance = 0;

		for (unsigned int i = 1; i < distance.size(); i++)
		{
			long sx1 = 0;
			long sy1 = 0;
			long sx2 = 0;
			long sy2 = 0;

			double mx1 = distance.at(i - 1).x;
			double my1 = distance.at(i - 1).y;
			double mx2 = distance.at(i).x;
			double my2 = distance.at(i).y;

			UNIT unit;
			CString strUnit;
			switch (ENCCommon::UNIT_DISTANCE)
			{
			case ENCCommon::unitDistance_km:
				unit = km;
				strUnit = _T("km");
				break;
			case ENCCommon::unitDistance_nautical_mile:
				unit = nautical_mile;
				strUnit = _T("해리");
				break;
			default:
				unit = km;
				strUnit = _T("km");
				break;
			}

			sumDistance += GetDistanceRhumbLineMercator(my1, mx1, my2, mx2, false, unit);

			m_pGisLib->Projection(&mx1, &my1);
			m_pGisLib->Projection(&mx2, &my2);

			m_pGisLib->WorldToDevice(mx1, my1, &sx1, &sy1);
			m_pGisLib->WorldToDevice(mx2, my2, &sx2, &sy2);

			sx1 += offsetX;
			sy1 += offsetY;
			sx2 += offsetX;
			sy2 += offsetY;

			CD2DPointF d2dStartPoint;
			d2dStartPoint.x = (float)sx1;
			d2dStartPoint.y = (float)sy1;

			CD2DPointF d2dEndPoint;
			d2dEndPoint.x = (float)sx2;
			d2dEndPoint.y = (float)sy2;

			m_RenderTarget.DrawLine(d2dStartPoint, d2dEndPoint, m_pBlackBrush, 3);

			CD2DRectF d2dTextRect;
			d2dTextRect.left = (FLOAT)sx2 + 5;
			d2dTextRect.right = d2dTextRect.left + 300;
			d2dTextRect.top = (FLOAT)sy2;
			d2dTextRect.bottom = d2dTextRect.top + 300;

			CString strDistance;
			strDistance.Format(_T("%0.2lf"), sumDistance);
			strDistance.Append(strUnit);
			m_pBlackBrush->SetOpacity((FLOAT)1.0);
			m_RenderTarget.DrawText(strDistance, d2dTextRect, m_pBlackBrush);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);
		}
	}

	m_RenderTarget.EndDraw();
}

void CGISViewerView::DrawDistanceCurrent(CDC* pDC, int offsetX, int offsetY)
{
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();

	if (m_vectorCurrentDistance.size() > 0)
	{
		double sumDistance = 0;

		if (m_vectorCurrentDistance.size() == 1)
		{
			DrawDistanceCurrentSizeOne(pDC, offsetX, offsetY);
		}
		else
		{
			DrawDistanceCurrentSizeOneMore(pDC, offsetX, offsetY);
		}
	}

	m_RenderTarget.EndDraw();
}

void CGISViewerView::DrawDistanceCurrentSizeOne(CDC* pDC, int offsetX, int offsetY)
{
	long sx1 = 0;
	long sy1 = 0;
	long sx2 = m_ptCurrent.x;
	long sy2 = m_ptCurrent.y;

	double mx1 = m_vectorCurrentDistance.at(0).x;
	double my1 = m_vectorCurrentDistance.at(0).y;
	double mx2 = 0;
	double my2 = 0;

	m_pGisLib->DeviceToWorld(sx2, sy2, &mx2, &my2);
	m_pGisLib->InverseProjection(&mx2, &my2);

	UNIT unit;
	CString strUnit;
	switch (ENCCommon::UNIT_DISTANCE)
	{
	case ENCCommon::unitDistance_km:
		unit = km;
		strUnit = _T("km");
		break;
	case ENCCommon::unitDistance_nautical_mile:
		unit = nautical_mile;
		strUnit = _T("해리");
		break;
	default:
		unit = km;
		strUnit = _T("km");
		break;
	}

	double distance = GetDistanceRhumbLineMercator(my1, mx1, my2, mx2, false, unit);

	m_pGisLib->Projection(&mx1, &my1);
	m_pGisLib->WorldToDevice(mx1, my1, &sx1, &sy1);

	sx1 += offsetX;
	sy1 += offsetY;
	sx2 += offsetX;
	sy2 += offsetY;

	CD2DPointF d2dStartPoint;
	d2dStartPoint.x = (float)sx1;
	d2dStartPoint.y = (float)sy1;

	CD2DPointF d2dEndPoint;
	d2dEndPoint.x = (float)sx2;
	d2dEndPoint.y = (float)sy2;

	m_pBlackBrush->SetOpacity((FLOAT)0.2);
	m_RenderTarget.DrawLine(d2dStartPoint, d2dEndPoint, m_pBlackBrush, 3);
	double radius = sqrt((sx2 - sx1) * (sx2 - sx1) + (sy2 - sy1) * (sy2 - sy1));
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(d2dStartPoint, (FLOAT)radius, (FLOAT)radius);
	m_RenderTarget.DrawEllipse(ellipse, m_pBlackBrush);
	m_pBlackBrush->SetOpacity((FLOAT)0.7);

	CD2DRectF d2dTextRect;
	d2dTextRect.left = (FLOAT)sx2 + 5;
	d2dTextRect.right = d2dTextRect.left + 300;
	d2dTextRect.top = (FLOAT)sy2 - 20;
	d2dTextRect.bottom = d2dTextRect.top + 300;

	CString strDistance;
	strDistance.Format(_T("%0.2lf"), distance);
	strDistance.Append(strUnit);
	m_pBlackBrush->SetOpacity((FLOAT)1.0);
	m_RenderTarget.DrawText(strDistance, d2dTextRect, m_pBlackBrush);
	m_pBlackBrush->SetOpacity((FLOAT)0.7);
}

void CGISViewerView::DrawDistanceCurrentSizeOneMore(CDC* pDC, int offsetX, int offsetY)
{
	double sumDistance = 0;

	for (unsigned int i = 1; i < m_vectorCurrentDistance.size(); i++)
	{
		long sx1 = 0;
		long sy1 = 0;
		long sx2 = 0;
		long sy2 = 0;

		double mx1 = m_vectorCurrentDistance.at(i - 1).x;
		double my1 = m_vectorCurrentDistance.at(i - 1).y;
		double mx2 = m_vectorCurrentDistance.at(i).x;
		double my2 = m_vectorCurrentDistance.at(i).y;

		UNIT unit;
		CString strUnit;
		switch (ENCCommon::UNIT_DISTANCE)
		{
		case ENCCommon::unitDistance_km:
			unit = km;
			strUnit = _T("km");
			break;
		case ENCCommon::unitDistance_nautical_mile:
			unit = nautical_mile;
			strUnit = _T("해리");
			break;
		default:
			unit = km;
			strUnit = _T("km");
			break;
		}

		sumDistance += GetDistanceRhumbLineMercator(my1, mx1, my2, mx2, false, unit);

		m_pGisLib->Projection(&mx1, &my1);
		m_pGisLib->Projection(&mx2, &my2);

		m_pGisLib->WorldToDevice(mx1, my1, &sx1, &sy1);
		m_pGisLib->WorldToDevice(mx2, my2, &sx2, &sy2);

		sx1 += offsetX;
		sy1 += offsetY;
		sx2 += offsetX;
		sy2 += offsetY;

		CD2DPointF d2dStartPoint;
		d2dStartPoint.x = (float)sx1;
		d2dStartPoint.y = (float)sy1;

		CD2DPointF d2dEndPoint;
		d2dEndPoint.x = (float)sx2;
		d2dEndPoint.y = (float)sy2;

		m_RenderTarget.DrawLine(d2dStartPoint, d2dEndPoint, m_pBlackBrush, 3);

		CD2DRectF d2dTextRect;
		d2dTextRect.left = (FLOAT)sx2 + 5;
		d2dTextRect.right = d2dTextRect.left + 300;
		d2dTextRect.top = (FLOAT)sy2;
		d2dTextRect.bottom = d2dTextRect.top + 300;

		CString strDistance;
		strDistance.Format(_T("%0.2lf"), sumDistance);
		strDistance.Append(strUnit);
		m_pBlackBrush->SetOpacity((FLOAT)1.0);
		m_RenderTarget.DrawText(strDistance, d2dTextRect, m_pBlackBrush);
		m_pBlackBrush->SetOpacity((FLOAT)0.7);

		if (i == m_vectorCurrentDistance.size() - 1)
		{
			sx1 = 0;
			sy1 = 0;
			sx2 = m_ptCurrent.x;
			sy2 = m_ptCurrent.y;

			mx1 = m_vectorCurrentDistance.at(i).x;
			my1 = m_vectorCurrentDistance.at(i).y;
			mx2 = 0;
			my2 = 0;

			m_pGisLib->DeviceToWorld(sx2, sy2, &mx2, &my2);
			m_pGisLib->InverseProjection(&mx2, &my2);

			sumDistance += GetDistanceRhumbLineMercator(my1, mx1, my2, mx2, false, unit);

			m_pGisLib->Projection(&mx1, &my1);
			m_pGisLib->WorldToDevice(mx1, my1, &sx1, &sy1);

			sx1 += offsetX;
			sy1 += offsetY;
			sx2 += offsetX;
			sy2 += offsetY;

			CD2DPointF d2dStartPoint;
			d2dStartPoint.x = (float)sx1;
			d2dStartPoint.y = (float)sy1;

			CD2DPointF d2dEndPoint;
			d2dEndPoint.x = (float)sx2;
			d2dEndPoint.y = (float)sy2;

			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.DrawLine(d2dStartPoint, d2dEndPoint, m_pBlackBrush, 3);
			double radius = sqrt((sx2 - sx1) * (sx2 - sx1) + (sy2 - sy1) * (sy2 - sy1));
			D2D1_ELLIPSE ellipse = D2D1::Ellipse(d2dStartPoint, (FLOAT)radius, (FLOAT)radius);
			m_RenderTarget.DrawEllipse(ellipse, m_pBlackBrush);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);

			CD2DRectF d2dTextRect;
			d2dTextRect.left = (FLOAT)sx2 + 5;
			d2dTextRect.right = d2dTextRect.left + 300;
			d2dTextRect.top = (FLOAT)sy2 - 20;
			d2dTextRect.bottom = d2dTextRect.top + 300;

			CString strDistance;
			strDistance.Format(_T("%0.2lf"), sumDistance);
			strDistance.Append(strUnit);
			m_pBlackBrush->SetOpacity((FLOAT)1.0);
			m_RenderTarget.DrawText(strDistance, d2dTextRect, m_pBlackBrush);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);
		}
	}
}

void CGISViewerView::RButtonUpDistance(UINT nFlags, CPoint point)
{
	m_vectorDistance.push_back(m_vectorCurrentDistance);
	m_vectorCurrentDistance.clear();
	Invalidate();
}

void CGISViewerView::DrawMeasureArea(CDC* pDC, int offsetX, int offsetY)
{
	DrawMeasureAreaCurrent(pDC, offsetX, offsetY);

	for (unsigned i = 0; i < m_vecMeasureArea.size(); i++)
	{
		DrawMeasureAreaSegment(pDC, m_vecMeasureArea.at(i), offsetX, offsetY);
	}
}

void CGISViewerView::DrawMeasureAreaSegment(CDC* pDC, Area area, int offsetX, int offsetY)
{
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();
	m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

	long* sx = new long[area.points.size()];
	long* sy = new long[area.points.size()];

	double* ox = new double[area.points.size()];
	double* oy = new double[area.points.size()];

	for (unsigned j = 0; j < area.points.size(); j++)
	{
		double mx = area.points.at(j).x;
		double my = area.points.at(j).y;

		ox[j] = mx;
		oy[j] = my;

		m_pGisLib->Projection(&mx, &my);
		m_pGisLib->WorldToDevice(mx, my, &sx[j], &sy[j]);
		sx[j] += offsetX;
		sy[j] += offsetY;

		m_RenderTarget.FillEllipse(CD2DEllipse(CD2DPointF((float)sx[j], (float)sy[j]), CD2DSizeF(1.5, 1.5)), m_pBlackBrush);
	} 
	CD2DPathGeometry* m_pGeometry = new CD2DPathGeometry((CRenderTarget*)&m_RenderTarget);

	m_pGeometry->Create(&m_RenderTarget);
	CD2DGeometrySink m_pSink(*m_pGeometry);

	m_pSink.SetFillMode(D2D1_FILL_MODE_WINDING);
	m_pSink.BeginFigure(CD2DPointF((FLOAT)sx[0], (FLOAT)sy[0]), D2D1_FIGURE_BEGIN_FILLED);

	for (unsigned j = 1; j < area.points.size(); j++)
	{
		m_pSink.AddLine(CD2DPointF((FLOAT)sx[j], (FLOAT)sy[j]));
	}

	m_pSink.EndFigure(D2D1_FIGURE_END_CLOSED);
	m_pSink.Close();

	m_pBlackBrush->SetOpacity((FLOAT)0.2);
	m_RenderTarget.FillGeometry(m_pGeometry, m_pBlackBrush);
	m_pBlackBrush->SetOpacity((FLOAT)0.7);

	m_RenderTarget.DrawGeometry(m_pGeometry, m_pBlackBrush, 3);


	double cx = 0, cy = 0;
	Centroid(ox, oy, area.points.size(), cx, cy);
	long vx, vy;
	m_pGisLib->Projection(&cx, &cy);
	m_pGisLib->WorldToDevice(cx, cy, &vx, &vy);

	CD2DRectF textRect;
	textRect.left = (FLOAT)vx + 5;
	textRect.right = textRect.left + 300;
	textRect.top = (FLOAT)vy;
	textRect.bottom = textRect.top + 300; 
	CString strArea;

	if (area.area < 1000000)
	{
		strArea.Format(_T("%.02lf㎡"), area.area);
	}
	else if (area.area < 10000000)
	{
		strArea.Format(_T("%.03lfk㎡"), area.area / 1000000);
	}
	else
	{
		strArea.Format(_T("%.02lfk㎡"), area.area / 1000000);
	}

	m_pBlackBrush->SetOpacity(1.0);
	m_RenderTarget.DrawText(strArea, textRect, m_pBlackBrush);
	m_pBlackBrush->SetOpacity(7.0);
	delete[] sx;
	delete[] sy;

	m_RenderTarget.EndDraw();
}

void CGISViewerView::DrawMeasureAreaCurrent(CDC* pDC, int offsetX, int offsetY)
{
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();
	m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

	if (m_vecCurMeasureArea.size() > 0)
	{
		long* sx = new long[m_vecCurMeasureArea.size()];
		long* sy = new long[m_vecCurMeasureArea.size()];

		double* ox = new double[m_vecCurMeasureArea.size()];
		double* oy = new double[m_vecCurMeasureArea.size()];

		for (unsigned int i = 0; i < m_vecCurMeasureArea.size(); i++)
		{
			double mx = m_vecCurMeasureArea.at(i).x;
			double my = m_vecCurMeasureArea.at(i).y;

			ox[i] = mx;
			oy[i] = my;

			m_pGisLib->Projection(&mx, &my);
			m_pGisLib->WorldToDevice(mx, my, &sx[i], &sy[i]);
			sx[i] += offsetX;
			sy[i] += offsetY;
		}

		for (unsigned int i = 0; i < m_vecCurMeasureArea.size(); i++)
		{
			m_RenderTarget.FillEllipse(CD2DEllipse(CD2DPointF((float)sx[i], (float)sy[i]), CD2DSizeF(1.5, 1.5)), m_pBlackBrush);
		}

		if (m_vecCurMeasureArea.size() == 1)
		{
			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.DrawLine(CD2DPointF((float)sx[0], (float)sy[0]), CD2DPointF((float)m_ptCurrent.x, (float)m_ptCurrent.y), m_pBlackBrush, 3);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);
		}
		else
		{ 
			CD2DPathGeometry* m_pGeometry = new CD2DPathGeometry((CRenderTarget*)&m_RenderTarget);

			m_pGeometry->Create(&m_RenderTarget);
			CD2DGeometrySink m_pSink(*m_pGeometry);

			m_pSink.SetFillMode(D2D1_FILL_MODE_WINDING);
			m_pSink.BeginFigure(CD2DPointF((FLOAT)sx[0], (FLOAT)sy[0]), D2D1_FIGURE_BEGIN_FILLED);

			for (unsigned int i = 1; i < m_vecCurMeasureArea.size(); i++)
			{
				m_pSink.AddLine(CD2DPointF((FLOAT)sx[i], (FLOAT)sy[i]));
			}

			m_pSink.AddLine(CD2DPointF((FLOAT)m_ptCurrent.x, (FLOAT)m_ptCurrent.y));

			m_pSink.EndFigure(D2D1_FIGURE_END_CLOSED);
			m_pSink.Close();


			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.FillGeometry(m_pGeometry, m_pBlackBrush);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);

			m_RenderTarget.DrawGeometry(m_pGeometry, m_pBlackBrush, 3);

			if (m_vecCurMeasureArea.size() >= 2)
			{
				double lam1 = 0;
				double lam2 = 0;
				double beta1 = 0;
				double beta2 = 0;
				double cosB1 = 0;
				double cosB2 = 0;
				double hav = 0;
				double sum = 0;

				PointD curP;
				double tmpMX = 0;
				double tmpMY = 0;
				m_pGisLib->DeviceToWorld(m_ptCurrent.x, m_ptCurrent.y, &tmpMX, &tmpMY);
				m_pGisLib->InverseProjection(&tmpMX, &tmpMY);
				curP.x = tmpMX;
				curP.y = tmpMY;
				m_vecCurMeasureArea.push_back(curP);

				for (unsigned j = 0; j < m_vecCurMeasureArea.size(); j++)
				{
					int k = j + 1;
					if (j == 0)
					{
						lam1 = m_vecCurMeasureArea.at(j).x * DEG2RAD;
						beta1 = m_vecCurMeasureArea.at(j).y * DEG2RAD;
						lam2 = m_vecCurMeasureArea.at(j + 1).x * DEG2RAD;
						beta2 = m_vecCurMeasureArea.at(j + 1).y * DEG2RAD;
						cosB1 = cos(beta1);
						cosB2 = cos(beta2);
					}
					else
					{
						k = (j + 1) % m_vecCurMeasureArea.size();
						lam1 = lam2;
						beta1 = beta2;
						lam2 = m_vecCurMeasureArea.at(k).x * DEG2RAD;
						beta2 = m_vecCurMeasureArea.at(k).y * DEG2RAD;
						cosB1 = cosB2;
						cosB2 = cos(beta2);
					}

					if (lam1 != lam2)
					{
						hav = Haversine(beta2 - beta1) +
							cosB1 * cosB2 * Haversine(lam2 - lam1);
						double a = 2 * asin(sqrt(hav));
						double b = acos(-1.0) / 2 - beta2;
						double c = acos(-1.0) / 2 - beta1;
						double s = 0.5 * (a + b + c);
						double t = tan(s / 2) * tan((s - a) / 2) *
							tan((s - b) / 2) * tan((s - c) / 2);

						double excess = abs(4 * tan(sqrt(
							abs(t))));

						if (lam2 < lam1)
						{
							excess = -excess;
						}

						sum += excess;
					}
				}

				m_vecCurMeasureArea.pop_back();

				sum = abs(sum) * RADIAN * RADIAN * 1000 * 1000;


				double cx = 0, cy = 0;
				Centroid(ox, oy, m_vecCurMeasureArea.size(), cx, cy);
				long vx, vy;
				m_pGisLib->Projection(&cx, &cy);
				m_pGisLib->WorldToDevice(cx, cy, &vx, &vy);

				CD2DRectF textRect;
				textRect.left = (FLOAT)vx + 5;
				textRect.right = textRect.left + 300;
				textRect.top = (FLOAT)vy;
				textRect.bottom = textRect.top + 300; 
				CString strArea;

				if (sum < 1000000)
				{
					strArea.Format(_T("%.02lf㎡"), sum);
				}
				else if (sum < 10000000)
				{
					strArea.Format(_T("%.03lfk㎡"), sum / 1000000);
				}
				else
				{
					strArea.Format(_T("%.02lfk㎡"), sum / 1000000);
				} 
				m_pBlackBrush->SetOpacity(1.0);
				m_RenderTarget.DrawText(strArea, textRect, m_pBlackBrush);
				m_pBlackBrush->SetOpacity(7.0);
			}
		}
	}

	m_RenderTarget.EndDraw();
}

void CGISViewerView::OnTimer(UINT_PTR nIDEvent)
{
#ifdef ROUTE_CHECK
	if (nIDEvent == 1126)
	{
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
		int curPos = slider->GetPos();
		curPos += routeSpeed;
		slider->SetPos(curPos);
		MapRefresh();
		if (m_bRouteCheckOwnShipCent)
		{

		}
		else
		{
			Invalidate();
		}
	}
#endif 
	if (nIDEvent == TID_S111_SIMULATION)
	{
		m_pGisLib->GetLayerManager()->m_surfaceCurrentIndex++;

		m_pGisLib->NextTimeIndex();
		m_pGisLib->S101RebuildPortrayal();
		MapRefresh();
	}

	CView::OnTimer(nIDEvent);
}

void CGISViewerView::DrawCopyright(CDC* pDC)
{
#ifdef _KHOA_ENC_VIEWER
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();
	m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Identity());

	CD2DRectF textRect;
	textRect.left = (FLOAT)(viewRect.right - 300 - 610);
	textRect.right = (FLOAT)(viewRect.right);
	textRect.top = (FLOAT)(viewRect.bottom - 30 - 4);
	textRect.bottom = (FLOAT)(viewRect.bottom);
	m_pBlackBrush->SetOpacity((FLOAT)1.0);

	CD2DTextFormat*    m_pTextFormat = new CD2DTextFormat(GetRenderTarget(), _T("돋움"), 12);
	m_pTextFormat->Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	m_pBlackBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	m_RenderTarget.DrawText(_T("Copyright@ 해양수산부 국립해양조사원(KHOA)"), textRect, m_pBlackBrush, m_pTextFormat);
	m_pBlackBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Crimson));
	delete m_pTextFormat;

	m_RenderTarget.EndDraw();
#endif
}

void CGISViewerView::DrawLogo(CDC* pDC)
{
#ifdef _KHOA_ENC_VIEWER
	HRSRC hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LOGO), TEXT("PNG"));
	if (!hResource) return;

	DWORD imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	HGLOBAL hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	LPVOID pData = LockResource(hGlobal);

	HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	LPVOID pBuffer = GlobalLock(hBuffer);

	CopyMemory(pBuffer, pData, imageSize);
	GlobalUnlock(hBuffer);

	IStream *pStream;
	HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

	Image imagePNG(pStream);

	pStream->Release();
	if (imagePNG.GetLastStatus() != Ok) return;

	Graphics g(pDC->GetSafeHdc());

	CRect viewRect;
	GetClientRect(viewRect);

	g.DrawImage(&imagePNG,
		(INT)viewRect.right - 315,
		(INT)viewRect.bottom - 45,
		(INT)300,
		(INT)38);
#endif
}

void CGISViewerView::DrawWatermark(CDC* pDC)
{
#ifdef _KHOA_ENC_VIEWER
	if (bExpired == false) return;

	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();

	D2D1_POINT_2F pivot = D2D1::Point2F((FLOAT)(viewRect.Width() / 2), (FLOAT)(viewRect.Height() / 2));

	m_RenderTarget.SetTransform(D2D1::Matrix3x2F::Rotation(-20, pivot));

	CD2DRectF textRect;
	textRect.left = (FLOAT)(viewRect.left);
	textRect.right = (FLOAT)(viewRect.right);
	textRect.top = (FLOAT)(viewRect.top);
	textRect.bottom = (FLOAT)(viewRect.bottom);
	m_pBlackBrush->SetOpacity((FLOAT)0.6);

	CD2DTextFormat*    m_pTextFormat = new CD2DTextFormat(GetRenderTarget(), _T("돋움"), 120);
	m_pTextFormat->Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	m_pBlackBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Crimson));
	m_RenderTarget.DrawText(_T("프로그램이 만기되었습니다"), textRect, m_pBlackBrush, m_pTextFormat);

	delete m_pTextFormat;

	m_RenderTarget.EndDraw();
#endif
}

void CGISViewerView::GetSelectedPC()
{ 
}

Layer* CGISViewerView::GetCurrentLayer()
{
	return m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
}

int CGISViewerView::GetCurrentLayerIndexnum() 
{
	return theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem;
}

void CGISViewerView::MoveToObject(ENC_Feature* fe)
{
}

void CGISViewerView::SetPickedFeature(ENC_Feature* fe)
{    
}

BOOL CGISViewerView::PreTranslateMessage(MSG* pMsg) 
{ 
	switch (pMsg->message)
	{
	case 0:
		break;
	case WM_KEYDOWN:
	{
		int i = 9;
		break;
	}
	case KRS_CODE_MESSAGE:
	{  
		int msgType = (int)pMsg->wParam;
		if (msgType == KRS_MSG_INFO || msgType == KRS_MSG_ERROR || msgType == KRS_MSG_WARNING)
		{
			CDialogDockLogger::m_ListLogger.ShowWindow(FALSE);
			CString* Totalcontent = (CString*)pMsg->lParam;
			CString msg = *Totalcontent;
			int retval = 0;
			retval = msg.Find('$');


			CString Content = msg.Left(retval); 
			CString ModeandData = msg.Mid(retval + 1); 

			retval = ModeandData.Find('$');
			CString Mode = ModeandData.Left(retval);
			CString Data = ModeandData.Mid(retval + 1);


			ENCCommon::UserMode usermode = CStringToUserEnum(Mode);
			ENCCommon::ReportingData reporting = CStringToDataEnum(Data);

			if (ENCCommon::m_UserMode == ENCCommon::UserMode::User_Mode)
			{
				if (usermode == ENCCommon::UserMode::Developer_Mode)
				{
					break;
				}
			}

			CString fullMsg; 
			CString comboBox;
			int nIndex;


			nIndex = CDialogDockLogger::m_ComboLogType.GetCurSel();
			CDialogDockLogger::m_ComboLogType.GetLBText(nIndex, comboBox);   
			if (Mode.Compare(EnumToCstring(ENCCommon::m_UserMode)) == 0 || Mode.Compare(L"User_Developer_Mode") == 0) 
			{
				if (comboBox == "ALL")
				{
					switch (msgType)
					{
					case KRS_MSG_INFO:
						fullMsg.Append(L"INFO : ");

						break;
					case KRS_MSG_ERROR:
						fullMsg.Append(L"ERROR : ");
						break;
					case KRS_MSG_WARNING:
						fullMsg.Append(L"WARNING : ");
						break;
					}
					fullMsg.Append((LPCTSTR)Content);
					theApp.m_DockablePaneLogger.AppendList(fullMsg); 
				}
				else if (comboBox == "INFO")
				{
					if (msgType == KRS_MSG_INFO)
					{
						fullMsg.Append(L"INFO : ");
						fullMsg.Append((LPCTSTR)Content);
						theApp.m_DockablePaneLogger.AppendList(fullMsg); 
					}
				}
				else if (comboBox == "ERROR")
				{
					if (msgType == KRS_MSG_ERROR)
					{
						fullMsg.Append(L"ERROR : ");
						fullMsg.Append((LPCTSTR)Content);
						theApp.m_DockablePaneLogger.AppendList(fullMsg); 
					}
				}
				else if (comboBox == "WARNING")
				{
					if (msgType == KRS_MSG_WARNING)
					{
						fullMsg.Append(L"WARNING : ");
						fullMsg.Append((LPCTSTR)Content);
						theApp.m_DockablePaneLogger.AppendList(fullMsg); 
					}
				}
			}
			else 
			{
				switch (msgType)
				{
				case KRS_MSG_INFO:
					fullMsg.Append(L"INFO : ");
					break;
				case KRS_MSG_ERROR:
					fullMsg.Append(L"ERROR : ");
					break;
				case KRS_MSG_WARNING:
					fullMsg.Append(L"WARNING : ");
					break;
				}
				fullMsg.Append((LPCTSTR)Content);
			}

			LOG log;
			log.Set_Log(fullMsg, usermode, msgType, reporting);
			LogList.push_back(log); 
			CDialogDockLogger::m_ListLogger.ShowWindow(TRUE);
		}
		else 
		{
			MapRefresh();
			if (m_pGisLib->GetLayerManager()->GetLayerCount() == 1)
				theApp.pView->m_pNewFeatureManager->m_cell = m_pGisLib->GetLayerManager()->GetLayer(0)->m_spatialObject;
			theApp.m_pDockablePaneLayerManager.UpdateList();
		}
		break;
	}
	default:
		break;
	}

	return CView::PreTranslateMessage(pMsg);
}

CString CGISViewerView::EnumToCstring(ENCCommon::UserMode mode)
{
	CString value;
	LPCTSTR g_lpszID[] = { _T("User_Mode"), _T("Developer_Mode"),_T("User_Developer_Mode") };
	value = g_lpszID[mode];
	return value;
}

ENCCommon::UserMode CGISViewerView::CStringToUserEnum(CString mode) 
{

	if (mode == "User_Mode")
	{
		return ENCCommon::User_Mode;
	}
	else if (mode == "Developer_Mode")
	{
		return ENCCommon::Developer_Mode;
	}
	else
	{
		return ENCCommon::User_Developer_Mode;
	}

}
ENCCommon::ReportingData CGISViewerView::CStringToDataEnum(CString mode)
{
	if (mode == "DataSet")
	{
		return ENCCommon::DataSet;
	}
	else if (mode == "PC")
	{
		return ENCCommon::PC;
	}
	else if (mode == "FC")
	{
		return ENCCommon::FC;
	}
	else
	{
		return ENCCommon::None;
	}

}



void CGISViewerView::OnButtonMoveByLatAndLon()
{
	CDialogExMovePointDegree dlg;
	if (dlg.DoModal() == IDOK)
	{

	}
}

void CGISViewerView::SetEditSnapPoint2()
{
	snapEditPoint.clear(); 
	POSITION pos = NULL;
	__int64 iKey;
	R_PointRecord *pr;
	R_CurveRecord *cr;
	int layerCount = gisLib->GetLayerManager()->GetLayerCount();

	for (int i = 0; i < layerCount; i++)
	{
		auto layer = gisLib->GetLayerManager()->GetLayer(i);

		if (layer->m_spatialObject->m_FileType == FILE_S_100_VECTOR)
		{
			auto cell = (S101Cell *)layer->m_spatialObject;

			pos = cell->m_ptMap.GetStartPosition();
			while (pos != NULL)
			{
				cell->m_ptMap.GetNextAssoc(pos, iKey, pr);

				EditPoint ep;
				ep.m_pPR = pr;

				if (pr->m_c2it)
				{
					ep.m_pC2IT = pr->m_c2it;
					ep.x = pr->m_c2it->m_xcoo / 10000000.;
					ep.y = pr->m_c2it->m_ycoo / 10000000.;
				}
				if (pr->m_c3it)
				{
					ep.m_pC3IT = pr->m_c3it;
					ep.x = pr->m_c3it->m_xcoo / 10000000.;
					ep.y = pr->m_c3it->m_ycoo / 10000000.;
				}

				m_pGisLib->Projection(&ep.x, &ep.y);
				snapEditPoint.push_back(ep);
			}

			pos = cell->m_curMap.GetStartPosition();
			while (pos != NULL)
			{
				cell->m_curMap.GetNextAssoc(pos, iKey, cr);

				EditPoint ep;
				ep.m_pPR = pr;

				for (auto it = cr->m_c2il.begin(); it != cr->m_c2il.end(); it++)
				{
					F_C2IL* fc2il = *it;
					for (auto it2 = fc2il->m_arr.begin(); it2 != fc2il->m_arr.end(); it2++)
					{
						IC2D* ic2d = *it2;

						if (pr->m_c2it)
						{
							ep.m_pC2IT = NULL;
							ep.x = ic2d->m_xcoo / 10000000.;
							ep.y = ic2d->m_ycoo / 10000000.;
						}

						m_pGisLib->Projection(&ep.x, &ep.y);
						snapEditPoint.push_back(ep);
					}
				}
			}
		}
	}
}

void CGISViewerView::SetEditSnapPoint()//스넵포인트
{
	return SetEditSnapPoint2();
	snapEditPoint.clear(); 

	POSITION pos = NULL;
	__int64 iKey;
	R_PointRecord *pr;
	R_CurveRecord *cr; 

	if (m_pNewFeatureManager->m_cell != nullptr)
	{
		if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_57)
		{
			ENCCell *cell = (ENCCell*)m_pNewFeatureManager->m_cell;

			for (auto itor = cell->m_veMap.begin(); itor != cell->m_veMap.end(); itor++)
			{
				ENC_Vector* v = itor->second;
				if (v->m_vrid.RCNM == 110)
				{
					for (auto vItor = v->m_sg2dList.begin(); vItor != v->m_sg2dList.end(); vItor++)
					{
						EditPoint ep;
						ep.m_pVec = v;
						ep.m_pSG2D = *vItor;
						ep.x = ep.m_pSG2D->XCOO / (double)cell->COMF;
						ep.y = ep.m_pSG2D->YCOO / (double)cell->COMF;
						snapEditPoint.push_back(ep);
					}
				}
			}
		}
		else if (
			m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)            
		{
			S101Cell *cell = (S101Cell*)m_pNewFeatureManager->m_cell;
			pos = cell->m_ptMap.GetStartPosition();
			while (pos != NULL)
			{
				cell->m_ptMap.GetNextAssoc(pos, iKey, pr);

				EditPoint ep;
				ep.m_pPR = pr;

				if (pr->m_c2it)
				{
					ep.m_pC2IT = pr->m_c2it;
					ep.x = pr->m_c2it->m_xcoo / 10000000.;
					ep.y = pr->m_c2it->m_ycoo / 10000000.;
				}
				if (pr->m_c3it)
				{
					ep.m_pC3IT = pr->m_c3it;
					ep.x = pr->m_c3it->m_xcoo / 10000000.;
					ep.y = pr->m_c3it->m_ycoo / 10000000.;
				}

				m_pGisLib->Projection(&ep.x, &ep.y);
				snapEditPoint.push_back(ep);
			}

			pos = cell->m_curMap.GetStartPosition();
			while (pos != NULL)
			{
				cell->m_curMap.GetNextAssoc(pos, iKey, cr);

				EditPoint ep;
				ep.m_pPR = pr;

				for (auto it = cr->m_c2il.begin(); it != cr->m_c2il.end(); it++)
				{
					F_C2IL* fc2il = *it;
					for (auto it2 = fc2il->m_arr.begin(); it2 != fc2il->m_arr.end(); it2++)
					{
						IC2D* ic2d = *it2;

						if (pr->m_c2it)
						{
							ep.m_pC2IT = NULL;
							ep.x = ic2d->m_xcoo / 10000000.;
							ep.y = ic2d->m_ycoo / 10000000.;
						}

						m_pGisLib->Projection(&ep.x, &ep.y);
						snapEditPoint.push_back(ep);
					}
				}
			}
		}

	}
	else
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"Add a layer, please.", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	}
}

void CGISViewerView::OnFeatureAddMultiPoint()
{
	m_pNewFeatureManager->m_addFeaturePoints.clear();
	m_pNewFeatureManager->m_addFeatureInnerCirclePointsList.clear();

	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex();

	if (selectedLayerIndex < 0)
	{
		AfxMessageBox(_T("Select Layer."));
		return;
	}
	else if (m_Icon == FEATURE_ADD_MULTI_POINT)
	{
		m_Icon = MOVE;
	}
	else
	{
		CDialogAddFeatureList dlg;
		dlg.SetView(this);
		dlg.m_mode = 4;
		m_pNewFeatureManager->m_cell = m_pGisLib->GetLayer(selectedLayerIndex)->m_spatialObject;

		if (dlg.DoModal() == IDOK)
		{
			m_Icon = FEATURE_ADD_MULTI_POINT;
			SetEditSnapPoint();
		}
		else
		{
			m_Icon = MOVE;
		}
	}
	return;

}

void CGISViewerView::OnFeatureAddPoint()
{
	m_pNewFeatureManager->m_addFeaturePoints.clear();
	m_pNewFeatureManager->m_addFeatureInnerCirclePointsList.clear();

	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex(); 
	if (selectedLayerIndex < 0)
	{
		AfxMessageBox(_T("Select Layer."));
		return;
	} 
	else if (m_Icon == FEATURE_ADD_POINT)
	{
		m_Icon = MOVE;
	} 
	else
	{
		CDialogAddFeatureList dlg;
		dlg.SetView(this);
		dlg.m_mode = 1;

		m_pNewFeatureManager->m_cell = m_pGisLib->GetLayer(selectedLayerIndex)->m_spatialObject;

		if (dlg.DoModal() == IDOK)
		{
			m_Icon = FEATURE_ADD_POINT;
			SetEditSnapPoint();
		}
		else
		{
			m_Icon = MOVE;
		}
	}

	return;
}

void CGISViewerView::OnFeatureAddLine()
{
	m_pNewFeatureManager->m_addFeaturePoints.clear();
	m_pNewFeatureManager->m_addFeatureInnerCirclePointsList.clear();

	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex();
	if (selectedLayerIndex < 0)
	{
		AfxMessageBox(_T("Select Layer."));
	}
	else if (m_Icon == FEATURE_ADD_LINE)
		m_Icon = MOVE;
	else
	{
		CDialogAddFeatureList dlg;
		dlg.SetView(this);
		dlg.m_mode = 2;
		m_pNewFeatureManager->m_cell = m_pGisLib->GetLayer(selectedLayerIndex)->m_spatialObject;
		if (dlg.DoModal() == IDOK)
		{
			m_Icon = FEATURE_ADD_LINE;
		}
		else
		{
			m_Icon = MOVE;
		}
	}
}
void CGISViewerView::OnFeatureAddArea()
{
	m_pNewFeatureManager->m_addFeaturePoints.clear();
	m_pNewFeatureManager->m_addFeatureInnerCirclePointsList.clear();
	
	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex();
	if (selectedLayerIndex < 0)
	{
		AfxMessageBox(_T("Select Layer."));
	}
	else if (m_Icon == FEATURE_ADD_AREA)
		m_Icon = MOVE;
	else
	{
		CDialogAddFeatureList dlg;
		dlg.SetView(this);
		dlg.m_mode = 3;
		m_pNewFeatureManager->m_cell = m_pGisLib->GetLayer(selectedLayerIndex)->m_spatialObject;
		if (dlg.DoModal() == IDOK)
		{
			m_Icon = FEATURE_ADD_AREA;
		}
		else
		{
			m_Icon = MOVE;
		}
	}
}
void CGISViewerView::OnFeatureChange()
{
	CDialogAddFeatureList dlg;
	dlg.SetView(this);
	m_pNewFeatureManager->m_addFeaturePoints.clear();
	m_pNewFeatureManager->m_addFeatureInnerCirclePointsList.clear();

	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex();
	if (selectedLayerIndex < 0)
	{
		AfxMessageBox(_T("Select Layer."));
	}
	else if (m_Icon == FEATURE_ADD_AREA)
		m_Icon = MOVE;
	else
	{
		m_pNewFeatureManager->m_cell = m_pGisLib->GetLayer(selectedLayerIndex)->m_spatialObject; 
		if (m_pNewFeatureManager->m_cell->m_FileType == FILE_S_57)
		{
			dlg.m_mode = fePick->m_frid.PRIM;

			if (dlg.DoModal() == IDOK)
			{
				fePick->m_frid.OBJL = m_pNewFeatureManager->m_featureType;

				((ENCCell*)m_pNewFeatureManager->m_cell)->GetFeatureDisplayOption(fePick);
				((ENCCell*)m_pNewFeatureManager->m_cell)->GetEffectiveFeatures();
				((ENCCell*)m_pNewFeatureManager->m_cell)->GetDisplayFeatures();
				((ENCCell*)m_pNewFeatureManager->m_cell)->ProcessCSProcedure();
				MapRefresh();
			}
		}
		else if (
			m_pNewFeatureManager->m_cell->m_FileType == FILE_S_100_VECTOR)            
		{
			if (!frPick)
			{
				return;
			}

			dlg.m_mode = frPick->m_geometry->type;
			if (dlg.DoModal() == IDOK)
			{
				frPick->m_frid.m_nftc = m_pNewFeatureManager->m_featureType;  

				S101Cell *cell = (S101Cell*)m_pNewFeatureManager->m_cell; 
				int code = frPick->m_frid.m_nftc;
				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
				m_pDlgPickReport->ChangeObject(itor->second->m_code,
					itor->second->m_code,
					cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
					frPick,
					cell);

				Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC(); 
				SelectedFeatureType = catalog->m_pCatalogueList.begin()->second->GetFeatureType(std::wstring(itor->second->m_code));

				theApp.m_DockablePaneAttributeList.SetShowTree(catalog, SelectedFeatureType);
				theApp.m_DockablePaneEditWindow.SetSpatialObject(cell);
				theApp.m_DockablePaneEditWindow.SetFeatureRecord(frPick);  
				m_pGisLib->BuildS101Portrayal(m_pNewFeatureManager->m_cell->m_pLayer);
				MapRefresh();
			}
		}
	}
}

void CGISViewerView::OnENCNewCell()
{ 
	CDialogExCatalogSelect dlg;

	int result = dlg.DoModal();

	if (result == IDOK)
	{ 
		if (dlg.m_selectedIndex < 0)
		{
			return;
		}

		auto selectedFC = dlg.m_selectedCatalog;
		auto selectedPC = LayerManager::CatalogueList[selectedFC];
		S101Layer *layer = new S101Layer(selectedFC, selectedPC);

		S101Cell* createdCell = ENC_S101_Factory::CreateEmptyFileByCatalog(dlg.m_selectedCatalog, std::wstring(dlg.m_fileName));
		layer->SetSpatialObject(createdCell); 
		if (createdCell->S100Product == S100::S100_DataProduct::S_101)
		{
			((S101Layer*)layer)->GetPC()->portrayalRuleType = PortrayalRuleType::LUA;
		}

		m_pGisLib->GetLayerManager()->AddLayer(layer);
		theApp.m_pDockablePaneLayerManager.pDlg->UpdateList();  
	}
}

void CGISViewerView::OnFeatureAddUseExistingVector()
{
	m_bEditUseExistingVector = m_bEditUseExistingVector == true ? false : true;
}

void CGISViewerView::OnFeatureAddFeatureRelation()
{
	m_bEditFeatureRelation = m_bEditFeatureRelation == true ? false : true;
}

void CGISViewerView::OnUpdateFeatureAddUseExistingVector(CCmdUI *pCmdUI)
{
	if (m_bEditUseExistingVector)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}
void CGISViewerView::OnUpdateFeatureAddFeatureRelation(CCmdUI *pCmdUI)
{
	if (m_bEditFeatureRelation)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}

void CGISViewerView::OnUpdateFeatureAddMultiPoint(CCmdUI *pCmdUI)
{
	if (m_Icon == FEATURE_ADD_MULTI_POINT)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}
void CGISViewerView::OnUpdateFeatureAddPoint(CCmdUI *pCmdUI)
{
	if (m_Icon == FEATURE_ADD_POINT)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}
void CGISViewerView::OnUpdateFeatureAddLine(CCmdUI *pCmdUI)
{
	if (m_Icon == FEATURE_ADD_LINE)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}
void CGISViewerView::OnUpdateFeatureAddArea(CCmdUI *pCmdUI)
{
	if (m_Icon == FEATURE_ADD_AREA)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	return;
}

void CGISViewerView::OnButtonReadPcOutputXml()
{  


	return;
}

void CGISViewerView::DrawEditingResource(CDCRenderTarget* pRenderTarget, int offsetX, int offsetY)
{
	if (m_Icon != FEATURE_ADD_POINT &&
		m_Icon != FEATURE_ADD_MULTI_POINT &&
		m_Icon != FEATURE_ADD_LINE &&
		m_Icon != FEATURE_ADD_AREA &&
		m_Icon != FEATURE_ADD_INNER_AREA
		)
		return;

	CRect viewRect;
	GetClientRect(viewRect);

	m_pBlackBrush->SetColor(D2D1::ColorF((FLOAT)(0xDC / 255.0), (FLOAT)(0x14 / 255.0), (FLOAT)(0x3C / 255.0), (FLOAT)1));

	switch (m_pNewFeatureManager->m_geometryType)
	{
	case 1:
	case 4:
	{
		long x, y;
		double mx = m_pNewFeatureManager->m_addFeaturePoint.x;
		double my = m_pNewFeatureManager->m_addFeaturePoint.y;

		m_pGisLib->Projection(&mx, &my);
		m_pGisLib->WorldToDevice(mx, my, &x, &y);

		CD2DPointF cp;
		cp.x = (float)x;
		cp.y = (float)y;
		CD2DSizeF size;
		size.width = 5;
		size.height = 5;
		CD2DEllipse* pGeometry = new CD2DEllipse(cp, size);
		size.width = 1;
		size.height = 1;
		CD2DEllipse* pGeometry2 = new CD2DEllipse(cp, size);

		m_RenderTarget.DrawEllipse(pGeometry, m_pBlackBrush, 2);
		m_RenderTarget.FillEllipse(pGeometry2, m_pBlackBrush);

		m_pBlackBrush->SetColor(D2D1::ColorF((FLOAT)(0x3C / 255.0), (FLOAT)(0x14 / 255.0), (FLOAT)(0xDC / 255.0), (FLOAT)1));

		if (m_bEditUseExistingVector)
		{
			double shortestDistance = 145;

			for (auto itor = snapEditPoint.begin(); itor != snapEditPoint.end(); itor++)
			{
				EditPoint* ep = &(*itor);

				m_pGisLib->WorldToDevice(ep->x, ep->y, &x, &y);

				double distance = (x - m_ptCurrent.x) * (x - m_ptCurrent.x) + (y - m_ptCurrent.y)*(y - m_ptCurrent.y);

				if (shortestDistance > distance)
				{
					shortestDistance = distance;   
					cp.x = (float)x + offsetX;
					cp.y = (float)y + offsetY;
				}
			}

			if (shortestDistance == 145)
			{
				cp.x = (float)m_ptCurrent.x + offsetX;
				cp.y = (float)m_ptCurrent.y + offsetY;
			}
		}
		else
		{
			cp.x = (float)m_ptCurrent.x + offsetX;
			cp.y = (float)m_ptCurrent.y + offsetY;
		}
		size.width = 5;
		size.height = 5;
		pGeometry->point = cp;
		pGeometry->radiusX = size.width;
		pGeometry->radiusX = size.height;
		size.width = 1;
		size.height = 1;
		pGeometry2->point = cp;
		pGeometry2->radiusX = size.width;
		pGeometry2->radiusX = size.height;

		m_RenderTarget.DrawEllipse(pGeometry, m_pBlackBrush, 2);
		m_RenderTarget.FillEllipse(pGeometry2, m_pBlackBrush);

		delete pGeometry;
		delete pGeometry2;

		break;
	}
	case 2:
	{ 
		long* sx = new long[m_pNewFeatureManager->m_addFeaturePoints.size()];
		long* sy = new long[m_pNewFeatureManager->m_addFeaturePoints.size()];

		for (unsigned int i = 0; i < m_pNewFeatureManager->m_addFeaturePoints.size(); i++)
		{
			double mx = m_pNewFeatureManager->m_addFeaturePoints.at(i).x;
			double my = m_pNewFeatureManager->m_addFeaturePoints.at(i).y;

			m_pGisLib->Projection(&mx, &my);
			m_pGisLib->WorldToDevice(mx, my, &sx[i], &sy[i]);
		}

		for (unsigned int i = 0; i < m_pNewFeatureManager->m_addFeaturePoints.size() && m_pNewFeatureManager->m_addFeaturePoints.size() > 0; i++)
		{
			m_RenderTarget.FillEllipse(CD2DEllipse(CD2DPointF((float)sx[i] + offsetX, (float)sy[i] + offsetY), CD2DSizeF(1.5, 1.5)), m_pBlackBrush);
		}

		if (m_pNewFeatureManager->m_addFeaturePoints.size() == 1)
		{
			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.DrawLine(CD2DPointF((float)sx[0] + offsetX, (float)sy[0] + offsetY), CD2DPointF((float)m_ptCurrent.x, (float)m_ptCurrent.y), m_pBlackBrush, 3);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);
		}
		else
		{ 
			CD2DPathGeometry* m_pGeometry = new CD2DPathGeometry((CRenderTarget*)&m_RenderTarget);

			m_pGeometry->Create(&m_RenderTarget);
			CD2DGeometrySink m_pSink(*m_pGeometry);

			m_pSink.SetFillMode(D2D1_FILL_MODE_WINDING);
			m_pSink.BeginFigure(CD2DPointF((FLOAT)sx[0] + offsetX, (FLOAT)sy[0] + offsetY), D2D1_FIGURE_BEGIN_FILLED);

			for (unsigned int i = 1; i < m_pNewFeatureManager->m_addFeaturePoints.size(); i++)
			{
				m_pSink.AddLine(CD2DPointF((FLOAT)sx[i] + offsetX, (FLOAT)sy[i] + offsetY));
			}

			if (m_pNewFeatureManager->m_addFeaturePoints.size() > 0)
			{
				m_pSink.AddLine(CD2DPointF((FLOAT)m_ptCurrent.x, (FLOAT)m_ptCurrent.y));
			}
			m_pSink.EndFigure(D2D1_FIGURE_END_OPEN);
			m_pSink.Close();

			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.DrawGeometry(m_pGeometry, m_pBlackBrush, 2);
			m_pBlackBrush->SetOpacity((FLOAT)0.7); 

			delete m_pGeometry;
		}

		delete[] sx;
		delete[] sy;
		break;
	}
	case 3:
	{ 
		long* sx = new long[m_pNewFeatureManager->m_addFeaturePoints.size()];
		long* sy = new long[m_pNewFeatureManager->m_addFeaturePoints.size()];

		for (unsigned int i = 0; i < m_pNewFeatureManager->m_addFeaturePoints.size(); i++)
		{
			double mx = m_pNewFeatureManager->m_addFeaturePoints.at(i).x;
			double my = m_pNewFeatureManager->m_addFeaturePoints.at(i).y;

			m_pGisLib->Projection(&mx, &my);
			m_pGisLib->WorldToDevice(mx, my, &sx[i], &sy[i]);
		}

		for (unsigned int i = 0; i < m_pNewFeatureManager->m_addFeaturePoints.size(); i++)
		{
			m_RenderTarget.FillEllipse(CD2DEllipse(CD2DPointF((float)sx[i] + offsetX, (float)sy[i] + offsetY), CD2DSizeF(1.5, 1.5)), m_pBlackBrush);
		}

		if (m_pNewFeatureManager->m_addFeaturePoints.size() == 1)
		{
			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.DrawLine(CD2DPointF((float)sx[0] + offsetX, (float)sy[0] + offsetY), CD2DPointF((float)m_ptCurrent.x, (float)m_ptCurrent.y), m_pBlackBrush, 3);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);
		}
		else
		{ 
			CD2DPathGeometry* m_pGeometry = new CD2DPathGeometry((CRenderTarget*)&m_RenderTarget);

			m_pGeometry->Create(&m_RenderTarget);
			CD2DGeometrySink m_pSink(*m_pGeometry);

			m_pSink.SetFillMode(D2D1_FILL_MODE_WINDING);
			m_pSink.BeginFigure(CD2DPointF((FLOAT)sx[0] + offsetX, (FLOAT)sy[0] + offsetY), D2D1_FIGURE_BEGIN_FILLED);

			for (unsigned int i = 1; i < m_pNewFeatureManager->m_addFeaturePoints.size(); i++)
			{
				m_pSink.AddLine(CD2DPointF((FLOAT)sx[i] + offsetX, (FLOAT)sy[i] + offsetY));
			}
			if (m_pNewFeatureManager->m_addFeaturePoints.size() > 0)
			{
				m_pSink.AddLine(CD2DPointF((FLOAT)m_ptCurrent.x, (FLOAT)m_ptCurrent.y));
			}
			m_pSink.EndFigure(D2D1_FIGURE_END_CLOSED);

			m_pSink.Close();

			m_pBlackBrush->SetOpacity((FLOAT)0.2);
			m_RenderTarget.FillGeometry(m_pGeometry, m_pBlackBrush);
			m_pBlackBrush->SetOpacity((FLOAT)0.7);

			m_RenderTarget.DrawGeometry(m_pGeometry, m_pBlackBrush, 2);

			delete m_pGeometry;
		}

		delete[] sx;
		delete[] sy;
		break;
	}
	}
}

void CGISViewerView::OnButtonRouteAdd()
{
	CDialogExAddRoute dlg; 
	dlg.pView = this;

	if (dlg.DoModal() != IDOK) 
	{
		return;
	} 
	m_pDockablePaneRoutePlan->pDlg->UpdateRouteList(); 

	int currentRouteIndex = pRoutePlanner->GetRouteCount() - 1;
	m_pDockablePaneRoutePlan->pDlg->SelectRouteIndex(currentRouteIndex); 

	time_t departureTime;
	pRoutePlanner->GetDepartureTime(currentRouteIndex, &departureTime); 
	struct tm t;
	localtime_s(&t, &departureTime);
	int year = t.tm_year + 1900;
	int month = t.tm_mon + 1;
	int day = t.tm_mday;
	int hour = t.tm_hour;
	int min = t.tm_min;

	CString strDepartureTime;
	strDepartureTime.Format(_T("%d-%02d-%02d, %02d:%02d"), year, month, day, hour, min);
	m_pDockablePaneRoutePlan->pDlg->SetDepartureTime(strDepartureTime);
}

void CGISViewerView::OnUpdateButtonRouteAdd(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CGISViewerView::OnButtonRouteModify()
{
	int curIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (curIndex >= 0)
	{
		CDialogExChangeRouteName dlg;
		dlg.pView = this;

		int result = dlg.DoModal();

		m_pDockablePaneRoutePlan->pDlg->UpdateRouteList();
		m_pDockablePaneRoutePlan->pDlg->SelectRouteIndex(curIndex);

		int currentRouteIndex = pRoutePlanner->GetRouteCount() - 1;

		time_t departureTime;
		pRoutePlanner->GetDepartureTime(currentRouteIndex, &departureTime); 
		struct tm t;
		localtime_s(&t, &departureTime);
		int year = t.tm_year + 1900;
		int month = t.tm_mon + 1;
		int day = t.tm_mday;
		int hour = t.tm_hour;
		int min = t.tm_min;

		CString strDepartureTime;
		strDepartureTime.Format(_T("%d-%02d-%02d, %02d:%02d"), year, month, day, hour, min);
		m_pDockablePaneRoutePlan->pDlg->SetDepartureTime(strDepartureTime);

		m_pDockablePaneRoutePlan->pDlg->UpdateWaypointList();
	}
	else
	{
		AfxMessageBox(_T("Try again!\n: Select route"));
	}
}

void CGISViewerView::OnUpdateButtonRouteModify(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonRouteDelete()
{
	int currentRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (currentRouteIndex < 0)
	{
		AfxMessageBox(_T("삭제 가능한 항로가 없습니다."));
		return;
	}

	CString routeName = (pRoutePlanner->GetRouteName(currentRouteIndex)).c_str();

	CDialogExDeleteRoute dlg(this);
	dlg.m_strRouteName.Format(routeName);

	if (dlg.DoModal() == IDOK)
	{
		pRoutePlanner->DeleteRoute(currentRouteIndex);
		m_pDockablePaneRoutePlan->pDlg->UpdateRouteList();
		m_pDockablePaneRoutePlan->pDlg->SelectRouteIndex(-1);
		m_pDockablePaneRoutePlan->pDlg->UpdateWaypointList();
		m_pDockablePaneRoutePlan->pDlg->SetDepartureTime(_T(""));
		Invalidate();
	}
}


void CGISViewerView::OnUpdateButtonRouteDelete(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonRouteLoad()
{ 
	CString File;
	CString strFileList;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, _T("GML Files(*.gml)|*.gml|All Files (*.*)|*.*|"), this);

	const int c_cMaxFiles = 400 ; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CString name = dlg.GetFileName();
		CString path = dlg.GetFolderPath();

		CString pathName = dlg.GetPathName(); 

		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
		{ 
			File = dlg.GetNextPathName(pos);
			OpenRouteFromGML(File);
		}

		EndWaitCursor();
	}
}


void CGISViewerView::OnUpdateButtonRouteLoad(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonRouteSave()
{ 
	int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

	if (routeIndex < 0)
	{
		AfxMessageBox(_T("Select route!"));
		return;
	} 
	CFileDialog dlg(FALSE);
	CString nameFilter = _T("GML File (*.gml)\0*.gml\0All Files (*.*)\0*.*\0\0");
	dlg.m_ofn.lpstrFilter = nameFilter;

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CString name = dlg.GetFileName();
		CString path = dlg.GetFolderPath();

		CString pathName = dlg.GetPathName();

		SaveRoutePlanAsGML(pathName, routeIndex);

		EndWaitCursor();
	}
}


void CGISViewerView::OnUpdateButtonRouteSave(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointAdd()
{
	int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

	if (routeIndex < 0)
	{
		AfxMessageBox(_T("Select route plan"));
		return;
	}

	int waypointCount = pRoutePlanner->GetWaypointCount(routeIndex);

	CDialogExAddWaypoint dlg;

	dlg.m_fLon = 0;
	dlg.m_fLat = 0;
	dlg.m_dSpeed = 10.0;

	if (pRoutePlanner->GetWaypointCount(routeIndex) == 0)
	{
		dlg.m_dSpeed = 0;
	}

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	if (routeIndex >= 0)
	{
		double lon = dlg.m_fLon;
		double lat = dlg.m_fLat;  
		double speed = dlg.m_dSpeed; 
		pRoutePlanner->AddWaypoint(routeIndex, lon, lat, speed, speed);
		theApp.m_DockablePaneRoutePlan.pDlg->UpdateWaypointList();
		Invalidate();
	}
}


void CGISViewerView::OnUpdateButtonWaypointAdd(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointModify()
{
	int currentSelectedRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();
	int currentSelectedWaypointIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentWaypointIndex();

	if (currentSelectedWaypointIndex < 0)
	{
		AfxMessageBox(_T("Select waypoint"));
		return;
	}

	CDialogExAddWaypoint dlg;
	dlg.isAdd = false;

	dlg.m_dSpeed = pRoutePlanner->GetSpeed(currentSelectedRouteIndex, currentSelectedWaypointIndex); 

	dlg.m_fLon = pRoutePlanner->GetX(currentSelectedRouteIndex, currentSelectedWaypointIndex);
	dlg.m_fLat = pRoutePlanner->GetY(currentSelectedRouteIndex, currentSelectedWaypointIndex);

	m_pGisLib->InverseProjection(&dlg.m_fLon, &dlg.m_fLat);
	if (IDOK == dlg.DoModal())
	{
		projection(dlg.m_fLon, dlg.m_fLat); 
		pRoutePlanner->SetWaypoint(currentSelectedRouteIndex, currentSelectedWaypointIndex, dlg.m_fLon, dlg.m_fLat, dlg.m_dSpeed, dlg.m_dSpeed);
		m_pDockablePaneRoutePlan->pDlg->UpdateWaypointList();
		Invalidate();
	}
}


void CGISViewerView::OnUpdateButtonWaypointModify(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointDelete()
{
	int currentSelectedRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();
	int currentSelectedWaypointIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentWaypointIndex();

	if (currentSelectedWaypointIndex < 0)
	{
		AfxMessageBox(_T("Select waypoint"));
		return;
	}

	CDialogExDeleteWaypoint dlg;
	dlg.m_strWaypointNumber.Format(_T("%d번"), currentSelectedWaypointIndex + 1);

	if (dlg.DoModal() == IDOK)
	{
		pRoutePlanner->DeleteWaypoint(currentSelectedRouteIndex, currentSelectedWaypointIndex);
		theApp.m_DockablePaneRoutePlan.pDlg->UpdateWaypointList();
		Invalidate();
	}
}


void CGISViewerView::OnUpdateButtonWaypointDelete(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointMouseAdd()
{
	(m_Icon == MOUSE_ADD_WP) ? m_Icon = MOVE : m_Icon = MOUSE_ADD_WP;
}


void CGISViewerView::OnUpdateButtonWaypointMouseAdd(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_Icon == MOUSE_ADD_WP);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointMouseModify()
{
	(m_Icon == MOUSE_MODIFY_WP) ? m_Icon = MOVE : m_Icon = MOUSE_MODIFY_WP;
}


void CGISViewerView::OnUpdateButtonWaypointMouseModify(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_Icon == MOUSE_MODIFY_WP);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OnButtonWaypointMouseDelete()
{
	(m_Icon == MOUSE_REMOVE_WP) ? m_Icon = MOVE : m_Icon = MOUSE_REMOVE_WP;
}


void CGISViewerView::OnUpdateButtonWaypointMouseDelete(CCmdUI *pCmdUI)
{
	if (theApp.m_DockablePaneRoutePlan.IsVisible())
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_Icon == MOUSE_REMOVE_WP);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CGISViewerView::OpenRouteFromGML(CString _filePathName)
{   
	pRoutePlanner->AddRouteFromGML(std::wstring(_filePathName)); 
	m_pDockablePaneRoutePlan->pDlg->UpdateRouteList();                                   
}

void CGISViewerView::OpenRouteFromGMLByPugi(CString _filePath)
{  
	m_pDockablePaneRoutePlan->pDlg->UpdateRouteList();

}




void CGISViewerView::SaveRoutePlanAsGML(CString _filePathName, unsigned int _index)
{ 
	pRoutePlanner->Save(_filePathName, _index);                                                                                                                                                                                                                                      
}

void CGISViewerView::DrawRoute(CDC* pDC, bool isMoveDraw, int offsetX, int offsetY)
{
#ifdef ROUTE_CHECK
	MakeOwnShipPosition();
#endif 
	int routeIndex = theApp.m_DockablePaneRoutePlan.pDlg->GetCurrentRouteIndex();

	if (routeIndex < 0)
	{
		return;
	} 
	int waypointCount = pRoutePlanner->GetWaypointCount(routeIndex);

	if (waypointCount < 1) return;

	GeoPoint* ptWp = new GeoPoint[waypointCount];

	for (int i = 0; i < waypointCount; i++) {
		ptWp[i].x = pRoutePlanner->GetX(routeIndex, i);
		ptWp[i].y = pRoutePlanner->GetY(routeIndex, i);
	}

	ClipperLib::PolyTree* clippedPLs = m_pGisLib->ClipPolyline(ptWp, waypointCount);
	ClipperLib::Paths paths;
	ClipperLib::PolyTreeToPaths(*clippedPLs, paths);

	Symbol* symbol = m_pSymbolManager->GetComposite(_T("PLNRTE04")); 
	for (unsigned i = 0; i < paths.size(); i++) {
		ClipperLib::Path path = paths.at(i);

		POINT* tmpPtWp = new POINT[path.size()];

		for (unsigned j = 0; j < path.size(); j++) {
			m_pGisLib->WorldToDevice(
				(double)path.at(j).X / Scaler::COMF,
				(double)path.at(j).Y / Scaler::COMF,
				&tmpPtWp[j].x,
				&tmpPtWp[j].y);

			if (isMoveDraw) {
				tmpPtWp[j].x += m_ep.x - m_sp.x;
				tmpPtWp[j].y += m_ep.y - m_sp.y;
			}
		}

		ENCLine line;
		line.DrawCompositeLineOnPolyline(pDC, tmpPtWp, path.size(), symbol);

		delete[] tmpPtWp;
	}

	if (waypointCount >= 1) {
		delete[] ptWp;
	}

	delete clippedPLs; 
	POINT tmpP;
	for (int i = 0; i < waypointCount; i++)
	{
		double x = pRoutePlanner->GetX(routeIndex, i);
		double y = pRoutePlanner->GetY(routeIndex, i);

		if (m_pGisLib->PtInMap(x, y)) {
			m_pGisLib->WorldToDevice(x, y, &(tmpP.x), &(tmpP.y));

			if (isMoveDraw)
			{
				tmpP.x += m_ep.x - m_sp.x;
				tmpP.y += m_ep.y - m_sp.y;
			}

			m_pSymbolManager->DrawSymbol(_T("WAYPNT02"), pDC, CPoint(tmpP.x, tmpP.y));
		}
	} 
	DrawRouteBuffer(pDC, routeIndex, isMoveDraw);
}

void CGISViewerView::DrawRouteBuffer(CDC* pDC, int _routeIndex, bool isMoveDraw)
{
	if (_routeIndex < 0) {
		return;
	} 
	int waypointCount = pRoutePlanner->GetWaypointCount(_routeIndex);

	if (waypointCount < 1) {
		return;
	} 
	GeoPoint* ptWp = new GeoPoint[waypointCount];

	for (int i = 0; i < waypointCount; i++) {
		ptWp[i].x = pRoutePlanner->GetX(_routeIndex, i);
		ptWp[i].y = pRoutePlanner->GetY(_routeIndex, i);
		m_pGisLib->InverseProjection(&ptWp[i].x, &ptWp[i].y);
	}

	auto rightBufLeg = new RT::BufLeg[waypointCount - 1];
	auto leftBufLeg = new RT::BufLeg[waypointCount - 1];

	bool* isRight = nullptr;
	if (waypointCount >= 3) {
		isRight = new bool[waypointCount - 2];
	}

	double* startOffset = new double[waypointCount - 1];
	double* endOffset = new double[waypointCount - 1];

	for (int i = 0; i < (waypointCount - 1); i++) {
		startOffset[i] = 0;
		endOffset[i] = 0;
	}

	double buffDistance = 0.2;

	CPen rightPen, leftPen, centerPen;
	rightPen.CreatePen(PS_DASH, 1, RGB(0, 255, 0));
	leftPen.CreatePen(PS_DASH, 1, RGB(0, 0, 255));
	centerPen.CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	CPen* oldPen;

	for (int i = 0; i < waypointCount - 1; i++) {
		if ((i == 0) && (i == waypointCount - 2)) { 
			leftBufLeg[i].ptStart = SimpleLeftBufPoint(ptWp[i].x, ptWp[i].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptStart.x, &leftBufLeg[i].ptStart.y);
			rightBufLeg[i].ptStart = SimpleRightBufPoint(ptWp[i].x, ptWp[i].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptStart.x, &rightBufLeg[i].ptStart.y); 
			leftBufLeg[i].ptEnd = SimpleLeftBufPoint(ptWp[i + 1].x, ptWp[i + 1].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptEnd.x, &leftBufLeg[i].ptEnd.y);
			rightBufLeg[i].ptEnd = SimpleRightBufPoint(ptWp[i + 1].x, ptWp[i + 1].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptEnd.x, &rightBufLeg[i].ptEnd.y);
		}
		else if (i == 0) { 
			leftBufLeg[i].ptStart = SimpleLeftBufPoint(ptWp[i].x, ptWp[i].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptStart.x, &leftBufLeg[i].ptStart.y);
			rightBufLeg[i].ptStart = SimpleRightBufPoint(ptWp[i].x, ptWp[i].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptStart.x, &rightBufLeg[i].ptStart.y); 
			double currentHeading = pRoutePlanner->GetHeading(_routeIndex, i);
			double nextHeading = pRoutePlanner->GetHeading(_routeIndex, i + 1);

			double theta = GetAngleFromLegs(currentHeading, nextHeading, false) * DEG2RAD;

			double offset = 0;

			if (theta != M_PI) {
				offset = buffDistance / tan(theta / 2.0);
			}

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(ptWp[i + 1].y, ptWp[i + 1].x, pRoutePlanner->GetHeading(_routeIndex, i) + 180, offset, false);
			leftBufLeg[i].ptEnd = SimpleLeftBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptEnd.x, &leftBufLeg[i].ptEnd.y);
			rightBufLeg[i].ptEnd = SimpleRightBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptEnd.x, &rightBufLeg[i].ptEnd.y);

			endOffset[i] = GetDistanceRhumbLineMercator(pos.lat, pos.lon, ptWp[i + 1].y, ptWp[i + 1].x, false);
		}
		else if (i == waypointCount - 2) { 
			double prevHeading = pRoutePlanner->GetHeading(_routeIndex, i - 1);
			double currentHeading = pRoutePlanner->GetHeading(_routeIndex, i);

			double theta = GetAngleFromLegs(prevHeading, currentHeading, false) * DEG2RAD;

			double offset = 0;

			if (theta != M_PI) {
				offset = buffDistance / tan(theta / 2.0);
			}

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(ptWp[i].y, ptWp[i].x, pRoutePlanner->GetHeading(_routeIndex, i), offset, false);
			leftBufLeg[i].ptStart = SimpleLeftBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptStart.x, &leftBufLeg[i].ptStart.y);
			rightBufLeg[i].ptStart = SimpleRightBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptStart.x, &rightBufLeg[i].ptStart.y);

			startOffset[i] = GetDistanceRhumbLineMercator(pos.lat, pos.lon, ptWp[i].y, ptWp[i].x, false);

			POINT ptOffset;
			m_pGisLib->Projection(&pos.lon, &pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &ptOffset.x, &ptOffset.y);

			if (waypointCount >= 3) {
				isRight[i - 1] = IsRight(ptWp[i - 1].x, ptWp[i - 1].y, ptWp[i].x, ptWp[i].y,
					ptWp[i].x, ptWp[i].y, ptWp[i + 1].x, ptWp[i + 1].y);

				POINT ptCircle;
				CRect rectInnerCircle;
				CRect rectOuterCircle;

				if (isRight[i - 1]) { 
					m_pGisLib->WorldToDevice(rightBufLeg[i].ptStart.x, rightBufLeg[i].ptStart.y, &ptCircle.x, &ptCircle.y);
					double bufDistancePixel = sqrt((ptCircle.x - ptOffset.x) * (ptCircle.x - ptOffset.x) + (ptCircle.y - ptOffset.y) * (ptCircle.y - ptOffset.y));
					rectInnerCircle.SetRect((int)(ptCircle.x - bufDistancePixel),
						(int)(ptCircle.y - bufDistancePixel),
						(int)(ptCircle.x + bufDistancePixel),
						(int)(ptCircle.y + bufDistancePixel));
					rectOuterCircle.SetRect((int)(ptCircle.x - bufDistancePixel * 2),
						(int)(ptCircle.y - bufDistancePixel * 2),
						(int)(ptCircle.x + bufDistancePixel * 2),
						(int)(ptCircle.y + bufDistancePixel * 2));

					POINT ptCircleStart;
					POINT ptCircleEnd;

					m_pGisLib->WorldToDevice(leftBufLeg[i - 1].ptEnd.x, leftBufLeg[i - 1].ptEnd.y, &ptCircleStart.x, &ptCircleStart.y);
					m_pGisLib->WorldToDevice(leftBufLeg[i].ptStart.x, leftBufLeg[i].ptStart.y, &ptCircleEnd.x, &ptCircleEnd.y);

					if (isMoveDraw) {
						rectInnerCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
						rectOuterCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
						ptCircleStart.x += m_ep.x - m_sp.x;
						ptCircleStart.y += m_ep.y - m_sp.y;
						ptCircleEnd.x += m_ep.x - m_sp.x;
						ptCircleEnd.y += m_ep.y - m_sp.y;
					}

					oldPen = pDC->SelectObject(&centerPen);
					pDC->Arc(rectInnerCircle, ptCircleEnd, ptCircleStart);
					pDC->SelectObject(oldPen);

					oldPen = pDC->SelectObject(&leftPen);
					pDC->Arc(rectOuterCircle, ptCircleEnd, ptCircleStart);
					pDC->SelectObject(oldPen);
				}
				else { 
					m_pGisLib->WorldToDevice(leftBufLeg[i].ptStart.x, leftBufLeg[i].ptStart.y, &ptCircle.x, &ptCircle.y);
					double bufDistancePixel = sqrt((ptCircle.x - ptOffset.x) * (ptCircle.x - ptOffset.x) + (ptCircle.y - ptOffset.y) * (ptCircle.y - ptOffset.y));
					rectInnerCircle.SetRect(
						(int)(ptCircle.x - bufDistancePixel),
						(int)(ptCircle.y - bufDistancePixel),
						(int)(ptCircle.x + bufDistancePixel),
						(int)(ptCircle.y + bufDistancePixel));
					rectOuterCircle.SetRect(
						(int)(ptCircle.x - bufDistancePixel * 2),
						(int)(ptCircle.y - bufDistancePixel * 2),
						(int)(ptCircle.x + bufDistancePixel * 2),
						(int)(ptCircle.y + bufDistancePixel * 2));

					POINT ptCircleStart;
					POINT ptCircleEnd;

					m_pGisLib->WorldToDevice(rightBufLeg[i - 1].ptEnd.x, rightBufLeg[i - 1].ptEnd.y, &ptCircleStart.x, &ptCircleStart.y);
					m_pGisLib->WorldToDevice(rightBufLeg[i].ptStart.x, rightBufLeg[i].ptStart.y, &ptCircleEnd.x, &ptCircleEnd.y);

					if (isMoveDraw) {
						rectInnerCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
						rectOuterCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
						ptCircleStart.x += m_ep.x - m_sp.x;
						ptCircleStart.y += m_ep.y - m_sp.y;
						ptCircleEnd.x += m_ep.x - m_sp.x;
						ptCircleEnd.y += m_ep.y - m_sp.y;
					}

					oldPen = pDC->SelectObject(&centerPen);
					pDC->Arc(rectInnerCircle, ptCircleStart, ptCircleEnd);
					pDC->SelectObject(oldPen);

					oldPen = pDC->SelectObject(&rightPen);
					pDC->Arc(rectOuterCircle, ptCircleStart, ptCircleEnd);
					pDC->SelectObject(oldPen);
				}
			} 
			leftBufLeg[i].ptEnd = SimpleLeftBufPoint(ptWp[i + 1].x, ptWp[i + 1].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptEnd.x, &leftBufLeg[i].ptEnd.y);
			rightBufLeg[i].ptEnd = SimpleRightBufPoint(ptWp[i + 1].x, ptWp[i + 1].y, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptEnd.x, &rightBufLeg[i].ptEnd.y);
		}
		else { 
			double prevHeading = pRoutePlanner->GetHeading(_routeIndex, i - 1);
			double currentHeading = pRoutePlanner->GetHeading(_routeIndex, i);

			double theta = GetAngleFromLegs(prevHeading, currentHeading, false) * DEG2RAD;

			double offset = 0;

			if (theta != M_PI) {
				offset = buffDistance / tan(theta / 2.0);
			}

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(ptWp[i].y, ptWp[i].x, pRoutePlanner->GetHeading(_routeIndex, i), offset, false);
			leftBufLeg[i].ptStart = SimpleLeftBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptStart.x, &leftBufLeg[i].ptStart.y);
			rightBufLeg[i].ptStart = SimpleRightBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptStart.x, &rightBufLeg[i].ptStart.y);

			startOffset[i] = GetDistanceRhumbLineMercator(pos.lat, pos.lon, ptWp[i].y, ptWp[i].x, false);

			POINT ptOffset;
			m_pGisLib->Projection(&pos.lon, &pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &ptOffset.x, &ptOffset.y);

			isRight[i - 1] = IsRight(ptWp[i - 1].x, ptWp[i - 1].y, ptWp[i].x, ptWp[i].y,
				ptWp[i].x, ptWp[i].y, ptWp[i + 1].x, ptWp[i + 1].y);

			POINT ptCircle;
			CRect rectInnerCircle;
			CRect rectOuterCircle;

			if (isRight[i - 1]) { 
				m_pGisLib->WorldToDevice(rightBufLeg[i].ptStart.x, rightBufLeg[i].ptStart.y, &ptCircle.x, &ptCircle.y);
				double bufDistancePixel = sqrt((ptCircle.x - ptOffset.x) * (ptCircle.x - ptOffset.x) + (ptCircle.y - ptOffset.y) * (ptCircle.y - ptOffset.y));
				rectInnerCircle.SetRect(
					(int)(ptCircle.x - bufDistancePixel),
					(int)(ptCircle.y - bufDistancePixel),
					(int)(ptCircle.x + bufDistancePixel),
					(int)(ptCircle.y + bufDistancePixel));
				rectOuterCircle.SetRect(
					(int)(ptCircle.x - bufDistancePixel * 2),
					(int)(ptCircle.y - bufDistancePixel * 2),
					(int)(ptCircle.x + bufDistancePixel * 2),
					(int)(ptCircle.y + bufDistancePixel * 2));

				POINT ptCircleStart;
				POINT ptCircleEnd;

				m_pGisLib->WorldToDevice(leftBufLeg[i - 1].ptEnd.x, leftBufLeg[i - 1].ptEnd.y, &ptCircleStart.x, &ptCircleStart.y);
				m_pGisLib->WorldToDevice(leftBufLeg[i].ptStart.x, leftBufLeg[i].ptStart.y, &ptCircleEnd.x, &ptCircleEnd.y);

				if (isMoveDraw) {
					rectInnerCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
					rectOuterCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
					ptCircleStart.x += m_ep.x - m_sp.x;
					ptCircleStart.y += m_ep.y - m_sp.y;
					ptCircleEnd.x += m_ep.x - m_sp.x;
					ptCircleEnd.y += m_ep.y - m_sp.y;
				}

				oldPen = pDC->SelectObject(&centerPen);
				pDC->Arc(rectInnerCircle, ptCircleEnd, ptCircleStart);
				pDC->SelectObject(oldPen);

				oldPen = pDC->SelectObject(&leftPen);
				pDC->Arc(rectOuterCircle, ptCircleEnd, ptCircleStart);
				pDC->SelectObject(oldPen);
			}
			else { 
				m_pGisLib->WorldToDevice(leftBufLeg[i].ptStart.x, leftBufLeg[i].ptStart.y, &ptCircle.x, &ptCircle.y);
				double bufDistancePixel = sqrt((ptCircle.x - ptOffset.x) * (ptCircle.x - ptOffset.x) + (ptCircle.y - ptOffset.y) * (ptCircle.y - ptOffset.y));
				rectInnerCircle.SetRect(
					(int)(ptCircle.x - bufDistancePixel),
					(int)(ptCircle.y - bufDistancePixel),
					(int)(ptCircle.x + bufDistancePixel),
					(int)(ptCircle.y + bufDistancePixel));
				rectOuterCircle.SetRect(
					(int)(ptCircle.x - bufDistancePixel * 2),
					(int)(ptCircle.y - bufDistancePixel * 2),
					(int)(ptCircle.x + bufDistancePixel * 2),
					(int)(ptCircle.y + bufDistancePixel * 2));

				POINT ptCircleStart;
				POINT ptCircleEnd;

				m_pGisLib->WorldToDevice(rightBufLeg[i - 1].ptEnd.x, rightBufLeg[i - 1].ptEnd.y, &ptCircleStart.x, &ptCircleStart.y);
				m_pGisLib->WorldToDevice(rightBufLeg[i].ptStart.x, rightBufLeg[i].ptStart.y, &ptCircleEnd.x, &ptCircleEnd.y);

				if (isMoveDraw) {
					rectInnerCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
					rectOuterCircle.OffsetRect(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
					ptCircleStart.x += m_ep.x - m_sp.x;
					ptCircleStart.y += m_ep.y - m_sp.y;
					ptCircleEnd.x += m_ep.x - m_sp.x;
					ptCircleEnd.y += m_ep.y - m_sp.y;
				}

				oldPen = pDC->SelectObject(&centerPen);
				pDC->Arc(rectInnerCircle, ptCircleStart, ptCircleEnd);
				pDC->SelectObject(oldPen);

				oldPen = pDC->SelectObject(&rightPen);
				pDC->Arc(rectOuterCircle, ptCircleStart, ptCircleEnd);
				pDC->SelectObject(oldPen);
			} 
			currentHeading = pRoutePlanner->GetHeading(_routeIndex, i);
			double nextHeading = pRoutePlanner->GetHeading(_routeIndex, i + 1);

			theta = GetAngleFromLegs(currentHeading, nextHeading, false) * DEG2RAD;

			offset = 0;

			if (theta != M_PI) {
				offset = buffDistance / tan(theta / 2.0);
			}

			pos = GetDestinationPointRhumbLineMercator(ptWp[i + 1].y, ptWp[i + 1].x, pRoutePlanner->GetHeading(_routeIndex, i) + 180, offset, false);
			leftBufLeg[i].ptEnd = SimpleLeftBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&leftBufLeg[i].ptEnd.x, &leftBufLeg[i].ptEnd.y);
			rightBufLeg[i].ptEnd = SimpleRightBufPoint(pos.lon, pos.lat, pRoutePlanner->GetHeading(_routeIndex, i), buffDistance, false);
			m_pGisLib->Projection(&rightBufLeg[i].ptEnd.x, &rightBufLeg[i].ptEnd.y);

			endOffset[i] = GetDistanceRhumbLineMercator(pos.lat, pos.lon, ptWp[i + 1].y, ptWp[i + 1].x, false);

			m_pGisLib->Projection(&pos.lon, &pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &ptOffset.x, &ptOffset.y);
		} 
		oldPen = pDC->SelectObject(&rightPen);
		POINT ptStart;
		POINT ptEnd;

		m_pGisLib->WorldToDevice(rightBufLeg[i].ptStart.x, rightBufLeg[i].ptStart.y, &ptStart.x, &ptStart.y);
		m_pGisLib->WorldToDevice(rightBufLeg[i].ptEnd.x, rightBufLeg[i].ptEnd.y, &ptEnd.x, &ptEnd.y);

		if (isMoveDraw) {
			ptStart.x += m_ep.x - m_sp.x;
			ptStart.y += m_ep.y - m_sp.y;
			ptEnd.x += m_ep.x - m_sp.x;
			ptEnd.y += m_ep.y - m_sp.y;
		}

		pDC->MoveTo(ptStart);
		pDC->LineTo(ptEnd);
		pDC->SelectObject(oldPen); 
		oldPen = pDC->SelectObject(&leftPen);
		m_pGisLib->WorldToDevice(leftBufLeg[i].ptStart.x, leftBufLeg[i].ptStart.y, &ptStart.x, &ptStart.y);
		m_pGisLib->WorldToDevice(leftBufLeg[i].ptEnd.x, leftBufLeg[i].ptEnd.y, &ptEnd.x, &ptEnd.y);

		if (isMoveDraw) {
			ptStart.x += m_ep.x - m_sp.x;
			ptStart.y += m_ep.y - m_sp.y;
			ptEnd.x += m_ep.x - m_sp.x;
			ptEnd.y += m_ep.y - m_sp.y;
		}

		pDC->MoveTo(ptStart);
		pDC->LineTo(ptEnd);
		pDC->SelectObject(oldPen);
	}

	DrawOwnShip(pDC, isMoveDraw, ptWp, rightBufLeg, leftBufLeg, isRight, startOffset, endOffset, buffDistance, waypointCount);

	delete[] rightBufLeg;
	delete[] leftBufLeg;
	delete[] ptWp;
	delete[] isRight;
	delete[] startOffset;
	delete[] endOffset;
}



void CGISViewerView::OnSliderRoute()
{
#ifdef ROUTE_CHECK
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
	Invalidate();

	OutputDebugString(_T("Slider\n"));
#endif
}

void CGISViewerView::OnButtonRouteSlow()
{
#ifdef ROUTE_CHECK
	routeSpeed /= 2;
	if (routeSpeed < 1)
	{
		routeSpeed = 1;
	}
	OutputDebugString(_T("Slow\n"));
#endif
}

void CGISViewerView::OnButtonRoutePrev()
{
#ifdef ROUTE_CHECK
	OutputDebugString(_T("Prev\n"));
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);

	slider->SetPos(slider->GetPos() - routeSpeed);
	Invalidate();
#endif
}

void CGISViewerView::OnButtonRoutePlay()
{
#ifdef ROUTE_CHECK
	OutputDebugString(_T("Play\n"));
	if (m_bRoutePlay == false)
	{
		SetTimer(1126, 1000, NULL);
	}
	else
	{
		KillTimer(1126);
	}
#endif
}

void CGISViewerView::OnButtonRoutePause()
{
#ifdef ROUTE_CHECK
	OutputDebugString(_T("Pause\n"));
	KillTimer(1126);
#endif
}

void CGISViewerView::OnButtonRouteStop()
{
#ifdef ROUTE_CHECK
	KillTimer(1126);
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);

	slider->SetPos(0);
	OutputDebugString(_T("Stop\n"));
	Invalidate();
#endif
}

void CGISViewerView::OnButtonRouteNext()
{
#ifdef ROUTE_CHECK
	OutputDebugString(_T("Next\n"));
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);

	slider->SetPos(slider->GetPos() + routeSpeed);
	Invalidate();
#endif	
}

void CGISViewerView::OnButtonRouteFast()
{
#ifdef ROUTE_CHECK
	routeSpeed *= 2;
	if (routeSpeed > 16)
	{
		routeSpeed = 16;
	}
	OutputDebugString(_T("Fast\n"));
#endif
}



RT::PointD CGISViewerView::SimpleRightBufPoint(double _x, double _y, double _heading, double _distance, bool _radian)
{
	if (_radian) {
		_heading += (M_PI / 2);
	}
	else {
		_heading += 90;
	}

	LatLonUtility::Pos pos = LatLonUtility::GetDestinationPointRhumbLineMercator(_y, _x, _heading, _distance, _radian);
	RT::PointD result;
	result.x = pos.lon;
	result.y = pos.lat;
	return result;
}


RT::PointD CGISViewerView::SimpleLeftBufPoint(double _x, double _y, double _heading, double _distance, bool _radian)
{
	if (_radian) {
		_heading -= (M_PI / 2);
	}
	else {
		_heading -= 90;
	}

	LatLonUtility::Pos pos = LatLonUtility::GetDestinationPointRhumbLineMercator(_y, _x, _heading, _distance, _radian);
	RT::PointD result;
	result.x = pos.lon;
	result.y = pos.lat;
	return result;
}


double CGISViewerView::GetAngleFromLegs(double _heading1, double _heading2, bool _radian)
{
	double PI = acos(-1.0);

	if (!_radian) {
		PI *= RAD2DEG;
	}

	if (_heading1 > PI) {
		_heading1 -= PI;
	}

	if (_heading2 > PI) {
		_heading2 -= PI;
	}

	double result = PI - _heading1 + _heading2;   

	if (result > PI) {
		result = (2 * PI) - result;
	}

	return abs(result);
}


bool CGISViewerView::IsRight(double _x1Leg1, double _y1Leg1, double _x2Leg1, double _y2Leg1,
	double _x1Leg2, double _y1Leg2, double _x2Leg2, double _y2Leg2)
{
	double x1 = _x2Leg1 - _x1Leg1;
	double y1 = _y2Leg1 - _y1Leg1;
	double x2 = _x2Leg2 - _x1Leg2;
	double y2 = _y2Leg2 - _y1Leg2;

	double det = (x1 * y2) - (y1 * x2);

	if (det < 0) {
		return true;
	}

	return false;
}


void CGISViewerView::MakeOwnShipPosition()
{
	BeginWaitCursor();
#ifdef ROUTE_CHECK 
	int currentRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (currentRouteIndex < 0)
	{
		EndWaitCursor();
		return;
	}

	RT::Route* currentRoute = pRoutePlanner->GetRoute(currentRouteIndex);
	int wpCnt = currentRoute->GetWaypointCount();
	if (wpCnt < 2)
	{
		EndWaitCursor();
		return;
	}

	std::time_t departTime;
	pRoutePlanner->GetDepartureTime(currentRouteIndex, &departTime);

	std::time_t arrivalTime;
	arrivalTime = pRoutePlanner->GetArrivalTime(currentRouteIndex, wpCnt - 1);


	double diff = difftime(arrivalTime, departTime);
	if (diff > 0)
	{
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
		slider->SetRange(0, (int)diff - 1);
	}

#endif
	EndWaitCursor();
}

void CGISViewerView::DrawOwnShip(CDC* pDC, bool isMoveDraw)
{
	return;

#ifdef ROUTE_CHECK 
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
	int ownShipIndex = slider->GetPos();

	int currentRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (currentRouteIndex < 0)
	{
		EndWaitCursor();
		return;
	}

	RT::Route* route = pRoutePlanner->GetRoute(currentRouteIndex);

	if (!route) {
		EndWaitCursor();
		return;
	}

	if (route->GetLegCount() < 1)
	{
		EndWaitCursor();
		return;
	}

	time_t departTime = route->GetDepartureTime();
	time_t currentTime = departTime + ownShipIndex;
	time_t nextTime = currentTime + 1;
	double x = 0, xn = 0;
	double y = 0, yn = 0;
	double s = 0, sn = 0;
	route->GetPosSpeedAtTime(currentTime, x, y, s);
	route->GetPosSpeedAtTime(nextTime, xn, yn, sn);
	long sx = 0;
	long sy = 0; 
	m_pGisLib->WorldToDevice(x, y, &sx, &sy);

	if (isMoveDraw) {
		sx += (m_ep.x - m_sp.x);
		sy += (m_ep.y - m_sp.y);
	}

	m_pSymbolManager->DrawSymbol(_T("OWNSHP02"), pDC, CPoint(sx, sy));   

	m_pGisLib->InverseProjection(&x, &y);
	m_pGisLib->InverseProjection(&xn, &yn);

	double heading = GetBearingRhubmLineMercator(y, x, yn, xn, false);
	heading *= DEG2RAD;
	{
		int d = 70;  
		double h = heading;
		double yd = -(d * cos(h));
		double xd = d * sin(h);

		long x1 = sx;
		long y1 = sy;
		long x2 = 0;
		long y2 = 0;

		x2 = long(x1 + xd);
		y2 = long(y1 + yd);

		Gdiplus::Point ownShipSym[3];

		ownShipSym[0].X = INT(ownShipVector[0].X * cos(h) - ownShipVector[0].Y * sin(h));
		ownShipSym[0].Y = INT(ownShipVector[0].X * sin(h) + ownShipVector[0].Y * cos(h));

		ownShipSym[1].X = INT(ownShipVector[1].X * cos(h) - ownShipVector[1].Y * sin(h));
		ownShipSym[1].Y = INT(ownShipVector[1].X * sin(h) + ownShipVector[1].Y * cos(h));

		ownShipSym[2].X = INT(ownShipVector[2].X * cos(h) - ownShipVector[2].Y * sin(h));
		ownShipSym[2].Y = INT(ownShipVector[2].X * sin(h) + ownShipVector[2].Y * cos(h));

		ownShipSym[0].X += (INT)x2;
		ownShipSym[0].Y += (INT)y2;
		ownShipSym[1].X += (INT)x2;
		ownShipSym[1].Y += (INT)y2;
		ownShipSym[2].X += (INT)x2;
		ownShipSym[2].Y += (INT)y2;

		CPen newPen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen *oldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);

		pDC->SelectObject(oldPen);
		Graphics _g(pDC->GetSafeHdc());
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[1]);
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[2]);

		ownShipSym[0].X = (INT)(ownShipVector[0].X * cos(h) - (ownShipVector[0].Y + 10) * sin(h));
		ownShipSym[0].Y = (INT)(ownShipVector[0].X * sin(h) + (ownShipVector[0].Y + 10) * cos(h));

		ownShipSym[1].X = (INT)(ownShipVector[1].X * cos(h) - (ownShipVector[1].Y + 10) * sin(h));
		ownShipSym[1].Y = (INT)(ownShipVector[1].X * sin(h) + (ownShipVector[1].Y + 10) * cos(h));

		ownShipSym[2].X = (INT)(ownShipVector[2].X * cos(h) - (ownShipVector[2].Y + 10) * sin(h));
		ownShipSym[2].Y = (INT)(ownShipVector[2].X * sin(h) + (ownShipVector[2].Y + 10) * cos(h));

		ownShipSym[0].X += (INT)x2;
		ownShipSym[0].Y += (INT)y2;
		ownShipSym[1].X += (INT)x2;
		ownShipSym[1].Y += (INT)y2;
		ownShipSym[2].X += (INT)x2;
		ownShipSym[2].Y += (INT)y2;

		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[1]);
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[2]);
	}
#endif
}

void CGISViewerView::DrawOwnShip(CDC* pDC, bool isMoveDraw, GeoPoint* ptWp, RT::BufLeg* rightBufLeg, RT::BufLeg* leftBufLeg,
	bool* isRight, double* startOffset, double* endOffset, double buffDistance, int waypointCount)
{
#ifdef ROUTE_CHECK 
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
	int ownShipIndex = slider->GetPos();

	int currentRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (currentRouteIndex < 0)
	{
		EndWaitCursor();
		return;
	}

	RT::Route* route = pRoutePlanner->GetRoute(currentRouteIndex);

	if (!route) {
		EndWaitCursor();
		return;
	}

	if (route->GetLegCount() < 1)
	{
		EndWaitCursor();
		return;
	}

	time_t departTime = route->GetDepartureTime();
	time_t currentTime = departTime + ownShipIndex;



	time_t nextTime = currentTime + 1;
	double x = 0, xn = 0;
	double y = 0, yn = 0;
	double s = 0, sn = 0;
	route->GetPosSpeedAtTime(currentTime, x, y, s);
	route->GetPosSpeedAtTime(nextTime, xn, yn, sn);

	int legIndex = route->GetLegIndexAtTime(currentTime);
	if ((legIndex == 0) && (legIndex == (waypointCount - 2))) {

	}
	else if (legIndex == 0) {
		double ownX = x;
		double ownY = y;
		LatLonUtility::InverseProjectionToDegree(ownX, ownY);

		double legDistance = route->GetDistanceLeg(legIndex);
		double ownShipOffset = GetDistanceRhumbLineMercator(ownY, ownX, ptWp[legIndex].y, ptWp[legIndex].x, false);

		double theta = 0;
		double heading = 0;

		double xOnCircle = 0;
		double yOnCircle = 0;

		double xCenter = 0;
		double yCenter = 0;

		if (ownShipOffset > (legDistance - endOffset[legIndex])) {
			if (isRight[legIndex]) {
				xCenter = rightBufLeg[legIndex].ptEnd.x;
				yCenter = rightBufLeg[legIndex].ptEnd.y;
				heading = 90;
			}
			else {
				xCenter = leftBufLeg[legIndex].ptEnd.x;
				yCenter = leftBufLeg[legIndex].ptEnd.y;
				heading = -90;
			}

			LatLonUtility::InverseProjectionToDegree(xCenter, yCenter);

			theta = GetBearingGreatCircle(yCenter, xCenter, ownY, ownX, false);
			heading += theta;

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(yCenter, xCenter, theta, buffDistance, false);

			long sx = 0;
			long sy = 0;

			LatLonUtility::ProjectionFromDegree(pos.lon, pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &sx, &sy);

			DrawOwnShip(pDC, isMoveDraw, sx, sy, heading, false);

			return;
		}
	}
	else if (legIndex == (waypointCount - 2)) {
		double ownX = x;
		double ownY = y;
		LatLonUtility::InverseProjectionToDegree(ownX, ownY);
		double legDistance = route->GetDistanceLeg(legIndex);
		double ownShipOffset = GetDistanceRhumbLineMercator(ownY, ownX, ptWp[legIndex].y, ptWp[legIndex].x, false);

		double theta = 0;
		double heading = 0;

		double xOnCircle = 0;
		double yOnCircle = 0;

		double xCenter = 0;
		double yCenter = 0;

		if (ownShipOffset < (startOffset[legIndex])) {
			if (isRight[legIndex - 1]) {
				xCenter = rightBufLeg[legIndex].ptStart.x;
				yCenter = rightBufLeg[legIndex].ptStart.y;
				heading = 90;
			}
			else {
				xCenter = leftBufLeg[legIndex].ptStart.x;
				yCenter = leftBufLeg[legIndex].ptStart.y;
				heading = -90;
			}

			LatLonUtility::InverseProjectionToDegree(xCenter, yCenter);

			theta = GetBearingGreatCircle(yCenter, xCenter, ownY, ownX, false);
			heading += theta;

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(yCenter, xCenter, theta, buffDistance, false);

			long sx = 0;
			long sy = 0;

			LatLonUtility::ProjectionFromDegree(pos.lon, pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &sx, &sy);

			DrawOwnShip(pDC, isMoveDraw, sx, sy, heading, false);

			return;
		}
	}
	else {
		double ownX = x;
		double ownY = y;
		LatLonUtility::InverseProjectionToDegree(ownX, ownY);
		double legDistance = route->GetDistanceLeg(legIndex);
		double ownShipOffset = GetDistanceRhumbLineMercator(ownY, ownX, ptWp[legIndex].y, ptWp[legIndex].x, false);

		double theta = 0;
		double heading = 0;

		double xOnCircle = 0;
		double yOnCircle = 0;

		double xCenter = 0;
		double yCenter = 0;

		if (ownShipOffset < (startOffset[legIndex])) {
			if (isRight[legIndex - 1]) {
				xCenter = rightBufLeg[legIndex].ptStart.x;
				yCenter = rightBufLeg[legIndex].ptStart.y;
				heading = 90;
			}
			else {
				xCenter = leftBufLeg[legIndex].ptStart.x;
				yCenter = leftBufLeg[legIndex].ptStart.y;
				heading = -90;
			}

			LatLonUtility::InverseProjectionToDegree(xCenter, yCenter);

			theta = GetBearingGreatCircle(yCenter, xCenter, ownY, ownX, false);
			heading += theta;

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(yCenter, xCenter, theta, buffDistance, false);

			long sx = 0;
			long sy = 0;

			LatLonUtility::ProjectionFromDegree(pos.lon, pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &sx, &sy);

			DrawOwnShip(pDC, isMoveDraw, sx, sy, heading, false);

			return;
		}
		else if (ownShipOffset > (legDistance - endOffset[legIndex])) {
			if (isRight[legIndex]) {
				xCenter = rightBufLeg[legIndex].ptEnd.x;
				yCenter = rightBufLeg[legIndex].ptEnd.y;
				heading = 90;
			}
			else {
				xCenter = leftBufLeg[legIndex].ptEnd.x;
				yCenter = leftBufLeg[legIndex].ptEnd.y;
				heading = -90;
			}

			LatLonUtility::InverseProjectionToDegree(xCenter, yCenter);

			theta = GetBearingGreatCircle(yCenter, xCenter, ownY, ownX, false);
			heading += theta;

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(yCenter, xCenter, theta, buffDistance, false);

			long sx = 0;
			long sy = 0;

			LatLonUtility::ProjectionFromDegree(pos.lon, pos.lat);
			m_pGisLib->WorldToDevice(pos.lon, pos.lat, &sx, &sy);

			DrawOwnShip(pDC, isMoveDraw, sx, sy, heading, false);

			return;
		}
	}


	long sx = 0;
	long sy = 0;
	m_pGisLib->WorldToDevice(x, y, &sx, &sy);

	m_pGisLib->InverseProjection(&x, &y);
	m_pGisLib->InverseProjection(&xn, &yn);

	double heading = GetBearingRhubmLineMercator(y, x, yn, xn, false);

	DrawOwnShip(pDC, isMoveDraw, sx, sy, heading, false);
#endif
}


void CGISViewerView::DrawOwnShip(CDC* pDC, bool isMoveDraw, int _x, int _y, double _heading, bool _radian)
{
	if (isMoveDraw) {
		_x += (m_ep.x - m_sp.x);
		_y += (m_ep.y - m_sp.y);
	}

	m_pSymbolManager->DrawSymbol(_T("OWNSHP02"), pDC, CPoint(_x, _y));

	if (!_radian) {
		_heading *= DEG2RAD;
	}

	{
		int d = 70;  
		double h = _heading;
		double yd = -(d * cos(h));
		double xd = d * sin(h);

		long x1 = _x;
		long y1 = _y;
		long x2 = 0;
		long y2 = 0;

		x2 = (long)(x1 + xd);
		y2 = (long)(y1 + yd);

		Gdiplus::Point ownShipSym[3];

		ownShipSym[0].X = (INT)(ownShipVector[0].X * cos(h) - ownShipVector[0].Y * sin(h));
		ownShipSym[0].Y = (INT)(ownShipVector[0].X * sin(h) + ownShipVector[0].Y * cos(h));

		ownShipSym[1].X = (INT)(ownShipVector[1].X * cos(h) - ownShipVector[1].Y * sin(h));
		ownShipSym[1].Y = (INT)(ownShipVector[1].X * sin(h) + ownShipVector[1].Y * cos(h));

		ownShipSym[2].X = (INT)(ownShipVector[2].X * cos(h) - ownShipVector[2].Y * sin(h));
		ownShipSym[2].Y = (INT)(ownShipVector[2].X * sin(h) + ownShipVector[2].Y * cos(h));

		ownShipSym[0].X += (INT)x2;
		ownShipSym[0].Y += (INT)y2;
		ownShipSym[1].X += (INT)x2;
		ownShipSym[1].Y += (INT)y2;
		ownShipSym[2].X += (INT)x2;
		ownShipSym[2].Y += (INT)y2;

		CPen newPen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen *oldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);

		pDC->SelectObject(oldPen);
		Graphics _g(pDC->GetSafeHdc());
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[1]);
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[2]);

		ownShipSym[0].X = (INT)(ownShipVector[0].X * cos(h) - (ownShipVector[0].Y + 10) * sin(h));
		ownShipSym[0].Y = (INT)(ownShipVector[0].X * sin(h) + (ownShipVector[0].Y + 10) * cos(h));

		ownShipSym[1].X = (INT)(ownShipVector[1].X * cos(h) - (ownShipVector[1].Y + 10) * sin(h));
		ownShipSym[1].Y = (INT)(ownShipVector[1].X * sin(h) + (ownShipVector[1].Y + 10) * cos(h));

		ownShipSym[2].X = (INT)(ownShipVector[2].X * cos(h) - (ownShipVector[2].Y + 10) * sin(h));
		ownShipSym[2].Y = (INT)(ownShipVector[2].X * sin(h) + (ownShipVector[2].Y + 10) * cos(h));

		ownShipSym[0].X += (INT)x2;
		ownShipSym[0].Y += (INT)y2;
		ownShipSym[1].X += (INT)x2;
		ownShipSym[1].Y += (INT)y2;
		ownShipSym[2].X += (INT)x2;
		ownShipSym[2].Y += (INT)y2;

		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[1]);
		_g.SetSmoothingMode(SmoothingModeAntiAlias);
		_g.DrawLine(&Pen(Color(0, 0, 0), 2), ownShipSym[0], ownShipSym[2]);
	}
}


void CGISViewerView::OnButtonRouteCheck()
{
	BeginWaitCursor();
#ifdef ROUTE_CHECK
	m_pDockablePaneRoutePlan->pDlg->wpWarning.clear(); 
	delete pRoutePlannerForCheck;
	pRoutePlannerForCheck = nullptr;

	int currentRouteIndex = m_pDockablePaneRoutePlan->pDlg->GetCurrentRouteIndex();

	if (currentRouteIndex < 0)
	{
		AfxMessageBox(_T("검사할 항로가 없습니다."));
		EndWaitCursor();
		return;
	}

	std::time_t departTime;
	pRoutePlanner->GetDepartureTime(currentRouteIndex, &departTime);
	pRoutePlannerForCheck = new RT::RoutePlanner();
	pRoutePlannerForCheck->AddRoute(L"temp", departTime);

	bool res = false;

	double x = 0;
	double y = 0;
	double speed = 0;

	std::time_t arrivalTime;
	int wpCnt = pRoutePlanner->GetWaypointCount(currentRouteIndex);
	for (int i = 0; i < wpCnt - 1; i++)
	{
		double tmpX = pRoutePlanner->GetX(currentRouteIndex, i);
		double tmpY = pRoutePlanner->GetY(currentRouteIndex, i);

		m_pGisLib->InverseProjection(&tmpX, &tmpY);

		pRoutePlannerForCheck->AddWaypoint(0,
			tmpX,
			tmpY,
			pRoutePlanner->GetSpeed(currentRouteIndex, i),
			pRoutePlanner->GetSpeed(currentRouteIndex, i));

		arrivalTime = pRoutePlanner->GetArrivalTime(currentRouteIndex, i);
		arrivalTime += 10;

		while (arrivalTime < pRoutePlanner->GetArrivalTime(currentRouteIndex, i + 1))
		{
			if (pRoutePlanner->GetRoute(currentRouteIndex)->GetPosSpeedAtTime(arrivalTime, x, y, speed)) {
				tmpX = x;
				tmpY = y;
				m_pGisLib->InverseProjection(&tmpX, &tmpY);
				pRoutePlannerForCheck->AddWaypoint(0, tmpX, tmpY, speed, speed);
			}
			arrivalTime += 10;
		}
	}

	double tmpX = pRoutePlanner->GetX(currentRouteIndex, wpCnt - 1);
	double tmpY = pRoutePlanner->GetY(currentRouteIndex, wpCnt - 1);

	m_pGisLib->InverseProjection(&tmpX, &tmpY);

	pRoutePlannerForCheck->AddWaypoint(0,
		tmpX,
		tmpY,
		pRoutePlanner->GetSpeed(currentRouteIndex, wpCnt - 1),
		pRoutePlanner->GetSpeed(currentRouteIndex, wpCnt - 1));  
	ENC_ExchangeSet* exSet = m_pGisLib->GetExchangeSet();

	std::list<std::wstring> tempNameList;

	for (unsigned ri = 0; ri < pRoutePlannerForCheck->GetWaypointCount(0); ri++)
	{
		double wpX = pRoutePlannerForCheck->GetX(0, ri);
		double wpY = pRoutePlannerForCheck->GetY(0, ri); 
		bool end = false;
		for (int i = 5; (i >= 0) && (end == false); i--)
		{
			CatalogueList::iterator iter;

			for (iter = exSet->m_catListByLevel[i].begin(); iter != exSet->m_catListByLevel[i].end(); iter++)
			{
				ENC_Catalogue* encCat = *iter;

				if (encCat->m_mbr.PtInMBR(wpX, wpY))
				{
					tempNameList.push_back(encCat->m_filePath.GetString());
					end = true;
					break;
				}
			}
		}
	}

	tempNameList.unique();

	for (std::list<std::wstring>::iterator i = tempNameList.begin(); i != tempNameList.end(); i++)
	{
		m_pGisLib->m_pRCLayerManager->AddLayer((*i).c_str());
	}

	delete pRoutePlannerForCheckResult;

	pRoutePlannerForCheckResult = new RT::RoutePlanner();
	pRoutePlannerForCheckResult->AddRoute(L"temp", departTime); 
	for (unsigned i = 0; i < pRoutePlannerForCheck->GetWaypointCount(0); i++)
	{
		bool find = false;
		double wpX = pRoutePlannerForCheck->GetX(0, i);
		double wpY = pRoutePlannerForCheck->GetY(0, i); 
		for (int j = 0; (j < m_pGisLib->m_pRCLayerManager->GetLayerCount()) && (find == false); j++)
		{
			Layer* layer = m_pGisLib->m_pRCLayerManager->GetLayer(j);

			if (layer->m_mbr.PtInMBR(wpX, wpY))
			{ 
				for (std::list<ENC_Feature*>::iterator it = ((ENCCell*)(layer->m_spatialObject))->m_DEPARE.begin();
					(it != ((ENCCell*)(layer->m_spatialObject))->m_DEPARE.end()) && (find == false);
					it++)
				{
					ENC_Feature* ff = *it;

					if (ff->m_frid.PRIM != 3)
						continue;

					if (GeometricFuc::inside(wpX, wpY, (ENCArea*)(*it)->m_geometry) == 1)
					{
						pRoutePlannerForCheck->GetWaypoint(0, i)->m_feature = (RT::ENC_Feature*)*it;

						double nDRVAL1 = 0;
						double nDRVAL2 = 0;

						CString wVal1;
						CString wVal2;

						for (LISTATTF::iterator itor = (*it)->m_attfList.begin();
							itor != (*it)->m_attfList.end();
							itor++)
						{ 
							if ((*itor)->ATTL == 87)
							{
								nDRVAL1 = stod((*itor)->ATVL);
								wVal1.Format(_T("%lf"), nDRVAL1);
							} 
							else if ((*itor)->ATTL == 88)
							{
								nDRVAL2 = stod((*itor)->ATVL);
								wVal2.Format(_T("%lf"), nDRVAL2);
							}
						}

						if ((ENCCommon::SAFETY_CONTOUR > nDRVAL1) || (ENCCommon::SAFETY_CONTOUR > nDRVAL2))
						{ 
							time_t arrivalTime = pRoutePlannerForCheck->GetArrivalTime(0, i);
							int indexDanger = pRoutePlanner->GetDangerWaypointIndex(0, arrivalTime);
							m_pDockablePaneRoutePlan->pDlg->wpWarning.push_back(indexDanger); 

							tmpX = pRoutePlannerForCheck->GetX(0, i);
							tmpY = pRoutePlannerForCheck->GetY(0, i);

							m_pGisLib->InverseProjection(&tmpX, &tmpY);

							pRoutePlannerForCheckResult->AddWaypoint(0,
								tmpX,
								tmpY,
								pRoutePlannerForCheck->GetSpeed(0, i),
								pRoutePlannerForCheck->GetSpeed(0, i));

							CString strOutputLine(_T("Warning! : "));

							double DX = 0;
							double MX = 0;
							double SX = 0;

							double DY = 0;
							double MY = 0;
							double SY = 0;

							double degWpX = wpX;
							double degWpY = wpY;

							m_pGisLib->InverseProjection(&degWpX, &degWpY);

							DegreeToDMS(degWpX, DX, MX, SX);
							DegreeToDMS(degWpY, DY, MY, SY);

							CString lat;
							lat.Format(_T("%d°%d'%lf\""), (int)DY, (int)MY, SY);

							if (DY >= 0)
							{
								lat.Append(_T("N "));
							}
							else
							{
								lat.Append(_T("S "));
							}

							CString lon;
							lon.Format(_T("%d°%d'%lf\""), (int)DX, (int)MX, SX);

							if (DX >= 0)
							{
								lon.Append(_T("E "));
							}
							else
							{
								lon.Append(_T("W "));
							}

							CString strDRVAL1;
							strDRVAL1.Format(_T("%d"), nDRVAL1);
							strDRVAL1 = wVal1;

							CString strDRVAL2;
							strDRVAL2.Format(_T("%d"), nDRVAL2);
							strDRVAL2 = wVal2;
							CString strSafetyContour;
							strSafetyContour.Format(_T("%d"), (int)ENCCommon::SAFETY_CONTOUR);

							strOutputLine.Append(_T("Safety Contour("));
							strOutputLine.Append(strSafetyContour);
							strOutputLine.Append(_T("m) "));
							strOutputLine.Append(_T("DRVAL1("));
							strOutputLine.Append(strDRVAL1);
							strOutputLine.Append(_T("m) "));
							strOutputLine.Append(_T("DRVAL2("));
							strOutputLine.Append(strDRVAL2);
							strOutputLine.Append(_T("m)"));
							strOutputLine.Append(layer->GetLayerName());
							strOutputLine.Append(_T("\n"));

							OutputDebugString(strOutputLine);
						}

						find = true;
					}
				}

				for (std::list<ENC_Feature*>::iterator it = ((ENCCell*)(layer->m_spatialObject))->m_LNDARE.begin();
					(it != ((ENCCell*)(layer->m_spatialObject))->m_LNDARE.end()) && (find == false);
					it++) {
					ENC_Feature* ff = *it;

					if (ff->m_frid.PRIM != 3)
						continue;

					if (GeometricFuc::inside(wpX, wpY, (ENCArea*)(*it)->m_geometry) == 1) { 
						time_t arrivalTime = pRoutePlannerForCheck->GetArrivalTime(0, i);
						int indexDanger = pRoutePlanner->GetDangerWaypointIndex(0, arrivalTime);
						m_pDockablePaneRoutePlan->pDlg->wpWarning.push_back(indexDanger); 
					}
				}
			}
		}
	}

	int resultWpCnt = pRoutePlannerForCheck->GetWaypointCount(0);
	if (resultWpCnt > 0)
	{
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
		slider->SetRange(0, resultWpCnt - 1);
		m_bRouteCheckOwnShip = true;
	}
	else
	{
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_SLIDER_ROUTE);
		slider->SetRange(0, 0);
		m_bRouteCheckOwnShip = false;
	}
#endif
	EndWaitCursor();
	m_pDockablePaneRoutePlan->pDlg->UpdateWaypointList();

	if (m_pDockablePaneRoutePlan->pDlg->wpWarning.size() > 0) {
		AfxMessageBox(_T("위험한 항로입니다.\n항로 목록의 붉게 변한 변침점을 수정해 주세요."));
	}
	else {
		AfxMessageBox(_T("항로 검사를 마쳤습니다.\n수정할 부분이 없습니다."));
	}
}

void CGISViewerView::EndOfEditing()
{
	if (m_pEditingContent == nullptr)
	{
		return;
	}


	if (m_pEditingContent->workingList.size() > 0)
	{
		int ret = AfxMessageBox(L"수정 사항을 적용하시겠습니까?", MB_OKCANCEL);

		if (ret == IDOK)
		{
			m_pEditingContent->Apply();
			MapRefresh();
		}
		else
		{
			m_pEditingContent->Cancel();
		}
	}
	g_editInnerCircle = 0;
}

void CGISViewerView::OnButtonScaledSymbolSize()
{ 

	MapRefresh();
}

void CGISViewerView::OnUpdateButtonScaledSymbolSize(CCmdUI *pCmdUI)
{        
}

void CGISViewerView::OnButtonApplyDataCoverageScale()
{
	ENCCommon::APPLY_DATA_COVERAGE_SCALE = !ENCCommon::APPLY_DATA_COVERAGE_SCALE;

	m_pGisLib->CheckDataCoverageComputing();

	MapRefresh();
}

void CGISViewerView::OnUpdateButtonApplyDataCoverageScale(CCmdUI *pCmdUI)
{
	if (ENCCommon::APPLY_DATA_COVERAGE_SCALE)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnButtonEditMouseVector()
{
	if (m_pEditingContent == nullptr)
	{
		return;
	}

	if (m_Icon == EDIT_VECTOR)
	{
		EndOfEditing();
		m_Icon = MOVE;
		Invalidate();
	}
	else
	{
		m_Icon = EDIT_VECTOR;
		Invalidate();
	}
}

void CGISViewerView::OnUpdateButtonEditMouseVector(CCmdUI *pCmdUI)
{
	if (m_Icon == EDIT_VECTOR)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CGISViewerView::OnButtonEditAraeInnerCircle()
{
	if (m_Icon == FEATURE_ADD_INNER_AREA)
	{
		m_Icon = MOVE;
	}
	else
	{
		if (frPick)
		{
			if (frPick->m_geometry->type == 3) 
			{
				if (theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem >= m_pGisLib->GetLayerCount() || theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem == -1)
				{
				}
				else
				{
					Layer *l = (Layer*)m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
					if (l == NULL)
						return;
					m_pNewFeatureManager->m_cell = (S101Cell*)l->m_spatialObject;
				}

				S101Cell* cell = (S101Cell*)m_pNewFeatureManager->m_cell;

				m_pNewFeatureManager->m_geometryType = frPick->m_geometry->type;


				int code = frPick->m_frid.m_nftc;
				auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);

				m_pNewFeatureManager->m_pWorkFeatureRecord = frPick;

				m_Icon = FEATURE_ADD_INNER_AREA;
			}
		}
	}
}

void CGISViewerView::OnUpdateButtonEditAraeInnerCircle(CCmdUI *pCmdUI)
{
	if (m_Icon == FEATURE_ADD_INNER_AREA)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnButtonS111IndexUp()
{
	if (0 < m_pGisLib->GetLayerManager()->m_surfaceCurrentIndex)
		m_pGisLib->GetLayerManager()->m_surfaceCurrentIndex++;

	m_pGisLib->PrevTimeIndex();
	m_pGisLib->S101RebuildPortrayal();
	MapRefresh();
}


void CGISViewerView::OnButtonS111IndexDn()
{
	m_pGisLib->GetLayerManager()->m_surfaceCurrentIndex++;


	m_pGisLib->NextTimeIndex();
	m_pGisLib->S101RebuildPortrayal();
	MapRefresh();
}


void CGISViewerView::OnButtonZoomArea()
{
	(m_Icon == ZOOM_AREA) ? m_Icon = MOVE : m_Icon = ZOOM_AREA;
}


void CGISViewerView::OnUpdateButtonZoomArea(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Icon == ZOOM_AREA);
}

void CGISViewerView::DrawZoomArea(CDC* pDC)
{
	if (!m_bZoomArea)
	{
		return;
	}


	CRect rect;

	if (m_ptStartZoomArea.x < m_ptEndZoomArea.x)
	{
		rect.left = m_ptStartZoomArea.x;
		rect.right = m_ptEndZoomArea.x;
	}
	else
	{
		rect.left = m_ptEndZoomArea.x;
		rect.right = m_ptStartZoomArea.x;
	}

	if (m_ptStartZoomArea.y < m_ptEndZoomArea.y)
	{
		rect.top = m_ptStartZoomArea.y;
		rect.bottom = m_ptEndZoomArea.y;
	}
	else
	{
		rect.top = m_ptEndZoomArea.y;
		rect.bottom = m_ptStartZoomArea.y;
	}

	CPen newPen;
	CBrush newBrush;
	newPen.CreatePen(PS_DASH, 1, RGB(255, 51, 51));
	newBrush.CreateStockObject(NULL_BRUSH);

	CPen *oldPen = pDC->SelectObject(&newPen);
	CBrush *oldBrush = pDC->SelectObject(&newBrush);

	pDC->Rectangle(rect);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CGISViewerView::OnBtnLayerFeatureSearch()
{
	if (theApp.m_pDialogCellFeatureList == NULL)
	{
		theApp.m_pDialogCellFeatureList = new CDialogCellFeatureList();
		theApp.m_pDialogCellFeatureList->Create(IDD_DIALOG_LIST_FEATURE);

	}
	else
	{

	}
	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
	theApp.m_pDialogCellFeatureList->SetLayer(l);

	CRect r;
	GetClientRect(&r);

	theApp.m_pDialogCellFeatureList->MoveWindow(200, 100, 250, r.Height() - 100);
	theApp.m_pDialogCellFeatureList->ShowWindow(SW_SHOW);
}




void CGISViewerView::OnBtnShowLayoutLayerManager()
{
	if (theApp.m_pDockablePaneLayerManager.IsVisible())
	{
		theApp.m_pDockablePaneLayerManager.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_pDockablePaneLayerManager.ShowPane(TRUE, FALSE, FALSE);
	}
}

void CGISViewerView::OnBtnShowLayoutCurrentSelection()
{
	if (theApp.m_DockablePaneCurrentSelection.IsVisible())
	{
		theApp.m_DockablePaneCurrentSelection.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_DockablePaneCurrentSelection.ShowPane(TRUE, FALSE, FALSE);
	}
}


void CGISViewerView::OnBtnShowLayoutAttributeList()
{
	if (theApp.m_DockablePaneAttributeList.IsVisible())
	{
		theApp.m_DockablePaneAttributeList.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_DockablePaneAttributeList.ShowPane(TRUE, FALSE, FALSE);
	}
}


void CGISViewerView::OnBtnShowLayoutFeatureInformation()
{
	if (theApp.m_DockablePaneEditWindow.IsVisible())
	{
		theApp.m_DockablePaneEditWindow.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_DockablePaneEditWindow.ShowPane(TRUE, FALSE, FALSE);
	}
}

void CGISViewerView::OnBtnShowLayoutRelation()
{
	if (theApp.m_DockablePaneRelation.IsVisible())
	{
		theApp.m_DockablePaneRelation.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_DockablePaneRelation.ShowPane(TRUE, FALSE, FALSE);
	}
}

void CGISViewerView::OnBtnShowLayoutLogger()
{
	if (theApp.m_DockablePaneLogger.IsVisible())
	{
		theApp.m_DockablePaneLogger.ShowPane(FALSE, FALSE, FALSE);
	}
	else {
		theApp.m_DockablePaneLogger.ShowPane(TRUE, FALSE, FALSE);
	}
} 
void CGISViewerView::OnBtnLayerShowYourMessage()
{
	DialogExShowYourMessage dlg;
	CString msgMessage;
	CString msgCategory;
	CString msgOption;
	CString msgAgreement1;
	CString msgCheckListStr;


	if (IDOK == dlg.DoModal())
	{
		msgMessage.Format(_T("%s"), dlg.m_message); 
		msgCategory.Format(_T("%s"), dlg.m_category);
		msgOption.Format(_T("%s"), dlg.m_option);
		msgAgreement1.Format(_T("%d"), dlg.m_radioAgreement1);
		msgCheckListStr.Format(_T("%s"), dlg.m_checkListStr);

		AfxMessageBox(msgCategory + "\n" + msgMessage + "\n" + msgOption + "\n" + msgAgreement1 + "\n" + msgCheckListStr, MB_OK);
	}
}

void CGISViewerView::OnBtnSelectFilter()
{
	S101Layer *l = (S101Layer*)m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
	if (!l)	return;

	CDialogExSelectFilter dlg;
	std::unordered_map<std::wstring, R_FeatureRecord*> featureHash; 
	S101Cell *cell = (S101Cell*)l->m_spatialObject;
	dlg.m_cell = cell;

	if (IDOK == dlg.DoModal()) {

		theApp.m_DockablePaneCurrentSelection.RemoveAll();

		featureHash.clear();
		CStringArray csa;
		csa.SetSize(1000);
		BOOL isCtrl = true;
		CString isCtrlClicked;
		isCtrlClicked = isCtrl ? "1" : "0";
		POSITION pos = cell->m_feaMap.GetStartPosition(); 
		while (pos != NULL)
		{
			__int64 key = 0;
			R_FeatureRecord* fr = NULL;
			cell->m_feaMap.GetNextAssoc(pos, key, fr);

			int code = fr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code); 
			if (itor->second->m_code == dlg.m_feature) {

				for (auto itorAttr = fr->m_attr.begin(); itorAttr != fr->m_attr.end(); itorAttr++)
				{
					F_ATTR *attr = *itorAttr;
					for (auto aitor = attr->m_arr.begin(); aitor != attr->m_arr.end(); aitor++)
					{
						ATTR* attr1 = *aitor;

						CString natc;
						CString atvl;
						CString realValue;
						string * tok;
						natc.Format(_T("%d"), attr1->m_natc);
						atvl = attr1->m_atvl; 
						if (dlg.m_enumValueYn) {
							std::string str1 = std::string(CT2CA(dlg.m_value.operator LPCWSTR()));
							char toks[4] = { "___" };
							tok = StringSplit(str1, toks);
							realValue = CString::CStringT(CA2CT(tok[1].c_str()));
						}
						else {
							realValue = dlg.m_value;
						} 
						int nNum = _ttoi(realValue);
						BOOL isValueNum = true; 
						if (nNum == 0 && realValue != L"0") {
							isValueNum = false;
						} 
						if (natc == dlg.m_attributeCode)
						{

							wstring frida = std::to_wstring(fr->m_frid.m_name.RCID);   
							if (dlg.m_operator == L">" && isValueNum) {

								if (_ttoi(atvl) > _ttoi(realValue)) {
									featureHash.insert(std::unordered_map<wstring, R_FeatureRecord*>::value_type(frida, fr));
								}

							} 
							else if (dlg.m_operator == L">=" && isValueNum) {

								if (_ttoi(atvl) >= _ttoi(realValue) || _ttoi(atvl) == _ttoi(realValue)) {
									featureHash.insert(std::unordered_map<wstring, R_FeatureRecord*>::value_type(frida, fr));
								}

							} 
							else if (dlg.m_operator == L"=") { 
								if (atvl == realValue || realValue.CompareNoCase(atvl) == 0) {
									featureHash.insert(std::unordered_map<wstring, R_FeatureRecord*>::value_type(frida, fr));
								}

							} 
							else if (dlg.m_operator == L"<" && isValueNum) {

								if (_ttoi(atvl) < _ttoi(realValue)) {
									featureHash.insert(std::unordered_map<wstring, R_FeatureRecord*>::value_type(frida, fr));
								}

							} 
							else if (dlg.m_operator == L"<=" && isValueNum) {

								if (_ttoi(atvl) <= _ttoi(realValue) || _ttoi(atvl) == _ttoi(realValue)) {
									featureHash.insert(std::unordered_map<wstring, R_FeatureRecord*>::value_type(frida, fr));
								}

							}

						}

					}

				}

			}
		}

		for (auto it = featureHash.begin(); it != featureHash.end(); it++)
		{
			R_FeatureRecord *rfr = it->second; 
			int code = rfr->m_frid.m_nftc;
			auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);

			CString csFrid, csFoid, csLat, csLon, csType, csName, csAssoCnt;
			CString featureType = L"Feature";

			double lat;
			double lon;

			if (rfr->m_geometry->type == 1) {
				SPoint* sr = (SPoint*)rfr->m_geometry;
				lat = sr->m_point.x;
				lon = sr->m_point.y;

				m_pGisLib->InverseProjection(&lat, &lon);
				csType.Format(_T("%d"), sr->type);
			}
			else if (rfr->m_geometry->type == 2) {
				SCompositeCurve* sr = (SCompositeCurve*)rfr->m_geometry;
				if (sr->m_listCurveLink.size() > 0)
				{
					lat = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].x;
					lon = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].y;
				}
				m_pGisLib->InverseProjection(&lat, &lon);
				csType.Format(_T("%d"), sr->type);
			}
			else if (rfr->m_geometry->type == 3) {
				SSurface* sr = (SSurface*)rfr->m_geometry;
				lat = sr->m_pPoints[0].x;
				lon = sr->m_pPoints[0].y;
				m_pGisLib->InverseProjection(&lat, &lon);
				csType.Format(_T("%d"), sr->type);
			}
			else if (rfr->m_geometry->type == 4) {
				double geoX = ((ENCSounding*)rfr->m_geometry)->m_pPoints[0].x;
				double geoY = ((ENCSounding*)rfr->m_geometry)->m_pPoints[0].y;
				SMultiPoint* sr = (SMultiPoint*)rfr->m_geometry;
				m_pGisLib->InverseProjection(&geoX, &geoY);
				csType.Format(_T("%d"), sr->type);
			}

			vector<int>::size_type assoCnt;
			assoCnt = rfr->m_fasc.size() + rfr->m_inas.size();

			csFrid.Format(_T("%d"), rfr->m_frid.m_name.RCID);
			csFoid.Format(_T("%d"), rfr->m_foid.m_objName.m_fidn);
			csLat.Format(_T("%f"), lat);
			csLon.Format(_T("%f"), lon);
			csName.Format(_T("%s"), itor->second->m_code);
			csAssoCnt.Format(_T("%d"), assoCnt);
			csa.Add(isCtrlClicked + _T("|||") + csFoid + _T("|||") + csFrid + _T("|||") + csLat + _T("|||") + csLon + _T("|||") + csType + _T("|||") + csName + _T("|||") + csAssoCnt + _T("|||") + featureType); 
		}

		Invalidate();
		theApp.m_DockablePaneCurrentSelection.UpdateListTest(&csa, cell, isCtrlClicked);
	}
}

void CGISViewerView::OnBtnCreateNoGeometry()
{
	CDialogExCreateNoGeometry dlg;

	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
	if (!l)
		return;

	dlg.SetNoGeometryFeatureList((S101Cell*)l->m_spatialObject); 
	if (IDOK == dlg.DoModal())
	{

	}
}

void CGISViewerView::OnBtnCreateInformationFeature()
{
	auto selectedLayerIndex = theApp.m_pDockablePaneLayerManager.pDlg->GetSafeSelectedIndex();

	CDialogExCreateInformationFeature dlg;
	Layer* l = m_pGisLib->GetLayer(selectedLayerIndex);
	if (!l)
	{
		return;
	}

	dlg.SetInformationFeatureList((S101Cell*)l->m_spatialObject);
	dlg.DoModal();
}


void CGISViewerView::OnBtnCreateAutoRelation()
{
	CDialogExCreateAutoRelation dlg;

	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
	if (!l)
	{
		return;
	}

	dlg.SetNoGeometryFeatureList((S101Cell*)l->m_spatialObject); 
	if (IDOK == dlg.DoModal())
	{

	}
}


void CGISViewerView::OnBtnCreateSoundingByXyzFile()
{
	CFileDialog dlg(TRUE, L"../ProgramData/SampleData/xyz_test/", NULL, OFN_READONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("Usable Files(*.xyz)|*.xyz|"), NULL);

	CString strFileList;

	const int c_cMaxFiles = 400 ; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;) 
		{ 

			CString filePath = dlg.GetNextPathName(pos);//경로+파일명

			Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);
			if (!l)
				return;

			S101Cell* c = (S101Cell*)l->m_spatialObject;

			R_FeatureRecord* soundingFeature = ENC_S101_Factory::CreateSoundingFeatureByXyzFile(c, filePath.GetBuffer());
			filePath.ReleaseBuffer();

			if(soundingFeature)
			{
				c->MakeSoundingData(soundingFeature);			
			}

			m_pGisLib->BuildS101Portrayal(l);

			MapRefresh();
		}
	}
}


void CGISViewerView::OnBtnRelationListAll()
{ 
}


void CGISViewerView::EditLButtonDown(CPoint p)
{
	if (m_pEditingContent->MouseButtonDown(p.x, p.y, m_pGisLib))
	{
		theApp.m_DockablePaneEditWindow.SelectMultiData(m_pEditingContent->curVector);
	}
}

void CGISViewerView::EditMouseMove(UINT nFlags, CPoint p)
{
	if (m_pEditingContent && nFlags & MK_LBUTTON)
	{
		int compX = m_pEditingContent->pWorkSheet->m_dsgir.m_dssi.m_cmfx;
		int compY = m_pEditingContent->pWorkSheet->m_dsgir.m_dssi.m_cmfy;
		double dx = 0, dy = 0;
		int cx = 0;
		int cy = 0;

		long x, y;

		if (m_bEditUseExistingVector)
		{
			double shortestDistance = 145;
			for (auto itor = snapEditPoint.begin(); itor != snapEditPoint.end(); itor++)
			{
				EditPoint* ep = &(*itor);

				m_pGisLib->WorldToDevice(ep->x, ep->y, &x, &y);

				double distance = (x - m_ptCurrent.x) * (x - m_ptCurrent.x) + (y - m_ptCurrent.y)*(y - m_ptCurrent.y);

				if (shortestDistance > distance)
				{
					shortestDistance = distance;   
					p.x = x;
					p.y = y;
				}
			}

			if (shortestDistance == 145)
			{
				p.x = m_ptCurrent.x;
				p.y = m_ptCurrent.y;
			}
		}
		else
		{
			p.x = m_ptCurrent.x;
			p.y = m_ptCurrent.y;
		}

		m_pGisLib->DeviceToWorld(p.x, p.y, &dx, &dy);
		m_pGisLib->InverseProjection(&dx, &dy);

		cx = (int)(dx * compX);
		cy = (int)(dy * compY);

		if (m_pEditingContent->MouseMove(cx, cy))
		{
			theApp.m_DockablePaneEditWindow.MoveVectorToPoint(cx, cy);
			Invalidate();
		}
		else
		{
			if (abs(m_sp.x - m_ep.x) + abs(m_sp.y - m_ep.y) > 3)
			{
				isMoved = true;
			}

			m_bMoveStart = TRUE;
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_GRAB));
			Invalidate();
		}
	}
}

void CGISViewerView::EditLButtonUp(CPoint p)
{
	m_pEditingContent->LButtonUp(p.x, p.y);
}


void CGISViewerView::OnButtonEditUndo()
{
	if (m_pEditingContent)
	{
		if (m_pEditingContent->Undo())
			Invalidate();
	}
	else
	{

	}
}

void CGISViewerView::OnButtonEditRedo()
{
	if (m_pEditingContent)
	{
		if (m_pEditingContent->Redo())
			Invalidate();
	}
	else
	{

	}
}

void CGISViewerView::OnButtonEditMouseVectorDelete()
{
	m_pEditingContent->DeleteCurrentVector();
	m_pEditingContent->ReleaseEditVector();

	theApp.m_DockablePaneEditWindow.SetVectors();
	Invalidate();
	return;
}

void CGISViewerView::OnButtonEditMouseVectorAdd()
{
	m_pEditingContent->AddVectorAfterCurrentVector();
	m_pEditingContent->ReleaseEditVector();

	theApp.m_DockablePaneEditWindow.SetVectors();
	Invalidate();
	return;
}


void CGISViewerView::OnButtonEditSnap()
{
	if (m_bEditUseExistingVector)
	{
		m_bEditUseExistingVector = false;
		snapEditPoint.clear();
	}
	else
	{
		m_bEditUseExistingVector = true;
		SetEditSnapPoint();
	}

}


void CGISViewerView::OnUpdateButtonUncertainty(CCmdUI *pCmdUI)
{
	if (ENCCommon::SHOW_UNCERTAINTY)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnButtonUncertainty()
{
	if (ENCCommon::SHOW_UNCERTAINTY)
	{
		ENCCommon::SHOW_UNCERTAINTY = FALSE;
	}
	else
	{
		ENCCommon::SHOW_UNCERTAINTY = TRUE;
	}
	MapRefresh();
}

void CGISViewerView::OnButtonGoToKoreaArea()
{
	CRect rect;
	GetClientRect(rect);

	double lon = 129.099256;
	double lat = 35.085707;
	m_pGisLib->Projection(&lon, &lat);

	m_pGisLib->MoveMap(rect.Width() / 2, rect.Height() / 2, lon, lat);

	m_pGisLib->SetScale(10000000);
	m_pGisLib->AdjustScreenMap();
	MapRefresh();
}

HRESULT CGISViewerView::CreateDirect2dDeviceIndependentResources()
{
	CoInitialize(NULL);

	gisLib->D2.CreateDeviceIndependentResources();

	HRESULT hr = S_OK; 
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));


	} 
	if (SUCCEEDED(hr))
	{
		hr = m_pDirect2dFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties1(
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_ROUND,
				10.0f,
				D2D1_DASH_STYLE_SOLID,
				0.0f,
				D2D1_STROKE_TRANSFORM_TYPE_FIXED),
			NULL,
			0,
			&m_pStrokeStyleS101Solid);
	}

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
	);

	if (!SUCCEEDED(hr))
	{
		return false;
	}

	hr = m_pDWriteFactory->CreateTextFormat(
		L"Arial", 
		NULL, 
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,
		L"en-us",
		&m_pTextFormat
	);

	m_pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); 
	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	return hr;
}

HRESULT CGISViewerView::CreateDirect2dDeviceResources()
{
	HRESULT hr = S_OK;

	gisLib->D2.CreateDeviceDependentResources();

	if (!m_pRenderTarget)
	{ 
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM,
				D2D1_ALPHA_MODE_IGNORE),
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		); 
		hr = m_pDirect2dFactory->CreateDCRenderTarget
		(
			&props,
			&m_pRenderTarget
		);


		if (SUCCEEDED(hr))
		{ 
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Crimson),
				&m_pDirect2dSolidColorBrush
			);  
		}
	}

	return hr;
}

void CGISViewerView::DiscardDirect2dDeviceResources()
{
	gisLib->D2.DeleteDeviceDependentResources();
	SafeRelease(&m_pDirect2dSolidColorBrush);
}

void CGISViewerView::DiscardDirect2dDeviceIndependentResouces()
{
	gisLib->D2.DeleteDeviceIndependentResources();
} 
void CGISViewerView::OnS100ExchangeSetOpen()
{
	CString strExt = _T("xml");
	CString strTitle = _T("S-10X Feature Catalogue Open");
	CString strFilter = _T("XML Files (*.xml)|*.XML|");

	CFileDialog fileDialog(TRUE, strExt, NULL, OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, strFilter, this);

	fileDialog.m_ofn.lpstrTitle = strTitle;

	int ret = fileDialog.DoModal();
	std::wstring path;
	path = fileDialog.GetPathName();
	if (StrCmp(L"", path.c_str()))
	{ 
		ExchangeSet::AddExchangeSet(path);
	}
	auto it = path.find_last_of(L"\\");
	std::wstring pp = path.substr(0, ++it);
	std::list<DatasetStructureInExchangeSet> datasets = ExchangeSet::GetDatasetInExchangeSet(path);

	for (auto i = datasets.begin(); i != datasets.end(); i++)
	{
		DatasetStructureInExchangeSet* t = &(*i); 
		CString fp;
		fp.Format(L"%s%s", pp.c_str(), t->datasetPath.c_str()); 
		Catalog* fc;
		PortrayalCatalogue* pc;

		fc = LayerManager::GetFC(t->product);
		pc = LayerManager::GetPC(t->product);

		if (t->product == 100)
		{
			std::wstring fcName = ExchangeSet::GetFeatureCatalogName(path);
			std::wstring pcName = ExchangeSet::GetPortrayalCatalogName(path);  

			if (fc == nullptr || pc == nullptr)
			{
				continue;
			}
		}
		else if (t->product == 111)
		{
			libS111::Open(std::wstring(fp));
		}
		else if (t->product == 413)
		{
			libS413::Open(std::wstring(fp));
		}
		else if (t->product == 104)
		{
			libS104::Open(std::wstring(fp));
		}
		else if (t->product == 102)
		{
			libS102::Open(std::wstring(fp));
		}
		else
		{
			if (fc == nullptr || pc == nullptr)
			{
				continue;
			}
		}

		if (!m_pGisLib->AddLayerFromS100ExchangeSet(fp, fc, pc))
		{
			continue;
		} 
		m_pGisLib->SetMap(*m_pGisLib->GetMBR()); 
		m_pGisLib->UpdateScale();

		int index = m_pGisLib->GetLayerCount();

		if (index > 0)
		{
			theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem = index - 1;
			theApp.m_pDockablePaneLayerManager.pDlg->AdjustToolbarMenu();  
			Layer* l = m_pGisLib->GetLayer(index - 1);
			m_pGisLib->BuildS101Portrayal(l); 
		}
	}
	MapRefresh(); 
	theApp.m_pDockablePaneLayerManager.UpdateList(); 
	EndWaitCursor();

}

string* CGISViewerView::StringSplit(string strTarget, string strTok)
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

void CGISViewerView::OnButtonS111IndexPlay()
{
	CString msg;
	KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"Surface Current Simulation Play", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
	if (m_bCurrentPlay == false)
	{
		m_bCurrentPlay = true;
		SetTimer(TID_S111_SIMULATION, 3000, NULL);
		msg.Format(L"Surface Current Simulation Play (3 seconds");
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
	}
	else
	{
		m_bCurrentPlay = false;
		KillTimer(TID_S111_SIMULATION);
		msg.Format(L"Surface Current Simulation Stop");
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
	}
}

void CGISViewerView::OnUpdateButtonS111IndexPlay(CCmdUI *pCmdUI)
{ 
	if (m_bCurrentPlay)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnButtonS111IndexStop()
{
	OutputDebugString(_T("Stop\n"));

	CString msg;
	msg.Format(L"Surface Current Simulation Stop");
	KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);

	m_bCurrentPlay = false;
	KillTimer(TID_S111_SIMULATION);
	Invalidate();
}

void CGISViewerView::OnButtonICOpen()
{                
	S100_IC_OPENByPugi(L"..\\ProgramData\\xml\\Sample_of_IC_level_2.xml");                               
	OnComboICLevel();
}    
void CGISViewerView::OnComboICLevel()
{
	std::vector<std::wstring> ic_pathes;
	int cnt = GET_S100_IC_LIST(ic_pathes);

	if (cnt == 0)
	{
		return;
	}


	CMainFrame *m_pMainFramze = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_pMainFrame->m_wndRibbonBar.FindByID(ID_CB_IC_LEVEL));

	CString curStr = pComboBox->GetEditText();

	CString strScale;

	int scaleData[10] = { 0,
		1,
		2,
		3,
		4
	};

	int nCurSel = pComboBox->GetCurSel();

	ENCCommon::INTEROPERABILITY_LEVEL = scaleData[nCurSel];

	m_pGisLib->S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE::ALL*/);

	MapRefresh();
}

void CGISViewerView::OnButtonCreateCatalog()
{ 
	CStdioFile file;

	unordered_map<wstring, int> saMap;
	unordered_map<wstring, int> caMap;


	CString saveFileName = L"C:\\S-124 IDL Catalog.txt"; 
	if (file.Open(saveFileName, CFile::modeCreate | CFile::modeWrite))
	{
		int f_index = 0;
		int i_index = 1000;
		int attr_index = 2000;
		int asso_index = 3000;

		for (auto it = LayerManager::pS100Catalogs->begin(); it != LayerManager::pS100Catalogs->end(); it++)
		{
			FeatureCatalogue* fc = (*it)->m_pCatalogueList.begin()->second;
			if (fc->product.compare(L"S-101") == 0)
			{ 
				for (auto i = fc->simpleAttributes.simpleAttribute.begin(); i != fc->simpleAttributes.simpleAttribute.end(); i++)
				{
					SimpleAttribute* at = &i->second;
					attr_index++;

					saMap.insert(unordered_map<wstring, int>::value_type(at->code.GetValueString(), attr_index));
				}

				for (auto i = fc->complexAttributes.complexAttribute.begin(); i != fc->complexAttributes.complexAttribute.end(); i++)
				{
					ComplexAttribute* at = &i->second;
					attr_index++;

					caMap.insert(unordered_map<wstring, int>::value_type(at->code.GetValueString(), attr_index));
				} 
				for (auto fti = fc->featureTypes.featureType.begin(); fti != fc->featureTypes.featureType.end(); fti++)
				{
					FeatureType* ft = &fti->second;

					CString t;
					t.Format(L"%d_", f_index++);
					file.WriteString(t);
					file.WriteString(ft->name.c_str());
					t.Format(L"_");
					file.WriteString(t); 

					for (auto ai = ft->attributeBinding.begin(); ai != ft->attributeBinding.end(); ai++)
					{
						AttributeBinding* ab = &(*ai);
						Reference *r = &ab->attribute;

						wstring an;
						for (auto atr = r->Getattributes().begin(); atr != r->Getattributes().end(); atr++)
						{
							if (atr->Getname().compare(L"ref") == 0)
							{
								an = atr->Getvalue();
							}

						}

						auto fi = saMap.find(an);
						if (fi != saMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}

						fi = caMap.find(an);
						if (fi != caMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}
					}

					t.Format(L"\n"); 
					file.WriteString(t);


				}

				for (auto fti = fc->informationTypes.informationType.begin(); fti != fc->informationTypes.informationType.end(); fti++)
				{
					InformationType* ft = &fti->second;

					CString t;
					t.Format(L"%d_", f_index++);
					file.WriteString(t);
					file.WriteString(ft->name.c_str());
					t.Format(L"_");
					file.WriteString(t); 

					for (auto ai = ft->attributeBinding.begin(); ai != ft->attributeBinding.end(); ai++)
					{
						AttributeBinding* ab = &(*ai);
						Reference *r = &ab->attribute;

						wstring an;
						for (auto atr = r->Getattributes().begin(); atr != r->Getattributes().end(); atr++)
						{
							if (atr->Getname().compare(L"ref") == 0)
							{
								an = atr->Getvalue();
							}

						}

						auto fi = saMap.find(an);
						if (fi != saMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}

						fi = caMap.find(an);
						if (fi != caMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}
					}

					t.Format(L"\n"); 
					file.WriteString(t);
				}

				for (auto i = saMap.begin(); i != saMap.end(); i++)
				{ 
					wstring name = i->first;
					int index = i->second;      

					CString t;
					t.Format(L"%d_", index++);
					file.WriteString(t);
					file.WriteString(name.c_str());
					t.Format(L"\n");
					file.WriteString(t);


				} 
				for (auto i = caMap.begin(); i != caMap.end(); i++)
				{       
					wstring name = i->first;
					int index = i->second;

					CString t;
					t.Format(L"%d_", index++);
					file.WriteString(t);
					file.WriteString(name.c_str());
					t.Format(L"_");
					file.WriteString(t);

					ComplexAttribute *ca = &(fc->complexAttributes.complexAttribute.find(i->first.c_str())->second);

					for (auto ai = ca->subAttributeBinding.begin(); ai != ca->subAttributeBinding.end(); ai++)
					{
						AttributeBinding* ab = &(*ai);
						Reference *r = &ab->attribute;

						wstring an;
						for (auto atr = r->Getattributes().begin(); atr != r->Getattributes().end(); atr++)
						{
							if (atr->Getname().compare(L"ref") == 0)
							{
								an = atr->Getvalue();
							}

						}

						auto fi = saMap.find(an);
						if (fi != saMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}

						fi = caMap.find(an);
						if (fi != caMap.end())
						{
							t.Format(L"%d,", fi->second);
							file.WriteString(t);
						}
					}

					t.Format(L"\n"); 
					file.WriteString(t);
				}
			}
		}
	}

	file.Close();
}

void CGISViewerView::OnButtonShowOverscale()
{
	m_pGisLib->GetLayerManager()->bShowDataCoverageOverscale = !m_pGisLib->GetLayerManager()->bShowDataCoverageOverscale;
	MapRefresh();
}

#pragma warning(disable:4996)
void CGISViewerView::OnButtonGetDepthAreaInfo()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	wchar_t path[255];
	wcscpy(path, L"C:\\ENC_ROOT\\GMT_S100\\KR*.000");
	hFind = FindFirstFile((LPCTSTR)path, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
		return ;
	do{		
		wprintf(L"%s", FindData.cFileName);
		S101Cell* cell = new S101Cell();
		CString name = FindData.cFileName;
		cell->Open(L"C:\\ENC_ROOT\\GMT_S100\\" + name);
		POSITION pos;
		R_FeatureRecord *fr;
		__int64 iKey;
		int depth1=0, depth2 = 0;
		int depthAreaCode = 0;
		int maxNumericCode = 0, minNumericCode = 0;
		auto sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"depthRangeMaximumValue");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			maxNumericCode = sitor->second->m_nmcd;
		sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"depthRangeMinimumValue");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			minNumericCode = sitor->second->m_nmcd;
		sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"DepthArea");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			depthAreaCode = sitor->second->m_nmcd;
		CFile f;
		int index = 0;
		CString t = L"C:\\ENC_ROOT\\GMT_S100\\D_TEXT\\";
		t += cell->m_dsgir.m_dsid.m_dsnm;
		t += L".txt";
		f.Open(t, CFile::modeCreate | CFile::modeWrite);
		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			string str;
			stringstream ss;
			ss << fixed;
			if (fr->m_frid.m_nftc == depthAreaCode)
			{
				ss.str("");
				ss << index++ << "^";
				ss << converter.to_bytes(cell->m_dsgir.m_dsid.m_dsnm).c_str() << "^";
				int geoType = 0;
				for (auto itorParent = fr->m_spas.begin(); itorParent != fr->m_spas.end(); itorParent++)
				{
					F_SPAS *spasParent = *itorParent;
					for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
					{
						SPAS* spas = *itor;
						__int64 key = ((__int64)spas->m_name.RCNM) << 32 | ((__int64)spas->m_name.RCID);
						if (spas->m_name.RCNM == 130)
						{
							geoType = 3;
						}
						else
						{
							geoType = 1;
						}
					}
				}
				if (geoType == 3)
				{
					SSurface* p = (SSurface*)fr->m_geometry;
					for (int i = 0; i < p->m_numPoints; i++)
					{
						double x, y;
						x = p->m_pPoints[i].x;
						y = p->m_pPoints[i].y;
						m_pGisLib->InverseProjection(&x, &y);
						ss << setprecision(7) << x << "," << setprecision(7) << y;
						if (i != p->m_numPoints - 1)
						{
							ss << " ";
						}
					}
				}
				for (auto itorParent = fr->m_attr.begin(); itorParent != fr->m_attr.end(); itorParent++)
				{
					F_ATTR* attrParent = *itorParent;
					for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
					{
						ATTR* attr = *itor;
						if (attr->m_natc == maxNumericCode)
						{
							depth1 = _wtoi(attr->m_atvl);
						}
						else if (attr->m_natc == minNumericCode)
						{
							depth2 = _wtoi(attr->m_atvl);
						}
					}
				}
				ss << "^";
				ss << "Depth1^" << depth1 << "^";
				ss << "Depth2^" << depth2 << "^";
				ss << "\n";
				str = ss.str();
				f.Write(str.c_str(), str.size());
			}
		}
		
		f.Flush();
		f.Close();
	} while (FindNextFile(hFind, &FindData));

	FindClose(hFind);
}

class BRIDGE_TYPE_FEATURE
{
public:
	BRIDGE_TYPE_FEATURE() {}
	BRIDGE_TYPE_FEATURE(int _type, R_FeatureRecord* _feature)
	{
		type = _type;
		feature = _feature;
	} 
	int type;
	R_FeatureRecord* feature;
};
class FEATURE_SET {
public:
	FEATURE_SET() {}
public:
	BRIDGE_TYPE_FEATURE bridge;
	std::list<R_FeatureRecord*> pylons;
	std::list<R_FeatureRecord*> piles;
};

static int get_bridge_navigational_purpose = 6;
#pragma warning(disable:4996)
void CGISViewerView::OnButtonGetBridgeInfo()
{    
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	wchar_t path[255]; 
	wcscpy(path, L"C:\\_S100_TDS\\e-NavTDS_S101\\DataSet\\6\\*.000");
	hFind = FindFirstFile((LPCTSTR)path, &FindData);

	string total_bridge_string = "";
	string total_span_fixed_string = "";
	string total_span_opening_string = "";

	int bridge_index = 1;
	int span_fixed_index = 1;
	int span_opening_index = 1;

	if (hFind == INVALID_HANDLE_VALUE)
		return ;
	do{		
		wprintf(L"%s", FindData.cFileName);
		S101Cell* cell = new S101Cell();
		CString name = FindData.cFileName;
		cell->Open(L"C:\\_S100_TDS\\e-NavTDS_S101\\DataSet\\6\\" + name);
		POSITION pos;
		R_FeatureRecord *fr;
		__int64 iKey;
		int bridgeCode = 0;
		int spanFixedCode = 0;
		int spanOpeningCode = 0;
		int pylonCode = 0;
		int pileCode = 0;

		auto sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"Bridge");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			bridgeCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"SpanFixed");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			spanFixedCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"SpanOpening");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			spanOpeningCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"PylonBridgeSupport");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			pylonCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_ftcs->m_arrFindForCode.find(L"Pile");
		if (sitor != cell->m_dsgir.m_ftcs->m_arrFindForCode.end())
			pileCode = sitor->second->m_nmcd;


		std::vector< FEATURE_SET > searchResultSet;

		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			if (fr->m_frid.m_nftc == bridgeCode)
			{
				FEATURE_SET set;
				set.bridge = BRIDGE_TYPE_FEATURE(1, fr);
				searchResultSet.push_back(set);
			}
		}

		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			if (fr->m_frid.m_nftc == spanFixedCode)
			{
				FEATURE_SET set;
				set.bridge = BRIDGE_TYPE_FEATURE(2, fr);
				searchResultSet.push_back(set);
			}
		}
		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			if (fr->m_frid.m_nftc == spanOpeningCode)
			{
				FEATURE_SET set;
				set.bridge = BRIDGE_TYPE_FEATURE(3, fr);
				searchResultSet.push_back(set);
			}
		}
		
		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			if (fr->m_frid.m_nftc == pylonCode)
			{
				for (auto si = searchResultSet.begin(); si != searchResultSet.end(); si++)
				{
					auto set = &(*si);

					if (MBR::CheckOverlap(fr->GetMBR(), set->bridge.feature->GetMBR()))
					{
						set->pylons.push_back(fr);
					}
				}
			}
		}

		pos = cell->m_feaMap.GetStartPosition();
		while (pos != NULL)
		{
			cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
			if (fr->m_frid.m_nftc == pileCode)
			{
				for (auto si = searchResultSet.begin(); si != searchResultSet.end(); si++)
				{
					auto set = &(*si);

					if (MBR::CheckOverlap(fr->GetMBR(), set->bridge.feature->GetMBR()))
					{
						set->piles.push_back(fr);
					}
				}
			}
		}


		CFile f;
		CString t = L"C:\\_S100_TDS\\e-NavTDS_S101\\DataSet\\D_TEXT\\";
		t += cell->m_dsgir.m_dsid.m_dsnm;
		t += L".txt";
		f.Open(t, CFile::modeCreate | CFile::modeWrite);

		for (auto si = searchResultSet.begin(); si != searchResultSet.end(); si++)
		{
			string str;
			stringstream ss;
			ss << fixed;
			if (si->bridge.type == 1)
			{
				auto set = &(*si);
				auto bridge = set->bridge;
				ss << bridge_index << "^" << cell->m_dsgir.m_dsid.m_dsnm << "^BRIDGE^" << bridge.feature->m_frid.m_name.RCID << "^" << bridge.feature->m_fasc.size() <<"^" << set->pylons.size() << "^" << set->piles.size();
				ss << "\n";

				str = ss.str();
				f.Write(str.c_str(), str.size());

				total_bridge_string.append(str);

				bridge_index++;
			}
			else if (si->bridge.type == 2)
			{
				auto set = &(*si);
				auto bridge = set->bridge;
				ss << span_fixed_index << "^" << cell->m_dsgir.m_dsid.m_dsnm << "^SPAN_FIXED^" << bridge.feature->m_frid.m_name.RCID << "^" << bridge.feature->m_fasc.size() << "^" << set->pylons.size() << "^" << set->piles.size();
				ss << "\n";

				str = ss.str();
				f.Write(str.c_str(), str.size());

				total_span_fixed_string.append(str);
				span_fixed_index++;
			}
			else if (si->bridge.type == 3)
			{
				auto set = &(*si);
				auto bridge = set->bridge;
				ss << span_opening_index << "^" << cell->m_dsgir.m_dsid.m_dsnm << "^SPAN_OPENING^" << bridge.feature->m_frid.m_name.RCID << "^" << bridge.feature->m_fasc.size() << "^" << set->pylons.size() << "^" << set->piles.size();
				ss << "\n";

				str = ss.str();
				f.Write(str.c_str(), str.size());

				total_span_opening_string.append(str);

				span_opening_index++;
			}
		}

		f.Flush();
		f.Close();

		delete cell;
	} while (FindNextFile(hFind, &FindData));

	CFile f;
	CString t;
	
	t.Format(L"C:\\_S100_TDS\\e-NavTDS_S101\\DataSet\\D_TEXT\\_%d_TOTAL.txt", get_bridge_navigational_purpose);
	f.Open(t, CFile::modeCreate | CFile::modeWrite);   
	string split = "\n--------------------------------------------------------------------\n";
	f.Write(total_bridge_string.c_str(), total_bridge_string.size());
	f.Write(split.c_str(), split.size());
	f.Write(total_span_fixed_string.c_str(), total_span_fixed_string.size());
	f.Write(split.c_str(), split.size());
	f.Write(total_span_opening_string.c_str(), total_span_opening_string.size());

	f.Flush();
	f.Close();
	FindClose(hFind);
}
void CGISViewerView::IC_LabelSetting()
{
	CMainFrame *m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_pMainFrame->m_wndRibbonBar.FindByID(ID_CB_IC_LEVEL));
	CString t;
	t.Format(L"%d", ENCCommon::INTEROPERABILITY_LEVEL);
	pComboBox->SetEditText(t);
}

void CGISViewerView::OnUpdateButtonEditSnap(CCmdUI *pCmdUI)
{
	if (m_bEditUseExistingVector)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

BOOL CGISViewerView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{ 

	int msgType = (int)pCopyDataStruct->cbData;
	switch (msgType)
	{
	case KRS_MSG_INFO:

		LPTSTR lpMessage = (LPTSTR)pCopyDataStruct->lpData;
		CString msg = lpMessage;
		delete lpMessage;

		CString fullMsg;
		switch (msgType)
		{
		case KRS_MSG_INFO:
			fullMsg.Append(L"INFO : ");
			break;
		case KRS_MSG_ERROR:
			fullMsg.Append(L"ERROR : ");
			break;
		case KRS_MSG_WARNING:
			fullMsg.Append(L"WARNING : ");
			break;
		}
		fullMsg.Append(msg);

		theApp.m_DockablePaneLogger.AppendList(fullMsg);
		break;
	}


	return CView::OnCopyData(pWnd, pCopyDataStruct);
}

void CGISViewerView::OnUpdateButtonTextPlacement_ON_OFF(CCmdUI *pCmdUI)
{
	if (ENCCommon::SHOW_TEXT_PLACEMENT)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CGISViewerView::OnUpdateButtonBaseMapOnOff(CCmdUI *pCmdUI)
{
	if (m_pGisLib->GetDrawBackground())
	{
		pCmdUI->SetCheck(0);
	}
	else
	{
		pCmdUI->SetCheck(1);
	}
}

void CGISViewerView::OnButtonTextPlacement_SAVE()
{
	int i = 0;

	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);

	if (!l)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"Failed to save file because there was no layer.", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	} 
	wstring name = l->m_spatialObject->GetFileName(); 
	CFileDialog dlg(FALSE, L"000", name.c_str(), OFN_OVERWRITEPROMPT, _T("S-10X GML Files (*.gml)|*.gml|ENC Files (*.000)|*.000|Usable Files(*.000, *.gml)|*.000;*.gml|All Files (*.*)|*.*|"), NULL); 
	if (dlg.DoModal() != IDOK)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"file Save Dialog is not open ", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	} 
	CString filepath;
	filepath = dlg.GetPathName(); 
	BeginWaitCursor(); 
	theApp.m_pDockablePaneLayerManager.SaveLayerTextPlacement(filepath, dlg.GetFileExt()); 
	EndWaitCursor();

}

void CGISViewerView::OnButtonCreateTextPlacement_from_S57ENC()
{
	int i = 0;

	Layer* l = m_pGisLib->GetLayer(theApp.m_pDockablePaneLayerManager.pDlg->nSelectedItem);

	if (!l)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"Failed to save file because there was no layer.", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
		return;
	} 
	BeginWaitCursor(); 

	S101Cell* c = (S101Cell*)l->m_spatialObject;


	c->m_infMap.RemoveAll(); 
	c->m_ptMap.RemoveAll(); 
	c->m_mpMap.RemoveAll(); 
	c->m_curMap.RemoveAll(); 
	c->m_comMap.RemoveAll(); 
	c->m_surMap.RemoveAll(); 
	c->m_feaMap.RemoveAll(); 

	c->m_curveMap.clear();

	c->m_vecMap.clear();

#ifdef _DEBUG
	c->m_feaMapFOID.clear();
#endif  
	c->m_PRFeatureList.clear();
	c->m_MPFeatureList.clear();
	c->m_CCFeatureList.clear();
	c->m_SRFeatureList.clear();

	csv::Parser file = csv::Parser("..\\SampleData\\objnam.csv");

	auto cnt = (int)file.rowCount();
	for (auto i = 0; i < cnt; i++)
	{
		auto objnam = file[i][0];
		auto nobjnm = file[i][1];
		auto x = file[i][2];
		auto y = file[i][3];

		NewFeatureManager newFeatureManager;
		R_FeatureRecord* fr = NULL; 

		newFeatureManager.m_featureType = ENC_S101_Factory::GetFTCS(c, L"TextPlacement");
		newFeatureManager.m_addFeaturePoint.x = atof(x.c_str());
		newFeatureManager.m_addFeaturePoint.y = atof(y.c_str()); 
		newFeatureManager.m_cell = c;
		newFeatureManager.m_geometryType = 1;

		fr = ENC_S101_Factory::CreateFeature(&newFeatureManager, theApp.pView->m_pGisLib->GetScaler());
		c->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

		ATTR* attr = new ATTR();
		F_ATTR* attrParent = new F_ATTR();
		attrParent->m_arr.push_back(attr);
		fr->m_attr.push_back(attrParent);
		attr->m_natc = ENC_S101_Factory::GetATCS(c, L"text");

		attr->m_atix = 1;
		attr->m_paix = 0;
		attr->m_atin = 1;


		auto wNobjnm = LibMFCUtil::ConvertCtoWC((char*)nobjnm.c_str());
		auto wObjnam = LibMFCUtil::ConvertCtoWC((char*)objnam.c_str());

		attr->m_atvl.Format(L"%s(%s)", wObjnam, wNobjnm);
		attr->m_atvl.Replace(_T("\""), _T(""));


		delete[] wNobjnm;
		delete[] wObjnam;

		attr = new ATTR();
		attrParent->m_arr.push_back(attr);
		attr->m_natc = ENC_S101_Factory::GetATCS(c, L"textJustification");

		attr->m_atix = 2;
		attr->m_paix = 0;
		attr->m_atin = 1;

		attr->m_atvl.Format(L"1");
	}

	c->Save(L"..\\SampleData\\result.000", L"000"); 
	EndWaitCursor();

}

void CGISViewerView::OnButtonTextPlacement_ON_OFF()
{
	if (ENCCommon::SHOW_TEXT_PLACEMENT)
	{
		ENCCommon::SHOW_TEXT_PLACEMENT = FALSE;
	}
	else
	{
		ENCCommon::SHOW_TEXT_PLACEMENT = TRUE;
	}
	MapRefresh();
}

void CGISViewerView::OnButtonBaseMapOnOff()
{
	m_pGisLib->SetDrawBackground(!m_pGisLib->GetDrawBackground());
	MapRefresh();
}

void CGISViewerView::OnPcfcsavebutton()
{
	if (LogList.size() != 0)
	{
		CString strExtFile, strFilePath;
		CString strFilter = _T("텍스트 문서(*.txt)|*.txt||");
		strExtFile = _T("*.txt");
		CFileDialog dlg(FALSE, strExtFile, strExtFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

		if (IDOK == dlg.DoModal())
		{
			strFilePath = dlg.GetPathName(); 

			string out_line;
			ofstream out(strFilePath);
			for (unsigned i = 0; i < LogList.size(); i++)
			{
				if (LogList[i].reportingData == ENCCommon::FC || LogList[i].reportingData == ENCCommon::PC)
				{
					out_line = CT2CA(LogList[i].LogContent);
					cin >> out_line;
					out << out_line << endl;
				}
			}
			MessageBox(_T("파일생성을 완료했습니다."), _T("알림창"));
			out.close();
		}
	}
	else
	{

	}
}

void CGISViewerView::OnDatasetsavebutton()
{
	if (LogList.size() != 0)
	{
		CString strExtFile, strFilePath;
		CString strFilter = _T("텍스트 문서(*.txt)|*.txt||");
		strExtFile = _T("*.txt");
		CFileDialog dlg(FALSE, strExtFile, strExtFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

		if (IDOK == dlg.DoModal())
		{
			strFilePath = dlg.GetPathName(); 

			string out_line;
			ofstream out(strFilePath);
			for (unsigned i = 0; i < LogList.size(); i++)
			{
				if (LogList[i].reportingData == ENCCommon::DataSet)
				{
					out_line = CT2CA(LogList[i].LogContent);
					cin >> out_line;
					out << out_line << endl;
				}
				else
				{

				}

			}
			MessageBox(_T("파일생성을 완료했습니다."), _T("알림창"));
			out.close();
		}
	}
	else
	{
	}
}

R_FeatureRecord* CGISViewerView::OnMenuTextplacement()
{
	auto feature = GetSelectedFeature();
	if (!feature)
	{
		return NULL;
	}

	auto layer = GetCurrentLayer();
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	m_pNewFeatureManager->m_featureType = ENC_S101_Factory::GetFTCS(cell, L"TextPlacement");;
	m_pNewFeatureManager->m_geometryType = 1/*Point*/;
	m_pNewFeatureManager->m_pOrgFeatureRecord = feature;


	bool sameGeometry = true;
	if (feature->m_geometry->type == 1) {   
		sameGeometry = true;
	}
	else if (feature->m_geometry->type == 2) {
		SCompositeCurve* sr = (SCompositeCurve*)feature->m_geometry;
		if (sr->m_listCurveLink.size() > 0)
		{
			m_pNewFeatureManager->m_addFeaturePoint.x = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].x;
			m_pNewFeatureManager->m_addFeaturePoint.y = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].y;
			m_pGisLib->InverseProjection(&m_pNewFeatureManager->m_addFeaturePoint.x, &m_pNewFeatureManager->m_addFeaturePoint.y);

		}
		sameGeometry = false;
	}
	else if (feature->m_geometry->type == 3) {
		SSurface* sr = (SSurface*)feature->m_geometry;
		m_pNewFeatureManager->m_addFeaturePoint.x = sr->m_pPoints[0].x;
		m_pNewFeatureManager->m_addFeaturePoint.y = sr->m_pPoints[0].y;
		m_pGisLib->InverseProjection(&m_pNewFeatureManager->m_addFeaturePoint.x, &m_pNewFeatureManager->m_addFeaturePoint.y);
		sameGeometry = false;
	}
	else if (feature->m_geometry->type == 4) {
		return NULL;
	}


	auto newFeature = ENC_S101_Factory::CreateFeature(m_pNewFeatureManager, m_pGisLib->GetScaler(), true, sameGeometry);


	if (newFeature)//좌표를 선택한다음에 넘어옵니다
	{
		cell->MakePointData(newFeature);

		SetPickReportFeature(newFeature); 
		int code = newFeature->m_frid.m_nftc;
		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
		m_pDlgPickReport->InitObjectList();
		m_pDlgPickReport->AddObject(itor->second->m_code,
			itor->second->m_code,
			cell->m_dsgir.m_dsid.m_dsnm,//m_pGisLib->GetLayerName(layerCount), 
			newFeature,
			cell);

		Catalog* catalog = ((S101Layer*)m_pNewFeatureManager->m_cell->m_pLayer)->GetFC();

		m_pDlgPickReport->SetObjectListCtrl(catalog); 
		SelectedFeatureType = catalog->m_pCatalogueList.begin()->second->GetFeatureType(std::wstring(itor->second->m_code));

		theApp.m_DockablePaneEditWindow.SetSpatialObject(m_pNewFeatureManager->m_cell);
		theApp.m_DockablePaneEditWindow.SetFeatureRecord(frPick);
		theApp.m_DockablePaneAttributeList.SetShowTree(catalog, SelectedFeatureType);     
		code = newFeature->m_frid.m_nftc;
		auto ftItor = cell->m_dsgir.m_ftcs->m_arr.find(code);

		CString csFrid, csFoid, csLat, csLon, csType, csName, csAssoCnt;
		CString featureType = L"Feature";

		double lat;
		double lon;

		if (newFeature->m_geometry->type == 1) {
			SPoint* sr = (SPoint*)newFeature->m_geometry;
			lat = sr->m_point.x;
			lon = sr->m_point.y;

			m_pGisLib->InverseProjection(&lat, &lon);
			csType.Format(_T("%d"), sr->type);
		}
		else if (newFeature->m_geometry->type == 2) {
			SCompositeCurve* sr = (SCompositeCurve*)newFeature->m_geometry;
			if (sr->m_listCurveLink.size() > 0)
			{
				lat = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].x;
				lon = ((*sr->m_listCurveLink.begin()).GetCurve())->m_pPoints[0].y;
			}
			m_pGisLib->InverseProjection(&lat, &lon);
			csType.Format(_T("%d"), sr->type);
		}
		else if (newFeature->m_geometry->type == 3) {
			SSurface* sr = (SSurface*)newFeature->m_geometry;
			lat = sr->m_pPoints[0].x;
			lon = sr->m_pPoints[0].y;
			m_pGisLib->InverseProjection(&lat, &lon);
			csType.Format(_T("%d"), sr->type);
		}
		else if (newFeature->m_geometry->type == 4) {
			double geoX = ((ENCSounding*)newFeature->m_geometry)->m_pPoints[0].x;
			double geoY = ((ENCSounding*)newFeature->m_geometry)->m_pPoints[0].y;
			SMultiPoint* sr = (SMultiPoint*)newFeature->m_geometry;
			m_pGisLib->InverseProjection(&geoX, &geoY);
			csType.Format(_T("%d"), sr->type);
		}

		vector<int>::size_type assoCnt;
		assoCnt = newFeature->m_fasc.size() + newFeature->m_inas.size();

		csFrid.Format(_T("%d"), newFeature->m_frid.m_name.RCID);
		csFoid.Format(_T("%d"), newFeature->m_foid.m_objName.m_fidn);
		csLat.Format(_T("%f"), lat);
		csLon.Format(_T("%f"), lon);
		csName.Format(_T("%s"), ftItor->second->m_code);
		csAssoCnt.Format(_T("%d"), assoCnt);


		CString type;


		if (newFeature->m_geometry->type == 1) {
			type = "point";
		}
		else if (newFeature->m_geometry->type == 2) {
			type = "curve";
		}
		else if (newFeature->m_geometry->type == 3) {
			type = "surface";
		}
		else if (newFeature->m_geometry->type == 4) {
			type = "multipoint (sounding)";
		}
		else if (newFeature->m_geometry->type == 999) {
			type = "No geometry";
		}
		else {
			type = "-";
		}


		bool isExist = false; 
		for (int j = 0; j < theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.GetItemCount(); j++)
		{
			if (csFrid == theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.GetItemText(j, 0) &&
				featureType == theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.GetItemText(j, 7))
			{
				isExist = true;
			}
		}

		if (!isExist)
		{
			LVITEM firstItem = { 0 };
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.InsertItem(&firstItem);  
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 0, csFrid);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 1, csFrid);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 2, csName);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 3, type);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 4, csLon);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 5, csLat);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 6, csAssoCnt);
			theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemText(0, 7, featureType);

			if (featureType == L"Feature") { 
				Catalog *catalog = ((S101Layer*)theApp.pView->m_pNewFeatureManager->m_cell->m_pLayer)->GetFC();
				FeatureCatalogue *fc = catalog->m_pCatalogueList.begin()->second; 
				wstring name = wstring(csName);
				csName.ReleaseBuffer();
				auto it = fc->featureTypes.featureType.find(name);
				if (it == fc->featureTypes.featureType.end())
				{
					CString msg;
					msg.Format(L"[%s] Feature not found. -CURRENT SELECTION", name);
					KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
				}
				else
				{
					FeatureType* ft = &it->second;
					theApp.m_DockablePaneCurrentSelection.pDlg->m_ListCurrentSelection.SetItemData(0, (LPARAM)ft);
				}
			}
			else { 
			}

		}


		int nameCode = 0, languageCode = 0, featureNameCode = 0, scaleMinimumCode = 0;;

		auto sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"name");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			nameCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"language");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			languageCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"featureName");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			featureNameCode = sitor->second->m_nmcd;

		sitor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"scaleMinimum");
		if (sitor != cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			scaleMinimumCode = sitor->second->m_nmcd;

		int featureNameCount = 0;
		wstring language = L"";
		wstring name;
		wstring scaleMinimum;

		wstring korName;
		wstring engName;

		for (auto itorParent = feature->m_attr.begin(); itorParent != feature->m_attr.end(); itorParent++)
		{
			F_ATTR* attrParent = *itorParent;
			for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
			{
				ATTR* attr = *itor;  
				if (attr->m_natc == featureNameCode)
				{
					featureNameCount = 3;
					language = L"";
					name = L"";
				}
				else if (attr->m_natc == languageCode)
				{
					language = attr->m_atvl;

					if (language.compare(L"kor") == 0)
					{
						if (name.size() > 0)
						{
							korName = name;
							name = L"";
						}
					}
					else if (language.compare(L"eng") == 0)
					{
						if (name.size() > 0)
						{
							engName = name;
							name = L"";
						}
					}
					else
					{
						language = L"";
					}
				}
				else if (attr->m_natc == nameCode && featureNameCount > 0)
				{
					name = attr->m_atvl;
					if (language.compare(L"kor") == 0)
					{
						korName = name;
						name = L"";
						language = L"";
					}
					else if (language.compare(L"eng") == 0)
					{
						engName = name;
						name = L"";
						language = L"";
					}
					else
					{
						language = L"";
					}
				}

				if (featureNameCount > 0)
					featureNameCount--;
				else
				{
					language = L"";
					name = L"";
				}  
				if (attr->m_natc == scaleMinimumCode)
				{
					scaleMinimum = attr->m_atvl;
				}
			}
		}

		F_ATTR* attrParent = *newFeature->m_attr.begin();

		ATTR* attr = new ATTR();
		attrParent->m_arr.push_back(attr);
		attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"text");

		attr->m_atix = 1;
		attr->m_paix = 0;
		attr->m_atin = 1; 
		attr->m_atvl.Format(L"%s (%s)", engName.c_str(), korName.c_str());


		attr = new ATTR();
		attrParent->m_arr.push_back(attr);
		attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"scaleMinimum");

		attr->m_atix = 2;
		attr->m_paix = 0;
		attr->m_atin = 1;

		attr->m_atvl = scaleMinimum.c_str();

		m_pDlgPickReport->SetObjectListCtrl(catalog); 
		SelectedFeatureType = catalog->m_pCatalogueList.begin()->second->GetFeatureType(std::wstring(itor->second->m_code));

		theApp.m_DockablePaneEditWindow.SetSpatialObject(m_pNewFeatureManager->m_cell);
		theApp.m_DockablePaneEditWindow.SetFeatureRecord(frPick);
		theApp.m_DockablePaneAttributeList.SetShowTree(catalog, SelectedFeatureType); 

		theApp.m_DockablePaneCurrentSelection.pDlg->UpdateData(false);


		m_pGisLib->GetLayerManager()->BuildS101Portrayal(cell->m_pLayer/*, fr->m_frid.m_name.GetName()*//*, PORTRAYAL_BUILD_TYPE::CHANGED_FEATURE*/);

		MapRefresh();
	}
	return newFeature;
}


R_FeatureRecord* CGISViewerView::GetSelectedFeature()
{
	return frPick;
}


void CGISViewerView::OnZooninlayer()
{
	auto thislayer = GetCurrentLayer();
	if (thislayer == nullptr)
	{
		AfxMessageBox(L"Plese Select Layer");
		return;
	}

	auto layerMBR = thislayer->GetMBR();
	m_pGisLib->GetLayerManager()->GetScaler()->SetMap(layerMBR);
	m_pGisLib->AdjustScreenMap();
	
	MapRefresh();
}

void CGISViewerView::OnDropFiles(HDROP hDropInfo)
{ 
	DWORD dwCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0); 
	wchar_t szFileName[2048]; 
	for (DWORD i = 0; i < dwCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFileName, sizeof(szFileName)); 

		CString filePath = szFileName;

		m_pGisLib->AddLayer(filePath); 
	}

	CView::OnDropFiles(hDropInfo);
}

void CGISViewerView::SaveTile(CImage& image, HDC& hdc, int x, int y, int z, CString path)
{
	auto layerList = gisLib->GetAllLayer();

	if (z == 11)
	{
		gisLib->LayerOn(0);

		gisLib->LayerOff(1);
		gisLib->LayerOff(2);
		gisLib->LayerOff(3);
		gisLib->LayerOff(4);
		gisLib->LayerOff(5);
		gisLib->LayerOff(6);
		gisLib->LayerOff(7);
		gisLib->LayerOff(8);
		gisLib->LayerOff(9);
		gisLib->LayerOff(10);
		gisLib->LayerOff(11);
		gisLib->LayerOff(12);
		gisLib->LayerOff(13);
		gisLib->LayerOff(14);
		gisLib->LayerOff(15);
	}
	else if (z == 12)
	{
		gisLib->LayerOn(0);
		gisLib->LayerOn(1);

		gisLib->LayerOff(2);
		gisLib->LayerOff(3);
		gisLib->LayerOff(4);
		gisLib->LayerOff(5);
		gisLib->LayerOff(6);
		gisLib->LayerOff(7);
		gisLib->LayerOff(8);
		gisLib->LayerOff(9);
		gisLib->LayerOff(10);
		gisLib->LayerOff(11);
		gisLib->LayerOff(12);
		gisLib->LayerOff(13);
		gisLib->LayerOff(14);
		gisLib->LayerOff(15);
	}
	else if (z == 13 || z == 14)
	{
		gisLib->LayerOn(0);
		gisLib->LayerOn(1);
		gisLib->LayerOn(2);

		gisLib->LayerOff(3);
		gisLib->LayerOff(4);
		gisLib->LayerOff(5);
		gisLib->LayerOff(6);
		gisLib->LayerOff(7);
		gisLib->LayerOff(8);
		gisLib->LayerOff(9);
		gisLib->LayerOff(10);
		gisLib->LayerOff(11);
		gisLib->LayerOff(12);
		gisLib->LayerOff(13);
		gisLib->LayerOff(14);
		gisLib->LayerOff(15);
	}
	else if (z == 15)
	{
		gisLib->LayerOn(0);
		gisLib->LayerOn(1);
		gisLib->LayerOn(2);
		gisLib->LayerOn(3);

		gisLib->LayerOff(4);
		gisLib->LayerOff(5);
		gisLib->LayerOff(6);
		gisLib->LayerOff(7);
		gisLib->LayerOff(8);
		gisLib->LayerOff(9);
		gisLib->LayerOff(10);
		gisLib->LayerOff(11);
		gisLib->LayerOff(12);
		gisLib->LayerOff(13);
		gisLib->LayerOff(14);
		gisLib->LayerOff(15);
	}
	else if (z == 16)
	{
		gisLib->LayerOn(0);
		gisLib->LayerOn(1);
		gisLib->LayerOn(2);
		gisLib->LayerOn(3);
		gisLib->LayerOn(4);

		gisLib->LayerOff(5);
		gisLib->LayerOff(6);
		gisLib->LayerOff(7);
		gisLib->LayerOff(8);
		gisLib->LayerOff(9);
		gisLib->LayerOff(10);
		gisLib->LayerOff(11);
		gisLib->LayerOff(12);
		gisLib->LayerOff(13);
		gisLib->LayerOff(14);
		gisLib->LayerOff(15);
	}
	else if (z >= 17)
	{
		gisLib->LayerOn(0);
		gisLib->LayerOn(1);
		gisLib->LayerOn(2);
		gisLib->LayerOn(3);
		gisLib->LayerOn(4);
		gisLib->LayerOn(5);
		gisLib->LayerOn(6);
		gisLib->LayerOn(7);
		gisLib->LayerOn(8);
		gisLib->LayerOn(9);
		gisLib->LayerOn(10);
		gisLib->LayerOn(11);
		gisLib->LayerOn(12);
		gisLib->LayerOn(13);
		gisLib->LayerOn(14);
		gisLib->LayerOn(15);
	}
	else 
	{
		return;
	}

	CRect rect(0, 0, 256, 256);

	if (true)
	{

		auto tileXMin = LatLonUtility::TileCalculator::TileXtoLon(x, z);
		auto tileYMin = LatLonUtility::TileCalculator::TileYtoLat(y + 1, z);
		auto tileXMax = LatLonUtility::TileCalculator::TileXtoLon(x + 1, z);
		auto tileYMax = LatLonUtility::TileCalculator::TileYtoLat(y, z);

		projection(tileXMin, tileYMin);
		projection(tileXMax, tileYMax);

		gisLib->SetMap(tileXMin, tileYMin, tileXMax, tileYMax);
		gisLib->SetScreen(rect);

		CRect viewedRect(-500, -500, 756, 756);

		gisLib->SetViewMBR(viewedRect);

		CString local_path;
		local_path.Format(_T("%s\\%d\\%d\\%d.png"), path, z, x, y);
		OutputDebugString(local_path);

		if (PathFileExists(local_path) == FALSE)
		{
			gisLib->GetLayerManager()->DrawLayerList(hdc);
			auto width = rect.Width();
			auto height = rect.Height();

			LibMFCUtil::SaveImage2(local_path, image, hdc, width, height);
		}
	} 
	if (z < 15)
	{
		SaveTile(image, hdc, 2 * x, 2 * y, z + 1, path);
		SaveTile(image, hdc, (2 * x) + 1, 2 * y, z + 1, path);
		SaveTile(image, hdc, 2 * x, (2 * y) + 1, z + 1, path);
		SaveTile(image, hdc, (2 * x) + 1, (2 * y) + 1, z + 1, path);
	}
}

void CGISViewerView::OnButtonGenerateTileMap()
{
	auto layerList = gisLib->GetAllLayer();    

	auto cdc = GetDC();
	CRect rect(0, 0, 256, 256);
	CDC tileDC;
	CBitmap tileBMP;
	if (tileDC.CreateCompatibleDC(cdc))
	{
		if (tileBMP.CreateCompatibleBitmap(cdc, rect.Width(), rect.Height()))
		{
			CBitmap* pOldBitmap = tileDC.SelectObject(&tileBMP);
			if (pOldBitmap != NULL)
			{
				pOldBitmap->DeleteObject();
			}
		}
		tileDC.SetBkMode(TRANSPARENT);
	}

	CImage capImage;

	if (!capImage.Create(rect.Width(), rect.Height(), 32))
	{
		return;
	}

	auto hdc = tileDC.GetSafeHdc();

	gisLib->GetLayerManager()->ChangeS100ColorPalette(L"Day");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::base;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Day_Base");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::standard;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Day_Standard");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::all;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Day_Others");

	gisLib->GetLayerManager()->ChangeS100ColorPalette(L"Dusk");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::base;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Dusk_Base");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::standard;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Dusk_Standard");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::all;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Dusk_Others");

	gisLib->GetLayerManager()->ChangeS100ColorPalette(L"Night");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::base;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Night_Base");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::standard;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Night_Standard");

	ENCCommon::DISPLAY_MODE = ENCCommon::DisplayModeTable::all;
	gisLib->ChangeDisplayMode();
	SaveTile(capImage, hdc, 1758, 810, 11, L"..\\TEMP\\tiles_Night_Others");

	ReleaseDC(cdc);

	AfxMessageBox(_T("타일생성완료"));
}