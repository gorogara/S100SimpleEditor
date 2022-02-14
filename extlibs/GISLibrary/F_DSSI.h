#pragma once
#include "Field.h"
class F_DSSI : Field
{
public:
	F_DSSI();
	virtual ~F_DSSI();
public:
	double m_dcox;
	double m_dcoy;
	double m_dcoz;
	unsigned m_cmfx;
	unsigned m_cmfy;
	unsigned m_cmfz;
	unsigned m_noir;
	unsigned m_nopn;
	unsigned m_nomn;
	unsigned m_nocn;
	unsigned m_noxn;
	unsigned m_nosn;
	unsigned m_nofr;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};