#pragma once
#include "SENC_Instruction.h"
class SENC_NullInstruction :
	public SENC_Instruction
{
public:
	SENC_NullInstruction();
	virtual ~SENC_NullInstruction();

public:
	void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
};