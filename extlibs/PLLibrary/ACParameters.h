#pragma once
#include "SymbolParameter.h"
#include "PLCommon.h" 

class ACParameters : public SymbolParameter
{
public:
	ACParameters();
	virtual ~ACParameters();

public:
	CString _COLOUR;
	COLOUR *COLOUR;
	CString _TRANSPARENCY;
	int TRANSPARENCY;
};