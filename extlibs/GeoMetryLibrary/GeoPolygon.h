// Complete!!!

#pragma once

#include "geometry.h"

class GeoPoint;

class GeoPolygon : public Geometry
{
public:
	GeoPolygon(void);
	virtual ~GeoPolygon(void);

public:
	int		 NumParts;
	int		 NumPoints;
	int		 *Parts;
	GeoPoint *Points; 
	POINT   *CPoints;

public:
	GeoPolygon* Clip(int left, int bottom, int right, int top);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawGeometry(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0);

};
