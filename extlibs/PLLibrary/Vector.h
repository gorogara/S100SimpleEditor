#pragma once
#include "PLCommon.h"
#include <vector>
class Symbol;
class Vector;
class CSymbolManager;

class Vector
{
public:
	Vector();
	virtual ~Vector();

public: 
	void AddPoint(char *str_point);

	void SetPen(SymbolColorRef pen);
	void SetWidth(int width);
	void SetTransparent(int transparent);	
	void SetRadius(int r);

	void SetMode();
	void SetMode(int mode);

	void SetFill(bool boolean = true);

	void Draw(CDC* pDC);
	void Draw(CDC* pDC, POINT point);
	void Draw(CDC* pDC, POINT point, double rotation);

	void Draw(Graphics* pG);
	void Draw(Graphics* pG, POINT point);
	void Draw(Graphics* pG, POINT point, double rotation);

	POINT Vector::RotatePoint(POINT p, double ROTATION);

	int point_num;
	int r;
	POINT *point;
	Gdiplus::Point *m_pPoint;

	Symbol *m_pSymbol;

	int transparent;
	int mode;
	
	int width;
	bool isFill;
	SymbolColorRef pen;	
};


namespace ePattern
{ 
	enum TypeOfFillPattern {STG , 
		                    LIN};  
	enum Spacing {CON, 
		          SCL}; 
}
