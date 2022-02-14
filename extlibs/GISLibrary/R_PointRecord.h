#pragma once

#include "R_VectorRecord.h"
#include "F_PRID.h"

class F_INAS;
class F_C2IT;
class F_C3IT;
class DRDirectoryInfo; 
class R_PointRecord : public R_VectorRecord
{
public:
	R_PointRecord();
	virtual ~R_PointRecord();

public:
	F_PRID m_prid;
	std::list<F_INAS*> m_inas;
	F_C2IT *m_c2it;
	F_C3IT *m_c3it;

public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file);
	int GetRCID();
};