#pragma once
#include "S101_ConditionalSymbol.h"

#include <list>
#include <string>

#include "..\\PLLibrary\\ACParameters.h"
#include "..\\PLLibrary\\APParameters.h"
#include "..\\PLLibrary\\SYParameters.h"
// DEPARE02 ////////////////////////////////////////////////

class R_FeatureRecord;
class S10lCell;
class SGeometry;

class S101_CS_DEPARE02 : public S101_ConditionalSymbol
{
public:
	S101_CS_DEPARE02(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_DEPARE02();
public:
	//static int isInit;
	double m_DRVAL1;
	double m_DRVAL2;
	list<unsigned> m_RESTRNList;

	bool m_bIsDredgedArea;

	double m_LOC_VALDCO;

	list<SpatialObjectPairDEPARE02> m_spatialCheckList;
	static LSParameters m_LSSymbolesDEPARE[3];
	ACParameters m_ACParam;
	APParameters m_APParam;
	SYParameters m_SYParam;

	int m_QUAPOS;

	////////////////////////////////////
	// this variable using in each spatial conditinal symbol only
	list<SpatialLSParamPair> m_LSPairList;
	// m_symbols[0] = LS(SOLD, 2, DEPSC)
	// m_symbols[1] = LS(DASH, 2, DEPSC)
	/////////////////////////////////////loop 

public:
	void SetDredgedArea(bool isDredged);
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
	void CheckCSVariableOnSENC(S101Cell* cell);
};
