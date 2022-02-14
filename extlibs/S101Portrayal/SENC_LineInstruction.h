#pragma once
#include "SENC_Instruction.h"
#include "SENC_LineStyleBase.h"
#include <vector>
class SCurveWithParentOrient;
class SENC_LineInstruction : public SENC_Instruction
{
public:
	SENC_LineInstruction();
	virtual ~SENC_LineInstruction();

private:
	bool suppression = false;

public:
	std::vector<SENC_LineStyleBase*> lineStyles; 
	std::list<SCurveWithParentOrient> m_listCurveLink;

public:
	void SetSuppression(bool value);
	bool GetSuppression();

	void DrawInstruction(HDC &hDC, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void DrawInstruction(ID2D1DCRenderTarget* rt, ID2D1Factory1* pDirect2dFactory, ID2D1SolidColorBrush* brush, std::vector<ID2D1StrokeStyle1*>* strokeGroup, Scaler *scaler, PortrayalCatalogue* pc = nullptr);
	void DrawInstruction(CDCRenderTarget* pRenderTarget, Scaler *scaler);
	void ChangePallete(PortrayalCatalogue *pc);
	
	static void WriteDebugMessage();
};