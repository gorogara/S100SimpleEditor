#pragma once

#include "Record.h"
#include "F_CSID.h"

class F_CRSH;
class F_CSAX;
class F_PROJ;
class F_GDAT;
class F_VDAT;
class DRDirectoryInfo; 
class R_DSCRS : Record
{
public:
	R_DSCRS();
	virtual ~R_DSCRS();
public:
	F_CSID m_csid;
	std::list<F_CRSH*> m_crsh;
	F_CSAX *m_csax;
	F_PROJ *m_proj;
	F_GDAT *m_gdat;
	F_VDAT *m_vdat;

public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file);
};