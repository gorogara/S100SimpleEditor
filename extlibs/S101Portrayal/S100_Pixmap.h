#pragma once

#include "S100_Color.h"
#include "S100_OverrideColor.h"

#include <string>
class S100_Pixmap
{
public:
	S100_Pixmap();
	virtual ~S100_Pixmap();

public: 
	std::wstring reference; 
	S100_Color overrideAll;
	S100_OverrideColor overrideColor;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNodeList);
	void GetContents(pugi::xml_node node);
};

