#pragma once

#include "..\\extlibs\pugixml\include\pugixml.hpp"
#include <string>
class S100_Dash
{
public:
	S100_Dash();
	virtual ~S100_Dash();

public:
	std::wstring start;
	std::wstring length;

public:
	void SetStart(std::wstring& value);
	std::wstring GetStart();
	
	void SetLength(std::wstring& value);
	std::wstring GetLength();

	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetFromStartLength(std::string& value);
};

