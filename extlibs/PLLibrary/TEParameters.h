#pragma once
#include "SymbolParameter.h"

class TEParameters : public SymbolParameter
{
public:
	TEParameters();
	virtual ~TEParameters();

public:
	CString STRING;
	int ATTRIBUTE;
	int     HJUST;
	int     VJUST;
	int     SPACE;
	CHARS   CHARS;
	int     XOFFS;
	int     YOFFS;
	COLOUR *COLOUR;
	int	 DISPLAY;
};