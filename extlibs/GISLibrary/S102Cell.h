#pragma once

#include "S100SpatialObject.h"    

#include <list>
namespace S100HDF5
{
	class S102;
}

class S102Cell : public S100SpatialObject
{
public:
	S102Cell();
	virtual ~S102Cell();

public:
	CBitmap bmpGrid;
	CDC dc;
	bool bBMP = false;   
	static int DRAWING_MODE;
	static int SAFETY_DEPTH;
	int minimumDepth = 0;
	int maximumDepth = 0;
	int ncols = 0;
	int nrows = 0;
	float dx = 0;
	float dy = 0;
	S100HDF5::S102 *s102 = nullptr;

public:
	bool Open(CString _filepath);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void CreateBitmap(CDC* pDC);
	int GetColour(double v);
	bool GetData(GeoPoint inputPt, GeoPoint& outputPt, float& depth);
	void SetMetadata();
	bool IsContain(float x, float y);
	void CalcDepthMinMax();
	bool ReOpen();
	void Close();
	bool IsOpen();
};