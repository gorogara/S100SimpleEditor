#include "stdafx.h"
#include "Bag.h"
#include "libS111.h"

#include "GeoMetryLibrary\\ENCCommon.h"
#include "GeoMetryLibrary\\Scaler.h"
#include "..\\libS100HDF5\\S102.h"


int Bag::DRAWING_MODE = 0;
int Bag::SAFETY_DEPTH = 0;

int Bag::DEPTH_RANGE[S102_STEP_COUNT];

Bag::Bag()
{
	bBMP = false;
}

Bag::~Bag()
{
	delete _S102;
	_S102 = nullptr;

	bmpGrid.DeleteObject();
	dc.DeleteDC();
}

bool Bag::ReOpen()
{
	_S102 = new S100HDF5::S102();
	return _S102->Open(_pathName);
}

bool Bag::IsOpen()
{
	if (_S102)
	{
		return true;
	}

	return false;
}

void Bag::Close()
{
	delete _S102;
	_S102 = nullptr;
}

int Bag::GetColour(double v, double vmin, double vmax)
{
	if (DRAWING_MODE == 0)
	{
		double r = 1;
		double g = 1;
		double b = 1;

		double dv;   

		if (v < vmin)
		{
			v = vmin;
		}

		if (v > vmax)
		{
			v = vmax;
		}

		dv = vmax - vmin;    

		double stan1 = 0.25;
		double stan2 = 0.5;
		double stan3 = 0.75;
		double stan4 = 0.8;

		double weight1 = 4;
		double weight2 = 4;
		double weight3 = 4;
		double weight4 = 4;

		if (v < (vmin + stan1 * dv))
		{  

			r = 0;
			g = weight1 * (v - vmin) / dv;
		}
		else if (v < (vmin + stan2 * dv))
		{  

			r = 0;
			b = 1 + weight2 * (vmin + stan1 * dv - v) / dv;
		}
		else if (v < (vmin + stan3 * dv))
		{  

			r = weight3 * (v - vmin - stan2 * dv) / dv;
			b = 0;
		}
		else
		{  

			g = 1 + weight4 * (vmin + stan3 * dv - v) / dv;
			b = 0;
		}                       

		int intr = (int)(r * 255);
		int intg = (int)(g * 255);
		int intb = (int)(b * 255);

		int c = intr << 16 | intg << 8 | intb;

		return(c);
	}
	else if (DRAWING_MODE == 2)
	{
		double greyWeight = 1;

		double dv;
		if (v < vmin)
		{
			v = vmin;
		}

		if (v > vmax)
		{
			v = vmax;
		}

		dv = vmax - vmin;

		double stan1 = 0.25;
		double stan2 = 0.5;
		double stan3 = 0.75;
		double stan4 = 0.8;

		double weight1 = 4;
		double weight2 = 4;
		double weight3 = 4;
		double weight4 = 4;

		if (v < (vmin + stan1 * dv))
		{
			greyWeight = weight1 * (v - vmin) / dv;
		}
		else if (v < (vmin + stan2 * dv))
		{
			greyWeight = weight2 * (v - vmin) / dv;
		}
		else if (v < (vmin + stan3 * dv))
		{
			greyWeight = weight3 * (v - vmin) / dv;
		}
		else
		{
			greyWeight = weight4 * (v - vmin) / dv;
		}

		int intGreyWeight = (int)(greyWeight * 255);

		int c = intGreyWeight << 16 | intGreyWeight << 8 | intGreyWeight;

		return(c);
	}

	else
	{
		int c = 0;
		if (v > SAFETY_DEPTH)
			c = 240 << 16 | 20 << 8 | 20;
		else
			c = 255 << 16 | 255 << 8 | 255;

		return(c);
	}
}

int Bag::GetColour(double v)
{
	int MODE = DRAWING_MODE % 100;
	if (MODE == 0)
	{
		int r = 255;
		int g = 255;
		int b = 255;

		if (v < -ENCCommon::DEEP_CONTOUR)
		{
			r = 201;
			g = 237;
			b = 255;
		}
		else if (v < -ENCCommon::SAFETY_CONTOUR)
		{
			r = 167;
			g = 217;
			b = 251;
		}
		else if (v < -ENCCommon::SHALLOW_CONTOUR)
		{
			r = 130;
			g = 202;
			b = 255;
		}
		else if (v < 0)
		{
			r = 97;
			g = 183;
			b = 255;
		}

		return r << 16 | g << 8 | b;
	}
	else if (MODE == 2)
	{
		double greyWeight = 1;

		double dv;
		if (v < minimumDepth)
		{
			v = minimumDepth;
		}

		if (v > maximumDepth)
		{
			v = maximumDepth;
		}

		dv = maximumDepth - minimumDepth;


		greyWeight = (v - minimumDepth) / dv;

		int intGreyWeight = (int)((1 - greyWeight) * 255);

		int c = intGreyWeight << 16 | intGreyWeight << 8 | intGreyWeight;

		return(c);
	}

	else
	{
		int c = 0;
		if (v > SAFETY_DEPTH)
			c = 240 << 16 | 20 << 8 | 20;
		else
			c = 255 << 16 | 255 << 8 | 255;

		return(c);
	}
}

