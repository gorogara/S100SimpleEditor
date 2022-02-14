#pragma once
#include "Field.h"
class F_C2FT :
	public Field
{
public:
	F_C2FT();
	virtual ~F_C2FT();
public: 
	double m_ycoo; 
	double m_xcoo;
	static const int size = 16;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

