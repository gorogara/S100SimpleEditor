#pragma once

#include "S100_Item.h"

#include <unordered_map>
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"
class S100_Palette
{
public:
	S100_Palette();
	virtual ~S100_Palette();

public:
	std::wstring name;
	std::wstring css;
	std::unordered_map<std::wstring, S100_Item*> items;

public:
	void GetContents(pugi::xml_node Node);
};