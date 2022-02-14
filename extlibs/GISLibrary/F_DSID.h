#pragma once

#include "Field.h"
#include "RecordName.h" 
class F_DSID : Field
{
public:
	F_DSID();
	virtual ~F_DSID();

public:
	RecordName m_name;
	CString m_ensp; 
	CString m_ened; 
	CString m_prsp; 
	CString m_pred; 
	CString m_prof; 
	CString m_dsnm; 
	CString m_dstl; 
	CString m_dsrd; 
	CString m_dslg; 
	CString m_dsab;//datasetAbstract
	CString m_dsed; 
	CArray<unsigned> m_dstc;

public:
	void ReadField(BYTE *&buf);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
};