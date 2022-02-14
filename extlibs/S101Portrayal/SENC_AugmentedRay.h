#pragma once

#include "SENC_Instruction.h"
#include "SENC_LineStyleBase.h"

class SENC_AugmentedRay :
	public SENC_Instruction
{
public:
	SENC_AugmentedRay();
	virtual ~SENC_AugmentedRay();

public:
	std::vector<SENC_LineStyleBase*> lineStyles; 
	int areaCRSType;
	ID2D1PathGeometry *pGeometry = nullptr;
	double direction;
	double length;

public:
	void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void DrawInstruction(ID2D1DCRenderTarget* rt, ID2D1Factory1* pDirect2dFactory, ID2D1SolidColorBrush* brush, std::vector<ID2D1StrokeStyle1*>* strokeGroup, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void ChangePallete(PortrayalCatalogue *pc);
};