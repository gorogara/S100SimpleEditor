#pragma once

#include "GML_DatasetMetaDataProperty.h"
//#include "GML_Object.h"
//#include "GML_Vector.h"
#include "spatialobject.h"
#include "GML_BoundedBy.h"

#import <msxml4.dll>

class Catalog;
class GML_DataSetAttribute;
class GML_Vector;
class GML_Feature;
class GML_Object;
class GML_Attribute;
class GML_Information;
class GMLElement;

class ShipReportMessage : public SpatialObject
{
public:
	ShipReportMessage();
	virtual ~ShipReportMessage();

	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0);

	GML_DatasetMetaDataProperty m_datasetMetaProperty;
	GML_BoundedBy				m_boundedBy;
	unordered_map<LPCWSTR, GML_Feature*> m_features;
	unordered_map<LPCWSTR, GML_Information*> m_Informations;

	unordered_map<LPCWSTR, GML_Vector*> m_vectors;
	////////////////////////////////////////////////
	// basic information
	wstring GML_ID;
	int		m_featureID;
	int		m_vectorID;
	int		m_assocID;
	////////////////////////////////////////////////
	// devided feature by spatial type
	list<GML_Feature*> m_PRFeature;
	list<GML_Feature*> m_MPRFeature;
	list<GML_Feature*> m_CCFeature;
	list<GML_Feature*> m_SRFeature;
	////////////////////////////////////////////////

	MBR m_mbr;

	bool Open(CString _filepath);
	void GetENCObject(MSXML2::IXMLDOMNodePtr listPtr);
	void GetFeatureType(MSXML2::IXMLDOMElementPtr itemPtr, GML_Object* pFe, GML_Attribute* pAttr = NULL);
	void GetDatasetMetadata(MSXML2::IXMLDOMNodePtr listPtr, GML_DataSetAttribute* m_attr = NULL);
	GMLElement* MakeFullSpatialData(MSXML2::IXMLDOMNodePtr listPtr);

	void InitShipData();
	void InitShip2ndData();

	GML_Feature* AddWaypoint(double x, double y);
	void SetNoticeOfArrivalWP(double x, double y);
	void SetPilotRequestWP(double x, double y);
	void ResetWP();
	int GetNextObjectID();

	void SortByFeatureType();
	MBR CalcMBR();

	void CreateAssociation();

	void ExportGMLData(wstring filepath);
	bool ImportGMLData(CString filepath){};
};

