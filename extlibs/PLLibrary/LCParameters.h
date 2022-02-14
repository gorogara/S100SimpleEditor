#pragma once
#include "SymbolParameter.h"

class LCParameters : public SymbolParameter
{
public:
	LCParameters();
	virtual ~LCParameters();

public:
	CString LINNAME;
};
