#pragma once
#include "Field.h"
#include "RecordName.h"

struct PTAS;
class F_PTAS : Field
{
public:
	F_PTAS();
	virtual ~F_PTAS();

public:
	CList<PTAS*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

