#pragma once
#include "GMLElement.h"

class S100_SurfaceProperty : public GMLElement
{
public:
	S100_SurfaceProperty();    
	virtual ~S100_SurfaceProperty();

public:
	ENCGeometry* CreateCoordinates();
};