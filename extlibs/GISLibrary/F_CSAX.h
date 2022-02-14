#pragma once
#include "Field.h"

struct CSAX;
class F_CSAX : Field
{
public:
	F_CSAX();
	virtual ~F_CSAX();

	CList<CSAX*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

};

