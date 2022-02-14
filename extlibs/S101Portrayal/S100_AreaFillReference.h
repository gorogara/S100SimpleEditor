#pragma once
#include "S100_AreaFillBase.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class S100_AreaFillReference : public S100_AreaFillBase
{
public:
	S100_AreaFillReference();
	virtual ~S100_AreaFillReference();

public:
	std::wstring reference;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

