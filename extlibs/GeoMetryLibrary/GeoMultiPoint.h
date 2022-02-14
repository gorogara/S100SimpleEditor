#pragma once
#include "GeoPoint.h"
class GeoMultiPoint :
	public Geometry
{
public:
	GeoMultiPoint(void);
	GeoMultiPoint(unsigned size);
	GeoMultiPoint(double _x, double _y);
	GeoMultiPoint(unsigned size, double* _x, double* _y);
	virtual ~GeoMultiPoint(void);

public:
	unsigned m_numPoints;
	GeoPoint* m_pPoints;

public:
	void SetPoint(unsigned index, double _x, double _y);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
};