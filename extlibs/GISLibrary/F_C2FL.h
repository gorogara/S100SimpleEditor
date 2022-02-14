#pragma once
#include "Field.h"


struct FC2D;
class F_C2FL : Field
{
public:
	F_C2FL();
	virtual ~F_C2FL(); 
	std::list<FC2D*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

