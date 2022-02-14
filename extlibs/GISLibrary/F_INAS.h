#pragma once
#include "Field.h"

#include "RecordName.h"
#include "F_ATTR.h"

class F_INAS : Field
{
public:
	F_INAS();
	virtual ~F_INAS(); 
public:
	RecordName m_name; 
	unsigned m_niac; 
	unsigned m_narc; 
	unsigned m_iuin; 
	CList<ATTR*> m_arr;
	
	static const int size = 10;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

