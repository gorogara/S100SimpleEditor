#pragma once
#include "SymbolParameter.h"

class APParameters : public SymbolParameter
{
public:
	APParameters();
	virtual ~APParameters();

public:
	CString PATNAME;
	CString _ROTATION;
	int ROTATION;
};