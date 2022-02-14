#pragma once
#include "GMLValue.h"
#include "GMLElement.h"

class GML_Vector
{
public:
	GML_Vector();
	virtual ~GML_Vector();

public:
	GMLElement* m_GMLElement;
	ENCGeometry* m_geo;
};