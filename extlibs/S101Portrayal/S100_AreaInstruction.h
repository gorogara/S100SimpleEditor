#pragma once
#include "S100_Instruction.h"
#include "S100_AreaFillBase.h"
class S100_AreaInstruction : public S100_Instruction
{
public:
	S100_AreaInstruction();
	virtual ~S100_AreaInstruction();

public:
	S100_AreaFillBase *areaFill;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

