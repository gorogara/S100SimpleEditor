#pragma once
#include "Field.h"
class F_C3IT :
	public Field
{
public:
	F_C3IT();
	virtual ~F_C3IT(); 
	unsigned m_vcid; 
	int m_ycoo; 
	int m_xcoo; 
	int m_zcoo;
	
	static const int size = 13;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

