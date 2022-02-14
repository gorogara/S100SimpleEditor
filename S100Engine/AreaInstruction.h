#pragma once
#include "DrawingInstruction.h"


class AbstractAreaFill;
class AreaInstruction :
	public DrawingInstruction
{
public:
	AreaInstruction();
	virtual ~AreaInstruction();
public:
	AbstractAreaFill *pAbstractAreaFill; 
	CString colorName;
	FLOAT transparency;
	CString patternName;
};