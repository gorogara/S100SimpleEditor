#pragma once
#include "Field.h"
#include "RecordName.h"

class F_IRID : Field
{
public:
	F_IRID();
	virtual ~F_IRID();
public: 
	RecordName m_name; 
	unsigned m_nitc; 
	unsigned m_rver; 
	unsigned m_ruin; 

	CString name = L"";

	

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

};

