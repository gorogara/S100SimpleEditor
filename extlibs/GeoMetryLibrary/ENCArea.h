#pragma once
#include "ENCGeometry.h"

class GeoPoint;    
class ENCArea :
	public ENCGeometry
{
public:
	ENCArea(void);
	virtual ~ENCArea(void); 
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);	
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);	
	
	void Serialize(CArchive &ar);

	int		 NumParts;
	int		 NumPoints;
	int		 *Parts;

	GeoPoint *Points; 
	POINT   *CPoints; 

};