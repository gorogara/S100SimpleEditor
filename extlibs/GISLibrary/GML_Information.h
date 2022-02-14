#pragma once
#include "GML_Object.h"

class GML_Information : public GML_Object
{
public:
	GML_Information();
	virtual ~GML_Information();

public:
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	void GetDataFromXML(MSXML2::IXMLDOMNodePtr ptr);
	void GetFeatureType(MSXML2::IXMLDOMElementPtr itemPtr, GML_Attribute* pAttr = NULL);
};