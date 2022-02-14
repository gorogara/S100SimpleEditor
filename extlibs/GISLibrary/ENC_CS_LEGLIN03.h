#pragma once
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LCParameters.h"
#include "..\\PLLibrary\\LSParameters.h"

class ENC_CS_LEGLIN03 : public ENC_ConditionalSymbol
{
	
public:
	ENC_CS_LEGLIN03(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_LEGLIN03();
	
public:
	int m_select;
	int m_plnspd;
	SYParameters m_SYParam;
	LCParameters m_LCParam;
	LSParameters m_LSParam;
	int m_DrawingType;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void Serialize(CArchive &ar);
};