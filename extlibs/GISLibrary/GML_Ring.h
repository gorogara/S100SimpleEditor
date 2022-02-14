#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_Ring : public GMLElement 
{
public:
	GML_Ring();
	virtual ~GML_Ring();

public:
	void GetCoordinates(ENCArea* a);
};