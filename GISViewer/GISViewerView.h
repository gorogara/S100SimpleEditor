#pragma once

#include "resource.h"
#include "DialogSVGView.h"
#include "MFCPropertySelectColorGridProperty.h"
#include "DialogDockLogger.h"
#include "LOG.h"

#include "GISLibrary\\ENCEditStructure.h"

#include "..\\RoutePlanner\\RoutePlannerNames.h" 
#include "..\\RoutePlanner\\UserLayer.h" 

#include <vector>

class CMainFrame;
class CGISViewerDoc;
class CDockablePaneTreeView;
class CDockablePaneLayerManager;
class CDialogExPickReport;
class CDialogDockCurrentSelection;
class CSymbolManager;
class CGISLibraryApp;
class Layer;
class ENCLayer;
class ENC_Feature;
class GML_Feature;
class ENCCell;
class R_FeatureRecord;
class GML_Attribute;
class NewFeatureManager;
class GeoPoint;
class CDockablePaneRoutePlan;
class EditingContent;
class FeatureType;
class InformationType;
struct ID2D1StrokeStyle1;
struct ID2D1Factory1;



class CGISViewerView : public CView
{
protected: 
	CGISViewerView();
	DECLARE_DYNCREATE(CGISViewerView) 
public:
	static std::vector<LOG>			 LogList;

	CGISViewerDoc				*GetDocument() const;
	CMainFrame					*m_pMainFrame;
	
	CGISLibraryApp				*m_pGisLib;
	CDockablePaneRoutePlan		*m_pDockablePaneRoutePlan;


  

	void DrawLogo(CDC* pDC);

	void DrawMovePoint(CDC* pDC, const PointD _p, const int _offX = 0, const int _offY = 0) const;
	bool bDrawMovePoint;
	PointD pDrawMoveMPoint;

	void LButtonUpDistance(UINT nFlags, CPoint point);

	typedef std::vector<PointD> Distance;
	Distance m_vectorCurrentDistance;
	bool m_bCurrentPlay = false;

	std::vector<Distance> m_vectorDistance;

