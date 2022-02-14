#pragma once

#include "geometry.h"
#include "ENCCommon.h"
#include "VectorMaskPair.h"

#include "..\\PLLibrary\\GeoObjectMap.h"
#include "..\\PLLibrary\\AttributeMap.h"
#include "..\\PLLibrary\\ColorMap.h"
#include "..\\PLLibrary\\SymbolMap.h"

#include "..\\S100_SVG_D2D1_DLL\\SVG.h"
#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#include <list>

class CSymbolManager;
class Symbol;
class ENCArea;
class ENCLine;
class ENCPoint;
class ENC_Feature;
class TEParameters;
class TXParameters;


using namespace std;

class ENCGeometry :
	public Geometry
{
public:
	ENCGeometry();
	virtual ~ENCGeometry();

public:   
	static int				typeOfDrawing;
	static CGeoObjectMap	*pObject;
	static CAttributeMap	*pAttribute;
	static CColorMap		*pColor;
	static CSymbolMap		*pSymbol;             
	S100_SVG_D2D1_DLL::SVGManager		*pSVGManager;

	static void SetPLLibrary(
		CGeoObjectMap *object,
		CAttributeMap *attribute,
		CColorMap *color,
		CSymbolMap *&symbol)
	{
		pObject = object;
		pAttribute = attribute;
		pColor = color;
		pSymbol = symbol;
	}

	ENC_Feature *m_pFeature;
	static CSymbolManager *pSymbolManager;
	int m_simplePLIndex;
	int m_paperPLIndex;
	S100_SVG_D2D1_DLL::SVG* m_svgSymbol;
	Pen pen;
	list<VectorMaskPair> m_MaskPairList;

public: 

	static bool AvoidClutter;
	static list<CRect> TextCommonRects;
	static list<CRect> SoundingTestRects;
	static list<CRect> IsobathTextRects;

	static void InitTextRect();
	bool TextClutterCheck(const CRect &r);
	static void InitSoundingTextRect();
	bool SoundingTextClutterCheck(const CRect &r);
	static void InitIsobathTextRect();
	bool IsobathTextClutterCheck(const CRect &r);

protected:

	CObjectFindStruct *m_ObjAttr;
	unsigned m_scaleMin;

public:
	void SetPLIndex(int simple, int paper);
	void SetAttribute(CObjectFindStruct *objAttr);
	void SetScaleMin(unsigned value); 
	void AC(HDC &hDC, POINT *_p, int _count, COLOUR *_color, int _transparency); 
	void AP(HDC &hDC, POINT *_p, int _count, CSymbol *_symbol, int APIndex); 
	void AP(HDC &hDC, POINT *_p, int _count, CString _symbolName); 
	void LS(HDC &hDC, POINT *_p, int _count, int _style, int _width, int _red, int _green, int _blue); 
	void LC(HDC &hDC, POINT *_p, int _count, CSymbol *_symbol, int LCIndex);  
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
	ENCArea* CalculateCenterOfGravityOfPolygon(ENCArea *_polygon, CRect *_viewPort); 
	ENCArea* ClipPolygon(ENCArea *_polygon, CRect *_viewPort); 
	POINT CalculateCenterOfGravityOfPolygon(POINT *_p, int _count); 
	double GetDistance(POINT _p1, POINT _p2); 
	double GetDistanceOfPolyline(POINT *_p, int _count); 
	void GetViewLineInPolyline(POINT *_p, int _count); 
	POINT* GetCenterPointOfPolyline(POINT *_p, int _count); 
	bool IsIntersect(POINT _s1, POINT _e1, POINT _s2, POINT _e2); 
	void CutLineToIntersect(POINT &_s1, POINT &_e1, POINT _s2, POINT _e2); 
	double GetAngle(POINT _p1, POINT _p2); 
	POINT GetOffsetPointOnLine(POINT _p1, POINT _p2, double offset); 
	void DrawCompositeLineOnLine(CDC *pDC, POINT _p1, POINT _p2, Symbol* _symbol); 
	void DrawCompositeLineOnPolyline(CDC *pDC, POINT *_p, int _count, Symbol* _symbol);
};