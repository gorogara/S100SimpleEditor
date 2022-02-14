#pragma once
#include "S100_Description.h"

class S100_AreaFillFile
{
public:
	S100_AreaFillFile();
	virtual ~S100_AreaFillFile();

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