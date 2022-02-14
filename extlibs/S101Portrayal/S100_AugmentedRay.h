#pragma once
#include "S100_AugmentedLineOrArea.h"
#include "S100_LineStyleReference.h"
#include "S100_CompositeLineStyle.h"
class S100_AugmentedRay :
	public S100_AugmentedLineOrArea
{
public:
	S100_AugmentedRay();
	virtual ~S100_AugmentedRay();

public:
	std::wstring direction;
	std::wstring length;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

