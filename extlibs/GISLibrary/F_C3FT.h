#pragma once
#include "Field.h"
class F_C3FT :
	public Field
{
public:
	F_C3FT();
	virtual ~F_C3FT(); 
	unsigned m_vcid; 
	double m_ycoo; 
	double m_xcoo; 
	double m_zcoo;

	static const int size = 25;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};