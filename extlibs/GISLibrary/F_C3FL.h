#pragma once
#include "Field.h"

struct FC3D;

class F_C3FL : Field
{
public:
	F_C3FL();
	virtual ~F_C3FL(); 
	unsigned m_vcid; 
	std::list<FC3D*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};