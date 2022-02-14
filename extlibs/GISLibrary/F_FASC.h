#pragma once
#include "Field.h"
#include "RecordName.h" 
struct FASC;
class F_FASC : Field
{
public:
	F_FASC();
	virtual ~F_FASC();
public: 
	RecordName m_name; 
	unsigned m_nfac; 
	unsigned m_narc; 
	unsigned m_faui;

	std::list<FASC*> m_arr;
public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};