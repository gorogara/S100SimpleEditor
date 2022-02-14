// QUAPOS01 
#pragma once
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\LCParameters.h"

class ENCCell;
class ENCGeometry;

class ENC_CS_QUAPOS01 : public ENC_ConditionalSymbol
{
public:
	ENC_CS_QUAPOS01(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_QUAPOS01();

public:
	int m_conrad;
	int m_quapos;
	SYParameters m_SYParam;
	LSParameters m_LSParam;
	LSParameters m_LSParam2;
	LCParameters m_LCParam;
	int m_DrawingType;
	ENCCell* m_cell;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void Serialize(CArchive &ar);
};

