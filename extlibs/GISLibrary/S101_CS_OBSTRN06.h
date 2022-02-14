#include "S101_ConditionalSymbol.h"
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\ACParameters.h"
#include "..\\PLLibrary\\APParameters.h"

////////////////////////////////////////////////////////////
// coded by dnwk
// OBSTRN06 ////////////////////////////////////////////////
class S101Cell;
class R_FeatureRecord;
class SGeometry;

class S101_CS_OBSTRN06 : public S101_ConditionalSymbol
{
public:
	S101_CS_OBSTRN06(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_OBSTRN06();
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
	//SYParameters m_SOUSYParam;

	SYParameters m_SYParam;
	LSParameters m_LSParam;
	ACParameters m_ACParam;
	APParameters m_APParam;
	//list<wstring> m_symbolList;
	bool m_showSNDFRM;
	SYParameters m_SNDSYParam;
	double m_sndValue;
	int m_DrawingType;
	S101Cell* m_cell;

public:
	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void InitCSSymbols();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void DrawSoundFrame(SGeometry *geo, HDC &hDC, POINT _p);

	void Serialize(CArchive &ar);
};
