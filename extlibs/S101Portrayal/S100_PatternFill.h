#pragma once
#include "S100_AreaFillBase.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class S100_PatternFill : public S100_AreaFillBase
{
public:
	S100_PatternFill();
	virtual ~S100_PatternFill();

public:
	std::wstring areaCRS;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};