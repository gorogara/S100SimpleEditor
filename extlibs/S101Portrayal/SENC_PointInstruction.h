#pragma once
#include "SENC_Instruction.h"
#include "SENC_Symbol.h"
class SENC_PointInstruction :
	public SENC_Instruction
{
public:
	SENC_PointInstruction();
	virtual ~SENC_PointInstruction();

public:
	SENC_Symbol *symbol;
	SENC_VectorPoint *vectorPoint;

public:
	void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void GetDrawPoints(Scaler *scaler, std::list<D2D1_POINT_2F> &points);
	void GetDrawPointsDynamic(Scaler *scaler, std::list<D2D1_POINT_2F> &points);
	static void WriteDebugMessage();
};


