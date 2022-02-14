#pragma once
#include "Field.h"
#include "RecordName.h"
class F_FRID : Field
{
public:
	F_FRID();
	virtual ~F_FRID();
public:
	RecordName m_name; 
	unsigned m_nftc;
	unsigned m_rver;
	unsigned m_ruin;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};