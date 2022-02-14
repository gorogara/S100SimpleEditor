#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_Curve : public GMLElement
{
public:
	GML_Curve();
	virtual ~GML_Curve();
public:
	void GetCoordinates(ENCArea* a);
};