void Bag::CreateBitmap(CDC* pDC)
{
	if (!_S102)
	{
		ReOpen();
	}

	auto regularGrid = _S102->GetRegularGrid(0);
	if (regularGrid)
	{
		auto featureValue = regularGrid->GetRegularGridFeatureValues(0);
		auto gridInfo = regularGrid->GetRegularGridInformation();
		if (gridInfo && featureValue)
		{
			auto floatValue = featureValue->GetFloatValues(0);
			if (!floatValue)
			{
				return;
			}

			float *values = floatValue->GetValues();

			int ncols = gridInfo->GetNumPointLongitudinal();
			int nrows = gridInfo->GetNumPointLatitudinal();

			if (bmpGrid.GetSafeHandle())
			{
				dc.DeleteDC();
				bmpGrid.DeleteObject();
				bBMP = false;
			}

			if (!bBMP)
			{
				if (bmpGrid.CreateBitmap(ncols, nrows, 1, 32, NULL) == 0)
				{
					return;
				}

				dc.CreateCompatibleDC(pDC);
				dc.SelectObject(bmpGrid);

				BITMAP pBitmap;
				bmpGrid.GetBitmap(&pBitmap);

				int *bmpBuffer = new int[pBitmap.bmWidth * pBitmap.bmHeight];
				memset(bmpBuffer, 0, sizeof(int) * (pBitmap.bmWidth * pBitmap.bmHeight));

				float gridOriginX = gridInfo->GetGridOgirinLongitude();
				float gridOriginY = gridInfo->GetGridOriginLatitude();
				float dx = gridInfo->GetGridSpacingLongitudinal();
				float dy = gridInfo->GetGridSpacingLatitudinal();

				for (int irow = 0; irow < nrows; irow++)
				{
					for (int icol = 0; icol < ncols; icol++)
					{
						int index = (nrows - 1 - irow) * ncols + icol;

						if (values[(irow * ncols) + icol] == 1000000.0)
						{
							bmpBuffer[index] = RGB(255, 255, 255);

							continue;
						}

						double elevation = values[(irow * ncols) + icol];

						if (libS102::GetS104Mode())
						{
							double waterLevel = 0;

							time_t now = time(nullptr); 
							libS104::GetData(gridOriginX + (dx * icol), gridOriginY + (dy * irow), waterLevel); 
							elevation += waterLevel;
						}

						bmpBuffer[index] = GetColour(elevation);
					}
				}

				bmpGrid.SetBitmapBits(pBitmap.bmWidthBytes * pBitmap.bmHeight, bmpBuffer);

				delete[] bmpBuffer;

				bBMP = true;
			}
		}
	}

	Close();
}

