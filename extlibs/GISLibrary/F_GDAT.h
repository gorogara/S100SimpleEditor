#pragma once
#include "Field.h"
class F_GDAT :
	public Field
{
public:
	F_GDAT();
	virtual ~F_GDAT();

public: 
	CString m_dtnm; 
	CString m_elnm; 
	double m_esma; 
	unsigned m_espt; 
	double m_espm; 
	CString m_cmnm; 
	double m_cmgl;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

