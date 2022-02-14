#pragma once

#include "spatialobject.h"

class Geometry;
class Scaler;

class SHPFile :
	public SpatialObject
{
public:
	SHPFile();
	virtual ~SHPFile();

public:
	unsigned int m_nRecords; 
	unsigned int m_nShapeType; 
	Geometry **m_pSHPObject;

public: 
	bool Open(CString _filepath);

	void Draw(CDC *pDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0) {};

	void Draw(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0);
	void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler, double offsetX = 0, double offsetY = 0); 
	void SwapWord(int _length, void *_pData);
};