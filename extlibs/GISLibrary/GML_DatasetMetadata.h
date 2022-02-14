#pragma once
#include "GML_DataSetAttribute.h"

class GML_DatasetMetadata 
{
public:
	GML_DatasetMetadata();
	virtual ~GML_DatasetMetadata();

public:
	list<GML_DataSetAttribute*> m_datasetAttributes;
	
public:
	void ResetAttributes();
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
};