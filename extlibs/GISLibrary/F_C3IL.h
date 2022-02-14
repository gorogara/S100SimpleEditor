#pragma once
#include "Field.h"

struct C3IL;
class F_C3IL : Field
{
public:
	F_C3IL();
	virtual ~F_C3IL(); 
	unsigned m_vcid; 
	std::list<C3IL*> m_arr;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};