#pragma once
#include "S101_ConditionalSymbol.h"

#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\LCParameters.h"

// QUAPOS01 ////////////////////////////////////////////////
class S101Cell;
class SGeometry;
class R_FeatureRecord;

class S101_CS_QUAPOS01 : public S101_ConditionalSymbol
{
public:
	S101_CS_QUAPOS01(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_QUAPOS01();
public:
	int m_conrad;
	int m_quapos;
	
	SYParameters m_SYParam;
	LSParameters m_LSParam;
	LSParameters m_LSParam2;
	LCParameters m_LCParam;

	int m_DrawingType;
	S101Cell* m_cell;

public:
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
};

