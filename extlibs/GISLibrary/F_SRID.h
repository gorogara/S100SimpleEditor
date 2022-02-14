#pragma once
#include "Field.h"
#include "RecordName.h"
class F_SRID : Field
{
public:
	F_SRID();
	virtual ~F_SRID();

public:
	RecordName m_name;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};