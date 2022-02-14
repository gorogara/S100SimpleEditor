#pragma once

#include "R_VectorRecord.h"
#include "F_CRID.h"

class F_INAS;
class F_PTAS;
class F_SECC;
class F_SEGH;
class F_COCC;
class F_C2IL;
class DRDirectoryInfo; 
class R_CurveRecord : public R_VectorRecord
{
public:
	R_CurveRecord();
	virtual ~R_CurveRecord();

public:
	F_CRID m_crid;
	list<F_INAS*> m_inas;
	F_PTAS* m_ptas;
	F_SECC* m_secc;
	list<F_SEGH*> m_segh;
	F_COCC* m_cocc;
	list<F_C2IL*> m_c2il;

public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file);
	int GetRCID();
};


