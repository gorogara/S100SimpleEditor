#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_PosList : public GMLElement
{
public:
	GML_PosList();
	virtual ~GML_PosList();

public:
	void GetCoordinates(ENCArea* a);
};