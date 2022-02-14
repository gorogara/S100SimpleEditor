#pragma once
#include "afxwin.h"
class CGeometryRgn :
	public CRgn
{
public:
	CGeometryRgn();
	virtual ~CGeometryRgn();

	virtual void Draw(CDC* pDC) = 0;
	void SetCoordinates(double _x, double _y);
	void GetCoordinates(double& _x, double& _y);

private:
	double x; 
	double y;
};