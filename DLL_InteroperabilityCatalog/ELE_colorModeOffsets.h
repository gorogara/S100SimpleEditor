#pragma once
#include "S100_IC_SaturationOffset.h"
#include <list>

class ELE_colorModeOffsets
{
public:
	ELE_colorModeOffsets();
	virtual ~ELE_colorModeOffsets();

	std::list<S100_IC_SaturationOffset> S100_IC_SaturationOffsets;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

