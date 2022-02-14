#pragma once

#include "ENC_Vector.h"
#include "ENC_Feature.h"
#include "AddtionalStruct.h"
#include "spatialobject.h"
#include "DDR.h"

#include "..\\PLLibrary\\GeoObjectMap.h"
#include "..\\PLLibrary\\AttributeMap.h"
#include "..\\PLLibrary\\ColorMap.h"
#include "..\\PLLibrary\\SymbolMap.h"

#include "..\\GeoMetryLibrary\\MBR.h" 

#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>

class DRDirectoryInfo;

class ENCCell :
	public SpatialObject
{
public:
	ENCCell();
	ENCCell(
		S100_SVG_D2D1_DLL::SVGManager*  svgSymbolManager,
		CGeoObjectMap *object,
		CAttributeMap *attribute,
		CColorMap *color,
		CSymbolMap *&symbol);
	virtual ~ENCCell();

public:
	S100_SVG_D2D1_DLL::SVGManager		*p_svgSymbolManager;
	CGeoObjectMap	*p_object;
	CAttributeMap	*p_attribute;
	CColorMap		*p_color;
	CSymbolMap		*p_symbol; 

public: 

	DDR m_DDR;
	unsigned EXPP; 
	unsigned INTU; 
	wstring DSNM; 
	wstring EDTN; 
	wstring UPDN; 
	wstring UADT; 
	wstring ISDT; 
	wstring STED; 
	unsigned PRSP; 
	wstring PSDN; 
	wstring PRED; 
	unsigned PROF; 
	unsigned AGEN; 
	wstring DSID_COMT; 

	unsigned DSTR; 
	unsigned AALL; 
	unsigned NALL; 
	unsigned NOMR; 
	unsigned NOCR; 
	unsigned NOGR; 
	unsigned NOLR; 
	unsigned NOIN; 
	unsigned NOCN; 
	unsigned NOED; 
	unsigned NOFA; 

	unsigned HDAT; 
	unsigned VDAT; 
	unsigned SDAT; 
	unsigned CSCL; 
	unsigned DUNI; 
	unsigned HUNI; 
	unsigned PUNI; 
	unsigned COUN; 
	unsigned COMF; 
	unsigned SOMF; 
	wstring DSPM_COMT; 


	unsigned U_EXPP; 
	unsigned U_INTU; 
	wstring U_DSNM; 
	wstring U_EDTN; 
	wstring U_UPDN; 
	wstring U_UADT; 
	wstring U_ISDT; 
	wstring U_STED; 
	unsigned U_PRSP; 
	wstring U_PSDN; 
	wstring U_PRED; 
	unsigned U_PROF; 
	unsigned U_AGEN; 
	wstring U_DSID_COMT; 

	unsigned U_DSTR; 
	unsigned U_AALL; 
	unsigned U_NALL; 
	unsigned U_NOMR; 
	unsigned U_NOCR; 
	unsigned U_NOGR; 
	unsigned U_NOLR; 
	unsigned U_NOIN; 
	unsigned U_NOCN; 
	unsigned U_NOED; 
	unsigned U_NOFA;   
	unordered_map<__int64, ENC_Vector*> m_veMap;
	unordered_map<__int64, ENC_Feature*> m_feMap;  
	list<ENC_Feature*> m_effectiveFe; 
	list<ENC_Feature*> m_textGroup[8];  
	unordered_map<__int64, ENC_Feature*> m_metaFeMap;  
	list<ENC_Feature*> m_feArea[10];
	list<ENC_Feature*> m_feLine[10];
	list<ENC_Feature*> m_fePoint[10];  
	list<ENC_Feature*> m_DEPARE;
	list<ENC_Feature*> m_DRGARE;
	list<ENC_Feature*> m_FLODOC;
	list<ENC_Feature*> m_HULKES;
	list<ENC_Feature*> m_LNDARE;
	list<ENC_Feature*> m_PONTON;
	list<ENC_Feature*> m_UNSARE; 
	list<ENC_Feature*> m_DEPCNT;
	list<ENC_Feature*> m_RIVERS;
	list<ENC_Feature*> m_LAKARE;
	list<ENC_Feature*> m_CANALS;
	list<ENC_Feature*> m_DOCARE; 
	list<ENC_Feature*> m_LIGHTS;

	list<ENC_Feature*> m_LITFLT;
	list<ENC_Feature*> m_LITVES;
	list<ENC_Feature*> m_BOY___;  
	list<ENC_Feature*> m_M_COVR;
	MBR m_mbr;

public:
	void Save(CString _filepath);
	void SaveRecordDSGIR(CFile *file, unsigned char DRIndex);
	void SaveRecordDSGRR(CFile *file, unsigned char DRIndex);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0);

	bool Open(CString fileName);
	bool Open(CFile* file);
	bool OpenSENC(CString fileName);
	bool SaveSENC(CString fileName);
	bool SencOpen(CFile* file);
	bool SencOpen(CString fileName);
	bool ApplyUpdate(CFile* file);
	bool ApplyUpdate(CString baseFileName); 
	bool ReadENCContent(BYTE*& buf, unsigned size);
	bool ReadENCUpdateContent(BYTE*& buf, unsigned size);
	bool ReadDDR(BYTE*& buf);

	bool ReadGeneralInformation(DRDirectoryInfo *dir, BYTE*& buf);
	bool ReadDatasetParameter(DRDirectoryInfo *dir, BYTE*& buf);
	bool ReadUpdateGeneralInformation(DRDirectoryInfo *dir, BYTE*& buf);

	bool UpdateVector(ENC_Vector* ve);
	bool UpdateFeature(ENC_Feature*fe);

	void ProcessCSProcedure(bool bSENC = false);
	void GetAllFeatureDisplayOptions();
	void GetFeatureDisplayOption(ENC_Feature* pFe);
	void GetEffectiveFeatures();
	void GetDisplayFeatures();
	bool MakeFullSpatialData();
	bool MakePointData(ENC_Feature* fe);
	bool MakeLineData(ENC_Feature* fe);
	bool MakeAreaData(ENC_Feature* fe);

	void UpdateCS_SafetyDepth();
	void UpdateCS_SafetyContour();
	void UpdateCS_ShadeType();
	void UpdateCS_BoundarySymbol();
	void ChangeDisplayMode();

	MBR CalcMBR();

#ifdef _GETOBJECT
	void PrintObjectNumber();
#endif
	void GetFeatureObjectByCode(int code, ListFindedFeature &feList);
};