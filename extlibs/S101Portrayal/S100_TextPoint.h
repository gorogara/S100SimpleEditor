#pragma once

#include "S100_Element.h"
#include "S100_AreaPlacement.h"
#include "S100_VectorPoint.h"

#include <vector>
class S100_TextPoint
{
public:
	S100_TextPoint();
	virtual ~S100_TextPoint();

public:
	std::wstring horizontalAlignment;
	std::wstring verticalAlignment;

	std::vector<S100_Element*> elements;
	S100_VectorPoint *offset;
	std::wstring rotation;
	S100_AreaPlacement *areaPlacement;


public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};