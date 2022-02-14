#pragma once
#include "GML_DatasetMetaDataProperty.h"

#include "GML_Vector.h"
#include "GML_SpatialObject.h"
#include "GML_BoundedBy.h"

#import <msxml4.dll>
class Catalog;
class GML_DataSetAttribute;
class GML_Feature;
class GML_Attribute;

class GML_SpatialObject :
	public SpatialObject
{
public:
	GML_SpatialObject();
	virtual ~GML_SpatialObject();

public:
	GML_DatasetMetaDataProperty m_datasetMetaProperty;
	GML_BoundedBy				m_boundedBy; 
	unordered_map<LPCWSTR, GML_Feature*> m_features;
	unordered_map<LPCWSTR, GML_Feature*> m_informations;
	unordered_map<LPCWSTR, GML_Vector*> m_vectors;  
	list<GML_Feature*> m_PRFeature;
	list<GML_Feature*> m_MPRFeature;
	list<GML_Feature*> m_CCFeature;
	list<GML_Feature*> m_SRFeature; 

	MBR m_mbr;

public:
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0);

	virtual bool Open(CString _filepath){return false;};
	virtual void GetENCObject(MSXML2::IXMLDOMNodePtr listPtr){};
	void GetFeatureType(MSXML2::IXMLDOMElementPtr itemPtr, GML_Feature* pFe, GML_Attribute* pAttr = NULL);
	void GetDatasetMetadata(MSXML2::IXMLDOMNodePtr listPtr, GML_DataSetAttribute* m_attr = NULL);
	GMLElement* MakeFullSpatialData(MSXML2::IXMLDOMNodePtr listPtr);

	void SortByFeatureType();
	MBR CalcMBR();
};