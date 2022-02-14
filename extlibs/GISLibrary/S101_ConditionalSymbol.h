#pragma once

class S101Cell;
class R_FeatureRecord;
class SGeometry;
//	for Procedure CS Logic 

class S101_ConditionalSymbol 
{
public:
	S101_ConditionalSymbol(R_FeatureRecord*, std::wstring);
	virtual ~S101_ConditionalSymbol();
	 
protected:
	R_FeatureRecord* m_pFeature;
	std::wstring m_csName;

public:
	virtual void CheckCSVariable(S101Cell* cell, bool bSENC = false){}
	virtual void ChooseSymbol(){}
	virtual void InitCSSymbols(){}
	virtual void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0) {}
	virtual void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0) {}

	virtual void Serialize(CArchive &ar){}
public:
	void SEABED01(double DRVAL1, double DRVAL2, ACParameters &ACParam, APParameters &APParam);
	void RESCSP02(list<unsigned> *m_RESTRNList, SYParameters &SYParam);
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
		wstring	&LITDSN
		);



	void  	get_category(wchar_t icat[10], wchar_t ccat[10]);
	void 	get_characteristic(int ichr, wchar_t cchr[20]);
	int	get_sig_group(wchar_t sgrp[10], wchar_t cgrp[2][10]);
	int	get_colour(wchar_t icol[10], wchar_t ccol[5][3]);
	int	get_status(wchar_t sstat[10], wchar_t cstat[2][20]);

	void SNDFRM03(list<wstring> &symbolList, double DEPTH_VALUE, int TECSOU, int QUASOU, int STATUS, int QUAPOS);
	void SNDFRM03(SYParameters &sy, double &depth, double DEPTH_VALUE, int TECSOU, int QUASOU, int STATUS, int QUAPOS);

	// Check overlap with unsurveyed area.
	// if then RETURN this fuction
	// if not overlap with unsurveyed area.
	// find minimum depth on overlaped depth area or dredge area.
	void DEPVAL02(S101Cell* cell, int WATLEV, int EXPSOU, double &SEABED_DEPTH, double &LEAST_DEPTH, bool overlapWithUnsurveyedArea, list<double> *depthValueOfOverlap);

	// find minimum depth on overlaped depth area or dredge area.
	void UDWHAZ04(S101Cell* cell, double DRVAL1, double DRVAL2, double DEPTH_VALUE, int WATLEV, SYParameters &SYParam, list<double> *depthValueOfOverlap);
	void QUAPNT02(S101Cell* cell, SYParameters &SYParam);
	void QUALIN01(S101Cell* cell, int conrad, LCParameters &LCParam, LSParameters &LSParam, LSParameters &LSParam2);
};
