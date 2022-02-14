#pragma once

#include "S100SpatialObject.h"
#include "R_DSGIR.h"
#include "R_DSCRS.h"
#include "F_CodeWithNumericCode.h"
#include "S100_Members.h"
#include "UncertaintyInformation.h"
#include "DDR.h"

#include "..\\GeoMetryLibrary\\MBR.h"
#include"..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <unordered_map>
#include <set>
#include <map>

#import <msxml4.dll>

class GeoPoint;
class GeoPointZ;
class Catalog;
class PCOutputSchemaManager; 
class SPoint;
class SCurve;
class SSurface;
class SMultiPoint;
class R_InformationRecord;
class R_FeatureRecord;
class R_PointRecord;
class R_MultiPointRecord;
class R_CurveRecord;
class R_CompositeRecord;
class R_SurfaceRecord;
class R_VectorRecord;
class SCompositeCurve;
struct ATTR;     

class TiXmlElement; 
class S101Cell : public S100SpatialObject
{
public:
	S101Cell();
	virtual ~S101Cell();

public:
	DDR m_S101DDR;

	S101Cell* updateInformation;

	std::vector<UncertaintyInformation> uncertaintyInformationList;

	R_DSGIR m_dsgir;
	R_DSCRS m_dscrs;
	CMap<__int64, __int64, R_InformationRecord*, R_InformationRecord*&> m_infMap; 
	CMap<__int64, __int64, R_PointRecord*, R_PointRecord*&> m_ptMap; 
	CMap<__int64, __int64, R_MultiPointRecord*, R_MultiPointRecord*&> m_mpMap; 
	CMap<__int64, __int64, R_CurveRecord*, R_CurveRecord*&> m_curMap; 
	CMap<__int64, __int64, R_CompositeRecord*, R_CompositeRecord*&> m_comMap; 
	CMap<__int64, __int64, R_SurfaceRecord*, R_SurfaceRecord*&> m_surMap; 
	CMap<__int64, __int64, R_FeatureRecord*, R_FeatureRecord*&> m_feaMap; 

	std::unordered_map<__int64, SCurve*> m_curveMap;
	std::unordered_map<__int64, R_VectorRecord*> m_vecMap; 
	std::unordered_map<std::wstring, std::wstring>* gml_namespace = nullptr;

#ifdef _DEBUG
	map<__int64, R_FeatureRecord*> m_feaMapFOID;
#endif 
	std::vector<std::list<R_FeatureRecord*>*> m_PRFeatureList;
	std::vector<std::list<R_FeatureRecord*>*> m_MPFeatureList;
	std::vector<std::list<R_FeatureRecord*>*> m_CCFeatureList;
	std::vector<std::list<R_FeatureRecord*>*> m_SRFeatureList;  
	std::unordered_map<int, CodeWithNumericCode*> m_useToGetFeatureInstruction;


public:
	R_DSGIR* GetDatasetGeneralInformationRecord();
	void RemoveAll(void);
	void ClearAll(void);
	bool Open(CString _filepath);
	BOOL ReadDDR(BYTE*& buf);
	void SortByFeatureType();
	void GetAllFeatureDisplayOptions();
	void GetFeatureDisplayOption(R_FeatureRecord* pFe);
	void ProcessCSProcedure();
	void SetInstructionToFeature();
	void SetInstructionToFeature(int type, R_FeatureRecord* fe);  

	void ClearCurveMap();

	BOOL MakeFullSpatialData();
	BOOL MakePointData(R_FeatureRecord* fe);
	BOOL MakeSoundingData(R_FeatureRecord* fe);
	BOOL MakeLineData(R_FeatureRecord* fe);
	BOOL MakeAreaData(R_FeatureRecord* fe); 

	BOOL GetFullSpatialData(R_PointRecord *r, GeoPoint &geo);
	BOOL GetFullSpatialData(R_PointRecord *r, GeoPointZ &geo);
	BOOL GetFullSpatialData(R_MultiPointRecord *r, CArray<GeoPointZ> &geoArr);
	BOOL GetFullSpatialData(R_CurveRecord *r, CArray<GeoPoint> &geoArr, unsigned ORNT = 1);
	BOOL GetFullSpatialData(R_CompositeRecord *r, CArray<GeoPoint> &geoArr, unsigned ORNT = 1);
	BOOL GetFullSpatialData(R_SurfaceRecord *r, CArray<GeoPoint> &geoArr);

