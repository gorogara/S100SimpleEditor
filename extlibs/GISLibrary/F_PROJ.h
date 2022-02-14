#pragma once
#include "Field.h" 
class F_PROJ :
	public Field
{
public:
	F_PROJ();
	virtual ~F_PROJ();

public: 
	unsigned m_prom; 
	double m_prp1; 
	double m_prp2; 
	double m_prp3; 
	double m_prp4; 
	double m_prp5; 
	double m_feas; 
	double m_fnor;

public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();

	static const int size = 57;
};

