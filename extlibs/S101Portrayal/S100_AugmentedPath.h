#pragma once
#include "S100_AugmentedLineOrArea.h"
#include "S100_Path.h"
class S100_AugmentedPath :
	public S100_AugmentedLineOrArea
{
public:
	S100_AugmentedPath();
	virtual ~S100_AugmentedPath();

public:
	S100_Path *path;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

