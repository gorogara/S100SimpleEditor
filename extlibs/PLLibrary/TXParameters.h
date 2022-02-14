#pragma once
#include "SymbolParameter.h"

class TXParameters : public SymbolParameter
{
public:
	TXParameters();
	virtual ~TXParameters();

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