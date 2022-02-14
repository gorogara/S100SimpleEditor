#pragma once

#include "Record.h"
#include "F_IRID.h"
class F_ATTR;
class F_INAS;
class DRDirectoryInfo; 
class R_InformationRecord : Record
{
public:
	R_InformationRecord();
	virtual ~R_InformationRecord();
public: 
	F_IRID m_irid;
	std::list<F_ATTR*> m_attr;
	std::list<F_INAS*> m_inas;
public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file);
	int GetRCID();
	int GetAttributeIndex(ATTR* value);

	int GetAssociationCount();
	int GetInformationAssociationCount();
};

