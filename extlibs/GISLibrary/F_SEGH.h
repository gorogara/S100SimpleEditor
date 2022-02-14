#pragma once
#include "Field.h"
class F_SEGH : Field
{
public:
	F_SEGH();
	virtual ~F_SEGH();

public: 
	unsigned m_intp; 
	unsigned m_circ; 
	double m_ycoo; 
	double m_xcoo; 
	double m_dist; 
	unsigned m_disu; 
	double m_sbrg; 
	double m_angl;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

};

