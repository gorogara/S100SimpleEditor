#pragma once
#include "SENC_Rotation.h"

#include "..\\S100_SVG_D2D1_DLL\\SVG.h" 
class SENC_LineSymbol
{
public:
	SENC_LineSymbol();
	~SENC_LineSymbol();

public:
	double position;

	std::wstring reference;
	SENC_Rotation rotation;
	double scaleFactor;
	int crsType;
	
	S100_SVG_D2D1_DLL::SVG* pSvg;
};

