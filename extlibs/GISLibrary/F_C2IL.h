#pragma once
#include "Field.h"

struct IC2D;
class F_C2IL : Field
{
public:
	F_C2IL();
	virtual ~F_C2IL(); 
	std::list<IC2D*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

