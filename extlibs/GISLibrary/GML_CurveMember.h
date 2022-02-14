#pragma once
#include "GMLElement.h"
#include "..//GeoMetryLibrary//ENCArea.h"

class GML_CurveMember : public GMLElement
{
public:
	GML_CurveMember();
	virtual ~GML_CurveMember();

public:
	void GetCoordinates(ENCArea* a);
};