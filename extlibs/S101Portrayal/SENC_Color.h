#pragma once

#include <string>

class PortrayalCatalogue;

class SENC_Color
{
public:
	SENC_Color();
	~SENC_Color();

public:
	int RGBColor;
	std::wstring token;
	float transparency;

public:
	void SetRGBColor(int value);
	int GetRGBColor();

	void SetToken(std::wstring& value);
	std::wstring GetToken();

	void SetTransparency(int value);
	int GetTransparency();

	void ChangePallete(PortrayalCatalogue *pc);
};