// Complete!!!

#pragma once

#include "Geometry.h"

class GeoPoint : public Geometry
{
public:
	GeoPoint(void);
	GeoPoint(double _x, double _y);
	virtual ~GeoPoint(void);

public:
	double x;
	double y;

public:
	void SetPoint(double _x, double _y);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawGeometry(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0);

	double GetX();
	double GetY();
};