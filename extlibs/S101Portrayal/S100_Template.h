#pragma once

#include "S100_Instruction.h"
#include "S100_DisplayList.h"
#include "S100_CallTemplate.h"

#include <vector>
class S100_Template
{
public:
	S100_Template();
	virtual ~S100_Template();

public:
	std::wstring match;
	std::wstring priority;
	std::vector<S100_Instruction*>instructions;
	S100_CallTemplate* calltemplete;
	S100_DisplayList *displayList;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};

