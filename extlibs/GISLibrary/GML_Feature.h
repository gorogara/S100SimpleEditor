#pragma once
#include "GML_Object.h"

class GMLElement;

class GML_Feature : public GML_Object
{
public:
	GML_Feature();
	virtual ~GML_Feature();
	
public:
	GMLElement* m_GMLGeoData;
	list<ATTF*> m_attfList;
	int m_type; 
	int m_scaleMin;
	int m_scaleMax;
	int m_bShownAllScale;
	int m_displayPriority;
	int m_viewingGroup; 
	int m_displayCategory;
	int m_radarOver;
	bool m_hasText; 
	ENC_ConditionalSymbol *m_cs;

public:
	void CreateCS(ENCCell *cell);
	void GetFeatureDisplayOption();
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	void GetDataFromXML(MSXML2::IXMLDOMNodePtr ptr);
	GMLElement* MakeFullSpatialData(MSXML2::IXMLDOMNodePtr item);
	void GetFeatureType(MSXML2::IXMLDOMElementPtr itemPtr, GML_Attribute* pAttr = NULL);
};