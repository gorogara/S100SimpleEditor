#pragma once

#include "S100_CIE.h"
#include "S100_SRGB.h"

#include <unordered_map>
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"
class S100_Item
{
public:
	S100_Item();
	virtual ~S100_Item();

public:
	std::wstring token;
	S100_CIE scie;
	S100_SRGB srgb;

public:
	void GetContents(pugi::xml_node Node);
};