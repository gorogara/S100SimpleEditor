#pragma once
#include "S100_Instruction.h"
#include "S100_TextPoint.h"

class S100_AugmentedGeometry : public S100_Instruction
{
public:
	S100_AugmentedGeometry();
	virtual ~S100_AugmentedGeometry();

public:
	std::wstring crsType;
	S100_VectorPoint* vectorPoint;
	S100_TextPoint* textPoint; 

};

