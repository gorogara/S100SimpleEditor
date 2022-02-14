#pragma once   

#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\ACParameters.h"
#include "..\\PLLibrary\\APParameters.h"

class ENCCell;
class ENCGeometry;

class ENC_CS_OBSTRN06 : public ENC_ConditionalSymbol
{
public:
	ENC_CS_OBSTRN06(ENC_Feature*, std::wstring);
	virtual ~ENC_CS_OBSTRN06();

public:
	list<double> m_depthValueOfOverlap;
	bool m_overlapWithUnsurveyedArea;
	double m_LEAST_DEPTH;
	double m_DEPTH_VALUE;
	double m_SEABED_DEPTH;
	int m_EXPSOU;
	double m_VALSOU;
	int m_WATLEV;
	int m_CATOBS;
	int m_TECSOU;
	int m_QUASOU;
	int m_QUAPOS;
	int m_STATUS;
	double m_DRVAL1;
	double m_DRVAL2;
	int m_org_scaleMin; 
	SYParameters m_UDWHAZSYParam;
	SYParameters m_QUAPNTSYParam; 
	SYParameters m_SYParam;
	LSParameters m_LSParam;
	ACParameters m_ACParam;
	APParameters m_APParam; 
	bool m_showSNDFRM;
	SYParameters m_SNDSYParam;
	double m_sndValue;
	int m_DrawingType;
	ENCCell* m_cell;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void InitCSSymbols();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawSoundFrame(ENCGeometry *geo, HDC &hDC, POINT _p);
	void Serialize(CArchive &ar);
};