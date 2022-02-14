#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_LineStringSegment : public GMLElement
{
public:
	GML_LineStringSegment();
	virtual ~GML_LineStringSegment();
public:
	void GetCoordinates(ENCArea* a);
};