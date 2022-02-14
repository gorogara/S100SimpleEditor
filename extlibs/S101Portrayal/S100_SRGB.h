#pragma once
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"
class S100_SRGB
{
public:
	S100_SRGB();
	virtual ~S100_SRGB();
	
public:
	int red = 0;
	int green = 0;
	int blue = 0;

public:
	void GetContents(pugi::xml_node Node);
};