#pragma once

#include <Windows.h>
#include <vector>

#include "..\\extlibs\\Clipper\\include\\clipper.hpp"

class MBR;
class GeoPoint;
class Scaler
{
public:
	Scaler();
	virtual ~Scaler();

public:
	static const long long COMF = 10000000000;

	double mox = 0;
	double moy = 0;
	double mxMin = 0;
	double myMin = 0;
	double mxMax = 0;
	double myMax = 0;

	double sox = 0;
	double soy = 0;
	double sxMin = 0;
	double syMin = 0;
	double sxMax = 0;
	double syMax = 0;

	double rotateDegree = 0;
	double currentRatio = 0;
	double currentScale = 0;

	double mxMinLimit = -179.9;
	double myMinLimit = -84.9;
	double mxMaxLimit = 179.9;
	double myMaxLimit = 84.9;

public: 
	void DeviceToWorld(long sx, long sy, double *mx, double *my, bool rotate = TRUE);
	void WorldToDevice(double mx, double my, long *sx, long *sy, bool rotate = TRUE);
	void DeviceToWorld_F(float sx, float sy, double *mx, double *my, bool rotate = TRUE);
	void WorldToDevice_F(double mx, double my, float *sx, float *sy, bool rotate = TRUE);  
	double GetDistanceLatitudeLongitude(double longitude1, double latitude1, double longitude2, double latitude2); 

	double GetDistanceRhumbLineMercator(double lat1, double lon1, double lat2, double lon2, bool radian);  
	double GetDistanceScreen(int x1, int y1, int x2, int y2);  
	void SetScreen(RECT *rect);
	void SetScreen(const RECT& rect); 
	int  GetScreenWidth();
	int  GetScreenHeight();
	CRect GetScreenRect();
	D2D1_RECT_F GetD2Rect();  
	void SetMap(double xmin, double ymin, double xmax, double ymax);
	void SetMap(MBR mbr);

	double GetMapWidth();
	double GetMapHeight();

	void GetMap(MBR *mbr);
	MBR GetMap(); 
	int GetCurrentScale();
	void   SetScale(int scale);
	void   UpdateScale(); 
	void ZoomIn(double value);
	void ZoomIn(double value, int x, int y);
	void ZoomOut(double value);
	void ZoomOut(double value, int x, int y);  
	void MoveMap(int x, int y); 
	void MoveMap(int sx, int sy, double mx, double my);

	void Projection(double *x, double *y);
	void InverseProjection(double *x, double *y); 
	void Rotate(LONG *sx, LONG *sy, double degree);
	void RotateMap(double degree); 
	void NorthUp(); 
	void AdjustScreenMap();

	void AdjustScreenMap_Internal(); 
	double GetScreenWidthKM();

	bool PtInMap(double _x, double _y);
	ClipperLib::PolyTree* ClipPolyline(GeoPoint* _p, int _cnt);

	void PrivateMoveMap(int sx, int sy, double mx, double my);

	D2D1::Matrix3x2F GetMatrix();
	D2D1::Matrix3x2F GetInverseMatrix();

	CRect WGS84MBRtoCRect(MBR& mbr);
};