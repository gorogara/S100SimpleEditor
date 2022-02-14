#pragma once

#include "SENC_Instruction.h"
#include "SENC_AreaFillBase.h"

class SENC_AreaInstruction : public SENC_Instruction
{
public: 
	SENC_AreaInstruction();
	virtual ~SENC_AreaInstruction();

public: 
	SENC_AreaFillBase *areaFill = nullptr;

public: 
	void SetAreaFill(SENC_AreaFillBase* value);
	SENC_AreaFillBase* GetAreaFill();

	void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void DrawInstruction(ID2D1DCRenderTarget* rt, ID2D1Factory1* pDirect2dFactory, ID2D1SolidColorBrush* brush, std::vector<ID2D1StrokeStyle1*>* strokeGroup, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void DrawInstruction(CDCRenderTarget* pRenderTarget, Scaler *scaler);
	void DrawInstruction(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory *pDXFactory, Scaler *scaler);
	void DrawInstructionDirectX(ID2D1DCRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pDirect2dSolidColorBrushScaler, Scaler* scaler);
	void ChangePallete(PortrayalCatalogue *pc);
};

