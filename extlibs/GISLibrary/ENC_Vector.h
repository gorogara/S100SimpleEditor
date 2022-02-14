#pragma once

#include "VRID.h"


#include <list>
#include <unordered_map>
using namespace std;

class DRDirectoryInfo;

class ATTV;
class VRPC;
class VRPT;
class SGCC;
class SG2D;
class SG3D;

class ENC_Vector
{
public:
	ENC_Vector();
	virtual ~ENC_Vector();

public:
	VRID m_vrid;
	list<ATTV*> m_attvList;
	VRPC *m_vrpc;
	list<VRPT*> m_vrptList;
	SGCC *m_sgcc;
	list<SG2D*> m_sg2dList;
	list<SG3D*> m_sg3dList;

public:
	bool ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	bool SaveRecord(CFile *file, unsigned char DRIndex);
	bool RemoveAllFeilds();
	bool UpdateFields(ENC_Vector* ve); 
};

typedef unordered_map<__int64, ENC_Vector*> VectorHash;
typedef pair <__int64, ENC_Vector*> Vector_Pair;