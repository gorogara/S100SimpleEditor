#pragma once  
#include "S100_Description.h"

#include <unordered_map>
#include <string>

class S100_Color;
class S100_Palette;

class S100_ColorProfile
{
public:
	S100_ColorProfile();
	virtual ~S100_ColorProfile();

public: 
	std::wstring id;
	S100_Description description;
	std::wstring fileName;
	std::wstring fileType;
	std::wstring fileFormat; 
	std::unordered_map<std::wstring, S100_Color*> colors;
	std::unordered_map<std::wstring, S100_Palette*> palettes;

public:
	bool ReadFile(std::wstring path); 
	void GetContents(pugi::xml_node node); 
	void GetContentsInfo(pugi::xml_node& node);

	D2D1_COLOR_F GetD2Color(std::wstring paletteName, std::wstring token);
	COLORREF GetRGBRef(std::wstring paletteName, std::wstring token);

	void Setid(std::wstring value);
	std::wstring Getid();

	void Setdescription(S100_Description value);
	S100_Description Getdescription();

	void SetfileName(std::wstring value);
	std::wstring GetfileName();

	void SetfileType(std::wstring value);
	std::wstring GetfileType();

	void SetfileFormat(std::wstring value);
	std::wstring GetfileFormat();

	void Setcolors(std::wstring key, S100_Color* value);
	std::unordered_map<std::wstring, S100_Color*> Getcolors(); 

	void Setpaletters(std::wstring key, S100_Palette* value);
	std::unordered_map<std::wstring, S100_Palette*> Getpalettes();
};