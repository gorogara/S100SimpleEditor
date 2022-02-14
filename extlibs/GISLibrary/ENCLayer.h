#pragma once

#include "Layer.h" 
#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#define MARINERLAYER_WP				0x00000001
#define MARINERLAYER_SHIP			0x00000002

class ENCCell;
class CGeoObjectMap;
class CAttributeMap;
class CColorMap;
class CSymbolMap;

class ENCLayer : public Layer
{
private:	
	int m_encType;
public:
	ENCLayer(
		CGeoObjectMap *object,
		CAttributeMap *attribute,
		CColorMap *color,
		CSymbolMap *&symbol);
	ENCLayer(
		S100_SVG_D2D1_DLL::SVGManager*  svgSymbolManager,
		CGeoObjectMap *object,
		CAttributeMap *attribute,
		CColorMap *color,
		CSymbolMap *&symbol);

	virtual ~ENCLayer(void);
public: 
	static int CheckENCType(CString _filepath);
	S100_SVG_D2D1_DLL::SVGManager		*p_svgSymbolManager;
	CGeoObjectMap	*p_object;
	CAttributeMap	*p_attribute;
	CColorMap		*p_color;
	CSymbolMap		*p_symbol; 

public:
	virtual bool Open(CString _filepath) override;
	void SetSpatialObject(ENCCell* cell);
	void UpdateCS_SafetyDepth();
	void UpdateCS_SafetyContour();
	void UpdateCS_ShadeType();
	void UpdateCS_BoundarySymbol();
	void ChangeDisplayMode();
	void SetENCType(int type);
	int GetENCType();
};