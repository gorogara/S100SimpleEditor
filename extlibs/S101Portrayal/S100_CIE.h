#pragma once
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"
class S100_CIE
{
public:
	S100_CIE();
	virtual ~S100_CIE();

public:
	float x = 0.0f;
	float y = 0.0f;;
	float L = 0.0f;;

public:
	void GetContents(pugi::xml_node Node);
};