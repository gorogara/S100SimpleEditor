#pragma once
#include <string>
class S100_Include
{
public:
	S100_Include();
	virtual ~S100_Include();

public:
	std::wstring href;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};

