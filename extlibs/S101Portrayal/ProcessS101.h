#pragma once
#include <string>

class S101Layer;
class PCOutputSchemaManager;

class ProcessS101
{
public:
	ProcessS101();
	virtual ~ProcessS101();

public:
	static int ProcessS101XSLT2XML(std::wstring xsltPath, std::wstring inXMLPath, std::wstring outXMLPath);
	static int ProcessS101_LUA(std::wstring luaRulePath, S101Layer* layer);

	static bool LUA_ParsingDrawingInstructions(std::string featureID, std::vector<std::string> elements, PCOutputSchemaManager* pcm);
	static std::wstring LUA_GetPriority(std::string lua_priority);
};