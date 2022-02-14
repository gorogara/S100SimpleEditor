#pragma once
#include <string>
class S100_WithParam
{
public:
	S100_WithParam();
	virtual ~S100_WithParam();

public:
	std::wstring name;
	std::wstring select;
	std::wstring value;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};

