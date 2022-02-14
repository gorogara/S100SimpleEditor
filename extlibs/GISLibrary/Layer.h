#pragma once

#include "Namespace_GISLibrary.h"

#include "..\\GeoMetryLibrary\\MBR.h"

class SpatialObject;
class Scaler; 
class Layer
{

public:
	Layer(void);
	virtual ~Layer(void);

public:
	bool	      On;
	bool		Info;   
	MBR			  m_mbr;
	SpatialObject *m_spatialObject;

public:
	virtual bool Open(CString _filepath);
	void Save(CString _filepath, CString extend);
	virtual void Draw(GISLibrary::D2D1Resources* D2, Scaler* scaler) {};
	void Draw(CDC *pDC, Scaler *scaler, double offset = 0);
	virtual void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawInfo(HDC &hDC, Scaler *scaler);
	void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset);
	void Draw(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0);
	void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler, double offsetX = 0, double offsetY = 0);
	bool IsOn();
	bool InfoOn();
	void LayerOn();
	void LayerOff();
	void LayerInfoOn();
	void LayerInfoOff();
	CString GetLayerName();
	CString GetLayerPath();
	CString GetLayerType();
	void SetMBR(MBR& value);
	MBR GetMBR();
	MBR* GetMBRPointer();
	void SetSpatialObject(SpatialObject* value);
	SpatialObject* GetSpatialObject();
	bool IsS100Layer();
}; 