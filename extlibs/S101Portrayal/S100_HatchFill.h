#pragma once
#include "S100_PatternFill.h"
#include "S100_Hatch.h"

#include <list>
class S100_HatchFill :
	public S100_PatternFill
{
public:
	S100_HatchFill();
	virtual ~S100_HatchFill();

public:
	std::list<S100_Hatch*> hatches;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNodeList);
	void GetContents(pugi::xml_node node);
};

