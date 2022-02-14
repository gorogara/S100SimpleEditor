#pragma once
#include "S101_ConditionalSymbol.h"
#include "..\\PLLibrary\\SYParameters.h"

////////////////////////////////////////////////////////////
// coded by dnwk
// TOPMAR01 ////////////////////////////////////////////////
class R_FeatureRecord;
class S101Cell;
class SGeometry;

class S101_CS_TOPMAR01 : public S101_ConditionalSymbol
{
public:
	S101_CS_TOPMAR01(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_TOPMAR01();
public:
	int m_TOPSHP;
	bool m_bFloating;

	SYParameters m_SYParam;

public:
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
};




