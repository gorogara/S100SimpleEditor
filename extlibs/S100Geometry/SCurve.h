#pragma once
#include "SGeometry.h"


class SCurve 
{
public:
	SCurve();
	virtual ~SCurve();

public:
	MBR m_mbr;

	__int64 m_id = 0;
	
	int		 m_numPoints = 0;
	GeoPoint *m_pPoints = nullptr;
	ID2D1PathGeometry *pGeometry = nullptr;


private:
	bool m_orient = true;

	bool m_duplicate = false;

public:

	int GetRCID();

	MBR& GetMBRRef();

	int GetNumPoints();
	double GetX(int i);
	double GetY(int i);
	

	void SetOrient(bool value);
	bool GetOrient();
	
	void SetDuplicate(bool value);
	bool GetDuplicate();

	void CreateD2Geometry(ID2D1Factory1* factory);

	ID2D1PathGeometry* GetD2Geometry();
	ID2D1PathGeometry* GetNewD2Geometry(ID2D1Factory1* factory, Scaler* scaler);
};
