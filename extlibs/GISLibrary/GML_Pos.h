#pragma once
#include "GMLElement.h"
#include "..\\GeoMetryLibrary\\ENCPoint.h"

class GML_Pos : public GMLElement
{
public:
	GML_Pos();   
	virtual ~GML_Pos();

public:
	void GetCoordinates(ENCPoint* p);
	void SetCoordinates(ENCPoint* p);
};