#pragma once

#include "SCurve.h"
#include "SCurveWithParentOrient.h"

class SCompositeCurve : public SGeometry
{
public:
	SCompositeCurve();
	virtual ~SCompositeCurve();

public:
	std::list<SCurveWithParentOrient> m_listCurveLink;

public:
	void SetMBR();
	void CreateD2Geometry(ID2D1Factory1* factory);
};