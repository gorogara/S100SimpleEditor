#pragma once
#include "ENCGeometry.h"

class GeoPoint;    
class ENCLine :
	public ENCGeometry
{

public:
	ENCLine(void);
	virtual ~ENCLine(void);

public:
	int		 NumParts;
	int		 NumPoints;
	int		 *Parts;
	GeoPoint *Points; 
	POINT   *CPoints;

public:
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar); 
};