#pragma once
#include "S100_Instruction.h"
#include "S100_Symbol.h"
#include "S100_AugmentedPoint.h"
class S100_PointInstruction : public S100_Instruction
{
public:
	S100_PointInstruction();
	virtual ~S100_PointInstruction();

public:
	S100_Symbol *symbol;
	S100_VectorPoint *vectorPoint;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};