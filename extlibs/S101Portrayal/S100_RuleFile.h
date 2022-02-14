#pragma once
#include "stdafx.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"

#include <string>
class S100_RuleFile
{
public:
	S100_RuleFile();
	virtual ~S100_RuleFile();
	
public:
	std::string id = "";
	std::wstring fileName = L"";
	std::wstring fileType = L"";
	std::wstring fileFormat = L"";
	std::wstring ruleType = L"";

public:
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node& node);

	void SetID(std::string value);
	std::string GetID();

	void SetFileName(std::wstring value);
	std::wstring GetFileName();

	void SetFileType(std::wstring value);
	std::wstring GetFileType();

	void SetFileFormat(std::wstring value);
	std::wstring GetFileFormat();

	void SetRuleType(std::wstring value);
	std::wstring GetRuleType();

	bool IsTypeLevelTemplate();
	
	bool IsLua();
};

