#pragma once

#include "S100_AreaFillBase.h"
#include "S100_Color.h"

class S100_ColorFill : public S100_AreaFillBase
{
public:
	S100_ColorFill();
	virtual ~S100_ColorFill();

public:
	S100_Color *color;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};