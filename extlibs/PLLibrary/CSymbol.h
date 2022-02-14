#pragma once
#include "Field3.h"
#include "PLCommon.h"


class CSymbol
{
public:
	CSymbol();
	virtual ~CSymbol(); 

public:
	int Code;
	CString Field1;
	Field2 *m_pField2;
	int Field2_Count;
	Field3 m_pField3;
	int Field4;
	int Field5;
	int Field6;
	int Field7;
};