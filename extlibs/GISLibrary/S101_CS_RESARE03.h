#pragma once
#include "S101_ConditionalSymbol.h"

#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LCParameters.h"
#include "..\\PLLibrary\\LSParameters.h"

//class Symbol;
class S101Cell;
class R_FeatureRecord;

class S101_CS_RESARE03 :
	public S101_ConditionalSymbol
{
public:
	S101_CS_RESARE03(R_FeatureRecord *_fe, std::wstring);
	virtual ~S101_CS_RESARE03();

	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void ContinuationA();
	void ContinuationB();
	void ContinuationC();
	void ContinuationD();
	void ContinuationE();

	//CString symbolName;
	//Symbol  *symbol;

	//bool isLC;

	//CString lcSymbolName;
	//Symbol  *lcSymbol;

	//int lsPenStyle;
	//int lsPenWidth;
	//int lsR, lsG, lsB;

	std::vector<int> m_listCATREA;
	std::vector<int> m_listRESTRN;

	SYParameters m_SYParam;
	LCParameters m_LCParam;
	LSParameters m_LSParam;

	void Serialize(CArchive &ar);
};