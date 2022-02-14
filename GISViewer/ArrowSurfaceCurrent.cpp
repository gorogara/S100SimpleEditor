#include "stdafx.h"
#include "ArrowSurfaceCurrent.h"
#include "GISViewer.h"
#include "GISViewerView.h"

#include "LatLonUtility\\LatLonUtility.h"

int ArrowSurfaceCurrent::size = (int)(GetSystemMetrics(SM_CXSCREEN) * 0.05);

ArrowSurfaceCurrent::ArrowSurfaceCurrent()
{
	
}


ArrowSurfaceCurrent::~ArrowSurfaceCurrent()
{
}


void ArrowSurfaceCurrent::Draw(CDCRenderTarget& _rt, CD2DSolidColorBrush* _pBrush, double _lon, double _lat, int _step, int _alpha, double _radian)
{
	long x = 0;
	long y = 0;
	theApp.pView->m_pGisLib->Projection(&_lon, &_lat);
	theApp.pView->m_pGisLib->WorldToDevice(_lon, _lat, &x, &y);
	Draw(_rt, _pBrush, x, y, _step, _alpha, _radian);
}

void ArrowSurfaceCurrent::Draw(CDCRenderTarget& _rt, CD2DSolidColorBrush* _pBrush, int _x, int _y, int _step, int _alpha, double _radian)
{
	int Red = 0;
	int Green = 0;
	int Blue = 0;

	SetRGB(_step, Red, Green, Blue);

	_pBrush->SetOpacity(1);
	D2D1_COLOR_F color;
	color.a = (float)_alpha;
	color.b = (float)(Blue / 255.0);
	color.r = (float)(Red / 255.0);
	color.g = (float)(Green / 255.0);
	_pBrush->SetColor(color);

	CD2DPathGeometry* m_pGeometry = new CD2DPathGeometry((CRenderTarget*)&_rt);
	m_pGeometry->Create(&_rt);
	CD2DGeometrySink m_pSink(*m_pGeometry);
	m_pSink.SetFillMode(D2D1_FILL_MODE_WINDING);

	CD2DPointF points[8];
	
	SetPoints(points, _x, _y, _radian , _step);

	m_pSink.BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
	
	for (int i = 1; i < 8; i++)
	{
		m_pSink.AddLine(points[i]);
	}

	m_pSink.EndFigure(D2D1_FIGURE_END_CLOSED);
	m_pSink.Close();

	_rt.FillGeometry(m_pGeometry, _pBrush);
}

void ArrowSurfaceCurrent::Draw()
{

}


void ArrowSurfaceCurrent::SetRGB(int _step, int& _R, int& _G, int& _B)
{
	switch (_step)
	{
	case 1:
		_R = 118;
		_G = 82;
		_B = 226;
		break;
	case 2:
		_R = 72;
		_G = 152;
		_B = 211;
		break;
	case 3:
		_R = 97;
		_G = 203;
		_B = 229;
		break;
	case 4:
		_R = 109;
		_G = 188;
		_B = 69;
		break;
	case 5:
		_R = 180;
		_G = 220;
		_B = 0;
		break;
	case 6:
		_R = 205;
		_G = 193;
		_B = 0;
		break;
	case 7:
		_R = 248;
		_G = 167;
		_B = 24;
		break;
	case 8:
		_R = 247;
		_G = 162;
		_B = 157;
		break;
	case 9:
		_R = 255;
		_G = 30;
		_B = 30;
		break;
	default:
		_R = 0;
		_G = 0;
		_B = 0;
		break;
	}
}


void ArrowSurfaceCurrent::SetPoints(CD2DPointF* _points, int _x, int _y, double _radian, int _step)
{
	double sf = size / 5.0;
	double fsize = size;
	switch (_step)
	{
	case 1:
		fsize = sf * 2.6;
		break;
	case 2:
		fsize = sf * 2.9;
		break;
	case 3:
		fsize = sf * 3.2;
		break;
	case 4:
		fsize = sf * 3.5;
		break;
	case 5:
		fsize = sf * 3.8;
		break;
	case 6:
		fsize = sf * 4.1;
		break;
	case 7:
		fsize = sf * 4.4;
		break;
	case 8:
		fsize = sf * 4.7;
		break;
	case 9:
		fsize = sf * 5;
		break;
	default:
		break;
	}

	_points[0].x = (float)_x;
	_points[0].y = (float)(_y - (0.35 * fsize));

	_points[1].x = (float)(_x - (0.2 * fsize));
	_points[1].y = (float)(_y);

	_points[2].x = (float)(_x - (0.1 * fsize));
	_points[2].y = (float)(_y);

	_points[3].x = (float)(_x - (0.05 * fsize));
	_points[3].y = (float)(_y + (0.65 * fsize));

	_points[4].x = (float)(_x + (0.05 * fsize));
	_points[4].y = (float)(_y + (0.65 * fsize));

	_points[5].x = (float)(_x + (0.1 * fsize));
	_points[5].y = (float)(_y);

	_points[6].x = (float)(_x + (0.2 * fsize));
	_points[6].y = (float)_y;

	_points[7] = _points[0];

	int x = 0;
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		LatLonUtility::RotatePoint((int)_points[i].x, (int)_points[i].y, _x, _y, x, y, _radian, true);
		_points[i].x = (float)x;
		_points[i].y = (float)y;
	}
}