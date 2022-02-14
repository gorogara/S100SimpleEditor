#pragma once
#include "S101_ConditionalSymbol.h"
#include <string>

#include "..\\PLLibrary\\TEParameters.h"
#include "..\\PLLibrary\\TXParameters.h"
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\ACParameters.h"


////////////////////////////////////////////////////////////
// coded by dnwk
// LIGHTS05 ////////////////////////////////////////////////
class R_FeatureRecord;
class S101Cell;

class S101_CS_LIGHTS05 : public S101_ConditionalSymbol
{
public:
	S101_CS_LIGHTS05(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_LIGHTS05();
public:
	__int32 m_COLOURHex;
	__int32 m_CATLITHex;
	//list<unsigned> m_COLOURList;
	//list<unsigned> m_CATLITList;
	// CATLIT, &LITCHR, SIGGRP, COLOUR, &SIGPER, &HEIGHT, &m_VALNMR, STATUS
	int m_GivenSector1_2;
	int m_SECTR1;
	int m_SECTR2;
	double m_ORIENT;
	__int32 m_LITVISHex;


	wchar_t	m_CATLIT[10];
	int		m_LITCHR;
	wchar_t	m_SIGGRP[10];
	wchar_t	m_COLOUR[10];
	double	m_SIGPER;
	double	m_HEIGHT;
	double	m_VALNMR;
	wchar_t	m_STATUS[10];
	wstring m_LITDSN;

	bool m_bShareLIGHTSGivenSECTR1_SECTR2;
	bool m_hasSamePointSectorLights;
	bool m_bExtendedArcRadius;

	bool m_bMarinerSelectedViewingGroup23;
	bool m_bMarinerSelectedFullLengthLightSectorLines;

	double m_legLength;
	int m_lightRadius;


public:
	int m_DrawingType;

	int m_penCnt;
	HPEN m_penArr[10];

public:
	TEParameters m_TEParam;
	TXParameters m_TXParam;
	SYParameters m_SYParam;
	SYParameters m_QuesmrkSYParam;
	LSParameters m_LSParam;
	LSParameters m_ArcLSParam;
	ACParameters m_ACParam;

public:
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
};

