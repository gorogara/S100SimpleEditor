#pragma once
#include <vector>
#include "S100_WithParam.h"
class S100_CallTemplate
{
public:
	S100_CallTemplate();
	virtual ~S100_CallTemplate();

public:
	std::wstring name;
	std::vector<S100_WithParam*> params;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};