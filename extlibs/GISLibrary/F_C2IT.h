#pragma once
#include "Field.h"

class F_C2IT :
	public Field
{
public:
	F_C2IT();
	virtual ~F_C2IT();

public: 
	int m_ycoo; 
	int m_xcoo;
	static const int size = 8;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};