#pragma once

#include "Enum_S100_FileType.h"
#include "Namespace_GISLibrary.h"

class Layer;
class Scaler;

class SpatialObject
{
public:
	SpatialObject();
	virtual ~SpatialObject();

public:
	Layer   *m_pLayer;
private:
	CString m_FilePath; 
	CString m_FileName; 
public:
	S100_FileType m_FileType; 

public:
	virtual bool Open(CString _filepath);
	virtual void Draw(CDC *pDC, Scaler *scaler, double offset = 0) {};
	virtual void Draw(HDC &hDC, Scaler *scaler, double offset = 0) {};
	virtual void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0) {};
	virtual void Draw(GISLibrary::D2D1Resources* D2, Scaler* scaler) {};
	virtual void Draw(CDCRenderTarget* pRenderTarget, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void Draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler, double offsetX = 0, double offsetY = 0) {};
	virtual void Save(CString filename, CString extend);

	void SetLayer(Layer* value);
	Layer* GetLayer();

	void SetFilePath(CString& value);
	CString GetFilePath();

	void SetFileName(CString& value);
	CString GetFileName();

	void SetFileType(S100_FileType value);
	S100_FileType GetFileType();
};