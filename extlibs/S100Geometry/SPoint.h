#pragma once
#include "SGeometry.h"

class SPoint : public SGeometry
{
public:
	SPoint();
	SPoint(double _x, double _y);
	virtual ~SPoint();
public:
		void SetPoint(double _x, double _y);    

public:
	GeoPoint m_point; 
	POINT   m_vPoint;
};

