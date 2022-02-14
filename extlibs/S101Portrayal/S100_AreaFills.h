#pragma once
#include "stdafx.h"
#include "S100_AreaFillFile.h"

#include <unordered_map>
#include <string>
class S100_AreaFills 
{
public:
	S100_AreaFills();
	virtual ~S100_AreaFills();

public:
	std::unordered_map<std::wstring, S100_AreaFillFile*> areaFillFiles;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

