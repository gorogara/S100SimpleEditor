#pragma once
#include "SymbolParameter.h"

class SYParameters : public SymbolParameter
{
public:
	SYParameters();
	virtual ~SYParameters();

public:
	CString SYNAME;
	int ROTATION;
};