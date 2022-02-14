#pragma once
#include "Field.h"
class F_CCOC :
	public Field
{
public:
	F_CCOC();
	virtual ~F_CCOC();

public: 
	unsigned m_ccui; 
	unsigned m_ccix; 
	unsigned m_ncco;
	static const int size = 5;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

