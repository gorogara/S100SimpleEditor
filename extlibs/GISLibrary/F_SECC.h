#pragma once
#include "Field.h"
class F_SECC :
	public Field
{

public:
	F_SECC();
	virtual ~F_SECC();

public: 
	unsigned *m_seui; 
	unsigned *m_seix; 
	unsigned *m_nseg;
public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

