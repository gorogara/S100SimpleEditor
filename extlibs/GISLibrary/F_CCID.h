#pragma once
#include "Field.h"
#include "RecordName.h"
class F_CCID : Field
{
public:
	F_CCID();
	virtual ~F_CCID();
	RecordName m_name;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};