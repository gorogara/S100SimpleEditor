#pragma once 
#include "..\\PLLibrary\\ACParameters.h"
#include "..\\PLLibrary\\APParameters.h"
#include "..\\PLLibrary\\SYParameters.h"
#include "SpatialLSParamPair.h"
#include "SpatialObjectPairDEPARE02.h"

class ENC_CS_DEPARE02 : public ENC_ConditionalSymbol
{
public:
	ENC_CS_DEPARE02(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_DEPARE02();
public: 
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
	list<SpatialLSParamPair> m_LSPairList;   

public:
	void SetDredgedArea(bool isDredged);
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
	void CheckCSVariableOnSENC(ENCCell* cell);
};
