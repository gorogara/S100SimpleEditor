#pragma once

#include "ENC_ExchangeSet.h"
#include "OwnShipLayer.h"
#include "AddtionalStruct.h"
#include "S101_CoverageLayer.h"
#include "S101Cell.h"

#include "..\\FeatureCatalog\\Catalog.h"
#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#include <vector>
#include <functional>

class Scaler;
class ENCCell;
class S111Layer;
class ShipMonitoringLayer;
class PortrayalCatalogue;
class CGISViewerView; 
class SENC_Instruction;

#define MSG_GETCATALOG 0x001F1F1F

class LayerManager
{
public:
	LayerManager(void);
	virtual ~LayerManager(void);

public:
	Scaler					*scaler = nullptr; 
	CList <Layer*, Layer* > m_listBackgroundLayer; 
	CList <ShipMonitoringLayer*, ShipMonitoringLayer* > m_listShipMonitoringLayer; 
	ENC_ExchangeSet			m_exchangeSet; 
	std::vector<Layer*>		m_listLayer;
	std::vector<Layer*>		m_SelectedLayer; 
	std::vector<S101_CoverageLayer* > m_s101DataCoverages;
	bool bShowDataCoverageOverscale; 
	list <ENCLayer*>		m_overlayLayer;
	MBR						mbr;
	ENCLayer				*gml_testLayer; 
	list <ENCLayer*>		m_validationLayer; 
	Layer*					m_coastlineLayer;
	static MBR ViewMBR;
	static std::unordered_map< Catalog*, PortrayalCatalogue*> CatalogueList;//피쳐 카탈로그와 포트리얼 카탈로그를 저장합니다.
	OwnShipLayer		m_ownShip; 
	CGeoObjectMap m_object;
	CAttributeMap m_attribute;
	CColorMap m_color;
	CSymbolMap *m_symbol;            
	int SelectCatalogindex = -1;
	static std::vector<PortrayalCatalogue*>	*pPortrayalCatalogues;
	static std::vector<Catalog*>			*pS100Catalogs;
	static std::unordered_map<std::wstring, PortrayalCatalogue*> *hash_PC;
	static std::unordered_map<std::wstring, Catalog*> *hash_FC;  
	CString selectedFCPath;
	CString selectedPCPath; 
	std::set<int> lineSuppressionMap;
#ifdef DEBUG
	bool m_baseMapOn = false;
#else
	bool m_baseMapOn = true;
#endif

	CString ExPCPath;
	CString ExFCPath;



public:
	void SetViewMBR(RECT r);
	ENC_ExchangeSet*	GetExchangeSet();
	ENCLayer*			GetOverlayLayer(int type);

	void InitPortrayal(CDC* pDC);
	void LoadFeatureCatalogs();

	bool AddExchangeSet(CString _filepath);
	bool AddBackgroundLayer(CString _filepath);
	bool AddLayer(CString _filepath);
	bool AddLayer(CString _filepath, Catalog* fc, PortrayalCatalogue* pc);
	bool AddLayerFromS100ExchangeSet(CString _filepath, Catalog* fc, PortrayalCatalogue* pc);
	bool AddLayer(Layer* layer); 
	static UINT WINAPI AddLayer_thread(LPVOID); 
	void AddLayerStart(CString _filename); 
	bool SetS101CoverageLayer(Layer *layer);

	Layer* LoadCoastline(CString _filepath);
	bool AddOverlayLayer(CString _filepath);
	bool AddShipMonitoringLayer(CString _filePath); 
	unsigned m_surfaceCurrentIndex = 0;
	void DrawS111(HDC &hDC, S111Layer *s111Layer, int offsetX, int offsetY);

	void BuildS101Portrayal(Layer* l/*, PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void DeleteS101Portrayal(Layer* l/*, PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void S101RebuildPortrayal(/*PORTRAYAL_BUILD_TYPE type = PORTRAYAL_BUILD_TYPE::ALL*/);
	void Apply_S100_IC(Layer* l);
	void Draw(HDC &hDC, int offset = 0);
	void DrawLayerList(HDC &hDC, int offset = 0);
	void DrawBackground(HDC &hDC, int offset = 0);
	void DrawS100Datasets(HDC &hDC, int offset = 0);
	void DrawS100Datasets_IC_OFF(HDC &hDC, int offset = 0);
	void DrawS100Datasets_IC_ON(HDC &hDC, int offset = 0);


