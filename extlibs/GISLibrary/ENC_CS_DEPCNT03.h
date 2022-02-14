#pragma once

#include "enc_conditionalsymbol.h"
#include "SpatialObjectPairDEPCNT03.h"
#include "SpatialLSParamPair.h"

#include <vector>

class ENC_CS_DEPCNT03 :
	public ENC_ConditionalSymbol
{
public:
	ENC_CS_DEPCNT03(ENC_Feature * _fe, std::wstring);
	virtual ~ENC_CS_DEPCNT03();

public:
	list<SpatialObjectPairDEPCNT03> m_spatialCheckList;
	list<SpatialLSParamPair> m_LSPairList;
	double VALDCO;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void Serialize(CArchive &ar);
};
