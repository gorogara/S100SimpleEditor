#pragma once
#include "SymbolParameter.h"

class CSParameters : public SymbolParameter
{
public:
	CSParameters();
	virtual ~CSParameters();
public:
	CString PROCNAME;
};