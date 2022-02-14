#pragma once
#include "Geometry.h"
#include "GeoPointZ.h"
class GeoMultiPointZ :
	public Geometry
{
public:
	GeoMultiPointZ(void);
	GeoMultiPointZ(unsigned size);
	GeoMultiPointZ(double _x, double _y, double _z);
	GeoMultiPointZ(unsigned size, double* _x, double* _y, double* _z);
	virtual ~GeoMultiPointZ(void);

public:
	unsigned m_numPoints;
	GeoPointZ* m_pPoints;

public:
	void SetPoint(unsigned index, double _x, double _y, double _z);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
};