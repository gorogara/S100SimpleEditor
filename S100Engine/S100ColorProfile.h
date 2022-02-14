#pragma once

#include <vector>
#include "Palette.h"
#include "Colors.h"  
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

using namespace std;


class S100ColorProfile
{
public:
	S100ColorProfile();
	virtual~S100ColorProfile();

public:
	vector<Palette> palette;
	libS100Engine::Colors colors;

public:
	bool Open(char* filePath);
	bool OpenByPugi(char* filePath);
	D2D1_COLOR_F GetColor(std::wstring _paletteName, std::wstring _token);

private: 
	void extractionColors(pugi::xml_node node); 
	void extractionPalette(pugi::xml_node node); 
	vector<CString> Split(CString _data, char parsingChar); 
	vector<CString> SplitBySpace(CString _data, int _space); 
	int Conert16to10(char* ch); 
	char* ConvertCstringToChar(CString inCstring); 
	CString ConvertCharToCString(char* inChar); 
	wstring ConvertCtoWS(char* c); 
	char* ConvertWCtoC(wchar_t* str);
};