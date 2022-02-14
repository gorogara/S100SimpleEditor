#pragma once

#include "SPoint.h"
#include "SCompositeCurve.h"
#include "SSurface.h"

class SCommonFuction
{
public:  
	static void CalculateCenterOfGravityOfSurface(std::vector<POINT> &vp, SSurface *_surface, CRect *_viewPort, Scaler *pScaler); 
	static ClipperLib::Paths ClipSurface(SSurface *_polygon, CRect *_viewPort); 
	static POINT CalculateCenterOfGravityOfSurface(POINT *_p, int _count); 
	static POINT CalculateCenterOfGravityOfSurface(ClipperLib::Path polygon); 
	static double GetDistance(POINT _p1, POINT _p2); 
	static double GetDistanceOfCurve(POINT *_p, int _count); 
	static void GetViewLineInCurve(POINT *_p, int _count); 
	static POINT* GetCenterPointOfCurve(POINT *_p, int _count); 
	static bool IsIntersect(POINT _s1, POINT _e1, POINT _s2, POINT _e2); 
	static void CutLineToIntersect(POINT &_s1, POINT &_e1, POINT _s2, POINT _e2); 
	static double GetAngle(POINT _p1, POINT _p2); 
	static POINT GetOffsetPointOnLine(POINT _p1, POINT _p2, double offset);                   
	static bool Intersect(
		float x1, float y1, float x2, float y2,
		float x3, float y3, float x4, float y4,
		float* intersectionX, float* intersectionY); 
	static bool Intersect(
		float xmin, float ymin, float xmax, float ymax,
		float x1, float y1, float x2, float y2,
		float& intersectionX1, float& intersectionY1,
		float& intersectionX2, float& intersectionY2);

	static const int NewGeometryScale = 1000000000;
};

