#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_Exterior : public GMLElement
{
public:
	GML_Exterior();
	void GetCoordinates(ENCArea* a);
};