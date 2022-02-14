#pragma once

#include "Field.h"

struct ATTR;
class F_ATTR : Field
{
public:
	F_ATTR();
	virtual ~F_ATTR();

public:
	std::vector<ATTR*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};