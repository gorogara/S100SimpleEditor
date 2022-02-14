#pragma once
#include "GMLElement.h"

class S100_PointProperty : public GMLElement
{
public:
	S100_PointProperty();    
	virtual ~S100_PointProperty(); 

public:
	ENCGeometry* GetCoordinates();
	void SetCoordinates();
};