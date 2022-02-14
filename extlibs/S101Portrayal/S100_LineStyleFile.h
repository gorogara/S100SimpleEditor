#pragma once
#include "stdafx.h"
#include "S100_Description.h"

#include <string>
class S100_LineStyleFile
{
public:
	S100_LineStyleFile();
	virtual ~S100_LineStyleFile();

public: 
	std::wstring id;


	S100_Description description;
	std::wstring fileName;
	std::wstring fileType;
	std::wstring fileFormat;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

