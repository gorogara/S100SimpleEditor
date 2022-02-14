#pragma once

#include "..\\GeoMetryLibrary\\Scaler.h"
#include "..\\PLLibrary\\PLCommon.h"
#include "..\\PLLibrary\\GeoObjectMap.h"
#include "..\\PLLibrary\\AttributeMap.h"
#include "..\\PLLibrary\\ColorMap.h"
#include "..\\PLLibrary\\SymbolMap.h"
#include "..\\PLLibrary\\TXParameters.h"
#include "..\\PLLibrary\\TEParameters.h"

#include "..\\S100_SVG_D2D1_DLL\\SVG.h"

#include <list>

class R_FeatureRecord;
class SENC_TextInstruction;
class SSurface;
class Symbol;
class SENC_SymbolFill;
class SENC_LineStyle;
class SENC_ArcByRadius;
class SENC_SpatialReference;

class SENC_Instruction
{
public: 
	SENC_Instruction();
	virtual ~SENC_Instruction();

public:  
	unsigned type;   
	unsigned featureReference; 
	std::list<SENC_SpatialReference*> spatialReference; 
	int viewingGroup; 
	int displayPlane; 
	int drawingPriority;
	int drawingPriority_initValue; 
	unsigned scaleMinimum; 
	unsigned scaleMaximum;

	bool suppressedInstance; 
	R_FeatureRecord* fr;

	static bool AvoidClutter;
	static std::list<CRect> TextCommonRects;
	static std::list<CRect> SoundingTestRects;
	static std::list<CRect> IsobathTextRects; 

public:  
	bool HasSpatialReference();

	virtual void GetDrawPoints(Scaler *scaler, std::list<D2D1_POINT_2F> &points){};
	virtual void GetDrawPointsDynamic(Scaler *scaler, std::list<D2D1_POINT_2F> &points){};

	virtual void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr) {};
	virtual void DrawInstruction(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush, std::vector<ID2D1StrokeStyle1*>* strokeGroup, Scaler *scaler, PortrayalCatalogue* pc = nullptr) {};
	virtual void DrawInstruction(ID2D1DCRenderTarget* rt, ID2D1Factory1* pDirect2dFactory, ID2D1SolidColorBrush* brush, std::vector<ID2D1StrokeStyle1*>* strokeGroup, Scaler *scaler, PortrayalCatalogue* pc = nullptr) {};
	virtual void DrawInstruction(CDCRenderTarget* pRenderTarget, Scaler *scaler){};
	virtual void DrawInstruction(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler){};
	virtual void DrawInstructionDirectX(ID2D1DCRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pDirect2dSolidColorBrushScaler, Scaler* scaler){};

	void DrawTextInstruction(HDC& hDC, SENC_TextInstruction* li, unsigned &strIndex, POINT _p, double _rotation);
	void DrawPointInstruction(HDC& hDC, POINT &_p, S100_SVG_D2D1_DLL::SVG* pSVG, int _rotation, double scaleFactor);
	void DrawCurveInstruction(HDC &hDC, POINT *_p, int _count, int _style, int _width, int _red, int _green, int _blue);
	void DrawSurfaceInstruction(HDC &hDC, POINT *_p, int _count, int _red, int _green, int _blue, int _transparency);

	void DrawTextInstruction(CDCRenderTarget* pRenderTarget, SENC_TextInstruction* li, unsigned &strIndex, POINT _p, double _rotation);
	void DrawPointInstruction(CDCRenderTarget* pRenderTarget, POINT &_p, S100_SVG_D2D1_DLL::SVG* pSVG, int _rotation);
	
	void AddDX2DPoint(CD2DGeometrySink* pSink, POINT *_p, int _count);
	void DrawSurfaceInstruction(CDCRenderTarget* pRenderTarget, POINT *_p, int _count, int _red, int _green, int _blue, int _transparency);

	virtual void ChangePallete(PortrayalCatalogue *pc) {}; 
	void AC(HDC &hDC, POINT *_p, int _count, COLOUR *_color, int _transparency); 
	void AP(HDC &hDC, POINT *_p, int _count, CSymbol *_symbol, int APIndex); 
	void AP(HDC &hDC, POINT *_p, int _count, CString _symbolName); 
	void AP(HDC &hDC, POINT *_p, int _count, SENC_SymbolFill *_symbolFill); 
	void LS(HDC &hDC, POINT *_p, int _count, int _style, int _width, int _red, int _green, int _blue); 
	void LC(HDC &hDC, POINT *_p, int _count, CSymbol *_symbol, int LCIndex); 
	void LC(HDC &hDC, POINT *_p, int _count, CString _symbolName); 
	void DrawLineStyle(HDC &hDC, Scaler* scaler, POINT *_p, int _count, SENC_LineStyle *_lineStyle, PortrayalCatalogue* pc = nullptr); 
	void DrawArcByRadius(HDC &hDC, POINT *_p, int _count, SENC_LineStyle *_lineStyle, SENC_ArcByRadius* _arcByRadius);  
	CRect TX(HDC&    hDC, 
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
	void TXWhiteBack(HDC&    hDC, 
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
	void TX(HDC& hDC, POINT _p, CSymbol *_symbol, int TXIndex); 
	void TX(HDC& hDC, POINT _p, TXParameters* _txParam); 
	void TE(HDC& hDC, POINT _p, CSymbol *_symbol, int TEIndex); 
	void TE(HDC &hDC, POINT _p, TEParameters* _teParam); 
	void SY(HDC& hDC, POINT _p, CString _symbolName, double _rotation = 0.0); 
	void SY(HDC& hDC, POINT _p, CSymbol *_symbol, int SYIndex);  
	void CalculateCenterOfGravityOfSurface(std::vector<POINT> &vp, SSurface *_surface, CRect *_viewPort, Scaler *pScaler); 
	ClipperLib::Paths ClipSurface(SSurface *_polygon, CRect *_viewPort); 
	POINT CalculateCenterOfGravityOfSurface(POINT *_p, int _count); 
	POINT CalculateCenterOfGravityOfSurface(ClipperLib::Path polygon); 
	double GetDistance(POINT _p1, POINT _p2); 
	double GetDistanceOfPolyline(POINT *_p, int _count); 
	void GetViewLineInPolyline(POINT *_p, int _count); 
	POINT* GetCenterPointOfPolyline(POINT *_p, int _count); 
	bool IsIntersect(POINT _s1, POINT _e1, POINT _s2, POINT _e2); 
	void CutLineToIntersect(POINT &_s1, POINT &_e1, POINT _s2, POINT _e2); 
	double GetAngle(POINT _p1, POINT _p2); 
	POINT GetOffsetPointOnLine(POINT _p1, POINT _p2, double offset);
	Gdiplus::PointF GetOffsetPointFOnLine(POINT _p1, POINT _p2, double offset);
	Gdiplus::PointF GetOffsetPointFOnLine(POINT _p1, POINT _p2, double offset, double gapX, double gapY); 
	void DrawCompositeLineOnLine(CDC *pDC, POINT _p1, POINT _p2, Symbol* _symbol); 
	void DrawCompositeLineOnPolyline(CDC *pDC, POINT *_p, int _count, Symbol* _symbol);
};

