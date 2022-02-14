#pragma once
#include "SENC_LineStyleBase.h"
#include "SENC_Symbol.h"
#include "SENC_Dash.h"
#include "SENC_LineSymbol.h"
#include "S100_LineStyle.h"

#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#include <list>

class PortrayalCatalogue;
class SENC_LineStyle : public SENC_LineStyleBase
{
public:
	SENC_LineStyle();
	virtual ~SENC_LineStyle();
	
public:
	double intervalLength = 0;	
	double pen_width = 0;
	double pen_transparency = 0;

	std::list<SENC_Dash*> dashes;
	std::list<SENC_LineSymbol*> symbols;

	int capStyle = 0;
	int joinStyle = 0;
	float offset = 0;
	int pen_color = 0;
	std::wstring colorToken = L"";
	std::wstring lineStyleName = L"";

public:
	void SetPenColor(int value);
	int GetPenColor();

	void SetPenColorToken(std::wstring& value);
	std::wstring GetPenColorToken();

	void GetStyleFromS100(S100_LineStyle* lineStyle, PortrayalCatalogue *pc);
	
	void ChangePallete(PortrayalCatalogue *pc);

	void SetLineStyleName(std::wstring& value);
	std::wstring GetLineStyleName();
};