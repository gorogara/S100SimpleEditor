#pragma once
#include "Field.h"
#include "RecordName.h"

class F_CRID : Field
{
public:
	F_CRID();
	virtual ~F_CRID();

public:
	RecordName m_name;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

};