#pragma once

//#include "S101_conditionalsymbol.h"
#include <vector>

struct SpatialObjectPairDEPCNT03
{
public:
	SpatialObjectPairDEPCNT03()
	{
		m_LSSymbol = NULL;
	}
	virtual ~SpatialObjectPairDEPCNT03()
	{
	}
	int m_itorVecCnt;
	//list<S101_Vector*>::iterator m_itorVec;

	LSParameters* m_LSSymbol;
};

#include "S101_ConditionalSymbol.h"
class S101Cell;
class R_FeatureRecord;
class SGeometry;

class S101_CS_DEPCNT03 :
	public S101_ConditionalSymbol
{
public:
	S101_CS_DEPCNT03(R_FeatureRecord * _fe, std::wstring);
	virtual ~S101_CS_DEPCNT03();

	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	
	list<SpatialObjectPairDEPCNT03> m_spatialCheckList;
	list<SpatialLSParamPair> m_LSPairList;
	double VALDCO;

	void Serialize(CArchive &ar);
};
