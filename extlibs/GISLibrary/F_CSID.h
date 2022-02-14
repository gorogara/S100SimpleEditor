#pragma once
#include "Field.h"
#include "RecordName.h"
class F_CSID : Field
{
public:
	F_CSID();
	virtual ~F_CSID();

public:
	RecordName m_name;
	unsigned m_ncrc;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};