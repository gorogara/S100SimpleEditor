#pragma once
#include "S101_ConditionalSymbol.h"
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"

#pragma once
class S101Cell;
class R_FeatureRecord;
class SGeometry;

class S101_CS_SLCONS03 : 
	public S101_ConditionalSymbol
{
public:
	S101_CS_SLCONS03(R_FeatureRecord *_fe, std::wstring);
	virtual ~S101_CS_SLCONS03();

	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	//void DrawLine(ENCGeometry *_geo, HDC &hDC, Scaler *scaler, double offset = 0);
	//void DrawArea(ENCGeometry *_geo, HDC &hDC, Scaler *scaler, double offset = 0);

	//int lineStyle;
	//int lineWidth;
	//int R;
	//int G;
	//int B;
	//int type; // point : 1
	//		  // line  : 2
	//		  // area  : 3

	int m_CONDTN; // 1 or 2
	int m_CATSLC; // 6, 15 or 16
	int m_WATLEV; // 2, 3 or 4
	
	int m_DrawingType;

	int m_QUAPOS;
	SYParameters m_SYParam;
	LSParameters m_LSParam;

	void Serialize(CArchive &ar);
};



