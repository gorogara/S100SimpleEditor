#pragma once
#include <string>

class SENC_CIE
{
public:
	double x;
	double y;
	double L;
};

class SENC_SRGB
{
public:
	double red;
	double blue;
	double green;
};

class SENC_Item
{
public:
	SENC_Item();
	~SENC_Item();

	std::wstring token;
	SENC_CIE cie;
	SENC_SRGB rgb;
};
