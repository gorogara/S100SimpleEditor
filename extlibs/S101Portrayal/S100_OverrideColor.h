#pragma once

#include "S100_Color.h"

class S100_OverrideColor
{
public:
	S100_OverrideColor();
	virtual ~S100_OverrideColor();

public: 
	S100_Color overrideColor;
	S100_Color color;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNodeList);
	void GetContents(pugi::xml_node node);
};