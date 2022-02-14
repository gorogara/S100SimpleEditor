#pragma once

#include "S100_LineManager.h"
#include "Symbol.h"
#include "S100_Text.h"
#include "RealSymbol.h"

#include "SVG.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <d2d1_1.h>

class S100_ColorProfile;
class PortrayalCatalogue;

namespace S100_SVG_D2D1_DLL
{
	class S100_Pattern;
	class SVG;
	class CSS;

	class SVGManager
	{
	public:
		SVGManager();
		SVGManager(std::wstring path, std::wstring paletteName, S100_ColorProfile *colorProfile);
		virtual ~SVGManager();

	public:
		S100_LineManager lineMng; 
		static ID2D1Factory1* m_pDirect2dFactory;
		static ID2D1DCRenderTarget* m_pRenderTarget;
		static ID2D1SolidColorBrush* m_pSolidColorBrush;
		static ID2D1StrokeStyle1* m_pStrokeStyle; 
		std::vector<S100_Pattern*> patList; 
		std::vector<S100_Text> textList; 
		std::vector<RealSymbol> symList; 
		std::unordered_map<std::wstring, SVG*> m_svgMap; 
		std::unordered_map<std::wstring, Symbol> symMap;

	public:
		void SetD2Resource(
			ID2D1Factory1* factory,
			ID2D1DCRenderTarget* renderTarget,
			ID2D1SolidColorBrush* brush,
			ID2D1StrokeStyle1* stroke);

		Symbol* GetSymbol(std::wstring name); 
		void GetSVGFiles(std::wstring path, std::wstring paletteName, S100_ColorProfile *colorProfile);
		void GetSVGFilesByPugiXML(std::wstring svgFolderPath, std::wstring paletteName, S100_ColorProfile *colorProfile);

		void GetCSSFiles(std::wstring cssPath); 
		HRESULT D2_SetFactory(); 
		HRESULT D2_SetTarget(); 
		HRESULT D2_SetBrush(D2D1::ColorF color); 
		void DiscardDeviceResources(); 
		void D2PaintSVG();
		void D2PaintSVG(PortrayalCatalogue *pc); 
		void D2PaintSymboledLine(); 
		void D2PaintBitmap(); 
		void D2PaintText(CRect rectView); 
		void DrawSymbols();
		void DrawSymbols(PortrayalCatalogue *pc);

		void DrawRealSymbol(RealSymbol& symbol);
		void DrawRealSymbol(RealSymbol& symbol, PortrayalCatalogue *pc); 
		void PushSymbol(std::wstring _symName, D2D_POINT_2F _position, float _rotation = 0.0, float _scale = 1.0);

		void SetTarget(CDC* pDC, CRect rectView); 
		D2D1_POINT_2F GetMovePoint(D2D1_POINT_2F point, float dgree, float distance); 
		float Distance(D2D1_POINT_2F p1, D2D1_POINT_2F p2); 
		ID2D1PathGeometry* getPatternGeom(D2D1_POINT_2F* points, int PointSize); 
		void ChangeColorPalette(std::wstring paletteName, S100_ColorProfile *colorProfile);

		void SetD2Factory(ID2D1Factory1* value);
		ID2D1Factory1* GetD2Factory();

		void SetD2RenderTarget(ID2D1DCRenderTarget* value);
		ID2D1DCRenderTarget* GetD2RenderTarget();

		void SetD2Brush(ID2D1SolidColorBrush* value);
		ID2D1SolidColorBrush* GetD2Brush();

		void SetD2Stroke(ID2D1StrokeStyle1* value);
		ID2D1StrokeStyle1* GetD2Stroke();
	};
}