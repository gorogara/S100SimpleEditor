#pragma once

#include "libS102.h"

#include "GeoMetryLibrary\\GeoPoint.h" 

namespace S100HDF5
{
	class S102;
}

class Scaler;

class Bag
{
public:
	Bag();
	virtual ~Bag();

public:

	bool ReOpen();
	void Close();
	bool IsOpen();
	void Draw(HDC &hDC, Scaler *scaler, Rect rectF);
	void CreateBitmap(CDC* pDC);
	int GetColour(double v, double vmin, double vmax);
	int GetColour(double v);
	bool GetData(GeoPoint inputPt, GeoPoint& outputPt, float& depth);
	void CalcDepthMinMax();
	void SetDepthMinMax(int minimumDepth, int maximumDepth);
	void GetDepthMinMax(int &minimumDepth, int &maximumDepth);
	void SetSummaryXY();
	void SetSummaryValues();
	void SetMetadata();
	bool IsContain(float x, float y); 

	CBitmap* GetBmpGrid();
	void SetBmpGrid(CBitmap* value);

	CDC* GetDc();
	void SetDc(CDC* value);

	CBitmap* GetBmpGridWithSummaryS104();
	void SetBmpGridWithSummaryS104(CBitmap* value );

	bool GetbBmp();
	void SetbBmp(bool value);

	CString* GetFileName();
	void SetFileName(CString* value);

	int GetMinimumDepth();
	void SetMinimumDepth(int value);

	int GetMaximumDepth();
	void SetMaximumDepth(int value);

	S100HDF5::S102 * GetS102();
	void SetS102(S100HDF5::S102 * value);

	std::string GetPathName();
	void SetPathName(std::string value);

	int GetCols();
	void SetCols(int value);

	int GetRows();
	void SetRows(int value);

	float GetDx();
	void SetDx(float value);

	float GetDy();
	void SetDy(float value);

	float GetXmin();
	void SetXmin(float value);

	float GetYmin();
	void SetYmin(float value);

	float GetXmax();
	void SetXmax(float value);

	float GetYmax();
	void SetYmax(float value);



public:

	CBitmap bmpGrid;
	CDC dc;

	CBitmap bmpGridWithSummaryS104;
	CDC dcWithSummaryS104;

	bool bBMP = false;
	CString fileName; 

	int minimumDepth = 0;
	int maximumDepth = 0;       
	static int DRAWING_MODE;
	static int SAFETY_DEPTH;

	static int DEPTH_RANGE[S102_STEP_COUNT];

	S100HDF5::S102 *_S102 = nullptr;

	std::string _pathName;

	int ncols = 0;
	int nrows = 0;
	float dx = 0;
	float dy = 0;
	float xmin = 0;
	float ymin = 0;
	float xmax = 0;
	float ymax = 0;
};