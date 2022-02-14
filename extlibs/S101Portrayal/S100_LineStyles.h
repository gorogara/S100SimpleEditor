#pragma once
#include "stdafx.h"
#include "S100_LineStyleFile.h"

#include <unordered_map>

class S100_LineStyles
{
public:
	S100_LineStyles();
	virtual ~S100_LineStyles();

public:
	std::unordered_map<std::wstring, S100_LineStyleFile*> lineStyleFiles;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};