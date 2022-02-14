#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_Patches : public GMLElement
{
public:
	GML_Patches(); 
	virtual ~GML_Patches();

public:
	void GetCoordinates(ENCArea* a);
};