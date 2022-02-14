#pragma once
#include "Result_DrawingInstruction.h"

#include <string>
#include <list>
class lua_session;
class S101Cell;
class FeatureCatalogue;
using namespace std; 
string unknown_attribute;

#ifdef KRS_LUA_SCRIPT_REFERENCE_DLL_EXPORTS
	#define KRS_LUA_SCRIPT_REFERENCE_API __declspec(dllexport)
#else
	#define KRS_LUA_SCRIPT_REFERENCE_API __declspec(dllimport)
#endif

namespace KRS_LUA_SCRIPT_REFERENCE
{ 
	KRS_LUA_SCRIPT_REFERENCE_API void InitPortrayal(/*const char* inputSchema, */const char* featureCatalog, const char* topLevelRule, S101Cell* cell, FeatureCatalogue* fc);
	KRS_LUA_SCRIPT_REFERENCE_API void PortrayalSetContextParameter(const char* parameterName, const char* parameterValue);
	KRS_LUA_SCRIPT_REFERENCE_API std::list<Result_DrawingInstruction>* GetResultDrawingInstructions();
	KRS_LUA_SCRIPT_REFERENCE_API void RemoveResultDrawingInstructions();
	KRS_LUA_SCRIPT_REFERENCE_API void SaveDrawingInstructions(std::string path);
}

class KRS_LUA_SCRIPT_REFERENCE_API S101LuaScriptingReference
{
public:
	S101LuaScriptingReference();
	virtual ~S101LuaScriptingReference();

public:
	lua_session *m_lua_session;
	S101Cell *m_s101_cell;
	FeatureCatalogue *m_s101_feature_catalogue;
};

