#pragma once
#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LCParameters.h"
#include "..\\PLLibrary\\LSParameters.h"

#include <vector>

class Symbol;
class ENCCell;
class ENCGeometry;

class ENC_CS_RESARE03 :
	public ENC_ConditionalSymbol
{
public:
	ENC_CS_RESARE03(ENC_Feature *_fe, std::wstring);
	virtual ~ENC_CS_RESARE03();

public:
	std::vector<int> m_listCATREA;
	std::vector<int> m_listRESTRN;

	SYParameters m_SYParam;
	LCParameters m_LCParam;
	LSParameters m_LSParam;

public:
	void CheckCSVariable(ENCCell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void ContinuationA();
	void ContinuationB();
	void ContinuationC();
	void ContinuationD();
	void ContinuationE();        

	void Serialize(CArchive &ar);
};