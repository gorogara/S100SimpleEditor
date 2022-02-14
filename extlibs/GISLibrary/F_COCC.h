#pragma once
#include "Field.h"
class F_COCC :
	public Field
{
public:
	F_COCC();
	virtual ~F_COCC();

public: 
	unsigned m_coui; 
	unsigned m_coix; 
	unsigned m_ncor;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};

