#pragma once

#include "SENC_Instruction.h"
#include "SENC_Attribute.h"

#include <list>
#include <vector>
class SENC_PointInstruction;
class SENC_LineInstruction;
class SENC_AreaInstruction;
class SENC_TextInstruction;
class SENC_CallTemplate;
class ENC_ConditionalSymbol;

class SENC_Template
{
public:
	SENC_Template();
	virtual ~SENC_Template();

public:
	std::list<SENC_Instruction*> instructions;
	std::vector<SENC_PointInstruction*> pointInstructions;
	std::vector<SENC_LineInstruction*> curveInstructions;
	std::vector<SENC_AreaInstruction*> surfaceInstructions;
	std::vector<SENC_TextInstruction*> textInstructions;
	SENC_CallTemplate* callTemplate;  
	int type;
	unsigned priority;

	std::wstring camelCase;
	std::vector<SENC_Attribute*> matchAttr;
};

