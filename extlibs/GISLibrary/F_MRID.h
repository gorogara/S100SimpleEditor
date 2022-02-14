#pragma once
#include "Field.h"
#include "RecordName.h"

class F_MRID : Field
{
public:
	F_MRID();
	virtual ~F_MRID();
public:
	RecordName m_name;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

};

