#pragma once
#include "Field.h"
#include "RecordName.h"

class F_PRID : Field
{
public:
	F_PRID();
	virtual ~F_PRID();

public:
	RecordName m_name;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};