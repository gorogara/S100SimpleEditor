#pragma once
#include "SpatialObject.h"
#include "S100_Members.h"

class PCOutputSchemaManager;

class BAG :
	public SpatialObject
{
public:
	BAG();
	virtual ~BAG();

public:
	struct BAG_GRID 
	{
		double x;
		double y;
		float elevation;
	};

	BAG_GRID** grid;
	int nrows;
	int ncols;
	float dx;
	float dy;
	float min_elevation;
	float max_elevation;
	CBitmap bmpGrid;
	CBitmap bmptmpGrid;
	CBitmap bmpGridback;
	CDC dc;
	CDC tmpdc;
	CDC dcback;
	std::vector<COLORREF> colorMap;  
	int s102ColorMapType;
	bool bBMP;
	PCOutputSchemaManager* pcManager; 
public:
	S100::S100_DataProduct S100Product;
	S100::S100_DataProduct GetDataProduct();
	virtual bool Open(CString _filepath);
	virtual void Draw(CDC *pDC, Scaler *scaler, double offset = 0);
	virtual void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	virtual void Draw(HDC &hDC, Scaler *scaler, int priority, int geoType, double offset = 0);
	virtual void Save(CString filename);
	int GetGridCount();
	double GetElevation(int _index);
	void ReadPCManager();
	void GetMBR(int _index, double& _xmin, double& _ymin, double& _xmax, double& _ymax);  
};