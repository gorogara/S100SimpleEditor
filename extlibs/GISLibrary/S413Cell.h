#pragma once

#include "GISLibrary.h"

#include "..\\libS111\\libS111.h"
#include "..\\libS100HDF5\\IrregularGridFeature.h"

#include "S100_Members.h"

namespace S100HDF5
{
	class S413;
}

class S413Cell : public S100SpatialObject
{
public:
	S413Cell();
	virtual ~S413Cell();

public:
	S100HDF5::S413 *s413 = nullptr;
	int _timeCount = 0;
	int _currentTimeIndex = -1;
	CBitmap bmpGrid;
	CDC dc;
	bool bBMP = false;
	int ncols = 0;
	int nrows = 0;
	float dx = 0;
	float dy = 0;
	float xmin = 0;
	float ymin = 0;
	float xmax = 0;
	float ymax = 0;
	libS413::S413FeatureType lastType = libS413::S413FeatureType::None;

public:
	bool Open(CString _filepath);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawDirection(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawOceanCurrent(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawSkyStatus(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawVisibility(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawWaveWind(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);
	void CreateBitmap(CDC* pDC, int featureType);
	void DrawBitmap(HDC &hDC, CRect rectF, Scaler *scaler);
	int GetColor(float value, int featureType);
	int GetColorByMinMax(float _v, float vmin, float vmax);
	void SetNextTime();
	void SetPrevTime();
	void SetNowTime();
};