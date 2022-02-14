#pragma once
#include "S100_Rotation.h"
#include "S100_AreaPlacement.h"
#include "S100_LinePlacement.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"

class S100_Symbol
{
public:
	S100_Symbol();
	virtual ~S100_Symbol();

public:
	std::wstring reference;
	S100_Rotation *rotation;
	std::wstring rotationCRS;
	std::wstring scaleFactor;

	S100_AreaPlacement *areaPlacement;
	S100_LinePlacement *linePlacement;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};