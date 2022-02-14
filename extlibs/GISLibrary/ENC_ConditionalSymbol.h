#pragma once
#include <string>
#include <list>


class ENCCell;
class ENC_Feature;
class ENC_Vector;
class ENCGeometry;
class ENCArea;
class ACParameters;
class APParameters;
class SYParameters;
class LCParameters;
class LSParameters; 
#include "..\\PLLibrary\\PLLibrary.h"
class ENC_ConditionalSymbol 
{
public:
	ENC_ConditionalSymbol(ENC_Feature*, std::wstring);
	virtual ~ENC_ConditionalSymbol();
	 
protected:
	ENC_Feature* m_pFeature;
	std::wstring m_csName;

public:
	virtual void CheckCSVariable(ENCCell* cell, bool bSENC = false){}
	virtual void ChooseSymbol(){}
	virtual void InitCSSymbols(){}
	virtual void DrawGeometry(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0) {}
	virtual void DrawTextInfo(ENCGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0) {}

	virtual void Serialize(CArchive &ar){}
public:
	void SEABED01(double DRVAL1, double DRVAL2, ACParameters &ACParam, APParameters &APParam);
	void RESCSP02(std::list<unsigned> *m_RESTRNList, SYParameters &SYParam);
	std::wstring GetCSName() { return m_csName; };
	void LITDSN01( 
		wchar_t	CATLIT[10], 
		int	*LITCHR, 
		wchar_t	SIGGRP[10], 
		wchar_t	COLOUR[10], 
		double	*SIGPER, 
		double	*HEIGHT, 
		double	*VALNMR, 
		wchar_t	STATUS[10], 
		std::wstring	&LITDSN
		);

	void SNDFRM03(std::list<std::wstring> &symbolList, double DEPTH_VALUE, int TECSOU, int QUASOU, int STATUS, int QUAPOS);
	void SNDFRM03(SYParameters &sy, double &depth, double DEPTH_VALUE, int TECSOU, int QUASOU, int STATUS, int QUAPOS);    
	void DEPVAL02(ENCCell* cell, int WATLEV, int EXPSOU, double &SEABED_DEPTH, double &LEAST_DEPTH, bool overlapWithUnsurveyedArea, std::list<double> *depthValueOfOverlap); 
	void UDWHAZ04(ENCCell* cell, double DRVAL1, double DRVAL2, double DEPTH_VALUE, int WATLEV, SYParameters &SYParam, std::list<double> *depthValueOfOverlap);
	void QUAPNT02(ENCCell* cell, SYParameters &SYParam);
	void QUALIN01(ENCCell* cell, int conrad, LCParameters &LCParam, LSParameters &LSParam, LSParameters &LSParam2);
};