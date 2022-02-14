#pragma once

#include <vector>
#include "S100DrawingUnit.h"

class S100DrawingUnitPolyLine :
	public S100DrawingUnit
{
public:
	S100DrawingUnitPolyLine();
	virtual ~S100DrawingUnitPolyLine();

public:
	D2D1_COLOR_F color;
	FLOAT width;
	ID2D1Geometry* pGeometry;
	ID2D1PathGeometry* pSimplifiedGeometry = nullptr;
	bool hasDash;
	std::vector<D2D1_POINT_2F> points; 
	std::vector<D2D1_POINT_2F> screenPoints; 

	CString lineStyleReference;
};