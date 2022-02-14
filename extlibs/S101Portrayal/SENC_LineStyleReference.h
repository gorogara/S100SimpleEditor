#pragma once

#include "SENC_LineStyleBase.h"
#include "string"

#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

class S100_LineStyleReference;
class SENC_LineStyleReference : public SENC_LineStyleBase
{
public:
	SENC_LineStyleReference();
	~SENC_LineStyleReference();

public:
	std::wstring reference;

public:
	void GetStyleFromS100(S100_LineStyleReference* lineStyle, S100_SVG_D2D1_DLL::SVGManager *svgMgr);

	void SetReference(std::wstring& value);
	std::wstring GetReference();
};