#pragma once 
#include "stdafx.h"
#include "PLCommon.h"

#define SYMBOL_TE 1
#define SYMBOL_TX 2
#define SYMBOL_SY 3
#define SYMBOL_LS 4
#define SYMBOL_LC 5
#define SYMBOL_AC 6
#define SYMBOL_AP 7
#define SYMBOL_CS 8

class SymbolParameter
{
public:
	SymbolParameter(unsigned symbolType);
	virtual ~SymbolParameter();

protected:
	unsigned m_symbolType;
};