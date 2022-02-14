#pragma once
#include "GMLElement.h"

class S100_GMLPoint : public GMLElement
{
public:
	GMLValue m_srsName;
	S100_GMLPoint(); 
	virtual ~S100_GMLPoint();

public:
	bool HasValue(); 
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr); 
	void GetCoordinates(ENCPoint* p);
	void SetCoordinates(ENCPoint* p);
};