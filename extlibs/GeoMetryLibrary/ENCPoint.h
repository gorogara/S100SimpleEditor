#pragma once

#include "ENCGeometry.h"

class GeoPoint;

class ENCPoint :
	public ENCGeometry
{
public:
	ENCPoint();
	ENCPoint(unsigned size);
	ENCPoint(double _x, double _y);
	ENCPoint(unsigned size, double* _x, double* _y);
	virtual ~ENCPoint();

public:
	unsigned m_numPoints = 0;
	GeoPoint* m_pPoints = nullptr;

public:
	void SetPoint(unsigned index, double _x, double _y);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);	
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);	
	void Serialize(CArchive &ar);
};