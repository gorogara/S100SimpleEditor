#pragma once

#define SATELLITE 1
#define RNC 2
#define ENCDAY 3
#define ENCDUSK 4
#define ENCNIGHT 5

class ArrowSurfaceCurrent
{
public:
	ArrowSurfaceCurrent();
	virtual ~ArrowSurfaceCurrent();

	static int size;  
	void Draw(CDCRenderTarget& _rt, CD2DSolidColorBrush* _pBrush, double _lon, double _lat, int _step, int _alpha, double _radian);
	void Draw(CDCRenderTarget& _rt, CD2DSolidColorBrush* _pBrush, int _x, int _y, int _step, int _alpha, double _radian);
	void Draw();

private:
	void SetRGB(int _step, int& _R, int& _G, int& _B);
	void SetPoints(CD2DPointF* _points, int _x, int _y, double _radian, int _step);
};