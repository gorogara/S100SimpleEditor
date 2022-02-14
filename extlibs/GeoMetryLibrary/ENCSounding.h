#pragma once
#include "ENCGeometry.h"

class GeoPointZ;    
class ENCSounding :
	public ENCGeometry
{
public:
	ENCSounding(void);
	ENCSounding(unsigned size);
	ENCSounding(double _x, double _y, double _z);
	ENCSounding(unsigned size, double* _x, double* _y, double* _z);
	virtual ~ENCSounding(void);

public:
	void SetPoint(unsigned index, double _x, double _y, double _z);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);	
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);	
	void Serialize(CArchive &ar);

public:
	unsigned m_numPoints;
	GeoPointZ* m_pPoints;
};