#pragma once
#include "Field.h"
class F_CRSH : Field
{
public:
	F_CRSH();
	virtual ~F_CRSH();
public: 
	unsigned m_crix; 
	unsigned m_crst; 
	unsigned m_csty; 
	CString m_crnm; 
	CString m_crsi; 
	unsigned m_crss; 
	CString m_scri;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

