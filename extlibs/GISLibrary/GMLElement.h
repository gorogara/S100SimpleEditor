#pragma once
#include "GMLValue.h"

class ENCGeometry;

class GMLElement
{
public:
	GMLElement();
	virtual ~GMLElement();

public:
	CString m_elementName;
	CString m_childName;
	GMLValue m_id;
	GMLValue m_text;
	ENCGeometry* m_geo;
	list<GMLElement*> m_elements;

public:
	bool HasValue();            
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr); 
	void GetData(MSXML2::IXMLDOMElementPtr ptr);
	virtual void GetCoordinates(ENCArea* a) {};
	virtual void GetCoordinates(ENCLine* p) {};
	virtual void GetCoordinates(ENCPoint* p) {};
	virtual void SetCoordinates(ENCPoint* p) {};
	virtual ENCGeometry* CreateCoordinates()/*{ return NULL; }*/;
};