	float GetTextPlaceBearingValue(S101Cell* c, R_FeatureRecord* fr);
	void DrawS100TextPlacementSemiCircle(HDC &hDC);
	void DrawSemiCircle(float x, float y, float radius, float startAngle, float endAngle); 
	void AddSymbolDrawing(
		int i,
		HDC &hdc,
		int offset,
		std::list<SENC_Instruction*>*augmentedRay,
		std::list<SENC_Instruction*>*augmentedPath,
		std::list<SENC_Instruction*>* point,
		std::list<SENC_Instruction*>* line,
		std::list<SENC_Instruction*>* area,
		std::list<SENC_Instruction*>* text,
		S100_SVG_D2D1_DLL::SVGManager* svg,
		bool IC = false,
		PortrayalCatalogue *pc = nullptr);

	void DrawS100HDF5(HDC &hDC, int drawingPriority, int offset = 0);

	void GetCurrentShowDataCoverageByLayer(Layer* l, S101_CoverageLayer &totalLayer);

	void DrawUncertainty(HDC &hDC, int offset = 0);
	void DrawInformationLayer(HDC &hDC, int nIndex);
	void ClearInformationLayer(int nindex);
	void ClearInformationLayer(CString filepath);
	void ClearAllInformationLayer();
	void CheckDataCoverageComputing();

	void DrawDataCoverageOverscale(HDC &hdc);


	void Draw(CDCRenderTarget* pRenderTarget, double offsetX = 0, double offsetY = 0);
	void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, double offsetX = 0, double offsetY = 0);
	void DrawS101UnitLayers(HDC &hDC, int offset = 0);
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
	int GetLayerIndex(CString _pathName);
	CString GetLayerName(int index);
	BOOL IsOn(int index);
	void DeleteLayer(int index);
	void DeleteLayer(CString filepath);
	void DeleteAllLayer();
	void ReMBR();

	void SaveLayerTextPlacement(CString filename, CString extend, int index);
	void SaveLayer(CString filename, CString extend, int index);
	void SaveLayer(CString filename, CString extend, Layer* layer);

	void UpdateCS_SafetyDepth();
	void UpdateCS_SafetyContour();
	void UpdateCS_ShadeType();
	void UpdateCS_BoundarySymbol();
	void ChangeDisplayMode();  
	void UpdateS102ColorMapType(int _type, std::vector<COLORREF> _colorMap);
	void GetS102ColorMapType(int& _type, std::vector<COLORREF>& _colorMap);

	void NextTimeIndex();
	void PrevTimeIndex(); 
	void DrawSounding(HDC hDC); 
	void ShowTextPlacement(BOOL bShow); 
	void ShowUncertainty(BOOL bShow); 
	int(*GetSelectedCatalogIndex)(CString filepath) = nullptr;

	static Catalog* AddS100FC(std::wstring path);
	static PortrayalCatalogue* AddS100PC(Catalog* fc, std::wstring path);
	static PortrayalCatalogue* AddS100PC(Catalog* fc, std::wstring path, std::wstring currentName);

	Catalog* GetCatalog(int index);
	PortrayalCatalogue* GetPortrayalCatalogue(int index);  
	CRect TXWhiteBack(HDC&    hDC, 
		POINT   _p, 
		CString _string, 
		int     _HJUST, 
		int		_VJUST, 
		int		__SPACE, 
		int		_STYLE, 
		int     _WEIGHT, 
		int     _WIDTH, 
		int		_BODYSIZE, 
		int		_XOFFS, 
		int		_YOFFS, 
		int		_red, 
		int		_green, 
		int		_blue 
	);

	int GetLayerCount();

	ListFindedFeature* FindFeatures(int code, ListFindedFeature &feList);
	ListFindedFeature* FindFeatures(wchar_t* acronym, ListFindedFeature &feList);

	void SetTestLayer(ENCLayer*);

	void InitValidationLayer();
	bool AddValidationLayer(CString _filepath);
	size_t GetValidationLayerCount();

	void ChangeS100ColorPalette(std::wstring paletteName);

	void SetSelectedFCPath(CString value);
	CString GetSelectedFCPath();
	void SetSelectedPCPath(CString value);
	CString GetSelectedPCPath();

	int SelectFCPC(CString path, Layer* layer, Catalog* fc, PortrayalCatalogue* pc);

	Scaler* GetScaler();

	static Catalog* GetFC(int productNumber);
	static PortrayalCatalogue* GetPC(int productNumber);

	static Catalog* GetFC(std::wstring fcName);
	static PortrayalCatalogue* GetPC(std::wstring pcName);

	CString GetExPCPath();
	void SetExPCPath(CString value);

	CString GetExFCPath();
	void SetExFCPath(CString value);
};