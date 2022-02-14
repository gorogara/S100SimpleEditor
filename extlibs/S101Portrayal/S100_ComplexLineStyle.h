#pragma once
#include <string>
class S100_ComplexLineStyle
{
public:
	S100_ComplexLineStyle();
	virtual ~S100_ComplexLineStyle();

public:
	std::wstring symbolReference;
	std::wstring scaleFactor;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};