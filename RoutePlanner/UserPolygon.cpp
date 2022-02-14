#include "stdafx.h"
#include "UserPolygon.h"
#include "UserLayer.h"
#include "LatLonUtility\\LatLonUtility.h"

#include <memory>

using namespace RT;
using namespace LatLonUtility;

UserPolygon::UserPolygon(double _px[], double _py[], int _cnt, std::wstring _name, std::wstring _description)
{
	px  = new double[_cnt];
	py  = new double[_cnt];
	cnt = _cnt;

	for (int i = 0; i < _cnt; i++)
	{
		px[i] = _px[i];
		py[i] = _py[i];
	}

	type = TYPE_POLYGON;
	name = _name;
	description = _description;

	Centroid(px, py, cnt, centX, centY);

	lineWeight = 3;
}

UserPolygon::~UserPolygon(void)
{
	delete[] px;
	delete[] py;
}

void UserPolygon::Set(double _px[], double _py[], int _cnt)
{
	memcpy(px, _px, sizeof(double) * _cnt);
	memcpy(py, _py, sizeof(double) * _cnt);
	cnt = _cnt;
}

void UserPolygon::Get(double** _px, double** _py, int& _cnt)
{
	*_px = new double[cnt];
	*_py = new double[cnt];
	_cnt = cnt;
	memcpy(*_px, px, sizeof(double) * _cnt);
	memcpy(*_py, py, sizeof(double) * _cnt);
}

void UserPolygon::GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax)
{
	_xmin = 0;
	_ymin = 0;
	_xmax = 0;
	_ymax = 0;

	if (cnt < 1) return;

	double xmin = px[0];
	double ymin = py[0];
	double xmax = px[0];
	double ymax = py[0];

	for (int i = 1; i < cnt; i++)
	{
		if (px[i] < xmin) xmin = px[i];
		if (py[i] < ymin) ymin = py[i];
		if (px[i] > xmax) xmax = px[i];
		if (py[i] > ymax) ymax = py[i];
	}

	_xmin = xmin;
	_ymin = ymin;
	_xmax = xmax;
	_ymax = ymax;
}