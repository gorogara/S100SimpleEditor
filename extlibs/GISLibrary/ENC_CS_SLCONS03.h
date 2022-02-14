#pragma once
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"

class ENCCell;
class ENCGeometry;

class ENC_CS_SLCONS03 :
	public ENC_ConditionalSymbol
{
public:
	ENC_CS_SLCONS03(ENC_Feature *_fe, std::wstring);
	virtual ~ENC_CS_SLCONS03();
public:        

	int m_CONDTN; 
	int m_CATSLC; 
	int m_WATLEV; 

	int m_DrawingType;

	int m_QUAPOS;
	SYParameters m_SYParam;
	LSParameters m_LSParam;

public:

	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);  
	void Serialize(CArchive &ar);
};

