#pragma once
#include "..\\PLLibrary\\SYParameters.h"
#include <list>

class ENCCell;
class ENCGeometry;

class ENC_CS_RESTRN01 : public ENC_ConditionalSymbol
{
public:
	ENC_CS_RESTRN01(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_RESTRN01();

public:
	int m_DrawingType;
	ENCCell* m_cell;
	std::list<unsigned> m_RESTRNList;
	SYParameters m_SYParam;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void Serialize(CArchive &ar);
};

