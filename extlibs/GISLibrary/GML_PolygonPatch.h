#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_PolygonPatch : public GMLElement
{
public:
	GML_PolygonPatch();
	virtual ~GML_PolygonPatch(); 


public:
	void GetCoordinates(ENCArea* a);
};