	SCurve* GetCurveGeometry(R_CurveRecord *r, CArray<GeoPoint> &geoArr, unsigned ORNT = 1);


	BOOL GetFullCurveData(R_FeatureRecord* fe, R_PointRecord *r, int ornt = 1);
	BOOL GetFullCurveData(R_FeatureRecord* fe, R_MultiPointRecord *r, int ornt = 1);
	BOOL GetFullCurveData(R_FeatureRecord* fe, R_CurveRecord *r, int ornt = 1);
	BOOL GetFullCurveData(R_FeatureRecord* fe, R_CompositeRecord *r, int ornt = 1);
	BOOL GetFullCurveData(R_FeatureRecord* fe, R_SurfaceRecord *r, int ornt = 1);

	BOOL GetFullMaskData(R_FeatureRecord* fe);

	BOOL CreateUpdateFile();

	void Draw(GISLibrary::D2D1Resources* D2, Scaler* scaler);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0); 
	void Draw(HDC &hDC, Scaler *scaler, int priority, int instructionType, double offset = 0);

	MBR CalcMBR();

	void SetAdditionalInformation();

	void SaveTextPlacement(CString _filepath, CString extend);
	void Save(CString _filepath, CString extend);
	void GetDDRFromFile(CString _filepath);

	void ReadPCManager(/*PORTRAYAL_BUILD_TYPE type*/);
	void ProcessSpatialReference(); 
	void CheckHasTextPlacement(); 
	void SetFeaturesType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr);
	void SetInformationsType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement); 
	void SetVector(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, R_FeatureRecord *fr);
	void SetVectorPointsType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, SPoint* p);
	void SetVectorMultiPointsType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, SMultiPoint* p);
	void SetVectorCurvesType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, SCurve* p);
	void SetVectorSurfacesType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, SSurface* p);  
	void SetInformationsType(pugi::xml_document *doc,pugi::xml_node parentNode, std::string productNamespace);
	void GmlifileMakeByPugi(CString _filePath);
	void SetFeaturesType(pugi::xml_document *document,pugi::xml_node parentNode, std::string productNamespace);
	void SetVector(pugi::xml_node parentNode, R_FeatureRecord *fr);
	void SetVectorPointsType(pugi::xml_node parentNode,SPoint* p);
	void SetVectorMultiPointsType(pugi::xml_node parentNode,SMultiPoint* p);
	void SetVectorCurvesType(pugi::xml_node parentNode, SCurve* p);
	void SetVectorCompositeCurvesType(pugi::xml_node parentNode, SCompositeCurve* p);
	void SetVectorSurfacesType(pugi::xml_node parentNode,SSurface* p);
	void SetFeaturesTypeRelation_v2(pugi::xml_node rootNode);
	void SetInformationsTypeRelation_v2(pugi::xml_node parentNode);
	void SetAttributeType(pugi::xml_document *doc ,pugi::xml_node parentNode, std::list<F_ATTR*>* f_attrList);           

	void SetEncodingSpecification(CString value);
	CString GetEncodingSpecification();
	std::string GetEncodingSpecificationToString();

	void SetEncodingSpecificationEdition(CString value);
	CString GetEncodingSpecificationEdition();
	std::string GetEncodingSpecificationEditionToString();

	void SetProductIdentifier(CString value);
	CString GetProductIdentifier();
	std::string GetProductIdentifierToString();

	void SetProductEdition(CString value);
	CString GetProductEdition();
	std::string GetProductEditionToString();
	
	void SetApplictionProfile(CString value);
	CString GetApplicationProfile();
	std::string GetApplicationProfileToString();

	void SetDatasetFileIdentifier(CString value);
	CString GetDatasetFileIdentifier();
	std::string GetDatasetFileIdentifierToString();

	void SetDatasetTitle(CString value);
	CString GetDatasetTitle();
	std::string GetDatasetTitleToString();

	void SetDatasetReferenceDate(CString value);
	CString GetDatasetReferenceDate();
	std::string GetDatasetReferenceDataToString();

	void SetDatasetLanguage(CString value);
	CString GetDatasetLanguage();
	std::string GetDatasetLanguageToString();

	void SetDatasetAbstract(CString value);
	CString GetDatasetAbstract();
	std::string GetDatasetAbstractToString();

	void SetDatasetEdition(CString value);
	CString GetDatasetEdition();
	std::string GetDatasetEditionToString();

	CString GetFeatureCode(int numericCode);
};