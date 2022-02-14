#pragma once

#include "..\\extlibs\\pugixml\\include\pugixml.hpp"

#include <list>

class S100_Instruction;

class S100_DisplayList
{
public:
	S100_DisplayList();
	virtual ~S100_DisplayList();
public:
	std::list<S100_Instruction*> displayInstructions;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
	void RemoveInstructions();
};