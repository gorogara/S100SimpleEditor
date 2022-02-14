#pragma once
#include "Field.h"

#include <unordered_map> 
class CodeWithNumericCode;
class F_CodeWithNumericCode : public Field
{ 
public:
	F_CodeWithNumericCode();
	virtual ~F_CodeWithNumericCode();
	std::unordered_map<int, CodeWithNumericCode*> m_arr;
	std::unordered_map<std::wstring, CodeWithNumericCode*> m_arrFindForCode;
public:
	void ReadField(BYTE *&buf);
	void ReadField(BYTE *&buf, int loopCnt);
	BOOL Save(CFile *file);
	unsigned GetFieldLength();
	CString GetFeatureCode(int numericCode);
};