void Bag::Draw(HDC &hDC, Scaler *scaler, Rect rectF)
{ 
	GeoPoint mLeftBottom;
	GeoPoint mRightTop;

	mLeftBottom.x = xmin * 10000000;
	mLeftBottom.y = ymin * 10000000;

	mRightTop.x = xmax * 10000000;
	mRightTop.y = ymax * 10000000; 
	GeoPoint viewLeftBottom;
	GeoPoint viewRightTop;

	scaler->DeviceToWorld(rectF.X, rectF.Y + rectF.Height, &viewLeftBottom.x, &viewLeftBottom.y);
	scaler->DeviceToWorld(rectF.X + rectF.Width, rectF.Y, &viewRightTop.x, &viewRightTop.y);

	scaler->InverseProjection(&viewLeftBottom.x, &viewLeftBottom.y);
	scaler->InverseProjection(&viewRightTop.x, &viewRightTop.y);  

	viewLeftBottom.x *= 10000000;
	viewLeftBottom.y *= 10000000;
	viewRightTop.x *= 10000000;
	viewRightTop.y *= 10000000; 
	CRect bagRect((int)mLeftBottom.x, (int)mLeftBottom.y, (int)mRightTop.x, (int)mRightTop.y);
	CRect viewRect((int)viewLeftBottom.x, (int)viewLeftBottom.y, (int)viewRightTop.x, (int)viewRightTop.y);
	CRect intersectRect; 

	if (intersectRect.IntersectRect(bagRect, viewRect))
	{
		int intDX = (int)(dx * 10000000);
		int intDY = (int)(dy * 10000000); 
		int xLeftIndex = (int)((intersectRect.left - mLeftBottom.x) / intDX);
		int xRightIndex = (int)((intersectRect.right - mLeftBottom.x) / intDX);
		int yTopIndex = (int)((intersectRect.bottom - mLeftBottom.y) / intDY);
		int yBottomIndex = (int)((intersectRect.top - mLeftBottom.y) / intDY); 
		if (xRightIndex >= ncols) xRightIndex = ncols - 1;
		if (yTopIndex >= nrows) yTopIndex = nrows - 1; 
		int nWidth = xRightIndex - xLeftIndex + 1;
		int nHeight = yTopIndex - yBottomIndex + 1; 
		intersectRect.left = (LONG)(mLeftBottom.x + (intDX * xLeftIndex));
		intersectRect.right = (LONG)(mLeftBottom.x + (intDX * (xRightIndex + 1)));
		intersectRect.top = (LONG)(mLeftBottom.y + (intDY * (yTopIndex + 1)));
		intersectRect.bottom = (LONG)(mLeftBottom.y + (intDY * yBottomIndex));

		GeoPoint newLeftBottom;
		GeoPoint newRightTop;
		newLeftBottom.x = intersectRect.left;
		newLeftBottom.y = intersectRect.bottom;
		newRightTop.x = intersectRect.right;
		newRightTop.y = intersectRect.top; 
		CPoint newSLeftBottom;
		CPoint newSRightTop;

		newLeftBottom.x -= 1000;
		newLeftBottom.y -= 1000;
		newRightTop.x += 1000;
		newRightTop.y += 1000;

		newLeftBottom.x /= 10000000.0;
		newLeftBottom.y /= 10000000.0;
		newRightTop.x /= 10000000.0;
		newRightTop.y /= 10000000.0;

		viewLeftBottom.x /= 10000000.0;
		viewLeftBottom.y /= 10000000.0;
		viewRightTop.x /= 10000000.0;
		viewRightTop.y /= 10000000.0;

		scaler->Projection(&viewLeftBottom.x, &viewLeftBottom.y);
		scaler->Projection(&viewRightTop.x, &viewRightTop.y);


		scaler->Projection(&newLeftBottom.x, &newLeftBottom.y);
		scaler->Projection(&newRightTop.x, &newRightTop.y);


		scaler->WorldToDevice(newLeftBottom.x, newLeftBottom.y, &newSLeftBottom.x, &newSLeftBottom.y);
		scaler->WorldToDevice(newRightTop.x, newRightTop.y, &newSRightTop.x, &newSRightTop.y);   
		SetStretchBltMode(hDC, COLORONCOLOR);

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = 0;  
		CDC::FromHandle(hDC)->TransparentBlt(newSLeftBottom.x, newSRightTop.y, newSRightTop.x - newSLeftBottom.x, newSLeftBottom.y - newSRightTop.y, &dc, xLeftIndex, nrows - yTopIndex - 1, nWidth, nHeight, RGB(255, 255, 255));
		return;
	}
}                                                                                                         

bool Bag::IsContain(float x, float y)
{
	if (x >= xmin && x <= xmax &&
		y >= ymin && y <= ymax)
	{
		return true;
	}
	return false;
}

void Bag::SetMetadata()
{
	if (_S102)
	{
		auto feature = _S102->GetRegularGrid(0);
		if (feature)
		{
			auto gridInfo = feature->GetRegularGridInformation();
			if (gridInfo)
			{
				ncols = gridInfo->GetNumPointLongitudinal();
				nrows = gridInfo->GetNumPointLatitudinal();

				dx = gridInfo->GetGridSpacingLongitudinal();
				dy = gridInfo->GetGridSpacingLatitudinal();

				xmin = gridInfo->GetGridOgirinLongitude();
				ymin = gridInfo->GetGridOriginLatitude();
				xmax = xmin + (dx * ncols);
				ymax = ymin + (dy * nrows);
			}
		}
	}
}

void Bag::SetSummaryValues()
{                       
}

void Bag::SetSummaryXY()
{                                               
}

void Bag::SetDepthMinMax(int _minimumDepth, int _maximumDepth)
{
	minimumDepth = _minimumDepth;
	maximumDepth = _maximumDepth;
}

void Bag::GetDepthMinMax(int &_minimumDepth, int &_maximumDepth)
{
	_minimumDepth = minimumDepth;
	_maximumDepth = maximumDepth;
}

