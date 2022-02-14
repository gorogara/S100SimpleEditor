#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_Segments : public GMLElement
{
public:
	GML_Segments();
	virtual ~GML_Segments();

public:
	void GetCoordinates(ENCArea* a);
};