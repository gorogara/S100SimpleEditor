#pragma once

#include "Record.h"
#include "F_DSID.h"
#include "F_DSSI.h"
#include "F_CodeWithNumericCode.h"

class F_ATTR;
class DRDirectoryInfo; 
class R_DSGIR : Record
{
public:
	R_DSGIR();
	virtual ~R_DSGIR();

public:
	F_DSID m_dsid;
	F_DSSI m_dssi;
	F_CodeWithNumericCode *m_atcs = new F_CodeWithNumericCode();
	F_CodeWithNumericCode *m_itcs = new F_CodeWithNumericCode();
	F_CodeWithNumericCode *m_ftcs = new F_CodeWithNumericCode();
	F_CodeWithNumericCode *m_iacs = new F_CodeWithNumericCode();
	F_CodeWithNumericCode *m_facs = new F_CodeWithNumericCode();
	F_CodeWithNumericCode *m_arcs = new F_CodeWithNumericCode(); 

public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file); 
	CString GetFeatureCode(int numericCode);
	CString GetInformationCode(int numericCode);
	CString GetAttributeCode(int numericCode);
	CString GetInformationAssociationCode(int numericCode);
	CString GetFeatureAssociationCode(int numericCode);
	CString GetAssociationRoleCode(int numericCode);
};

