#pragma once
#include "stdafx.h"
#include "MBR.h"

#include <windows.h>
#include <stdlib.h> 
class Scaler;
class GeoPoint;
class Geometry
{
public:
	Geometry();
	virtual ~Geometry();

public:
	HBRUSH m_hBrush;
	HPEN m_hPen;
	MBR m_mbr;

	static MBR *pViewMBR;
	static CRect m_viewRect;
	static void SetViewRect(CRect r);
	static void SetViewMBR(MBR *mbr);

public:

	virtual void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0) {};
	virtual void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0) {};
	virtual void DrawGeometry(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void DrawTextInfo(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void DrawGeometry(CD2DGeometrySink* pSink, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void DrawTextInfo(CD2DGeometrySink* pSink, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void DrawGeometry(ID2D1GeometrySink* pSink, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
};
