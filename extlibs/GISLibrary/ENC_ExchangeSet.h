#pragma once
#include <vector>
#include "ENCLayer.h"
#include "ENC_Catalogue.h"

class ENC_ExchangeSet
{
public:
	ENC_ExchangeSet();
	virtual ~ENC_ExchangeSet();

public:
	CatalogueMap m_catList;
	CatalogueList m_catListByLevel[6];
	
	vector<ENCLayer*> m_showLayer;
	CatalogueList m_loadedListCat[6]; 
private:
	CGeoObjectMap	*p_object;
	CAttributeMap	*p_attribute;
	CColorMap		*p_color;
	CSymbolMap		*p_symbol;                     

	enum PurposeScale
	{
		Berthing = 15000,
		Harbour = 60000,
		Approach = 180000,
		Coastal = 700000,
		General = 2000000,
		Overview = 9000000,
	};

public:
	bool Open(CString fileName);
	CatalogueMap* GetCatalogueMap();

	void SetPLLibrary(
		CGeoObjectMap *object,
		CAttributeMap *attribute,
		CColorMap *color,
		CSymbolMap *&symbol);

	void CheckExchangeSetLayer(Scaler *scaler);
	void Draw(HDC &hDC, Scaler *scaler, double offset);

	void UpdateCS_SafetyDepth();
	void UpdateCS_SafetyContour();
	void UpdateCS_ShadeType();
	void UpdateCS_BoundarySymbol();
	void ChangeDisplayMode();

private:
	bool ReadCatalogue(BYTE*& buf, unsigned size);
	bool ReadDDR(BYTE*& buf);
};