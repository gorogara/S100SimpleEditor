#pragma once
#include "SGeometry.h"
#include "SCurve.h"
#include "SCurveWithParentOrient.h"

class Scaler;
class SSurface : public SGeometry
{
public:
	SSurface();
	virtual ~SSurface(); 
	int		 m_numParts;
	int		 m_numPoints;
	int		 *m_pParts;
	GeoPoint *m_pPoints; 
	ID2D1PathGeometry* pGeometry = nullptr; 
	std::list<SCurveWithParentOrient> m_listCurveLink;

	GeoPoint* m_centerPoint = NULL;

public:
	void CreateD2Geometry(ID2D1Factory1* factory);
	int GetNumPointPerPart(int partIndex);

	void CalculateCenterPoint();

	ID2D1PathGeometry* GetD2Geometry();
	ID2D1PathGeometry* GetNewD2Geometry(ID2D1Factory1* factory, Scaler* scaler);
};