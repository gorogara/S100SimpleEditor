#pragma once
#include "stdafx.h"
#include "S100_RuleFile.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"

#include <unordered_map>

class S100_Rules
{
public:
	S100_Rules();
	virtual ~S100_Rules();

public:
	std::unordered_map<std::string, S100_RuleFile*> ruleFiles; 

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};