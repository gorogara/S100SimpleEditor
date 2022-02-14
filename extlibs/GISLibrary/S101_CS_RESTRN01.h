#pragma once
#include "S101_ConditionalSymbol.h"
#include "..\\PLLibrary\\SYParameters.h"
#include <list>

class SGeometry;
class S101Cell;

class S101_CS_RESTRN01 : public S101_ConditionalSymbol
{
public:
	S101_CS_RESTRN01(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_RESTRN01();

public:
	int m_DrawingType;
	S101Cell* m_cell;

	std::list<unsigned> m_RESTRNList;

	SYParameters m_SYParam;

public:
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void Serialize(CArchive &ar);
};

