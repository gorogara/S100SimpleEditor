#pragma once
#include "SymbolParameter.h"

class LSParameters : public SymbolParameter
{
public:
	LSParameters();
	virtual ~LSParameters();

public:
	CString _PSTYLE;
	int PSTYLE;
	int WIDTH;
	CString _COLOUR;
	COLOUR *COLOUR;
};