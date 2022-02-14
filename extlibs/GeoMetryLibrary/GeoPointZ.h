#pragma once
#include "Geometry.h"

class GeoPointZ :public Geometry
{
public:
	GeoPointZ(void);
	GeoPointZ(double _x, double _y, double _z);
	virtual ~GeoPointZ(void);

public:
	double x;
	double y;
	double z;

public:
	void SetPoint(double _x, double _y, double _z);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
};