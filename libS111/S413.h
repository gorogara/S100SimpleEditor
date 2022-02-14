#pragma once

#include "..\\libS100HDF5\\S413.h"

class S100HDF5::IrregularGridFeature;

class S413
{
public:
	S413();
	virtual ~S413();

public:
	S100HDF5::S413 *_S413 = nullptr;
	
	CString m_FilePath; 
	CString m_FileName; 

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

public:
	bool Open(CString path);

	void Draw(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		Gdiplus::Rect rectF,
		Scaler *scaler);

	void Draw(
		std::string featureName,
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		Gdiplus::Rect rectF,
		Scaler *scaler);

	void DrawTextFeature(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawHumidity(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawOceanCurrent(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawDirection(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawTemperature(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawVisibility(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawWaterTemperature(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawWaterSalt(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawSkyStatus(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void DrawWaveWind(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler);

	void CreateBitmap(CDC* pDC, int featureType);
	void DrawBitmap(HDC &hDC, Rect rectF, Scaler *scaler);
	int GetColor(float value1, float value2, int featureType);
	int GetColor(float value, int featureType);
	int GetColorByMinMax(float v, float vmin, float vmax);

	void SetNextTime();
	void SetPrevTime();
	void SetNowTime();
	CString PickReport(float x, float y);


	void SetS413(S100HDF5::S413 * value);
	S100HDF5::S413* GetS413();


	void SetFilePath(CString value);
	CString GetFilePath();

	void SetFileName(CString value);
	CString GetFileName();

	void SetTimeCount(int value);
	int GetTimeCount();

	void SetCurrentTimeIndex(int value);
	int GetCurrentTimeIndex();    

	void SetBMP(bool value);
	bool GetBMP();

	void SetCols(int value);
	int GetCols();

	void SetRows(int value);
	int GetRows();

	void SetDx(int value);
	int GetDx();

	void SetDy(int value);
	int GetDy();

	void SetXMin(int value);
	int GetXMin();

	void SetYMin(int value);
	int GetYMin();

	void SetXMax(int value);
	int GetXMax();

	void SetYMax(int value);
	int GetYMax();
};