void Bag::CalcDepthMinMax()
{
	if (_S102)
	{
		auto feature = _S102->GetRegularGrid(0);
		if (feature)
		{
			auto gridInfo = feature->GetRegularGridInformation();
			auto featureValue = feature->GetRegularGridFeatureValues(0);
			if (featureValue)
			{
				auto floatValue = featureValue->GetFloatValues(0);
				if (floatValue)
				{
					auto value = floatValue->GetValues();
					if (value)
					{
						if (gridInfo)
						{
							int ncols = gridInfo->GetNumPointLongitudinal();
							int nrows = gridInfo->GetNumPointLatitudinal();

							if (ncols < 1 || nrows < 1)
							{
								minimumDepth = 0;
								maximumDepth = 0;
								return;
							}

							double min = 0;
							double max = 0;
							for (int irow = 0; irow < nrows; irow++)
							{
								for (int icol = 0; icol < ncols; icol++)
								{
									if (value[(irow * ncols) + icol] == 1000000.0)
									{
										continue;
									}
									else
									{
										min = value[(irow * ncols) + icol] < min ? value[(irow * ncols) + icol] : min;
										max = value[(irow * ncols) + icol] > max ? value[(irow * ncols) + icol] : max;
									}
								}
							}

							minimumDepth = (int)(min - 1);
							maximumDepth = (int)(max + 0.99);
						}
					}
				}
			}
		}
	}
}

bool Bag::GetData(GeoPoint inputPt, GeoPoint& outputPt, float& depth)
{
	if (_S102)
	{
		auto feature = _S102->GetRegularGrid(0);
		if (feature)
		{
			auto featureValue = feature->GetRegularGridFeatureValues(0);
			if (featureValue)
			{
				auto floatValue = featureValue->GetFloatValues(0);
				if (floatValue)
				{
					auto value = floatValue->GetValues();
					if (value)
					{
						auto gridInfo = feature->GetRegularGridInformation();
						if (gridInfo)
						{
							double inputX = (double)(inputPt.x / 10000000.0);
							double inputY = (double)(inputPt.y / 10000000.0);

							int xIndex = 0;
							int yIndex = 0;

							xIndex = (int)((inputX - xmin) / dx);
							yIndex = (int)((inputY - ymin) / dy);

							if ((xIndex >= 0 && xIndex < ncols) && (yIndex >= 0 && yIndex < nrows))
							{
								depth = value[(yIndex * ncols) + xIndex];
								if (depth == 1000000.0)
								{
									depth = 0;
									return false;
								}

								outputPt.x = (xmin * 10000000.0) + (dx * 10000000.0) * xIndex + ((dx / 2.0) * 10000000.0);
								outputPt.y = (ymin * 10000000.0) + (dy * 10000000.0) * yIndex + ((dy / 2.0) * 10000000.0);
							}
							else
							{
								return false;
							}
						}
					}
				}
			}

			return true;
		}


	}

	return false;
}         

bool Bag::GetbBmp() 
{
	return bBMP;
}

void Bag::SetbBmp(bool value) 
{
	bBMP = value;
}

CString* Bag::GetFileName() 
{
	return &fileName;
}

void Bag::SetFileName(CString* value)
{
	fileName = *value;
}

int Bag::GetMinimumDepth()
{
	return minimumDepth;
}

void Bag::SetMinimumDepth(int value) 
{
	minimumDepth = value;
}

int Bag::GetMaximumDepth() 
{
	return maximumDepth;
}

void Bag::SetMaximumDepth(int value) 
{
	maximumDepth = value;
}

S100HDF5::S102 * Bag::GetS102() 
{
	return _S102;
}

void Bag::SetS102(S100HDF5::S102 * value)
{
	_S102 = value;
}


std::string Bag::GetPathName() 
{
	return _pathName;
}

void Bag::SetPathName(std::string value) 
{
	_pathName = value;
}

int Bag::GetCols() 
{
	return ncols;
}

void Bag::SetCols(int value) 
{
	ncols = value;
}

int Bag::GetRows()
{
	return nrows;
}

void Bag::SetRows(int value) 
{
	nrows = value;
}

float Bag::GetDx()
{
	return dx;
}

void Bag::SetDx(float value) 
{
	dx = value;
}

float Bag::GetDy() 
{
	return dy;
}

void Bag::SetDy(float value) 
{
	dy = value;
}

float Bag::GetXmin() 
{
	return xmin;
}

void Bag::SetXmin(float value) 
{
	xmin = value;
}

float Bag::GetYmin()
{
	return ymin;
}

void Bag::SetYmin(float value) 
{
	ymin = value;
}

float Bag::GetXmax() 
{
	return xmax;
}

void Bag::SetXmax(float value) 
{
	xmax = value;
}

float Bag::GetYmax()
{
	return ymax;
}

void Bag::SetYmax(float value)
{
	ymax = value;
}


