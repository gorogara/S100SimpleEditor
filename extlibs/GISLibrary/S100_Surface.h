#pragma once
#include "GMLElement.h"

#include <list>

class ENCArea;
class S100_Surface : public GMLElement
{
public:
	S100_Surface(void);

public:
	GMLValue m_srsName;

public:
	bool HasValue(); 

	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr); 
	void GetCoordinates(ENCArea* a);
};