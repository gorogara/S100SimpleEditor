#pragma once
#include "Field.h"
class F_VDAT : Field
{
public:
	F_VDAT();
	virtual ~F_VDAT();

public:
	CString m_dtnm;
	CString m_dtid;
	unsigned m_dtsr;
	CString m_scri;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

