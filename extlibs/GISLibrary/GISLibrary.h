#pragma once

#include "LayerManager.h"
#include "S111NumericalInfo.h"

#include "D2D1Resources.h"

#include "..\\libS111\\libS111.h"

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

class S100Engine;
struct ID2D1Factory1;
struct ID2D1StrokeStyle1;

class CGISLibraryApp
{
public:
	CGISLibraryApp();
	virtual ~CGISLibraryApp();

public:
	Scaler* m_pScaler;
	LayerManager* m_pLayerManager;
#ifdef ROUTE_CHECK
	LayerManager* m_pRCLayerManager;
#endif
	std::vector<S111NumericalInfo> s111matrix; 
	ID2D1DCRenderTarget* m_pRenderTarget = nullptr;
	ID2D1SolidColorBrush* m_pDirect2DSolibBrush = nullptr; 
	IWICImagingFactory* pWICFactory = nullptr;
	ID2D1PathGeometry* m_pS111ArrowGeometry = nullptr;
	ID2D1Factory1* m_pDirect2dFactory = nullptr;
	ID2D1StrokeStyle1 *m_pStroke = nullptr;
	IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;

	S100Engine *s100Engine = nullptr;

	libS413::S413FeatureType s413Type = libS413::WaveWind;

	GISLibrary::D2D1Resources D2;
public:
	Scaler* GetScaler();
	LayerManager* GetLayerManager();

	int GetLayerIndex(CString pathName);

	void InitS100Engine();

	void InitLibrary();

	bool AddExchangeSet(CString _filepath);
	bool AddBackgroundLayer(CString _filepath);
	bool AddLayer(CString _filepath);
	bool AddLayer(CString _filepath, Catalog* fc, PortrayalCatalogue* pc);
	bool AddLayerFromS100ExchangeSet(CString _filepath, Catalog* fc, PortrayalCatalogue* pc);
	bool AddValidationLayer(CString _filepath);
	bool AddShipMonitoring(CString _filePath);

	void Draw(HDC &hDC, int offset = 0);
	void Draw(CDCRenderTarget* pRenderTarget, double offsetX = 0, double offsetY = 0);
	void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, double offsetX = 0, double offsetY = 0);
	void BuildS101Portrayal(Layer* l/*, PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void DeleteS101Portrayal(Layer* l/*, PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void DrawValidationLayers(HDC &hDC, int offset = 0);
	void DrawOverlay(HDC &hDC, int type, int offset = 0);
	void DrawShipMonitoringLayer(HDC &hDC, int offset = 0);
	void GetLayer(int index, Layer *_layer);
	Layer* GetLayer(int index);

	void LayerOn(int index);
	void LayerInfoOn(int index);

	void LayerOff(int index);
	void LayerInfoOff(int index);

	void LayerUp(int index);
	void LayerDown(int index);
	CString GetLayerName(int index);
	BOOL IsOn(int index);
	void DeleteLayer(int index);
	void DeleteLayer(CString filepath);
	void DeleteAllLayer();
	void ReMBR();

	void ClearInformationLayer(int index);
	void ClearInformationLayer(CString filepath);
	void ClearAllInformationLayer();
	void CheckDataCoverageComputing();

	void SaveLayerTextPlacement(CString filename, CString extend, int index);
	void SaveLayer(CString filename, CString extend, int index);
	void SaveLayer(CString filename, CString extend, Layer* pLayer);

	void UpdateCS_SafetyDepth();
	void UpdateCS_SafetyContour();
	void UpdateCS_ShadeType();
	void ChangeDisplayMode();
	void UpdateCS_BoundarySymbol();  
	void UpdateS102ColorMapType(int _type, std::vector<COLORREF> _colorMap);
	void GetS102ColorMapType(int& _type, std::vector<COLORREF>& _colorMap);

	ENC_ExchangeSet*	GetExchangeSet();
	ENCLayer*			GetOverlayLayer(int type);

	void SetViewMBR(RECT r);

	void SetTestLayer(ENCLayer* _enc); 
	int GetLayerCount();
	std::vector<Layer*> GetAllLayer();

	MBR* GetMBR();
	void SetColorTable(wstring _path);

	ListFindedFeature* FindFeatures(int code, ListFindedFeature &feList);
	ListFindedFeature* FindFeatures(wchar_t* acronym, ListFindedFeature &feList);
	void SetOwnShipCoordinate(double lon, double lat);
	void MoveToOwnShipLocation(int sx, int sy);   
	void DeviceToWorld(long sx, long sy, double *mx, double *my, bool rotate = TRUE);
	void WorldToDevice(double mx, double my, long *sx, long *sy, bool rotate = TRUE); 
	double GetDistanceLatitudeLongitude(double longitude1, double latitude1, double longitude2, double latitude2);
	double GetDistanceScreen(int x1, int y1, int x2, int y2);  
	void SetScreen(RECT *rect);
	void SetScreen(const RECT& rect);
	int GetCenterXScreen();
	int GetCenterYScreen(); 
	void SetMap(double xmin, double ymin, double xmax, double ymax);
	void SetMap(MBR mbr);

	double GetMapWidth();
	double GetMapHeight();

	void GetMap(MBR *mbr); 
	int GetCurrentScale();
	void   SetScale(int scale);
	void   UpdateScale(); 
	void ZoomIn(double value);
	void ZoomIn(double value, int x, int y);
	void ZoomOut(double value);
	void ZoomOut(double value, int x, int y);
	void AdjustScreenMap();  
	void MoveMap(int x, int y); 
	void MoveMap(int sx, int sy, double mx, double my);

	void Projection(double *x, double *y);
	void InverseProjection(double *x, double *y); 
	void Rotate(LONG *sx, LONG *sy, double degree);
	void RotateMap(double degree); 
	void NorthUp();

	void NextTimeIndex();
	void PrevTimeIndex();

	bool PtInMap(double _x, double _y);
	ClipperLib::PolyTree* ClipPolyline(GeoPoint* _p, int _cnt);


	void ChangeDisplayFont();

	void SetDrawBackground(bool on);
	bool GetDrawBackground();

	void SetExPCPath(CString value);
	CString GetExPCPath();

	void SetExFCPath(CString value);
	CString GetExFCPath();

};
extern CGISLibraryApp* gisLib;