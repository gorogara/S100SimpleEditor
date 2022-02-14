#pragma once
#include "..\\PLLibrary\\SYParameters.h"   
class ENC_CS_TOPMAR01 : public ENC_ConditionalSymbol
{
public:
	ENC_CS_TOPMAR01(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_TOPMAR01();
public:
	int m_TOPSHP;
	bool m_bFloating;

	SYParameters m_SYParam;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
};