	void DrawDistance(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void DrawDistanceSegment(CDC* pDC, Distance distance, int offsetX = 0, int offsetY = 0);
	void DrawDistanceCurrent(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void DrawDistanceCurrentSizeOne(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void DrawDistanceCurrentSizeOneMore(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void RButtonUpDistance(UINT nFlags, CPoint point);

	void IC_LabelSetting(); 
	std::vector<PointD> m_vecCurMeasureArea;

	typedef struct _Area
	{
		std::vector<PointD> points;
		double area;
	} Area;

	std::vector<Area> m_vecMeasureArea;

	void DrawMeasureArea(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void DrawMeasureAreaSegment(CDC* pDC, Area area, int offsetX = 0, int offsetY = 0);
	void DrawMeasureAreaCurrent(CDC* pDC, int offsetX = 0, int offsetY = 0);
	void RButtonUpMeasureArea(UINT nFlags, CPoint point);
	void LButtonUpMeasureArea(UINT nFlags, CPoint point);
	
	double Haversine(double x);

	void MoveToObject(ENC_Feature* fe);
	void SetPickedFeature(ENC_Feature* fe);


	Layer* GetCurrentLayer();
	int GetCurrentLayerIndexnum();
	CString CGISViewerView::EnumToCstring(ENCCommon::UserMode mode);
	ENCCommon::UserMode CGISViewerView::CStringToUserEnum(CString mode);
	ENCCommon::ReportingData CGISViewerView::CStringToDataEnum(CString mode);

	NewFeatureManager *m_pNewFeatureManager;
	void GetPickedFeature(CPoint _point);
	void LButtonUpFeatureAddPoint(UINT nFlags, CPoint point);
	void LButtonUpFeatureAddPoints(UINT nFlags, CPoint point);
public:

	EditingContent *m_pEditingContent;

	bool m_bEditUseExistingVector;
	bool m_bEditFeatureRelation;
	std::list<EditPoint> snapEditPoint;

	void SetEditSnapPoint();
	void SetEditSnapPoint2();

	void EditLButtonDown(CPoint p);
	void EditMouseMove(UINT nFlags, CPoint p);
	void EditLButtonUp(CPoint p);

	void EndOfEditing();

public:
	CDCRenderTarget		m_RenderTarget;
	CD2DSolidColorBrush* m_pBlackBrush;

	ID2D1Factory *mp_factory = NULL;
	ID2D1HwndRenderTarget *mp_render_target = NULL;

	unsigned int m_target_cx, m_target_cy;
	float m_rate_cx, m_rate_cy;
	D2D1_SIZE_F m_render_size;
private:
	void DrawEditingResource(CDCRenderTarget* pRenderTarget, int offsetX = 0, int offsetY = 0);
public:
	CDC mem_dc;
	CBitmap memBitmap;
	CDC transDC;
	CBitmap transBitmap;
	CDC map_dc;
	CBitmap mapBitmap;

	volatile int			     m_Icon;

	CPoint			 m_ptCurrentPoint; 
	double			 moveMX;
	double			 moveMY; 
	CPoint			m_sp, m_ep;  
	bool			 m_bMoveStart;
	bool			 m_bMapRefesh; 
	bool			 m_bLButtonDown;
	CPoint m_ptCurrent; 

	CPoint m_ptLDown; 
	CPoint m_ptLUp; 

	CPoint m_ptMDown; 
	CPoint m_ptMUp; 


	CPoint m_ptRDown; 
	CPoint m_ptRUp; 
	bool   m_bLMove; 
	bool   m_bRMove;  
	CString			 m_strScale;
	CString			 m_strLatitude;
	CString			 m_strLongitude; 
	double m_moveUnitX, m_moveUnitY;
	double m_movePointX, m_movePointY;

	CSymbolManager *m_pSymbolManager;    
	static CDialogExPickReport* m_pDlgPickReport;

	CDialogDockCurrentSelection* m_pDlgCurrentSelection;
	 
	CPoint ptPick;
	bool onPickArrow;
	bool isMoved;
	ENC_Feature* fePick = nullptr;
	GML_Feature* fePickGML = nullptr;
	R_FeatureRecord* frPick = nullptr; 
	double ptPickX;
	double ptPickY;
	double ptOldPickX;
	double ptOldPickY;

	bool bExpired;

	ENC_Feature* feSearchObject; 
	Layer*			m_pSelectedLayer; 
	unsigned int modifyWaypointIndex; 
	bool         beModifyWaypoint;  
	void DrawZoomArea(CDC* pDC);
	CPoint m_ptStartZoomArea;
	CPoint m_ptEndZoomArea;
	bool m_bZoomArea; 
public: 

	void OpenWorldMap();
	void OpenDefaultExchangeSet();
	void MapRefresh();
	void S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);

	void MoveMapToMyPosition();

	void DrawSelectedLayerRect(HDC& _hdc, int offsetX = 0, int offsetY = 0);

	void GetGMLAttributesString(GML_Attribute*& attr, std::wstring &string, int depth = 0);
	void DrawPickReport(HDC& _hdc, int offsetX = 0, int offsetY = 0);
	void DrawS101PickReport(Graphics& g, int offsetX = 0, int offsetY = 0);
	void ClearPickReport();
	void PickReport(CPoint _point);
	void PickMReport(CPoint _spoint, CPoint _epoint);

	void PickReportS57(CPoint _point, ENCCell* cell);
	void PickReportS101(CPoint _point, S101Cell* cell);

	void CurrentSelectionS101(CPoint _point, S101Cell* cell);
	void AddCurrentSelectionObject(CStringArray *csa);

	string* StringSplit(string strTarget, string strTok);


	void SetPickReportFeature(R_FeatureRecord* _fr);
	ENCLayer* GetLayerToPointFromExchangeSet(double x, double y);

	void DrawUIScale();
	void DrawUILatDegree();
	void DrawUILatDMS();
	void DrawUILonDegree();
	void DrawUILonDMS();
	void DrawCopyright(CDC* pDC); 
	void SaveLastPosScale(); 
	void DrawIndexMap(); 
	void DrawWatermark(CDC* pDC);
	
	void GetSelectedPC();


	R_FeatureRecord* OnMenuTextplacement(); 
	RT::RoutePlanner			*pRoutePlanner;
	RT::UserDefinedLayer        *pUserDefinedLayer; 
	RT::Route *pRouteForCheck;
	RT::Route* pRouteCheckResult;

	RT::RoutePlanner* pRoutePlannerForCheck;
	RT::RoutePlanner* pRoutePlannerForCheckResult;

	void DrawRouteCheck(CDC* pDC, bool isMoveDraw);
	bool m_bRouteCheckOwnShip;
	Gdiplus::Point ownShipVector[3];
	bool m_bRouteCheckOwnShipCent;
	bool m_bRoutePlay;

	int routeSpeed; 
	RT::PointD SimpleRightBufPoint(double _x, double _y, double _heading, double _distance, bool _radian = true);
	RT::PointD SimpleLeftBufPoint(double _x, double _y, double _heading, double _distance, bool _radian = true);
	double GetAngleFromLegs(double _heading1, double _heading2, bool _radian = true);
	bool IsRight(double _x1Leg1, double _y1Leg1, double _x2Leg1, double _y2Leg1,
		double _x1Leg2, double _y1Leg2, double _x2Leg2, double _y2Leg2);

	void MakeOwnShipPosition();
	void DrawOwnShip(CDC* pDC, bool isMoveDraw);
	void DrawOwnShip(CDC* pDC, bool isMoveDraw, GeoPoint* ptWp, RT::BufLeg* rightBufLeg, RT::BufLeg* leftBufLeg, bool* isRight, double* startOffset, double* endOffset, double buffDistance, int waypointCount);
	void DrawOwnShip(CDC* pDC, bool isMoveDraw, int _x, int _y, double _heading, bool _radian); 
	bool CheckFilePath(CString filePath);

	void SaveTile(CImage& image, HDC& hdc, int x, int y, int z, CString path);

public:
	long GetCatalogType(UINT wParam, LONG lParam); 
	HRESULT CreateDirect2dDeviceIndependentResources(); 
	HRESULT CreateDirect2dDeviceResources(); 
	void DiscardDirect2dDeviceIndependentResouces(); 
	void DiscardDirect2dDeviceResources();   
	ID2D1Factory1* m_pDirect2dFactory;
	IWICImagingFactory* pWICFactory;
	ID2D1StrokeStyle1* m_pStrokeStyleS101Solid; 
	ID2D1DCRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pDirect2dSolidColorBrush;
	IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr; 
public:
	virtual void OnDraw(CDC* pDC); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	R_FeatureRecord* GetSelectedFeature();

protected: 
public:
	virtual ~CGISViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif 
public:
		FeatureType* SelectedFeatureType = nullptr; 
		CString DataPath;

protected:

public:
	afx_msg void OnFeatureAddMultiPoint();
	afx_msg void OnFeatureAddPoint();
	afx_msg void OnFeatureAddLine();
	afx_msg void OnFeatureAddArea();
	afx_msg void OnFeatureChange();
	afx_msg void OnENCNewCell();
	afx_msg void OnFeatureAddUseExistingVector();
	afx_msg void OnFeatureAddFeatureRelation();
	afx_msg void OnUpdateFeatureAddMultiPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFeatureAddPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFeatureAddLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFeatureAddArea(CCmdUI *pCmdUI);

	afx_msg void OnUpdateFeatureAddUseExistingVector(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFeatureAddFeatureRelation(CCmdUI *pCmdUI); 
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

	bool OpenExFilePath(CString txtFilepath);
	void SaveExFilePath(CString data, CString pc, CString fc);   


	afx_msg void OnFileSave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnLayerFeatureSearch(); 
	afx_msg void OnBtnLayerShowYourMessage();
	afx_msg void OnBtnSelectFilter();
	afx_msg void OnBtnCreateNoGeometry();
	afx_msg void OnBtnCreateInformationFeature();
	afx_msg void OnBtnCreateAutoRelation();
	afx_msg void OnBtnCreateSoundingByXyzFile();

	afx_msg void OnBtnShowLayoutLayerManager();
	afx_msg void OnBtnShowLayoutPickReport();
	afx_msg void OnBtnShowLayoutCurrentSelection();
	afx_msg void OnBtnShowLayoutRoutePlan();
	afx_msg void OnBtnShowLayoutAttributeList();
	afx_msg void OnBtnShowLayoutFeatureInformation();
	afx_msg void OnBtnShowLayoutRelation();
	afx_msg void OnBtnShowLayoutLogger();
	afx_msg void OnBtnRelationListAll();
	
	

	afx_msg void OnButtonZoomIn();
	afx_msg void OnButtonZoomOut();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnButtonViewAll();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate(); 
	afx_msg void OnButtonModifyWp();

	afx_msg void OnUpdateEditScale(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditLatitude(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditLongitude(CCmdUI *pCmdUI);

	afx_msg void OnButtonRotateClockwise();
	afx_msg void OnButtonRotateAnticlockwise();
	afx_msg void OnButtonNorthUp();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateEditTmpLong(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditTmpLat(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonLmAdd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpenExchange();


	afx_msg void OnUpdateComboScale(CCmdUI *pCmdUI);
	afx_msg void OnComboScale();
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonMovePoint();
	afx_msg void OnMove(int x, int y);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnButtonDistance();
	afx_msg void OnUpdateButtonDistance(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonMeasureArea();
	afx_msg void OnUpdateButtonMeasureArea(CCmdUI *pCmdUI);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnButtonMoveByLatAndLon();
	afx_msg void OnButtonReadPcOutputXml();
	afx_msg void OnButtonS102Color(); 
	afx_msg void OnButtonRouteAdd();
	afx_msg void OnUpdateButtonRouteAdd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonRouteModify(CCmdUI *pCmdUI);
	afx_msg void OnButtonRouteModify();
	afx_msg void OnButtonRouteDelete();
	afx_msg void OnUpdateButtonRouteDelete(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointAdd();
	afx_msg void OnUpdateButtonWaypointAdd(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointModify();
	afx_msg void OnUpdateButtonWaypointModify(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointDelete();
	afx_msg void OnUpdateButtonWaypointDelete(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointMouseAdd();
	afx_msg void OnUpdateButtonWaypointMouseAdd(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointMouseModify();
	afx_msg void OnUpdateButtonWaypointMouseModify(CCmdUI *pCmdUI);
	afx_msg void OnButtonWaypointMouseDelete();
	afx_msg void OnUpdateButtonWaypointMouseDelete(CCmdUI *pCmdUI);
	afx_msg void OnButtonRouteLoad();
	afx_msg void OnUpdateButtonRouteLoad(CCmdUI *pCmdUI);
	afx_msg void OnButtonRouteSave();
	afx_msg void OnUpdateButtonRouteSave(CCmdUI *pCmdUI);

	afx_msg void OnButtonRouteCheck();
	afx_msg void OnSliderRoute();

	afx_msg void OnButtonRouteSlow();
	afx_msg void OnButtonRoutePrev();
	afx_msg void OnButtonRoutePlay();
	afx_msg void OnButtonRoutePause();
	afx_msg void OnButtonRouteStop();
	afx_msg void OnButtonRouteNext();
	afx_msg void OnButtonRouteFast();


	void OpenRouteFromGML(CString _filePathName);
	void OpenRouteFromGMLByPugi(CString _filepath);
	void SaveRoutePlanAsGML(CString _filePathName, unsigned int _index);
	void DrawRoute(CDC* pDC, bool isMoveDraw = false, int offsetX = 0, int offsetY = 0);
	void DrawRouteBuffer(CDC* pDC, int _routeIndex, bool isMoveDraw = false);

	

	afx_msg void OnButtonEditAraeInnerCircle();
	afx_msg void OnUpdateButtonEditAraeInnerCircle(CCmdUI *pCmdUI);
	afx_msg void OnButtonEditUndo();
	afx_msg void OnButtonEditRedo();
	afx_msg void OnButtonEditMouseVector();
	afx_msg void OnUpdateButtonEditMouseVector(CCmdUI *pCmdUI);
	afx_msg void OnButtonScaledSymbolSize();
	afx_msg void OnUpdateButtonScaledSymbolSize(CCmdUI *pCmdUI);
	afx_msg void OnButtonApplyDataCoverageScale();
	afx_msg void OnUpdateButtonApplyDataCoverageScale(CCmdUI *pCmdUI);
	afx_msg void OnButtonEditMouseVectorDelete();
	afx_msg void OnButtonEditMouseVectorAdd();


	afx_msg void OnButtonS111IndexUp();
	afx_msg void OnButtonS111IndexDn();

	afx_msg void OnButtonS111IndexPlay();
	afx_msg void OnUpdateButtonS111IndexPlay(CCmdUI *pCmdUI);
	afx_msg void OnButtonS111IndexStop();

	afx_msg void OnButtonZoomArea();
	afx_msg void OnUpdateButtonZoomArea(CCmdUI *pCmdUI);

	
	afx_msg void OnButtonEditSnap();
	afx_msg void OnS100ExchangeSetOpen();


	afx_msg void OnButtonICOpen();
	afx_msg void OnComboICLevel();

	afx_msg void OnButtonCreateCatalog();
	afx_msg void OnButtonGetDepthAreaInfo();
	afx_msg void OnButtonGetBridgeInfo();

	afx_msg void OnButtonShowOverscale();
	afx_msg void OnUpdateButtonEditSnap(CCmdUI *pCmdUI);

	afx_msg void OnButtonUncertainty();
	afx_msg void OnUpdateButtonUncertainty(CCmdUI *pCmdUI);

	afx_msg void OnButtonTextPlacement_SAVE();
	afx_msg void OnButtonCreateTextPlacement_from_S57ENC();

	afx_msg void OnButtonTextPlacement_ON_OFF();
	afx_msg void OnUpdateButtonTextPlacement_ON_OFF(CCmdUI *pCmdUI);

	afx_msg void OnButtonBaseMapOnOff();
	afx_msg void OnUpdateButtonBaseMapOnOff(CCmdUI *pCmdUI);

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg void OnButtonGoToKoreaArea();
	afx_msg void OnPcfcsavebutton();
	afx_msg void OnDatasetsavebutton();
	
	afx_msg void OnZooninlayer();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnButtonGenerateTileMap();
};

#ifndef _DEBUG 
inline CGISViewerDoc* CGISViewerView::GetDocument() const
   { return reinterpret_cast<CGISViewerDoc*>(m_pDocument); }
#endif
