// Complete!!!

#pragma once

#include "geometry.h"

class GeoPoint;

class GeoPolyline : public Geometry
{
public:
	GeoPolyline(void);
	virtual ~GeoPolyline(void);

public:
	int		 NumParts;
	int		 NumPoints;
	int		 *Parts;
	GeoPoint *Points; 
	POINT   *CPoints;

public:
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawGeometry(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0);
	void DrawGeometry(CD2DGeometrySink* pSink, Scaler *scaler, double offsetX = 0, double offsetY = 0);

	void DrawGeometry(ID2D1GeometrySink* pSink, Scaler *scaler, double offsetX = 0, double offsetY = 0); 
};